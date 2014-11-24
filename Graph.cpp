//
//  Graph.cpp
//  MaxBandwidthPath
//
//  Created by WeiZhong Chen on 3/6/14.
//  Copyright (c) 2014 WeiZhong Chen. All rights reserved.
//

#include "Graph.h"

Graph::Graph() {
    vexnode = new VexNode[MAXVEX];
    for (int i = 0; i < MAXVEX; ++i) {
        vexnode[i].vertex_index = i;
        vexnode[i].bandwidth = std::numeric_limits<double>::max();
        vexnode[i].next = nullptr;
    }
}

Graph::Graph(int degree, double percent_edge) {
    //initialization
    vexnode = new VexNode[MAXVEX];
    for (int i = 0; i < MAXVEX; ++i) {
        vexnode[i].vertex_index = i;
        vexnode[i].bandwidth = std::numeric_limits<double>::max();
        vexnode[i].next = nullptr;
    }
    //check the constructor argument
    if ((!degree && !percent_edge) || (degree && percent_edge)) {   //only one can be nonzero
        return;
    } else if (degree) {   //construct the graph according to given degree
        int i;
        int available_vex[MAXVEX];
        VexNode* v_tail[MAXVEX];
        for (i = 0; i < MAXVEX; ++i) {
            available_vex[i] = i;
            v_tail[i] = &vexnode[i];
        }
        for (i = 0; i < degree / 2; ++i) {
            int availabe_no = MAXVEX;
            int joint_vx_index = rand() % availabe_no;
            int joint_vx = available_vex[joint_vx_index];
            int first_vx = joint_vx;
            --availabe_no;
            mySwap(available_vex[joint_vx_index], available_vex[availabe_no]);
            while (availabe_no > 0) {
                //generate 2 vertices
                int new_vx_index = rand() % availabe_no;
                int new_vx = available_vex[new_vx_index];
                //check if the edge already exists
                bool exist = false;
                VexNode* v_iter = vexnode[joint_vx].next;
                while (v_iter != nullptr) {
                    if (v_iter->vertex_index == new_vx) {
                        exist = true;
                        break;
                    }
                    v_iter = v_iter->next;
                }
                if (exist) {
                    continue;   //generate again
                }
                --availabe_no;
                mySwap(available_vex[new_vx_index], available_vex[availabe_no]);
                
                double rand_bw = rand() % 5000 + rand() % 1000 * 0.001;
                VexNode* vx1 = new VexNode(joint_vx, rand_bw);
                VexNode* vx2 = new VexNode(new_vx, rand_bw);
                v_tail[joint_vx]->next = vx2;
                v_tail[joint_vx] = vx2;
                v_tail[new_vx]->next = vx1;
                v_tail[new_vx] = vx1;
                
                joint_vx = new_vx;
            }
            double rand_bw = rand() % 5000 + rand() % 1000 * 0.001;
            VexNode* vx1 = new VexNode(first_vx, rand_bw);
            VexNode* vx2 = new VexNode(joint_vx, rand_bw);
            v_tail[first_vx]->next = vx2;
            v_tail[first_vx] = vx2;
            v_tail[joint_vx]->next = vx1;
            v_tail[joint_vx] = vx1;
        }
    } else if (percent_edge) {   //construct the graph according to given percentage of edge
        int i;
        VexNode* v_tail[MAXVEX];
        for (i = 0; i < MAXVEX; ++i) {
            v_tail[i] = &vexnode[i];
        }
        for (i = 0; i < MAXVEX; ++i) {
            for (int j = i + 1; j < MAXVEX; j++) {
                if (rand() % 1000 < percent_edge * 10) {
                    double rand_bw = rand() % 5000 + rand() % 1000 * 0.001;
                    VexNode* new_vx1 = new VexNode(i, rand_bw);
                    VexNode* new_vx2 = new VexNode(j, rand_bw);
                    v_tail[i]->next = new_vx2;
                    v_tail[i] = new_vx2;
                    v_tail[j]->next = new_vx1;
                    v_tail[j] = new_vx1;
                }
            }
        }
    }
}

Graph::~Graph() {
    int i;
    for (i = 0; i < MAXVEX; ++i) {
        VexNode* v_it = vexnode[i].next;
        while (v_it != nullptr) {
            if (v_it->next != nullptr) {
                VexNode* v_it_next = v_it->next;
                delete v_it;
                v_it = v_it_next;
            } else {
                delete v_it;
                v_it = nullptr;
            }
        }
    }
    delete [] vexnode;
}