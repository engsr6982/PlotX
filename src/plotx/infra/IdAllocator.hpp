#pragma once
#include "plotx/Global.hpp"
#include <atomic>
#include <cstdint>


namespace plotx {


class IdAllocator {
    std::atomic<uint32_t> next_{0};

public:
    explicit IdAllocator() = default;
    PXAPI explicit IdAllocator(uint32_t start);

    PXAPI uint32_t next();

    PXAPI void reset(uint32_t start);
};


} // namespace plotx