//
// Created by Haluk AKGUNDUZ on 27.07.2020.
//

#include "Common.h"
#include "Util.h"

std::string Util::getFileName(const char *arg) {

    char fileBuffer[PATH_MAX];
    if (isdigit(arg[0])) {
        sprintf(fileBuffer, "MatrixInput_%s", arg);

    } else {
        sprintf(fileBuffer, "%s", arg);
    }

    return std::string(fileBuffer);
}

