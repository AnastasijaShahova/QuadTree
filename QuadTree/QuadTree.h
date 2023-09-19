#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H

#include "Input.h"
#include "def.h"
#include <queue>

using namespace std;

class QuadTreeNode {
public:
    vector<QuadTreeNode*> children = vector<QuadTreeNode*>(4);
    Input data;
    int level;
    vector<float> box;

    QuadTreeNode(vector<float> boundary, int level);
    ~QuadTreeNode() {}
    void insert(Record);
    bool intersects(Record r);
    void rangeQuery(Record q);
    void divide();
    bool isLeaf();
};

#endif //QUADTREE_QUADTREE_H
