//
//  Approaches.h
//  MaxBandwidthPath
//
//  Created by WeiZhong Chen on 3/6/14.
//  Copyright (c) 2014 WeiZhong Chen. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <stack>
#include <queue>
#include "Graph.h"
#include "Heap.h"
#include "Utils.h"

#ifndef __MaxBandwidthPath__Approaches__
#define __MaxBandwidthPath__Approaches__

extern Path dijkstra_pure(Graph* G, int src_index, int dst_index);
extern Path dijkstra_heap(Graph* G, int src_index, int dst_index);
extern Path kruskal(Graph* G, int src_index, int dst_index);

extern void path_print(Path p);

#endif
