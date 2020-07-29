#include <multiply/MultiplyApp.h>
#include <scan/ScanApp.h>
#include <conv/ConvApp.h>
#include "App.h"
#include "Util.h"

int main(int argc, char *const *argv) {

    int wait = 0;

    bool createMode = false;
    bool multiMode = false;

    int filtered_argc = 0;
    char filtered_argv[ARGV_MAX][PATH_MAX];

    setenv("LC_NUMERIC", "C", 1);

    for (int i = 1; i < argc; i++) {

        if (!strcmp(argv[i], "-w")) {

            if (isdigit(argv[++i][0])) {
                wait = atoi(argv[i]);
            }

            continue;
        }

        if (!strcmp (argv[i], "-c")) {

            createMode = true;

            continue;
        }

        if (!strcmp (argv[i], "-m")) {

            multiMode = true;

            continue;
        }

        strcpy(filtered_argv[filtered_argc++], argv[i]);
    }

    App* app = nullptr;

#if defined(MULTIPLY) || defined(ALL)

    app = new MultiplyApp();

#endif

#if defined(SCAN) || defined(ALL)

    app = new ScanApp();

#endif

#if defined(CONV) || defined(ALL)

    app = new ConvApp();

#endif


    if (argc < 2) {
        app->printHelp();
        return EXIT_SUCCESS;
    }

    if (createMode) {
        return app->creator(Util::getFileName(filtered_argv[0]).c_str(),
                atoi(filtered_argv[1]), atoi(filtered_argv[2]));
    }

    app->run(multiMode, filtered_argc, filtered_argv);

    if (wait) {

        printf("Waiting %d miliseconds\n", wait);

        std::this_thread::sleep_for(std::chrono::milliseconds(wait));
    }

    delete app;

    return EXIT_SUCCESS;
}
