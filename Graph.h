//
//  Graph.h
//  MaxBandwidthPath
//
//  Created by WeiZhong Chen on 3/6/14.
//  Copyright (c) 2014 WeiZhong Chen. All rights reserved.
//

#include <cstdlib>
#include <limits>
#include "Utils.h"

#ifndef MaxBandwidthPath_Graph_h
#define MaxBandwidthPath_Graph_h

class Graph {
public:
    VexNode* vexnode;   //the adjacent list of G
    Graph();   //construct a graph without edges
    Graph(int degree, double percent_edge);   //construct a graph with random edges
    ~Graph();
};

#endif
