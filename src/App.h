//
// Created by Haluk AKGUNDUZ on 27.07.2020.
//

#ifndef MATROP_APP_H
#define MATROP_APP_H

#include "Common.h"

#define ARGV_LENGTH 30
#define ARGV_MAX 20

enum APP_MODES {
    MATRIX_MODE,
    SCAN_MODE,
    CONV_MODE,
};

class App {

protected:

    char rootPath[PATH_MAX]{};

    bool print_enabled{false};

    FILE *debugFile = nullptr;

protected:

    explicit App(const char *);

public :

    bool creator(const char*, uint32_t, uint32_t);

    void setPath(const char *);
    const char *getPath();

    virtual bool run(int argc, char argv[ARGV_MAX][PATH_MAX]) = 0;
    virtual void printHelp() = 0;

    virtual ~App();

public:

    App() = default;

};


#endif //MATROP_APP_H
