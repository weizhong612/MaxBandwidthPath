//
//  DataStructure.cpp
//  MaxBandwidthPath
//
//  Created by WeiZhong Chen on 3/26/14.
//  Copyright (c) 2014 WeiZhong Chen. All rights reserved.
//

#include "DataStructure.h"

VexType::VexType() {
    vertex_index = -1;
    bandwidth = 0;
}

VexType::VexType(int vx, double bw) {
    vertex_index = vx;
    bandwidth = bw;
}

bool VexType::operator<(const VexType& vex) {
    return (this->bandwidth < vex.bandwidth);
}

bool VexType::operator>(const VexType& vex) {
    return (this->bandwidth > vex.bandwidth);
}

bool VexType::operator==(const VexType& vex) {
    return (this->vertex_index == vex.vertex_index);
}

EdgeType::EdgeType() {
    vex1_index = -1;
    vex2_index = -1;
    bandwidth = 0;
}
EdgeType::EdgeType(int vx1, int vx2, double bw) {
    vex1_index = vx1;
    vex2_index = vx2;
    bandwidth = bw;
}

bool EdgeType::operator<(const EdgeType& vex) {
    return (this->bandwidth < vex.bandwidth);
}

bool EdgeType::operator>(const EdgeType& vex) {
    return (this->bandwidth > vex.bandwidth);
}

bool EdgeType::operator==(const EdgeType& vex) {
    return (this->vex1_index == vex.vex1_index && this->vex2_index == vex.vex2_index);
}