//
// Created by Haluk AKGUNDUZ on 27.07.2020.
//

#ifndef MATROP_COMMON_H
#define MATROP_COMMON_H

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <cerrno>
#include <climits>
#include <sys/stat.h>
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <cstring>
#include <random>
#include <thread>
#include <chrono>

#define TILESIZE 32
#define ALIGNMENT 16
#define INVALID_SANITY 0xFFFF
#define MAX_FILE_COUNT 10
#define MAX_TIMEARRAY_COUNT 1000
#define MAX_ARGUMENT 10
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#endif //MATROP_COMMON_H
