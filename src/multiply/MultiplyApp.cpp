//
// Created by Haluk AKGUNDUZ on 27.07.2020.
//

#include "MultiplyApp.h"

MultiplyApp::MultiplyApp(const char *path) : App(path) {

}

MultiplyApp::~MultiplyApp() = default;

void MultiplyApp::printHelp() {

    printf("\n----------------- Multiply Parameters----------------- \n");
    printf("Create:    -c ID rowCount columnCount                    \n");
    printf("Sample:    -c 4 100 100                                  \n");
    printf("Default:   fileInput1 fileInput2 fileOutput3             \n");
    printf("Sample:    MatrixInput_1 MatrixInput_2 MatrixOutput_3    \n");
    printf("Default:   fileID1 fileID2 fileID3                       \n");
    printf("Sample:    1 2 3                                         \n");
    printf("Wait:      -w waitInMilliseconds                         \n");
    printf("Sample:    -w 3000                                       \n");
}

bool MultiplyApp::multiply(Matrix *A, Matrix *B, Matrix *calculated) {

    for (int i = 0; i < A->getRow(); i++) {

        for (int j = 0; j < B->getCol(); j++) {

            for (int k = 0; k < A->getCol(); k++) {

                calculated->getMem()[i * B->getCol() + j] +=
                        A->getMem()[i * A->getCol() + k] * B->getMem()[k * B->getCol() + j];
            }
        }
    }

    return true;
}

Matrix* MultiplyApp::calculate(Matrix *A, Matrix *B) {

    auto* calculated = new Matrix(A->getRow(), B->getCol());

    if (!multiply(A, B, calculated)) {
        delete calculated;
        return nullptr;
    }

    return calculated;
}

bool MultiplyApp::process(std::vector<std::string> fileInputs, bool multiMode) {

    Matrix *A, *B, *C;

    if (fileInputs.size() < 3) {

        printf("There is not enough matrix to multiply, at least 3, 2 for input and 1 for output\n");
        return false;
    }

    if (!multiMode) {

        printf("Loading Matrix Input File %d : %s \n", 0, fileInputs[0].c_str());

        C = new Matrix(fileInputs[0].c_str());

        for (int i = 1; i < fileInputs.size() - 1; i++) {

            A = C;

            printf("Loading Matrix Input File %d : %s \n", i, fileInputs[i].c_str());

            B = new Matrix(fileInputs[i].c_str());

            C = calculate(A, B);

            delete A;

            delete B;
        }

        C->printToFile(fileInputs[fileInputs.size() - 1].c_str());

        printf("Output File Generated : %s \n\n", fileInputs[fileInputs.size() - 1].c_str());

        delete C;

        return true;
    }

    for (int i = 0; i < fileInputs.size(); i = i + 3) {

        A = new Matrix(fileInputs[i].c_str());

        B = new Matrix(fileInputs[i + 1].c_str());

        C = calculate(A, B);

        C->printToFile(fileInputs[i + 2].c_str());

        printf("Output File Generated : %s \n\n", fileInputs[i + 2].c_str());

        delete A;

        delete B;

        delete C;
    }

    return true;
}

bool MultiplyApp::run(bool createMode, bool multiMode, int argc, char argv[ARGV_MAX][PATH_MAX]) {

    char fileBuffer[PATH_MAX];
    std::vector<std::string> fileInputs;

    for (int i = 0; i < argc; i++) {

        if (isdigit(argv[i][0])) {
            sprintf(fileBuffer, "%s/matrix/MatrixInput_%s", getPath(), argv[i]);

        } else {
            sprintf(fileBuffer, "%s/matrix/%s", getPath(), argv[i]);
        }
        fileInputs.emplace_back(fileBuffer);
    }

    if (createMode) {
        return creator(fileInputs[0].c_str(), atoi(argv[2]), atoi(argv[3]));
    }

    return process(fileInputs, multiMode);
}
