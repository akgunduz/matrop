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
    explicit MultiplyApp(const char *path);
    ~MultiplyApp() override;

    bool multiply(Matrix *, Matrix *, Matrix *);

    Matrix* calculate(Matrix *A, Matrix *B);

    bool process(std::vector<std::string> fileInputs);
    bool run(int argc, char argv[ARGV_MAX][PATH_MAX]) override;

    void printHelp() override;
};


#endif //MATROP_MULTIPLYAPP_H
