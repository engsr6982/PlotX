#pragma once
#include "plotx/Global.hpp"
#include <cstdint>
#include <string>
#include <vector>


namespace plotx {


using CommentID = uint32_t;
struct CommentRecord {
    CommentID   id_{};      // 评论id
    std::string author_{};  // 评论者
    std::string content_{}; // 评论内容
    std::string time_{};    // 评论时间
};

struct Vec2Record {
    int x{}, z{};
};

struct AABBRecord {
    Vec2Record min, max;
};

struct RoadRecord {
    Vec2Record position_{};     // 道路坐标
    bool       isTransverse_{}; // 道路方向(true: 横, false: 纵)
};

struct MultiPlotRecord {
    int                     counter_{};      // 合并计数器
    AABBRecord              currentAABB_{};  // 当前合并的地皮范围
    std::vector<Vec2Record> mergedPlots_{};  // 合并的地皮
    std::vector<Vec2Record> includeCross_{}; // 包含的十字路口
    std::vector<RoadRecord> includeRoads_{}; // 包含的道路
};

constexpr int PlotRecordVersion = 20;
struct PlotRecord {
    int                        version{PlotRecordVersion};
    Vec2Record                 position_{};  // 地皮坐标
    std::string                owner_{};     // 地皮主人
    std::string                name_{};      // 地皮名称
    bool                       isSale_{};    // 是否正在出售
    int                        price_{};     // 出售价格
    std::vector<std::string>   members_{};   // 地皮成员
    std::vector<CommentRecord> comments_{};  // 评论
    bool                       isMerged_{};  // 是否是合并的地皮
    MultiPlotRecord            multiPlot_{}; // 合并的地皮信息
};

STATIC_ASSERT_AGGREGATE(CommentRecord);
STATIC_ASSERT_AGGREGATE(Vec2Record);
STATIC_ASSERT_AGGREGATE(AABBRecord);
STATIC_ASSERT_AGGREGATE(RoadRecord);
STATIC_ASSERT_AGGREGATE(MultiPlotRecord);
STATIC_ASSERT_AGGREGATE(PlotRecord);


} // namespace plotx