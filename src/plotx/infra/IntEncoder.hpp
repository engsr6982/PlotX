#pragma once
#include <cstdint>
#include <utility>

namespace plotx {


using EncodedID = uint64_t;
struct IntEncoder {
    IntEncoder() = delete;

    /**
     * @note 有效数据位为 62 位 (x: 31, z: 31)
     */
    static EncodedID encode(int32_t x, int32_t z);

    static std::pair<int32_t, int32_t> decode(EncodedID id);

    /**
     * @note 有效数据位为 60 位 (x: 30, z: 30, flag1: 1, flag2: 1)
     */
    static EncodedID encodeWithFlags(int32_t x, int32_t z, bool flag1 = false, bool flag2 = false);

    struct DecodeResult {
        int32_t x;
        int32_t z;
        bool    flag1;
        bool    flag2;
    };
    static DecodeResult decodeWithFlags(EncodedID id);
};


} // namespace plotx