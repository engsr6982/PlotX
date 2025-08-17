#pragma once
#include "plotx/Global.hpp"
#include "plotx/infra/Concepts.hpp"
#include <string>


namespace plotx {


class WorldPos {
public:
    int x{}, y{}, z{};

    WorldPos() = default;
    PXAPI explicit WorldPos(int x, int y, int z);

    template <HasXYZ_v T>
    explicit WorldPos(T const& t) : WorldPos{t.x, t.y, t.z} {}

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
    bool operator==(T const& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};


} // namespace plotx