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
    ScanApp() = default;
    ~ScanApp() override = default;

    bool scan(Matrix *, Matrix *);

    Matrix* calculate(Matrix *);

    bool process(std::vector<std::string>, bool);
    bool run(bool, int argc, char argv[ARGV_MAX][PATH_MAX]) override;

    void printHelp() override;
};


#endif //MATROP_SCANAPP_H
