#pragma once

#include <iostream>
#include "spdlog/spdlog.h"

namespace Suki
{

class Logger
{
public:
    static void Init();

    static std::shared_ptr<spdlog::logger>& GetCoreLogger()
    {
        if(s_CoreLogger == nullptr)
            std::cerr << "Make sure to call Logger::Init()" << std::endl;
        return s_CoreLogger;
    }

    static std::shared_ptr<spdlog::logger>& GetClientLogger()
    {
        if(s_ClientLogger == nullptr)
            std::cerr << "Make sure to call Logger::Init()" << std::endl;
        return s_ClientLogger;
    }

private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

}  // namespace Suki

#define SK_CORE_TRACE(...) ::Suki::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define SK_CORE_INFO(...) ::Suki::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define SK_CORE_WARN(...) ::Suki::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define SK_CORE_ERROR(...) ::Suki::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define SK_CORE_CRITICAL(...) \
    ::Suki::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#define SK_TRACE(...) ::Suki::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define SK_INFO(...) ::Suki::Logger::GetClientLogger()->info(__VA_ARGS__)
#define SK_WARN(...) ::Suki::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define SK_ERROR(...) ::Suki::Logger::GetClientLogger()->error(__VA_ARGS__)
#define SK_CRITICAL(...) \
    ::Suki::Logger::GetClientLogger()->critical(__VA_ARGS__)
