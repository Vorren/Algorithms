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


int main(int argc, const char * argv[]) {
    
    std::vector<int> data {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9};
    
    auto output = mergeSort(data);
    
    for(auto& o : output){
        std::cout << o << std::endl;
    }
    
    return 0;
}

