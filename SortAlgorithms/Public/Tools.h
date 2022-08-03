//
// Created by hadriax on 03/08/22.
//

#ifndef CPP_SORT_ALGORITHMS_TOOLS_H
#define CPP_SORT_ALGORITHMS_TOOLS_H

class Tools {
    static bool IsArraySortedAsc(const int *array, int ar_size, bool print_success = true);

    static void RandFillWithInt(int *ar, const int size);

    static void MemSwap(int &a, int &b);
};

#endif //CPP_SORT_ALGORITHMS_TOOLS_H
