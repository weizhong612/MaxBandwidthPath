//
//  Utils.h
//  MaxBandwidthPath
//
//  Created by WeiZhong Chen on 3/6/14.
//  Copyright (c) 2014 WeiZhong Chen. All rights reserved.
//

#include "DataStructure.h"

#ifndef __MaxBandwidthPath__Utils__
#define __MaxBandwidthPath__Utils__

template <typename T>
void mySwap(T& x, T& y) {
    T tmp;
    tmp = x;
    x = y;
    y = tmp;
}

template <typename T>
inline T min(T& x, T& y) {
    return x < y ? x : y;
}

struct compare {
    bool operator()(EdgeType& a, EdgeType& b) const {
        if (a > b)
            return true;
        else
            return false;
    }
};

inline int get_key(VexType v) {return v.vertex_index;}
inline int get_key(EdgeType e) {return e.vex2_index;}

#endif
