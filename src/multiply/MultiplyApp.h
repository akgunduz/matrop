//
// Created by Haluk AKGUNDUZ on 27.07.2020.
//

#ifndef MATROP_MULTIPLYAPP_H
#define MATROP_MULTIPLYAPP_H

#include "Common.h"
#include <App.h>
#include "Matrix.h"

class MultiplyApp : public App {

public:
    MultiplyApp() = default;
    ~MultiplyApp() override = default;

    bool multiply(Matrix *, Matrix *, Matrix *);

    Matrix* calculate(Matrix *A, Matrix *B);

    bool process(std::vector<std::string> fileInputs, bool);
    bool run(bool, int argc, char argv[ARGV_MAX][PATH_MAX]) override;

    void printHelp() override;
};


#endif //MATROP_MULTIPLYAPP_H
