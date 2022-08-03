#include <cassert>
#include <iostream>

constexpr int ar_size = 20;

/*
 * ar[n] ->[0; 99]
 */
void static print_array(const int* ar, const int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("[%c%c]", static_cast<char>((ar[i] / 10) + '0'), static_cast<char>((ar[i] % 10) + '0'));
    }
    printf("\n");
}


void static rand_int_fill(int* ar, const int size)
{
    for (auto i = 0; i < size; ++i)
    {
        ar[i] = rand() % 100;  // NOLINT(concurrency-mt-unsafe)
    }
}

bool static check_is_sorted(const int* ar, const int size, bool print_success = false)
{
    for (int i = 0; i < size - 1; ++i)
    {
        if (ar[i] > ar[i + 1])
        {
        		std::cerr << "Error : Non sorted array.\n" << std::endl;
            return false;
        }
    }

    if (print_success)
        printf("Array is sorted.\n");

    return true;
}

void static swap(int& a, int& b)
{
    const int tmp = a;

    a = b;
    b = tmp;
}

/**
 * \brief Iterate through the whole array and find the smallest unsorted elements one by one.
 * Non adaptive.
 * Unstable, equal entities might be rearranged.
 * \param to_sort CArray to sort
 * \param size Size of the passed CArray
 */
void static selection_sort_asc(int* to_sort, const int size)
{
    for (auto i = 0; i < (size - 1); ++i)
    {
        printf("- Filling slot [%i]\n", i);

    	for (auto j = i + 1; j < size; ++j)
        {
            printf("    - Compare %i at [%i] to  %i at [%i] \n", to_sort[i], i , to_sort[j], j);

            if (to_sort[j] < to_sort[i])
            {
                printf("        - Swap %i at [%i] with  %i at [%i] \n", to_sort[i], i, to_sort[j], j);
                swap(to_sort[i], to_sort[j]);
            }
        }
    }
}

/**
 * \brief Iterate through array and compare current value to next one. Swap them if needed.
 * Adaptive
 * \param to_sort CArray to sort
 * \param size Size of the passed CArray
 */
void static bubble_sort_asc(int* to_sort, const int size)
{
    for (auto i = 0; i < size; ++i)
    {
        bool is_sorted = true;

	    for (auto j = 0; j < (size - 1); ++j)
		{
            printf("- Comparing %i at [%i] with %i at [%i]\n",
                to_sort[j], j, to_sort[j + 1], j + 1);

	        if (to_sort[j + 1] < to_sort[j])
	        {
                printf("  - Swap %i at [%i] with %i at [%i]\n",
                    to_sort[j], j, to_sort[j + 1], j + 1);
	            swap(to_sort[j + 1], to_sort[j]);
                is_sorted = false;
	        }
		}

        if (is_sorted)
            break;
    }	
}

/**
 * \brief Assume to_sort[0] is sorted. Check next value, and shift it left until it is sorted. Then go to next value.
 * As a result, values are inserted one by one in a virtual sub-list.
 * \param to_sort CArray to sort
 * \param size Size of the passed CArray
 */
void static insertion_sort_asc(int* to_sort, const int size)
{
    //  List iteration from 1, assuming 0 as sorted.
    for (auto i = 1; i < size; ++i)
    {
        printf("- Check %i at [%i] \n", to_sort[i], i);

        // Comparison justify a swap AND j has not moved to the list boundary (0).
        // Comparison can be tested in the FOR loop declaration, as it is an exit condition.
        for (auto j = i; (to_sort[j] < to_sort[j - 1]) && (j > 0); --j)
        {
        	printf("  - Swap %i at [%i] with %i at [%i]\n",
                to_sort[j], j, to_sort[j - 1], j - 1);

            // Shift elements toward left.
            swap(to_sort[j], to_sort[j - 1]);
        }
    }
}

/**
 * \Step 1 :  Divide the list into smaller sub-lists of equal size.
 * \Step 2 :  Sort them using Insertion Sort.
 * \Step 3 :  Repeat until interval surround the whole list.
 * \param to_sort CArray to sort
 * \param size Size of the passed CArray
 */
void static shell_sort_asc(int* to_sort, const int size)
{
    // Manage intervals size.
    for (auto interval = size / 2; interval > 0; interval /= 2)
    {
        printf("- Select %i as interval. Looking for sub-list of size %i\n", interval, (size / interval));
        
        // For each sub-list...
        for (auto sub_list = 0; sub_list < interval; ++sub_list)
        {
            printf("    - Working on sub-list %i\n", sub_list);

            // ACTUAL INSERTION SORT.
            // Starter index for insertion, taking sub-list index in account.
            for (auto to_compare = (sub_list + interval); to_compare < size; to_compare += interval)
            {
                printf("        - Check %i at [%i]\n",
                    to_sort[to_compare], to_compare);

                // Insert compared value in the actual sub-list. Shifting value to the left of the sub-list.
                for (auto j = to_compare; (to_sort[j] < to_sort[j - interval]) && (j >= interval); j -= interval)
                {
                	printf("                - Swap %i at [%i] with %i at [%i]\n",
                        to_sort[j], j, to_sort[j - interval], j - interval);

                    swap(to_sort[j], to_sort[j - interval]);
                }
            }
        }

        printf("State ");
        print_array(to_sort, ar_size);
    }
}

void static merge_list_asc(int* to_merge, int a, int b, int c)
{
	
}

/**
 * \brief Divide and Merge.
 * \Step 1 : If we have a size 1 list, it is already sorted.
 * \Step 2 : Recursively divide the list into two halves, until it can no more be divided.
 * \Step 3 : Merge the divided lists two by two, while keeping the new list sorted.
 */
void static merge_sort_asc(int* to_sort, const int size)
{
    if (size <= 1) return;

    // Manage lists sizes.
    for (auto i = size; i > 0; i /= 2)
    {

    }
}

void static selection_sort_test()
{
    auto* ar = new int[ar_size];
    rand_int_fill(ar, ar_size);

    printf("IN :  ");
    print_array(ar, ar_size);
    selection_sort_asc(ar, ar_size);
    printf("OUT : ");
    print_array(ar, ar_size);
    check_is_sorted(ar, ar_size, true);

    delete[] ar;
}

void static bubble_sort_test()
{
    auto* ar = new int[ar_size];
    rand_int_fill(ar, ar_size);

    printf("IN :  ");
    print_array(ar, ar_size);
    bubble_sort_asc(ar, ar_size);
    printf("OUT : ");
	print_array(ar, ar_size);
    check_is_sorted(ar, ar_size, true);

    delete[] ar;
}

void static insertion_sort_test()
{
    auto* ar = new int[ar_size];
    rand_int_fill(ar, ar_size);

    printf("IN :  ");
    print_array(ar, ar_size);
    insertion_sort_asc(ar, ar_size);
    printf("OUT : ");
    print_array(ar, ar_size);
    check_is_sorted(ar, ar_size, true);

    delete[] ar;
}

void static shell_sort_test()
{
    auto* ar = new int[ar_size];
    rand_int_fill(ar, ar_size);

    printf("IN :  ");
    print_array(ar, ar_size);
    shell_sort_asc(ar, ar_size);
    printf("OUT : ");
    print_array(ar, ar_size);
    check_is_sorted(ar, ar_size, true);

    delete[] ar;
}

void static merge_sort_test()
{
    auto* ar = new int[ar_size];
    rand_int_fill(ar, ar_size);

    printf("IN :  ");
    print_array(ar, ar_size);
    merge_sort_asc(ar, ar_size);
    printf("OUT : ");
    print_array(ar, ar_size);
    check_is_sorted(ar, ar_size, true);

    delete[] ar;
}

int main()
{
    // constexpr unsigned int seed = 4156459721; // time(nullptr)
    const auto seed = time(nullptr);
    srand(seed);  // NOLINT(clang-diagnostic-shorten-64-to-32, cert-msc51-cpp)

    std::cout << "SEED = " << seed << std::endl;

	std::cout << "Selection sort - size " << ar_size << std::endl;
	selection_sort_test();
	std::cout << std::endl;

	std::cout << std::endl << "Bubble sort - size " << ar_size << std::endl;
	bubble_sort_test();
	std::cout << std::endl;

	std::cout << std::endl << "Insert sort - size " << ar_size << std::endl;
	insertion_sort_test();
	std::cout << std::endl;

	std::cout << std::endl << "Shell sort - size " << ar_size << std::endl;
	shell_sort_test();
	std::cout << std::endl;

    std::cout << std::endl << "Merge sort - size " << ar_size << std::endl;
    merge_sort_test();
    std::cout << std::endl;
}