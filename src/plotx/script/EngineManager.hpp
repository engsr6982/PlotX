#pragma once
#include "plotx/Global.hpp"
#include "plotx/infra/IdAllocator.hpp"
#include "qjspp/JsEngine.hpp"
#include <cstdint>
#include <unordered_map>

namespace plotx::script {


using EngineID = uint32_t;
class EngineManager {
    IdAllocator                                    engineIDAlloc_;
    std::unordered_map<EngineID, qjspp::JsEngine*> engines_;

public:
    PLOTX_DISALLOW_COPY_AND_MOVE(EngineManager);

    explicit EngineManager();
    ~EngineManager();
};


} // namespace plotx::script