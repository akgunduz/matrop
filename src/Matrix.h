//
// Created by Haluk AKGUNDUZ on 28.07.2020.
//

#ifndef MATROP_MATRIX_H
#define MATROP_MATRIX_H

#include "Common.h"

class Matrix {

protected :
    uint32_t row{};
    uint32_t col{};

    size_t size{};
    float *mem{};

public:

    Matrix(const char*);
    Matrix(uint32_t, uint32_t, bool = false);
    virtual ~Matrix();

    bool allocMem(size_t, float **);
    void create(size_t, float *);
    bool readFromFile(const char*);
    void consoleOut(int, int);
    bool printToFile(const char *);

    size_t getSize() const;
    uint32_t getRow() const;
    uint32_t getCol() const;
    float* getMem();
};


#endif //MATROP_MATRIX_H
