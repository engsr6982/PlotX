#pragma once
#include <type_traits>

#ifdef PLOTX_EXPORT
#define PXAPI __declspec(dllexport)
#else
#define PXAPI __declspec(dllimport)
#endif

#define PXNDAPI [[nodiscard]] PXAPI


#define PLOTX_DISALLOW_COPY(CLASS)                                                                                     \
    CLASS(const CLASS&)            = delete;                                                                           \
    CLASS& operator=(const CLASS&) = delete

#define PLOTX_DISALLOW_MOVE(CLASS)                                                                                     \
    CLASS(CLASS&&)            = delete;                                                                                \
    CLASS& operator=(CLASS&&) = delete

#define PLOTX_DISALLOW_COPY_AND_MOVE(CLASS)                                                                            \
    PLOTX_DISALLOW_COPY(CLASS);                                                                                        \
    PLOTX_DISALLOW_MOVE(CLASS)


#define STATIC_ASSERT_AGGREGATE(TYPE) static_assert(std::is_aggregate_v<TYPE>, #TYPE " must be an aggregate type")