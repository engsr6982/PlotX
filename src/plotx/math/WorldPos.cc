#include "WorldPos.hpp"
#include "fmt/format.h"

namespace plotx {


WorldPos::WorldPos(int x, int y, int z) : x(x), y(y), z(z) {}

std::string WorldPos::toString() const { return fmt::format("WorldPos({}, {}, {})", x, y, z); }


} // namespace plotx