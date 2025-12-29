#pragma once

#if defined(_MSC_VER)
#define SK_DEBUGBREAK() __debugbreak()
#elif defined(__clang__) || defined(__GNUC__)
#define SK_DEBUGBREAK() __builtin_trap()
#else
#include <csignal>
#define SK_DEBUGBREAK() raise(SIGTRAP)
#endif

#include "Suki/Core/Logger.h"

#ifdef NDEBUG

#define SK_ASSERT(cond)
#define SK_ASSERT_MSG(cond, msg)

#else

#define SK_ASSERT(cond)                                                    \
    do                                                                     \
    {                                                                      \
        if(!(cond))                                                        \
        {                                                                  \
            SK_CORE_CRITICAL("ASSERT FAILED: {} ({}:{})", #cond, __FILE__, \
                             __LINE__);                                    \
            SK_DEBUGBREAK();                                               \
        }                                                                  \
    } while(0)

#define SK_ASSERT_MSG(cond, msg)                                         \
    do                                                                   \
    {                                                                    \
        if(!(cond))                                                      \
        {                                                                \
            SK_CORE_CRITICAL("ASSERT FAILED: {} ({}:{})", msg, __FILE__, \
                             __LINE__);                                  \
            SK_DEBUGBREAK();                                             \
        }                                                                \
    } while(0)

#endif
