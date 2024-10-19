#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>
namespace NRA {

template <class RandomAccessIterator, class Less>
void insertionsort(RandomAccessIterator first, RandomAccessIterator beyond, Less less) 
{
    for (RandomAccessIterator it = first + 1; it != beyond; ++it) 
    {
        auto insertee = std::move(*it);
        RandomAccessIterator j = it;

        while (j != first && less(insertee, *(j - 1))) 
        {
            *j = std::move(*(j - 1));
            --j;
        }

        *j = std::move(insertee);
    }
}

template <class RandomAccessIterator, class Less>
void heapify(RandomAccessIterator first, RandomAccessIterator last, Less less) 
{
    auto size = std::distance(first, last);
    for (auto i = size / 2 - 1; i >= 0; --i) {
        auto root = i;
        while (2 * root + 1 < size) {
            auto child = 2 * root + 1;
            if (child + 1 < size && less(*(first + child), *(first + child + 1))) 
            {
                ++child;
            }
            if (less(*(first + root), *(first + child))) 
            {
                std::swap(*(first + root), *(first + child));
                root = child;
            } else 
            {
                break;
            }
        }
    }
}

template <class RandomAccessIterator, class Less>
void heapsort(RandomAccessIterator first, RandomAccessIterator last, Less less) 
{
    // Build  heap
    heapify(first, last, less);

    // Extract each element
    for (auto i = std::distance(first, last) - 1; i > 0; --i) 
    {
        std::swap(*first, *(first + i));
        heapify(first, first + i, less);
    }
}

template <class RandomAccessIterator, class Less>
RandomAccessIterator medianOfThree(RandomAccessIterator first, RandomAccessIterator last, Less less) 
{
    RandomAccessIterator middle = first + std::distance(first, last) / 2;

    if (less(*middle, *first))
        std::swap(first, middle);
    if (less(*last, *middle))
        std::swap(last, middle);
    if (less(*middle, *first))
        std::swap(first, middle);

    return middle;
}

template <class RandomAccessIterator, class Less>
RandomAccessIterator qPartition(RandomAccessIterator first, RandomAccessIterator last, Less less) 
{
    RandomAccessIterator pivot = medianOfThree(first, last - 1, less);
    auto pivot_value = std::move(*pivot);

    --last; // Exclude the pivot from the partitioning process

    while (true) {
        while (less(*first, pivot_value))
            ++first;

        while (less(pivot_value, *last))
            --last;

        if (first >= last)
            return first;

        std::swap(*first, *last);
        ++first;
        --last;
    }
}

template <class RandomAccessIterator, class Less>
void customQuicksort(RandomAccessIterator first, RandomAccessIterator beyond, Less less, int depthLimit) {
    while (std::distance(first, beyond) > 10) 
    {
        if (depthLimit == 0) 
        {
            heapsort(first, beyond, less);
        }
        RandomAccessIterator partitionPoint = qPartition(first, beyond, less);
        customQuicksort(first, partitionPoint, less, depthLimit - 1);
        first = partitionPoint;
    }

    insertionsort(first, beyond, less);
}

template <class RandomAccessIterator, class Less>
void qihSort(RandomAccessIterator first, RandomAccessIterator last, Less less) 
{
    int depth_limit = 2 * log2(last - first);
    customQuicksort(first, last, less, depth_limit);
}

template <class RandomAccessIterator, class Less>
void sort(RandomAccessIterator first, RandomAccessIterator beyond, Less less) 
{
    qihSort(first, beyond, less);
}

template <class InputIterator, class OutputIterator, class Less>
OutputIterator sort(InputIterator first, InputIterator beyond, OutputIterator result, Less less) 
{
    using value_type = typename std::iterator_traits<InputIterator>::value_type;
    std::vector<value_type> tempV(first, beyond);
    qihSort(tempV.begin(), tempV.end(), less);
    return std::copy(tempV.begin(), tempV.end(), result);
}
}

