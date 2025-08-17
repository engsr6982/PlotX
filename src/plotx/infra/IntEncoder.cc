#include "IntEncoder.hpp"
#include <cstdlib>
#include <utility>

namespace plotx {


EncodedID IntEncoder::encode(int32_t x, int32_t z) {
    auto ux = static_cast<uint64_t>(std::abs(x));
    auto uz = static_cast<uint64_t>(std::abs(z));

    uint64_t signBits = 0;
    if (x >= 0) signBits |= (1ULL << 63);
    if (z >= 0) signBits |= (1ULL << 62);
    return signBits | (ux << 31) | (uz & 0x7FFFFFFF);
    // Memory layout:
    // [signBits][x][z] (signBits: 2 bits, x: 31 bits, z: 31 bits)
}

std::pair<int32_t, int32_t> IntEncoder::decode(EncodedID id) {
    bool xPositive = (id & (1ULL << 63)) != 0;
    bool zPositive = (id & (1ULL << 62)) != 0;

    int x = static_cast<int>((id >> 31) & 0x7FFFFFFF);
    int z = static_cast<int>(id & 0x7FFFFFFF);
    if (!xPositive) x = -x;
    if (!zPositive) z = -z;
    return {x, z};
}

EncodedID IntEncoder::encodeWithFlags(int32_t x, int32_t z, bool flag1, bool flag2) {
    uint64_t ux = static_cast<uint64_t>(std::abs(x)) & 0x3FFFFFFF; // 30-bit
    uint64_t uz = static_cast<uint64_t>(std::abs(z)) & 0x3FFFFFFF; // 30-bit

    uint64_t flags = (flag1 ? 1ULL : 0ULL) << 60 | (flag2 ? 1ULL : 0ULL) << 61;

    uint64_t signBits = 0;
    if (x >= 0) signBits |= (1ULL << 63);
    if (z >= 0) signBits |= (1ULL << 62);
    return signBits | flags | (ux << 30) | uz;
    // Memory layout:
    // [signBits][flags][x][z] (signBits: 2 bits, flags: 2 bits, x: 30 bits, z: 30 bits)
}

IntEncoder::DecodeResult IntEncoder::decodeWithFlags(EncodedID id) {
    bool xPositive = (id & (1ULL << 63)) != 0;
    bool zPositive = (id & (1ULL << 62)) != 0;

    bool flag1 = (id >> 60) & 1;
    bool flag2 = (id >> 61) & 1;

    int32_t x = static_cast<int32_t>((id >> 30) & 0x3FFFFFFF);
    int32_t z = static_cast<int32_t>(id & 0x3FFFFFFF);

    if (!xPositive) x = -x;
    if (!zPositive) z = -z;

    return {x, z, flag1, flag2};
}


} // namespace plotx