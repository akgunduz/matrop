//
// Created by Haluk AKGUNDUZ on 28.07.2020.
//

#include "Matrix.h"
#include "Util.h"

#ifdef _WIN32
#define posix_memalign(p, a, s) (((*(p)) = _aligned_malloc((s), (a))), *(p) ?0 :errno)
#endif

Matrix::Matrix(uint32_t _row, uint32_t _col, bool prepare)
        : row(_row), col(_col), size(_row * _col) {

    if (!allocMem(size, &mem)) {
        throw std::runtime_error("Memory insufficient!");
    }

    if (prepare) {
        create(size, mem);
    }
}

Matrix::Matrix(const char *path) {

    int tryCount = 3;
    do {

        if (readFromFile(path)) {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    } while (tryCount--);

    if (!tryCount) {

        throw std::runtime_error("Can not read from file!");
    }

}

Matrix::~Matrix() {

    freeMem(mem);
}

bool Matrix::allocMem(size_t _size, float **_mem) {

    size_t mem_size = sizeof(float) * _size;

    int res = posix_memalign((void**)_mem, ALIGNMENT, mem_size);
    if (res != 0) {
        printf("Alloc failed! : %d\n", errno);
        return false;
    }

    int check = (int)((unsigned long long)(*_mem) % ALIGNMENT);
    if (check != 0) {
        freeMem(*_mem);
        printf("Alignment failed!\n");
        return false;
    }

    memset(*_mem, 0, mem_size);
    return true;
}

bool Matrix::freeMem(float *_mem) {

    if (_mem == nullptr) {
        return false;
    }

#ifdef _WIN32
    _aligned_free(_mem);
#else
    free(_mem);
#endif

    return true;
}

void Matrix::create(size_t _size, float *_mem) {

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> distribution(0.0, 1.0);

    printf("Preparing Input in Size: %ld\n", _size);

    for (int i = 0; i < _size; i++) {

        _mem[i] = (float)distribution(generator);

    }
}

bool Matrix::readFromFile(const char *path) {

    FILE *fd = fopen(path, "r");
    if (!fd) {
        printf("File could not opened!\n");
        return false;
    }

    int res = fscanf(fd, "%d, %d", &row, &col);
    if (res == EOF) {
        fclose(fd);
        printf("File Size Read Error!, file : %s, size : %lu, err : %u\n", path, size, errno);
        return false;
    }

    size = row * col;

    if (!allocMem(size, &mem)) {
        fclose(fd);
        printf("Memory insufficient!, requested size : %zu\n", size);
        return false;
    }

    for (size_t i = 0; i < size; i++) {

        res = fscanf(fd, "%f,", &mem[i]);
        if (res == EOF) {
            fclose(fd);
            printf("File Data Read Error!, file : %s, size : %lu, index : %lu, err : %u\n", path, size, i, errno);
            return false;
        }
    }

    fclose(fd);

    return true;
}

bool Matrix::printToFile(const char *path) {

    FILE *fd = fopen(path, "w");
    if (!fd) {
        return false;
    }

    fprintf(fd, "%d, %d\n\n", row, col);

    for (int i = 0; i < size; i++) {

        fprintf(fd, "%f,", mem[i]);
    }

    fclose(fd);

    return true;

}

void Matrix::consoleOut(int offset, int max) {

    printf("Printing Out in Size: %d\n", (int)size);

    for (int i = offset; i < size; i++) {

        if (i == max) {
            printf("\n");
            return;
        }

        printf("%f, ", mem[i]);
    }
}

size_t Matrix::getSize() const {

    return size;
}

uint32_t Matrix::getRow() const {

    return row;
}

uint32_t Matrix::getCol() const {

    return col;
}

float *Matrix::getMem() {

    return mem;
}
