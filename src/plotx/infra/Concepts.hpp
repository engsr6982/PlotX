#pragma once
#include <concepts>


namespace plotx {


template <typename T>
concept HasXYZBase_v = requires(T const& t) {
    { t.x } -> std::convertible_to<int>;
    { t.y } -> std::convertible_to<int>;
    { t.z } -> std::convertible_to<int>;
};

template <typename T>
concept HasXYZStyle_v = requires(T const& t) {
    { t.x_ } -> std::convertible_to<int>;
    { t.y_ } -> std::convertible_to<int>;
    { t.z_ } -> std::convertible_to<int>;
};

template <typename T>
concept HasXYZ_v = HasXYZBase_v<T> || HasXYZStyle_v<T>;


} // namespace plotx