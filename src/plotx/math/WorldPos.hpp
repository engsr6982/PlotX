#pragma once
#include "plotx/Global.hpp"
#include "plotx/infra/Concepts.hpp"
#include <string>


namespace plotx {


class WorldPos {
public:
    int x{}, y{}, z{};

    PXNDAPI std::string toString() const;

    template <HasXYZ_v T>
    T as() const {
        return T{x, y, z};
    }

    template <HasXYZ_v T>
    explicit operator T() const {
        return as<T>();
    }

    template <HasXYZ_v T>
    static WorldPos from(T const& t) {
        return WorldPos{t.x, t.y, t.z};
    }
};

STATIC_ASSERT_AGGREGATE(WorldPos);


} // namespace plotx