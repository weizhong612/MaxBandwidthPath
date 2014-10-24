//
//  DataStructure.h
//  MaxBandwidthPath
//
//  Created by WeiZhong Chen on 3/6/14.
//  Copyright (c) 2014 WeiZhong Chen. All rights reserved.
//

#ifndef MaxBandwidthPath_DataStructure_h
#define MaxBandwidthPath_DataStructure_h

#define MAXVEX 5000

struct VexNode {
    int vertex_index;
    double bandwidth;
    struct VexNode* next;
    
    VexNode() {
        vertex_index = -1;
        bandwidth = 0;
    }
    VexNode(int vx, double bw) {
        vertex_index = vx;
        bandwidth = bw;
        next = nullptr;
    }
};
typedef struct VexNode VexNode;

struct fringes {
    int vertex_index;
    double  bandwidth;
    fringes* prev;
    fringes* next;
    
    fringes() {
        vertex_index = -1;
        bandwidth = 0;
        prev = nullptr;
        next = nullptr;
    }
    fringes(int v, double bw) {
        vertex_index = v;
        bandwidth = bw;
        prev = nullptr;
        next = nullptr;
    }
};
typedef struct fringes fringes;

struct Path {
    int vertex_index[MAXVEX];
    double bandwidth;
    
    Path() {
        for (int i = 0; i < MAXVEX; i++) {
            vertex_index[i] = -1;
        }
        bandwidth = 0;
    }
};
typedef struct Path Path;

class VexType {
public:
    int vertex_index;
    double bandwidth;
    
    VexType();
    VexType(int, double);
    ~VexType() {};
    bool operator<(const VexType&);
    bool operator>(const VexType&);
    bool operator==(const VexType&);
};

class EdgeType {
public:
    int vex1_index;
    int vex2_index;
    double bandwidth;

    EdgeType();
    EdgeType(int, int, double);
    ~EdgeType() {};
    bool operator<(const EdgeType&);
    bool operator>(const EdgeType&);
    bool operator==(const EdgeType&);
};

#endif
