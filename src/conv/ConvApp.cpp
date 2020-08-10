//
// Created by Haluk AKGUNDUZ on 27.07.2020.
//

#include "ConvApp.h"

void ConvApp::printHelp() {

    printf("\n------------------- Conv Parameters------------------- \n");
    printf("Create:    -c ID rowCount columnCount                    \n");
    printf("Sample:    -c 4 100 100                                  \n");
    printf("Filter:    -f filterInput                                \n");
    printf("Sample:    -f filterInput                                \n");
    printf("Default:   fileInput1 fileInput2                         \n");
    printf("Sample:    MatrixInput_1 MatrixInput_2                   \n");
    printf("Default:   fileID1 fileID2                               \n");
    printf("Sample:    1 2                                           \n");
    printf("Wait:      -w waitInMilliseconds                         \n");
    printf("Sample:    -w 3000                                       \n");
}

bool ConvApp::conv(Matrix *A, Matrix *Temp, TypeFilter& filter, Matrix *calculated) {

    uint32_t half_length = (filter.size() - 1) / 2;

    //horizontal
    for(int j = 0; j < A->getRow(); j++) {

        for(uint32_t i=(half_length+1); i<(A->getCol()-(half_length+1)); i++)
        {
            float acc = 0.0f;
            for(int k=0; k<filter.size(); k++)
            {
                acc += A->getMem()[j*A->getCol() + (i+k-half_length)] * filter[k];
            }
            Temp->getMem()[j*A->getCol() + i] = acc;
        }
    }

    //vertical
    for(uint32_t j=(half_length+1); j<(A->getRow()-(half_length+1)); j++)
    {
        for(int i=0; i<A->getCol(); i++)
        {
            float acc = 0.0f;
            for(int k=0; k<filter.size(); k++)
            {
                acc += Temp->getMem()[(j+k-half_length)*A->getCol() + i] * filter[k];
            }
            calculated->getMem()[j*A->getCol() + i] = acc;
        }
    }

    return true;
}



Matrix* ConvApp::calculate(Matrix *A, TypeFilter& filter) {

    auto* calculated = new Matrix(A->getRow(), A->getCol());
    auto* temp = new Matrix(A->getRow(), A->getCol());

    if (!conv(A, temp, filter, calculated)) {
        delete calculated;
        return nullptr;
    }

    return calculated;
}

bool ConvApp::extractFilter(const char* file, TypeFilter& filter) {

    if (strcmp(file, "") == 0) {

        filter = defaultFilter;

        return true;

    }

    FILE *fd = fopen(file, "r");
    if (!fd) {
        throw std::runtime_error("File could not opened!");
    }

    int size;
    int res = fscanf(fd, "%d", &size);
    if (res == EOF) {
        fclose(fd);
        return false;
    }

    for (int i = 0; i < size; i++) {

        float f;

        res = fscanf(fd, "%f,", &f);
        if (res == EOF) {

            fclose(fd);

            return false;
        }

        filter.emplace_back(f);

    }

    fclose(fd);

    return true;
}
bool ConvApp::process(std::vector<std::string> fileInputs, const char* filterFile, bool multiMode) {

    Matrix *A, *B;

    if (fileInputs.size() < 2) {

        printf("There is not enough matrix to multiply, at least 2, 1 for input and 1 for output\n");
        return false;
    }

    TypeFilter filter;

    bool status = extractFilter(filterFile, filter);
    if (!status) {
        printf("Can not extract the filter");
        return false;
    }

    if (!multiMode) {

        printf("Loading Matrix Input File %d : %s \n", 0, fileInputs[0].c_str());

        B = new Matrix(fileInputs[0].c_str());

        for (int i = 1; i < fileInputs.size(); i++) {

            A = B;

            B = calculate(A, filter);

            delete A;

        }

        B->printToFile(fileInputs[fileInputs.size() - 1].c_str());

        printf("Output File Generated : %s \n\n", fileInputs[fileInputs.size() - 1].c_str());

        delete B;

        return true;
    }

    for (int i = 0; i < fileInputs.size(); i = i + 2) {

        A = new Matrix(fileInputs[i].c_str());

        B = calculate(A, filter);

        B->printToFile(fileInputs[i + 1].c_str());

        printf("Output File Generated : %s \n\n", fileInputs[i + 1].c_str());

        delete A;

        delete B;
    }

    return true;
}

bool ConvApp::run(bool multiMode, int argc, char argv[ARGV_MAX][PATH_MAX]) {

    std::vector<std::string> fileInputs;
    std::string filterFile;

    bool filterMode = false;

    for (int i = 0; i < argc; i++) {

        if (!strcmp (argv[i], "-f")) {

            filterMode = true;
            continue;
        }

        if (filterMode) {
            filterFile = Util::getFileName(argv[i]);
            filterMode = false;
        } else {
            fileInputs.emplace_back(Util::getFileName(argv[i]));
        }
    }

    return process(fileInputs, filterFile.c_str(), multiMode);
}
