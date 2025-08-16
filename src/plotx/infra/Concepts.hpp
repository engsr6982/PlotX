#pragma once
#include <concepts>


namespace plotx {


template <typename T>
concept HasXYZ_v = requires(T const& t) {
    { t.x } -> std::convertible_to<int>;
    { t.y } -> std::convertible_to<int>;
    { t.z } -> std::convertible_to<int>;
};

template <typename T>
concept HasXZ_v = requires(T const& t) {
    { t.x } -> std::convertible_to<int>;
    { t.z } -> std::convertible_to<int>;
};


} // namespace plotx