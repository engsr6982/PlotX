#pragma once
#include "ll/api/reflection/Deserialization.h"
#include "ll/api/reflection/Serialization.h"
#include "nlohmann/json_fwd.hpp"
#include <type_traits>


namespace plotx::reflection {


template <typename T, typename J = nlohmann::ordered_json>
    requires std::is_aggregate_v<T>
[[nodiscard]] inline J struct2json(T const& t) {
    return ll::reflection::serialize<J>(t);
}

template <typename T, typename J = nlohmann::ordered_json>
    requires std::is_aggregate_v<T>
inline void json2struct(T& t, J const& j) {
    ll::reflection::deserialize(t, j).value();
}

template <typename T, typename J = nlohmann::ordered_json>
    requires std::is_aggregate_v<T>
inline void json2structDiffPatch(T& t, J const& j) {
    auto diff = struct2json(t);
    diff.merge_patch(j);
    json2struct(t, j);
}

template <class T>
concept HasVersion_v =
    ll::reflection::Reflectable<T> && std::integral<std::remove_cvref_t<decltype((std::declval<T>().version))>>;

template <HasVersion_v T, class J = nlohmann::ordered_json>
inline bool _merge_patch(T& obj, J& data) {
    data.erase("version");
    auto patch = ll::reflection::serialize<J>(obj);
    patch.value().merge_patch(data);
    data = *std::move(patch);
    return true;
}

template <HasVersion_v T, class J = nlohmann::ordered_json, class F = bool(T&, J&)>
inline void json2structVersionPatch(J& json, T& obj, F&& fixer = _merge_patch<T, J>) {
    bool noNeedMerge = true;
    if (!json.contains("version") || (int64)(json["version"]) != obj.version) {
        noNeedMerge = false;
    }
    if (noNeedMerge || std::invoke(std::forward<F>(fixer), obj, json)) {
        ll::reflection::deserialize(obj, json).value();
    }
}


} // namespace plotx::reflection