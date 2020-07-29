//
// Created by Haluk AKGUNDUZ on 27.07.2020.
//

#include "App.h"
#include "Matrix.h"

bool App::creator(const char* path, uint32_t row, uint32_t col) {

    auto *A = new Matrix(row, col, true);

    A->printToFile(path);

    delete A;
    return true;
}


