//
// Created by jzb on 2020/3/29.
//

#ifndef DAHUACAM_DEFS_HPP
#define DAHUACAM_DEFS_HPP

#ifdef _WIN32
#include <Windows.h>
#else

#include <unistd.h>

#endif
#ifdef _WIN32
#define SLEEP(a)    Sleep(a);
#else
#define SLEEP(a)    usleep((a) * 1000);
#endif

#endif //DAHUACAM_DEFS_HPP
