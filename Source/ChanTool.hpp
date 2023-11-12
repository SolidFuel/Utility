#pragma once

#include <juce_core/juce_core.h>

#if !defined(CHANTOOL_DEBUG)
 #define CHANTOOL_DEBUG 1
#endif

#include <string>

template<typename ...Args>
std::string concat(Args&&... args) {
    std::stringstream ss;

    (ss << ... << args);

    return ss.str();

}



#if CHANTOOL_DEBUG
    extern std::unique_ptr<juce::FileLogger> dbgout;
    #define DBGLOG(...) dbgout->logMessage(concat(__VA_ARGS__));
#else
    #define DBGLOG(...)
#endif