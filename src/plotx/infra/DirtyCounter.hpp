#pragma once
#include <atomic>
#include <cstdint>


namespace plotx {


/**
 * @brief 脏数据计数
 */
class DirtyCounter {
    std::atomic<uint64_t> counter_;

public:
    DirtyCounter();

    void inc(); // 增加

    void dec(); // 减少

    void reset(); // 重置

    bool isDirty() const; // 是否为脏数据

    uint64_t get() const; // 获取当前值
};


} // namespace plotx