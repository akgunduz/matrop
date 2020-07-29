//
// Created by Haluk AKGUNDUZ on 27.07.2020.
//


#include "ScanApp.h"

void ScanApp::printHelp() {

    printf("\n------------------- Scan Parameters------------------- \n");
    printf("Create:    -c ID size                                    \n");
    printf("Sample:    -c 4 100                                      \n");
    printf("Default:   fileInput1 fileOutput                         \n");
    printf("Sample:    MatrixInput_1 MatrixOutput_2                  \n");
    printf("Default:   fileID1 fileID2                               \n");
    printf("Sample:    1 2                                           \n");
    printf("Wait:      -w waitInMilliseconds                         \n");
    printf("Sample:    -w 3000                                       \n");
}

bool ScanApp::scan(Matrix *A, Matrix *calculated) {

    float sum = 0;
    for (int i = 0; i < A->getSize(); i++) {
        sum += A->getMem()[i];
        calculated->getMem()[i] = sum;
    }

    return true;
}

Matrix* ScanApp::calculate(Matrix *A) {

    auto* calculated = new Matrix(A->getRow(), A->getCol());

    if (!scan(A, calculated)) {
        delete calculated;
        return nullptr;
    }

    return calculated;
}

bool ScanApp::process(std::vector<std::string> fileInputs, bool multiMode) {

    Matrix *A, *B;

    if (fileInputs.size() < 2) {

        printf("There is not enough matrix to scan, at least 2, 1 for input and 1 for output\n");
        return false;
    }

    if (!multiMode) {

        printf("Loading Matrix Input File %d : %s \n", 0, fileInputs[0].c_str());

        B = new Matrix(fileInputs[0].c_str());

        for (int i = 1; i < fileInputs.size(); i++) {

            A = B;

            B = calculate(A);

            delete A;
        }

        B->printToFile(fileInputs[fileInputs.size() - 1].c_str());

        printf("Output File Generated : %s \n\n", fileInputs[fileInputs.size() - 1].c_str());

        delete B;

        return true;
    }

    for (int i = 0; i < fileInputs.size(); i = i + 2) {

        A = new Matrix(fileInputs[i].c_str());

        B = calculate(A);

        B->printToFile(fileInputs[i + 1].c_str());

        printf("Output File Generated : %s \n\n", fileInputs[i + 1].c_str());

        delete A;

        delete B;
    }

    return true;
}

bool ScanApp::run(bool multiMode, int argc, char argv[ARGV_MAX][PATH_MAX]) {

    std::vector<std::string> fileInputs;

    for (int i = 0; i < argc; i++) {

        fileInputs.emplace_back(Util::getFileName(argv[i]));
    }

    return process(fileInputs, multiMode);
}
