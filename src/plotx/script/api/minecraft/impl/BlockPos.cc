#include "mc/world/level/BlockPos.h"
#include "plotx/script/api/Helper.hpp"
#include "plotx/script/api/minecraft/defs.hpp"
#include "qjspp/Binding.hpp"


namespace plotx::script::api::inline minecraft {


extern qjspp::ClassDefine const BlockPosDef_ = qjspp::defineClass<BlockPos>("BlockPos")
                                                   .constructor<int, int, int>()
                                                   .instanceProperty("x", &BlockPos::x)
                                                   .instanceProperty("y", &BlockPos::y)
                                                   .instanceProperty("z", &BlockPos::z)
                                                   .build();


}
