#include "PlotHandle.hpp"
#include "mc/platform/UUID.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "plotx/data/StorageStructure.hpp"
#include "plotx/infra/DirtyCounter.hpp"
#include "plotx/infra/Reflection.hpp"
#include "plotx/math/PlotCoord.hpp"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>


namespace plotx {


PlotHandle::PlotHandle() = default;
PlotHandle::PlotHandle(PlotRecord record)
: record_(std::move(record)),
  coord_(record_.position_.x, record_.position_.z) {
    if (!record_.comments_.empty()) {
        // 初始化评论ID分配器
        uint32_t max = 0;
        for (auto const& comment : record_.comments_) {
            if (comment.id_ > max) {
                max = comment.id_;
            }
        }
        commentId_.reset(++max);
    }

    // 合并后的地皮，加载实际大小
    if (record_.isMerged_) {
        coord_.min.x = record_.multiPlot_.currentAABB_.min.x;
        coord_.min.z = record_.multiPlot_.currentAABB_.min.z;
        coord_.max.x = record_.multiPlot_.currentAABB_.max.x;
        coord_.max.z = record_.multiPlot_.currentAABB_.max.z;
    }
}

PlotHandle::~PlotHandle() = default;

DirtyCounter& PlotHandle::getDirtyCounter() { return dirty_; }

DirtyCounter const& PlotHandle::getDirtyCounter() const { return dirty_; }

PlotCoord const& PlotHandle::getCoord() const { return coord_; }

mce::UUID const& PlotHandle::getOwner() const {
    if (owner_.has_value()) {
        return *owner_;
    }
    owner_ = mce::UUID::fromString(record_.owner_);
    return *owner_;
}

void PlotHandle::setOwner(mce::UUID const& owner) {
    owner_         = owner; // cache the value
    record_.owner_ = owner.asString();
    dirty_.inc();
}

std::string const& PlotHandle::getName() const { return record_.name_; }

void PlotHandle::setName(std::string const& name) {
    record_.name_ = name;
    dirty_.inc();
}

bool PlotHandle::isSale() const { return record_.isSale_; }

void PlotHandle::setSale(bool sale) {
    record_.isSale_ = sale;
    dirty_.inc();
}

int PlotHandle::getPrice() const { return record_.price_; }

void PlotHandle::setPrice(int price) {
    record_.price_ = price;
    dirty_.inc();
}

bool PlotHandle::isMember(mce::UUID const& member) const {
    return std::find(record_.members_.begin(), record_.members_.end(), member.asString()) != record_.members_.end();
}

std::vector<std::string> const& PlotHandle::getMembers() const { return record_.members_; }

void PlotHandle::addMember(mce::UUID const& member) {
    if (isMember(member)) {
        return;
    }
    record_.members_.push_back(member.asString());
    dirty_.inc();
}

void PlotHandle::removeMember(mce::UUID const& member) {
    auto it = std::find(record_.members_.begin(), record_.members_.end(), member.asString());
    if (it == record_.members_.end()) {
        return;
    }
    record_.members_.erase(it);
    dirty_.inc();
}

std::vector<CommentRecord> const& PlotHandle::getComments() const { return record_.comments_; }

std::vector<CommentRecord> PlotHandle::getComments(mce::UUID const& author) const {
    auto str = author.asString();

    std::vector<CommentRecord> result;
    std::copy_if(record_.comments_.begin(), record_.comments_.end(), std::back_inserter(result), [&str](auto const& c) {
        return c.author_ == str;
    });
    return result;
}

std::optional<CommentRecord> PlotHandle::getComment(CommentID id) const {
    auto it =
        std::find_if(record_.comments_.begin(), record_.comments_.end(), [&id](auto const& c) { return c.id_ == id; });
    if (it == record_.comments_.end()) {
        return std::nullopt;
    }
    return *it;
}

CommentID PlotHandle::addComment(mce::UUID const& author, std::string const& content) {
    auto id = commentId_.next();
    record_.comments_.emplace_back(
        id,
        author.asString(),
        content,
        "time" // TODO: get current time
    );
    dirty_.inc();
    return id;
}

void PlotHandle::removeComment(CommentID id) {
    auto it =
        std::find_if(record_.comments_.begin(), record_.comments_.end(), [&id](auto const& c) { return c.id_ == id; });
    if (it == record_.comments_.end()) {
        return;
    }
    record_.comments_.erase(it);
    dirty_.inc();
}

bool PlotHandle::isMergedMultiPlot() const { return record_.isMerged_; }


// helper
nlohmann::json PlotHandle::dump() const { return reflection::struct2json(record_); }

std::shared_ptr<PlotHandle> PlotHandle::load(nlohmann::json& json) {
    auto record = PlotRecord{};
    reflection::json2structVersionPatch(json, record);
    return PlotHandle::make(std::move(record));
}

} // namespace plotx