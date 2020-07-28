//
// Created by Haluk AKGUNDUZ on 27.07.2020.
//

#ifndef MATROP_SCANAPP_H
#define MATROP_SCANAPP_H

#include "Common.h"
#include <App.h>
#include "Matrix.h"

class ScanApp : public App {

public:
    explicit ScanApp(const char *path);
    ~ScanApp() override;

    bool scan(Matrix *, Matrix *);

    Matrix* calculate(Matrix *);

    bool process(std::vector<std::string> fileInputs);
    bool run(int argc, char argv[ARGV_MAX][PATH_MAX]) override;

    void printHelp() override;
};


#endif //MATROP_SCANAPP_H