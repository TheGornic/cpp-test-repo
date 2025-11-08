#pragma once

#include <deque>

template<class T, class Comp>
std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comparator) {
    std::deque<T> result;
    size_t index_half1 = 0;
    size_t index_half2 = 0;
    while (index_half1 < half1.size() && index_half2 < half2.size()){
        if (comparator(half1[index_half1],half2[index_half2])){
            result.push_back(half1[index_half1]);
            ++index_half1;
        } else {
            result.push_back(half2[index_half2]);
            ++index_half2;
        }
    }
    while (index_half1 < half1.size()){
        result.push_back(half1[index_half1]);
        ++index_half1;
    }
    while (index_half2 < half2.size()){
        result.push_back(half2[index_half2]);
        ++index_half2;
    }
    return result;
}

template<class T, class Comp>
std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comparator) {
    if (src.size() <= 1){
        return src;
    }
    const size_t mid_src = src.size() / 2;
    std::deque<T> left_part_deque(src.begin(), src.begin() + mid_src);
    std::deque<T> right_part_deque(src.begin() + mid_src, src.end());
    left_part_deque = MergeSort(left_part_deque, comparator);
    right_part_deque = MergeSort(right_part_deque, comparator);
    return Merge(left_part_deque,right_part_deque, comparator);
}
