//
// Created by Haluk AKGUNDUZ on 27.07.2020.
//

#include "Common.h"
#include "Util.h"

void Util::mkPath(const char *path) {

    char tmp[PATH_MAX];
    char *p = nullptr;

    const char *pos = strrchr(path, '/');

    snprintf(tmp, pos - path + 1, "%s", path);

    for(p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = 0;
            mkdir(tmp, S_IRWXU);
            *p = '/';
        }
    }
    mkdir(tmp, S_IRWXU);
}

bool Util::endCheck(const char *str, const char *suffix) {

    if (!str || !suffix)
        return false;

    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);

    if (lensuffix >  lenstr) {
        return false;
    }

    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

