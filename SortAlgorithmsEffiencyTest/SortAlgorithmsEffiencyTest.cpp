#include <cassert>
#include <iostream>
#include <chrono>

// Not used in the tested algorithms.
#include <vector>
#include <algorithm>

typedef std::pair<std::string, long long> sample;

enum class sort_algorithm : uint8_t
{
    selection_sort,
    bubble_sort,
    insertion_sort,
	shell_sort
};

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
        for (auto j = i + 1; j < size; ++j)
        {
            if (to_sort[j] < to_sort[i])
            {
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
            if (to_sort[j + 1] < to_sort[j])
            {
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
        for (auto j = i; (to_sort[j] < to_sort[j - 1]) && (j > 0); --j)
        {
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
        for (auto sub_list = 0; sub_list < interval; ++sub_list)
        {
            for (auto to_compare = (sub_list + interval); to_compare < size; to_compare += interval)
            {
                // Insert compared value in the actual sub-list. Shifting value to the left of the sub-list.
                for (auto j = to_compare; (to_sort[j] < to_sort[j - interval]) && (j >= interval); j -= interval)
                {
                    swap(to_sort[j], to_sort[j - interval]);
                }
            }
        }
    }
}


/**
 * \brief Create a list given a size and a seed, then sort it and display the time the sort algorithm took.
 * \param to_sort_source The list whose copy will be sorted.
 * \param list_size Size of the list we want to create and sort.
 * \param sort_method Which algorithm should be use to sort the list.
 * \return Algorithm processing duration.
 */
long long static sort_tests(const int* to_sort_source, const int list_size, const sort_algorithm sort_method)
{
    auto* to_sort_copy = new int[list_size];

    // Copy of a source array ensure every test got the same array to work with.
    std::memcpy(to_sort_copy, to_sort_source, list_size * sizeof(int));

    const auto start = std::chrono::steady_clock::now();
    // Switch is inside the chrono, but can is non significative.
	switch (sort_method)
	{
		case sort_algorithm::selection_sort:
            selection_sort_asc(to_sort_copy, list_size);
            break;
		case sort_algorithm::bubble_sort:
            bubble_sort_asc(to_sort_copy, list_size);
            break;
		case sort_algorithm::insertion_sort:
            insertion_sort_asc(to_sort_copy, list_size);
            break;
		case sort_algorithm::shell_sort:
            shell_sort_asc(to_sort_copy, list_size);
            break;
	}
    const auto end = std::chrono::steady_clock::now();
    const auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();

    // Check test validity outside of test chrono.
    check_is_sorted(to_sort_copy, list_size);

    delete[] to_sort_copy;

    return elapsed_time;
}

void sort_and_print_durations(const int sample_size, std::vector<std::pair<std::string, long long>>& samples)
{
    std::sort(samples.begin(), samples.end(),
        [](const sample& a, const sample& b) -> bool { return (a.second < b.second); });

    std::cout << std::endl << "___ SIZE = " << sample_size << std::endl;
    for (const sample& s : samples)
    {
        std::cout << s.first << " took : " << s.second << " ms" << std::endl;
    }
}

void static test_serie(const int list_size)
{

	std::vector<sample> samples;

	auto* source = new int[list_size];
	rand_int_fill(source, list_size);

	samples.emplace_back( sample { "insertion_sort" , sort_tests(source, list_size, sort_algorithm::insertion_sort)} );
	samples.emplace_back( sample { "bubble_sort" , sort_tests(source, list_size, sort_algorithm::bubble_sort) } );
	samples.emplace_back( sample { "selection_sort" , sort_tests(source, list_size, sort_algorithm::selection_sort) } );
	samples.emplace_back( sample { "shell_sort" , sort_tests(source, list_size, sort_algorithm::shell_sort) } );
    
	sort_and_print_durations(list_size, samples);

	delete[] source;
}

int main()
{
    // constexpr unsigned int seed = 4156459721; // time(nullptr)
    const auto seed = time(nullptr);
    srand(seed);  // NOLINT(clang-diagnostic-shorten-64-to-32)
    
    test_serie(500);
    test_serie(1000);
    test_serie(2000);
    test_serie(10000);    	
}