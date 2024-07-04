#ifndef ENV_SYSTEM_VAR_H
#define ENV_SYSTEM_VAR_H

#include <string>

const std::string sys =
#ifdef YUSH_MACOS
    "macOS"
#elif YUSH_LINUX
    "Linux"
#elif YUSH_UNIX
    "Unix"
#elif YUSH_FREEBSD
    "FreeBSD"
#else
    "Unknown"
#endif
    ;

#endif
