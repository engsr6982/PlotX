#include "IdAllocator.hpp"


namespace plotx {


IdAllocator::IdAllocator(uint32_t start) : next_(start) {}

uint32_t IdAllocator::next() { return next_++; }

void IdAllocator::reset(uint32_t start) { next_ = start; }

} // namespace plotx