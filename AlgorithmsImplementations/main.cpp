//
//  main.cpp
//  AlgorithmsImplementations
//
//  Created by Phil Maevskiy on 26/01/15.
//  Copyright (c) 2015 Magic Forge. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

//
//mergesort
//
template <typename T>
std::vector<T> merge(std::vector<T>& data, std::vector<T>& left, std::vector<T>& right){
    
    std::vector<T> sorted;
    sorted.reserve(data.size());
    
    auto leftIt = left.begin();
    auto rightIt = right.begin();
    
    while( leftIt != left.end() && rightIt != right.end() ){

        auto l = *leftIt;
        auto r = *rightIt;
        
        if(l < r){
            sorted.push_back(l);
            ++leftIt;
        }else{
            sorted.push_back(r);
            ++rightIt;
        }
    }
    
    sorted.insert(sorted.end(), leftIt, left.end() );
    sorted.insert(sorted.end(), rightIt, right.end() );
    
    data = sorted;
    
    return data;
}

template<typename T>
std::vector<T> mergeSort(std::vector<T>& data){
    
    if(data.size() == 1){
        return data;
    }

    auto middle = data.begin() + int(data.size() * 0.5f);
    
    std::vector<T> left( data.begin(), middle );
    std::vector<T> right( middle, data.end() );
    
    auto sortedLeft = mergeSort(left);
    auto sortedRight = mergeSort(right);
    
    return merge(data, sortedLeft, sortedRight);
}

//
//inversion counting in array
//
template<typename T>
std::pair<std::vector<T>, unsigned long long int> mergeAndCountSplitInversions(std::vector<T>& b, std::vector<T>& c){
    int split = 0;
    std::vector<T> d;
    d.reserve(b.size() + c.size());
    
    auto leftIt = b.begin();
    auto rightIt = c.begin();
    
    while( leftIt != b.end() && rightIt != c.end() ){
        
        auto l = *leftIt;
        auto r = *rightIt;
        
        if(l < r){
            d.push_back(l);
            ++leftIt;
        }else{
            d.push_back(r);
            ++rightIt;
            split += b.end() - leftIt;
        }
    }
    
    d.insert(d.end(), leftIt, b.end() );
    d.insert(d.end(), rightIt, c.end() );
    
    return std::make_pair(d, split);
}

template<typename T>
std::pair<std::vector<T>, unsigned long long int> sortAndCountInversions(std::vector<T>& a){
    auto n = a.size();
    if(n<=1){
        return std::make_pair(a, 0);
    }
    
    auto middle = a.begin() + int(a.size() * 0.5f);
    
    std::vector<T> left( a.begin(), middle );
    std::vector<T> right( middle, a.end() );
    
    auto x = sortAndCountInversions( left );
    auto y = sortAndCountInversions( right );
    
    auto& b = x.first;
    auto& c = y.first;
    
    auto z = mergeAndCountSplitInversions( b, c );
    
    auto leftInversions = x.second;
    auto rightInversions = y.second;
    auto splitInversions = z.second;
    
    auto totalInversions = leftInversions + rightInversions + splitInversions;
    
    auto& d = z.first;
    
    return std::make_pair( d, totalInversions );
}


int main(int argc, const char * argv[]) {
    
    //mergesort test
    std::vector<int> mergesort_data {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9};
    auto mergesort_output = mergeSort(mergesort_data);
    for(auto& o : mergesort_output){
        std::cout << o << std::endl;
    }
    
    //inversion counting test
    std::vector<int> inversionCount_data{0,3,1,2,10,11,9}; // {1, 3, 5, 2, 4, 6};
    auto inversionCount_output = sortAndCountInversions(inversionCount_data);
    std::cout << "Inversion count: " << inversionCount_output.second << std::endl;
    for(auto& o : inversionCount_output.first){
        std::cout << o << std::endl;
    }
    
    return 0;
}

