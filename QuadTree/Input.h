#ifndef QUADTREE_INPUT_H
#define QUADTREE_INPUT_H

#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <sstream>
#include <iostream>
#include "def.h"

using namespace std;

class Record {
public:
    int id = 0;
    vector<float> box = vector<float>(4);

    Record() {}
    ~Record() {}
    Record(int _id, vector<float> r);
    Record(vector<float> boundary); 
    bool operator < (const Record& rhs) const;
    bool intersects(Record r);
    array<float, 2> toKNNPoint();
};


class Input : public vector<Record>
{
public:
    Input() {}
    ~Input() {}
    void loadData(const char* filename);
    void sortData();
};

#endif //QUADTREE_INPUT_H