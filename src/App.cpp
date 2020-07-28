//
// Created by Haluk AKGUNDUZ on 27.07.2020.
//

#include "App.h"
#include "Matrix.h"

App::App(const char *path) {

    setPath(path);
};

App::~App() = default;

bool App::creator(const char* path, uint32_t row, uint32_t col) {

    auto *A = new Matrix(row, col, true);

    A->printToFile(path);

    delete A;
    return true;
}

void App::setPath(const char *ref) {

    const char *pos = strrchr(ref, '/');
    strncpy(rootPath, ref, pos - ref + 1);
    printf("Working path : %s\n", rootPath);
}

const char* App::getPath() {

    return rootPath;
}

