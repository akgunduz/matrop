//
// Created by Haluk AKGUNDUZ on 27.07.2020.
//

#ifndef MATROP_APP_H
#define MATROP_APP_H

#include "Common.h"
#include "Util.h"

#define ARGV_MAX 20

enum APPTYPE {
    APPTYPE_MULTIPLY,
    APPTYPE_SCAN,
    APPTYPE_CONV,
    APPTYPE_MAX,
};

class App {

protected:

    App() = default;

public :

    bool creator(const char*, uint32_t, uint32_t);

    virtual bool run(bool, int argc, char argv[ARGV_MAX][PATH_MAX]) = 0;
    virtual void printHelp() = 0;

    virtual ~App() = default;

};


#endif //MATROP_APP_H
