//
// Created by hadriax on 03/08/22.
//

#include "../Public/Tools.h"
#include <iostream>

bool Tools::IsArraySortedAsc(const int *array, int ar_size, bool print_success) {
    for (int i = 0; i < (ar_size - 1); ++i) {
        if (array[i] > array[i + 1]) {
            std::cerr << "Error : Non sorted array.\n" << std::endl;
            return false;
        }
    }

    if (print_success)
        printf("Array is sorted.\n");

    return true;
}

void Tools::RandFillWithInt(int *array, const int size) {
    for (auto i = 0; i < size; ++i)
        array[i] = rand() % 100;
}

void Tools::MemSwap(int &a, int &b) {
    const int buffer = a;
    a = b;
    b = buffer;
}
