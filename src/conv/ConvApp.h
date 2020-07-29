//
// Created by Haluk AKGUNDUZ on 27.07.2020.
//

#ifndef MATROP_CONVAPP_H
#define MATROP_CONVAPP_H

#include "Common.h"
#include <App.h>
#include "Matrix.h"

typedef std::vector<float> TypeFilter;

class ConvApp : public App {

    TypeFilter defaultFilter {1.1f / 11.0f, 2.2f / 11.0f, 4.4f / 11.0f, 2.2f / 11.0f, 1.1f / 11.0f};

public:
    ConvApp() = default;
    ~ConvApp() override = default;

    bool conv(Matrix *, Matrix *, TypeFilter&, Matrix *);

    Matrix* calculate(Matrix *, TypeFilter&);
    bool extractFilter(const char* file, TypeFilter&);

    bool process(std::vector<std::string> fileInputs, const char*, bool);
    bool run(bool, int argc, char argv[ARGV_MAX][PATH_MAX]) override;

    void printHelp() override;
};


#endif //MATROP_CONVAPP_H
