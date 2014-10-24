//
//  Heap.h
//  MaxBandwidthPath
//
//  Created by WeiZhong Chen on 3/6/14.
//  Copyright (c) 2014 WeiZhong Chen. All rights reserved.
//

#include <vector>
#include "DataStructure.h"
#include "Utils.h"

#ifndef __MaxBandwidthPath__Heap__
#define __MaxBandwidthPath__Heap__

template <class Type>
class Heap {
private:
    std::vector<Type> element;
public:
    Heap();
    ~Heap() {};
    Type Max();
    void insert(Type, long*);
    void remove(long, long*);
    long get_current_no() {return element.size();}
};

template <class Type>
Heap<Type>::Heap() {
    element.reserve(MAXVEX * MAXVEX * sizeof(Type));
}

template <class Type>
Type Heap<Type>::Max() {
    return element[0];
}

template <class Type>
void Heap<Type>::insert(Type x, long* map) {
    long i;
    element.push_back(x);
    if (map != nullptr) {   //manage the map
        map[get_key(x)] = element.size() - 1;
    }
    for (i = element.size() - 1; i > 0; ) {
        if (element[i] > element[(i-1)/2]) {
            mySwap(element[i], element[(i-1)/2]);
            if (map != nullptr) {   //manage the map
                map[get_key(element[(i-1)/2])] = (i - 1) / 2;
                map[get_key(element[i])] = i;
            }
            i = (i - 1) / 2;
        } else {
            break;
        }
    }

}

template <class Type>
void Heap<Type>::remove(long x_index, long* map) {
    if (x_index == -1) {   //not found
        return;
    }
    mySwap(element[x_index], element.back());
    if (map != nullptr) {
        map[get_key(element[x_index])] = -1;
        map[get_key(element.back())] = x_index;
    }
    element.erase(element.end() - 1);
    if ((x_index - 1) / 2 > 0 && (element[x_index] > element[(x_index-1)/2])) {
        for (long j = x_index; j > 0; ) {
            if (element[j] > element[(j-1)/2]) {
                mySwap(element[j], element[(j-1)/2]);
                if (map != nullptr) {   //manage the map
                    map[get_key(element[(j-1)/2])] = (j - 1) / 2;
                    map[get_key(element[j])] = j;
                }
                j = (j - 1) / 2;
            } else {
                break;
            }
        }
    }
    else if ((x_index * 2 + 1 < element.size() && element[x_index] < element[x_index*2+1]) ||
             (x_index * 2 + 2 < element.size() && element[x_index] < element[x_index*2+2])) {
        //the bandwidth of invalid element is 0, therefore this case excludes that i is the leaf node
        for (long j = x_index; j * 2 + 1 < element.size(); ) {
            Type larger;
            if (j * 2 + 2 < element.size()) {
                larger = element[j*2+1] > element[j*2+2] ? element[j*2+1] : element[j*2+2];
            }
            else {
                larger = element[j*2+1];
            }
            if (element[j] < larger) {   //swap this element with the larger one
                if (larger == element[j*2+1]) {
                    mySwap(element[j], element[j*2+1]);
                    if (map != nullptr) {   //manage the map
                        map[get_key(element[j*2+1])] = j * 2 + 1;
                        map[get_key(element[j])] = j;
                    }
                    j = j * 2 + 1;
                } else if (larger == element[j*2+2]) {
                    mySwap(element[j], element[j*2+2]);
                    if (map != nullptr) {   //manage the map
                        map[get_key(element[j*2+2])] = j * 2 + 2;
                        map[get_key(element[j])] = j;
                    }
                    j = j * 2 + 2;
                }
            }
            else {
                break;
            }
        }
    }
}

#endif
