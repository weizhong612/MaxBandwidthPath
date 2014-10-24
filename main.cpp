//
//  main.cpp
//  MaxBandwidthPath
//
//  Created by WeiZhong Chen on 3/6/14.
//  Copyright (c) 2014 WeiZhong Chen. All rights reserved.
//

#include <iostream>
#include <ctime>
#include "DataStructure.h"
#include "Heap.h"
#include "Graph.h"
#include "Algorithm.h"

#define GRAPH_TESTED 5
#define VX_TESTED 5
#define TOTAL_GROUP 6

using namespace std;

int main(int argc, const char * argv[]) {
    //intialize clock parameter
    clock_t ts;
    clock_t te;
    
    //apply algorithms
    int i, j;
    srand((unsigned)time(NULL));
    
    double time[TOTAL_GROUP];
    for (i = 0; i < TOTAL_GROUP; ++i) {
        time[i] = 0;
    }
    
    Path dense_dijkstra_pure;
    Path sparse_dijkstra_pure;
    Path dense_dijkstra_heap;
    Path sparse_dijkstra_heap;
    Path dense_kruskal;
    Path sparse_kruskal;
    
    for (i = 0; i < GRAPH_TESTED; ++i) {
        cout << "------------------------------------------------" << endl;
        cout << "NEW GROUP:" << endl;
        //generate dense and sparse graph
        ts = clock();
        Graph graph_sparse(6, 0);
        te = clock();
        cout << "time to generate sparse graph: " << (te -ts) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
        
        ts = clock();
        Graph graph_dense(0, 20);
        te = clock();
        cout << "time to generate dense graph: " << (te -ts) * 1000.0 / CLOCKS_PER_SEC << "ms" << endl;
        
        cout << "------------------------------------------------" << endl;
        
        for (j = 0; j < VX_TESTED; ++j) {
            int src = rand() % MAXVEX;
            int dst = rand() % MAXVEX;
            
            ts = clock();
            dense_dijkstra_pure = dijkstra_pure(&graph_dense, src, dst);
            te = clock();
            path_print(dense_dijkstra_pure);
            time[0] += (te -ts) * 1000.0 / CLOCKS_PER_SEC;
            
            ts = clock();
            sparse_dijkstra_pure = dijkstra_pure(&graph_sparse, src, dst);
            te = clock();
            path_print(sparse_dijkstra_pure);
            time[1] += (te -ts) * 1000.0 / CLOCKS_PER_SEC;
            
            ts = clock();
            dense_dijkstra_heap = dijkstra_heap(&graph_dense, src, dst);
            te = clock();
            path_print(dense_dijkstra_heap);
            time[2] += (te -ts) * 1000.0 / CLOCKS_PER_SEC;
            
            ts = clock();
            sparse_dijkstra_heap = dijkstra_heap(&graph_sparse, src, dst);
            te = clock();
            path_print(sparse_dijkstra_heap);
            time[3] += (te -ts) * 1000.0 / CLOCKS_PER_SEC;
            
            ts = clock();
            dense_kruskal = kruskal(&graph_dense, src, dst);
            te = clock();
            path_print(dense_kruskal);
            time[4] += (te -ts) * 1000.0 / CLOCKS_PER_SEC;
            
            ts = clock();
            sparse_kruskal = kruskal(&graph_sparse, src, dst);
            te = clock();
            path_print(sparse_kruskal);
            time[5] += (te -ts) * 1000.0 / CLOCKS_PER_SEC;
            
            cout << "------------------------------------------------" << endl;
        }
    }
    
    cout << endl << "Computing time:" << endl;
    
    cout << "dense_dijkstra_pure time: " << time[0] / (GRAPH_TESTED * VX_TESTED) << "ms" << endl;
    
    cout << "sparse_dijkstra_pure time: " << time[1] / (GRAPH_TESTED * VX_TESTED) << "ms" << endl << endl;
    
    cout << "dense_dijkstra_heap time: " << time[2] / (GRAPH_TESTED * VX_TESTED) << "ms" << endl;
    
    cout << "sparse_dijkstra_heap time: " << time[3] / (GRAPH_TESTED * VX_TESTED) << "ms" << endl << endl;
    
    cout << "dense_kruskal time: " << time[4] / (GRAPH_TESTED * VX_TESTED) << "ms" << endl;
    
    cout << "sparse_kruskal time: " << time[5] / (GRAPH_TESTED * VX_TESTED) << "ms" << endl << endl;

    return 0;
}