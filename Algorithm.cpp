//
//  Algorithm.cpp
//  MaxBandwidthPath
//
//  Created by WeiZhong Chen on 3/6/14.
//  Copyright (c) 2014 WeiZhong Chen. All rights reserved.
//

#include "Algorithm.h"

Path construct(std::vector<int>& dad, std::vector<double>& bw, int src_index, int dst_index) {
    Path result;
    result.bandwidth = bw[dst_index];
    int path_node_index = dst_index;
    int i = 0;
    while (path_node_index != src_index) {
        if (path_node_index == -1) {
            Path invalid;
            return invalid;
        }
        result.vertex_index[i] = path_node_index;
        if (result.bandwidth > bw[path_node_index]) {
            result.bandwidth = bw[path_node_index];
        }
        path_node_index = dad[path_node_index];
        ++i;
    }
    result.vertex_index[i] = path_node_index;
    int vertex_no = i;
    //reverse the whole path
    for (i = 0; i < vertex_no / 2 + 1; ++i) {
        mySwap(result.vertex_index[i], result.vertex_index[vertex_no-i]);
    }
    return result;
}

void path_print(Path p) {
    if (p.bandwidth == 0) {
        std::cout << "The graph is not connected!" << std::endl;
        return;
    }
    /*
    std::cout << "Path: " << std::endl;
    int i;
    for (i = 0; p.vertex_index[i+1] != -1; ++i) {
        std::cout << p.vertex_index[i] << "->";
    }
    std::cout << p.vertex_index[i] << std::endl;
    */
    std::cout << "bandwidth: " << p.bandwidth << std::endl;
}

Path dijkstra_pure(Graph* G, int src_index, int dst_index) {
    enum status {intree, fringe, unseen};
    std::vector<status> state;
    state.reserve(MAXVEX * sizeof(status));
    std::vector<double> bw;
    bw.reserve(MAXVEX * sizeof(double));
    std::vector<int> dad;
    dad.reserve(MAXVEX * sizeof(int));
    fringes* f_head = new fringes();
    fringes* f_tail = f_head;
   
    int i;
    
    //initialization
    for (i = 0; i < MAXVEX; ++i) {
        bw.push_back(0);
        dad.push_back(-1);
        state.push_back(unseen);
    }
    
    //set up source
    state[G->vexnode[src_index].vertex_index] = intree;
    bw[G->vexnode[src_index].vertex_index] = std::numeric_limits<double>::max();   //infinity
    dad[src_index] = src_index;
    
    //set up all the vertices adjacent to source
    VexNode* v_iter = G->vexnode[src_index].next;
    while (v_iter != nullptr) {
        //change the status to fringe
        state[v_iter->vertex_index] = fringe;
        //add it to the fringe list
        fringes* new_fringe = new fringes(v_iter->vertex_index, v_iter->bandwidth);
        f_tail->next = new_fringe;
        new_fringe->prev = f_tail;
        f_tail = new_fringe;
        //set its bandwidth and dad information
        bw[v_iter->vertex_index] = v_iter->bandwidth;
        dad[v_iter->vertex_index] = src_index;
        v_iter = v_iter->next;
    }
    
    //main step
    while (f_head->next != nullptr) {   //there still exist fringes
        //get the fringe with the largest bandwidth
        fringes* f_iter = f_head;
        int max_index = f_iter->vertex_index;
        double max_bw = f_iter->bandwidth;
        while (f_iter != nullptr) {
            if (f_iter->bandwidth > max_bw) {
                max_bw = f_iter->bandwidth;
                max_index = f_iter->vertex_index;
            }
            f_iter = f_iter->next;
        }
        //set its status to intree
        state[max_index] = intree;
        //if this is the destination node, stop finding
        if (max_index == dst_index) {
            break;
        }
        //remove it from the fringe list
        f_iter = f_head->next;
        while (f_iter != nullptr) {
            if (f_iter->vertex_index == max_index) {   //find the fringe
                if (f_iter->next != nullptr) {   //if the fringe is not the last one on the list
                    f_iter->prev->next = f_iter->next;
                    f_iter->next->prev = f_iter->prev;
                } else {   //if the fringe is the last one on the list
                    f_tail = f_tail->prev;
                    f_tail->next = nullptr;
                }
                delete f_iter;
                f_iter = nullptr;
                break;
            }
            f_iter = f_iter->next;
        }
        //check every edge goes from this vertex
        v_iter = G->vexnode[max_index].next;
        while (v_iter != nullptr) {
            if (state[v_iter->vertex_index] == unseen) {
                state[v_iter->vertex_index] = fringe;
                //insert it to fringe list
                f_tail->next = new fringes(v_iter->vertex_index, v_iter->bandwidth);
                f_tail->next->prev = f_tail;
                f_tail = f_tail->next;
                bw[v_iter->vertex_index] = min(bw[max_index], v_iter->bandwidth);
                dad[v_iter->vertex_index] = max_index;
            } else if (state[v_iter->vertex_index] == fringe &&
                     bw[v_iter->vertex_index] < min(bw[max_index], v_iter->bandwidth)) {
                bw[v_iter->vertex_index] = min(bw[max_index], v_iter->bandwidth);
                //edit the fringe on the list
                f_iter = f_head->next;
                while (f_iter != nullptr) {
                    if (f_iter->vertex_index == v_iter->vertex_index) {   //find the fringe
                        f_iter->bandwidth = bw[v_iter->vertex_index];
                        break;
                    }
                    f_iter = f_iter->next;
                }
                dad[v_iter->vertex_index] = max_index;
            }
            v_iter = v_iter->next;
        }
    }
    
    //construct the path
    Path result;
    result = construct(dad, bw, src_index, dst_index);
    
    return result;
}

Path dijkstra_heap(Graph* G, int src_index, int dst_index) {
    enum status {intree, fringe, unseen};
    std::vector<status> state;
    state.reserve(MAXVEX * sizeof(status));
    std::vector<double> bw;
    bw.reserve(MAXVEX * sizeof(double));
    std::vector<int> dad;
    dad.reserve(MAXVEX * sizeof(int));
    long h_index[MAXVEX];   //record the heap index
    Heap<VexType> fringes;
    
    int i;
    
    //initialization
    for (i = 0; i < MAXVEX; ++i) {
        bw.push_back(0);
        dad.push_back(-1);
        state.push_back(unseen);
        h_index[i] = -1;
    }
    
    //set up source
    state[G->vexnode[src_index].vertex_index] = intree;
    bw[G->vexnode[src_index].vertex_index] = std::numeric_limits<double>::max();   //infinity
    dad[src_index] = src_index;
    
    //set up all the vertices adjacent to source
    VexNode* v_iter = G->vexnode[src_index].next;
    while (v_iter != nullptr) {
        //change the status to fringe
        state[v_iter->vertex_index] = fringe;
        //add it to the fringe list
        VexType new_fringe(v_iter->vertex_index, v_iter->bandwidth);
        fringes.insert(new_fringe, h_index);
        //set its bandwidth and dad information
        bw[v_iter->vertex_index] = v_iter->bandwidth;
        dad[v_iter->vertex_index] = src_index;
        v_iter = v_iter->next;
    }
    
    //main step
    while (fringes.get_current_no() > 0) {   //there still exist fringes
        //get the fringe with the largest bandwidth
        VexType max_fringe = fringes.Max();
        int max_index = max_fringe.vertex_index;
        //remove it from the fringe list
        fringes.remove(0, h_index);

        //set its status to intree
        state[max_index] = intree;
        //if this is the destination node, stop finding
        if (max_index == dst_index) {
            break;
        }
        
        //check every edge goes from this vertex
        v_iter = G->vexnode[max_index].next;
        while (v_iter != nullptr) {
            if (state[v_iter->vertex_index] == unseen) {
                state[v_iter->vertex_index] = fringe;
                //insert it to fringe heap
                bw[v_iter->vertex_index] = min(bw[max_index], v_iter->bandwidth);
                VexType new_fringe(v_iter->vertex_index, bw[v_iter->vertex_index]);
                fringes.insert(new_fringe, h_index);
                dad[v_iter->vertex_index] = max_index;
            } else if (state[v_iter->vertex_index] == fringe &&
                     bw[v_iter->vertex_index] < min(bw[max_index], v_iter->bandwidth)) {
                //edit the fringe on the heap
                VexType old_fringe(v_iter->vertex_index, bw[v_iter->vertex_index]);
                fringes.remove(h_index[v_iter->vertex_index], h_index);
                bw[v_iter->vertex_index] = min(bw[max_index], v_iter->bandwidth);
                VexType new_fringe(v_iter->vertex_index, bw[v_iter->vertex_index]);
                fringes.insert(new_fringe, h_index);
                dad[v_iter->vertex_index] = max_index;
            }
            v_iter = v_iter->next;
        }
    }
    
    //construct the path
    Path result;
    result = construct(dad, bw, src_index, dst_index);
    
    return result;
}


void heap_sort(std::vector<EdgeType>& arr) {
    Heap<EdgeType> h;
    int i;
    long* dummy = nullptr;
    
    for (i = 0; i < arr.size(); ++i) {
        h.insert(arr[i], dummy);
    }
    for (i = 0; i < arr.size(); ++i) {
        EdgeType max_edge = h.Max();
        arr[i] = max_edge;
        h.remove(0, dummy);
    }
}

int Find(std::vector<int>& dad, std::vector<int>& rank, int vertex_index) {
    int root;
    int path = vertex_index;
    while (dad[path] != -1) {   //find until reach the root
        path = dad[path];
    }
    root = path;
    path = vertex_index;
    while (dad[path] != -1) {
        int tmp = dad[path];
        dad[path] = root;
        path = tmp;
    }
    return root;
}

void Union(std::vector<int>& rank, std::vector<int>& dad, int root1, int root2) {
    if (rank[root1] < rank[root2]) {
        dad[root1] = root2;
    } else if (rank[root1] > rank[root2]) {
        dad[root2] = root1;
    } else if (rank[root1] == rank[root2]) {
        dad[root2] = root1;
        rank[root1]++;
    }
}

Path kruskal(Graph* G, int src_index, int dst_index) {
    int i;
    std::vector<EdgeType> edges;
    edges.reserve(MAXVEX * MAXVEX * sizeof(EdgeType));
    std::vector<int> dad;
    dad.reserve(MAXVEX * sizeof(int));
    std::vector<int> rank;
    rank.reserve(MAXVEX * sizeof(int));
    
    for (i = 0; i < MAXVEX; ++i) {
        VexNode* v_iter = G->vexnode[i].next;
        while (v_iter != nullptr) {
            if (i < v_iter->vertex_index) {
                EdgeType new_edge(i, v_iter->vertex_index, v_iter->bandwidth);
                edges.push_back(new_edge);
            }
            v_iter = v_iter->next;
        }
    }
    
    //sort all edges based on quick sort
    heap_sort(edges);
    //sort(edges.begin(), edges.end(), compare());
    
    //initialization
    std::vector<int> max_span_tree;
    max_span_tree.reserve(MAXVEX * sizeof(int));
    
    //Make Set
    for (i = 0; i < MAXVEX; ++i) {
        dad.push_back(-1);
        rank.push_back(0);
    }
    
    //main step
    int current_mst_no = 0;
    for (i = 0; i < edges.size(); ++i) {
        EdgeType current_edge = edges[i];
        int root1_index = Find(dad, rank, current_edge.vex1_index);
        int root2_index = Find(dad, rank, current_edge.vex2_index);
        if (root1_index != root2_index) {
            max_span_tree.push_back(i);   //record the edge index
            current_mst_no++;
            Union(rank, dad, root1_index, root2_index);
            if (current_mst_no > MAXVEX) {
                //break;
            }
        }
    }
    
    //construct the max-spanning-tree
    Graph mst;
    VexNode* tail[MAXVEX];
    for (i = 0; i < MAXVEX; ++i) {
        tail[i] = &mst.vexnode[i];
    }
    
    //add every edge in mst graph
    for (i = 0; i < current_mst_no; ++i) {
        int src_index = edges[max_span_tree[i]].vex1_index;
        int dst_index = edges[max_span_tree[i]].vex2_index;
        double bw = edges[max_span_tree[i]].bandwidth;
        
        VexNode* new_vex1 = new VexNode(dst_index, bw);
        VexNode* new_vex2 = new VexNode(src_index, bw);
        tail[src_index]->next = new_vex1;
        tail[src_index] = new_vex1;
        tail[dst_index]->next = new_vex2;
        tail[dst_index] = new_vex2;
    }
    
    //get the max-bandwidth-path by using bfs
    std::vector<int> father;
    father.reserve(MAXVEX * sizeof(int));
    std::vector<bool> visited;
    visited.reserve(MAXVEX * sizeof(bool));
    std::vector<double> bw;
    bw.reserve(MAXVEX * sizeof(double));
    std::queue<int> q;
    
    for (i = 0; i < MAXVEX; ++i) {
        father.push_back(-1);
        visited.push_back(false);
        bw.push_back(std::numeric_limits<double>::max());
    }
    
    visited[src_index] = true;
    q.push(src_index);
    
    while (!q.empty()) {
        int tmp_vx_index = q.front();
        q.pop();
        if (tmp_vx_index == dst_index) {   //find the destination node
            break;
        } else {
            VexNode* v_iter = mst.vexnode[tmp_vx_index].next;
            while (v_iter != nullptr) {
                if (visited[v_iter->vertex_index] == false) {
                    q.push(v_iter->vertex_index);
                    visited[v_iter->vertex_index] = true;
                    bw[v_iter->vertex_index] = min(bw[tmp_vx_index], v_iter->bandwidth);
                    father[v_iter->vertex_index] = tmp_vx_index;
                }
                v_iter = v_iter->next;
            }
        }
    }
    
    //construct the path
    Path result;
    result = construct(father, bw, src_index, dst_index);
    
    return result;
}