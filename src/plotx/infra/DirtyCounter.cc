#include "plotx/infra/DirtyCounter.hpp"

namespace plotx {


DirtyCounter::DirtyCounter() : counter_(0) {}

void DirtyCounter::inc() { counter_.fetch_add(1, std::memory_order_relaxed); }

void DirtyCounter::dec() { counter_.fetch_sub(1, std::memory_order_relaxed); }

void DirtyCounter::reset() { counter_.store(0); }

bool DirtyCounter::isDirty() const { return counter_ != 0; }

uint64_t DirtyCounter::get() const { return counter_; }


} // namespace plotx