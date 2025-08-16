#include "WorldPos.hpp"
#include "fmt/format.h"

namespace plotx {


std::string WorldPos::toString() const { return fmt::format("WorldPos({}, {}, {})", x, y, z); }


} // namespace plotx