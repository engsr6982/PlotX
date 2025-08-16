#include "PlotGenerator.hpp"
#include "Helper.hpp"
#include "mc/world/level/BlockPos.h"
#include "mc/world/level/Level.h"
#include "mc/world/level/block/BlockVolume.h"
#include "mc/world/level/block/registry/BlockTypeRegistry.h"
#include "mc/world/level/chunk/ChunkState.h"
#include "mc/world/level/chunk/LevelChunk.h"
#include "mc/world/level/levelgen/WorldGenerator.h"
#include "mc/world/level/levelgen/v1/ChunkLocalNoiseCache.h"
#include "plotx/infra/Config.hpp"
#include <cstdlib>
#include <mc/world/level/biome/registry/BiomeRegistry.h>
#include <mc/world/level/block/VanillaBlockTypeIds.h>
#include <mc/world/level/dimension/Dimension.h>


#include "minecraft/FixedBiomeSource.h"

namespace plotx::generator {


PlotGenerator::ThreadData::ThreadData(PlotGenerator& generator) : buffer_() {
    buffer_.fill(generator.airBlock_);

    fillLayer(buffer_, generator.bedrockBlock_, 0);
    fillRange(buffer_, generator.fillBlock_, 1, generator.generatorHeight_);
    fillLayer(buffer_, generator.surfaceBlock_, generator.generatorHeight_);

    volume_                 = generator.mPrototype;
    volume_.mHeight         = WorldTotalHeight;
    volume_.mBlocks->mBegin = &*buffer_.begin();
    volume_.mBlocks->mEnd   = &*buffer_.end();
}

PlotGenerator::PlotGenerator(Dimension& dimension, uint seed, Json::Value const& options)
: FlatWorldGenerator(dimension, seed, options) {
    auto const& cfg = gConfig_.generator;
    if (cfg.generatorHeight < WorldMinHeight || cfg.generatorHeight > WorldMaxHeight) {
        throw std::runtime_error(
            "generatorHeight must be between " + std::to_string(WorldMinHeight) + " and "
            + std::to_string(WorldMaxHeight)
        );
    }

    mBiome = mLevel->getBiomeRegistry().lookupByName(cfg.biome);
    if (!mBiome) {
        throw std::runtime_error("Unknown biome: " + cfg.biome);
    }
    mBiomeSource = std::make_unique<FixedBiomeSource>(*mBiome);

    airBlock_     = &BlockTypeRegistry::getDefaultBlockState("minecraft:air");
    bedrockBlock_ = &BlockTypeRegistry::getDefaultBlockState(VanillaBlockTypeIds::Bedrock());
    surfaceBlock_ = &BlockTypeRegistry::getDefaultBlockState(cfg.surfaceBlock.c_str());
    fillBlock_    = &BlockTypeRegistry::getDefaultBlockState(cfg.fillBlock.c_str());
    borderBlock_  = &BlockTypeRegistry::getDefaultBlockState(cfg.borderBlock.c_str());
    roadBlock_    = &BlockTypeRegistry::getDefaultBlockState(cfg.roadBlock.c_str());

    if (!airBlock_ || !bedrockBlock_ || !surfaceBlock_ || !fillBlock_ || !borderBlock_ || !roadBlock_) {
        throw std::runtime_error("Failed to get block, world generator failed to initialize");
    }

    // 由于总高为 384(-64 ~ 320), 所以 config 的 generatorHeight 需要 offset 64
    (*const_cast<int*>(&generatorHeight_)) = cfg.generatorHeight + std::abs(WorldMinHeight);
    (*const_cast<int*>(&borderHeight_))    = generatorHeight_ + 1;
    if (borderHeight_ > WorldMaxHeight) {
        throw std::runtime_error("borderHeight must be less than or equal to " + std::to_string(WorldMaxHeight));
    }
}


[[nodiscard]] inline int positiveMod(int value, int modulus) {
    int result = value % modulus;
    if (result < 0) {
        result += modulus;
    }
    return result;
}

void PlotGenerator::loadChunk(LevelChunk& lc, bool /* forceImmediateReplacementDataLoad */) {
    static thread_local std::unique_ptr<ThreadData> data(new ThreadData(*this));

    // 重置上个区块的更改
    fillLayer(data->buffer_, surfaceBlock_, generatorHeight_); // 重置生成层
    fillLayer(data->buffer_, airBlock_, borderHeight_);        // 重置边框层

    auto const& config   = gConfig_.generator;
    auto const& chunkPos = lc.mPosition.get();

    // 计算当前区块的全局坐标
    int startX = chunkPos.x * 16;
    int startZ = chunkPos.z * 16;

    // 遍历区块内的每个方块位置
    for (int x = 0; x < 16; x++) {
        for (int z = 0; z < 16; z++) {
            // 计算全局坐标
            int globalX = startX + x;
            int globalZ = startZ + z;

            // 计算在地盘网格中的位置
            int gridX = positiveMod(globalX, config.plotWidth + config.roadWidth); // 地皮 + 道路宽度
            int gridZ = positiveMod(globalZ, config.plotWidth + config.roadWidth);

            // 判断是否为道路或边框
            if (gridX >= config.plotWidth || gridZ >= config.plotWidth) {
                // 道路
                updateBuffer(data->buffer_, getIndex(x, generatorHeight_, z), roadBlock_);

            } else if (gridX == 0 || gridZ == 0 || gridX == config.plotWidth - 1 || gridZ == config.plotWidth - 1) {
                // 边框 北和西（靠近0,0,0）         南和东（地皮对角）
                updateBuffer(data->buffer_, getIndex(x, borderHeight_, z), borderBlock_);
            }
        }
    }

    lc.setBlockVolume(data->volume_, 0);
    mBiomeSource->fillBiomes(lc, ChunkLocalNoiseCache{});
    lc.recomputeHeightMap(false);
    lc.setSaved();

    auto ing = ChunkState::Generating;
    lc.mLoadState->compare_exchange_strong(ing, ChunkState::Generated);
}


} // namespace plotx::generator