#include "Input.h"

Record::Record(int _id, vector<float> r) {
    id = _id;
    box[XLOW] = box[XHIGH] = r[XLOW];
    box[YLOW] = box[YHIGH] = r[YLOW];
}

Record::Record(vector<float> r) {
    box[XLOW] = r[XLOW];
    box[YLOW] = r[YLOW];
    box[XHIGH] = r[XHIGH];
    box[YHIGH] = r[YHIGH];
}

bool Record::operator<(const Record& b) const {
    if (box[XLOW] != b.box[XLOW])
        return box[XLOW] < b.box[XLOW];
    return box[YLOW] < b.box[YLOW];
}

bool Record::intersects(Record r) {
    return ((box[XLOW] < r.box[XHIGH] && r.box[XLOW] < box[XHIGH]) && (box[YLOW] > r.box[YHIGH] && r.box[YLOW] > box[YHIGH]));
}

array<float, 2> Record::toKNNPoint() { return array<float, 2>({ box[XLOW], box[YLOW] }); }

void Input::sortData() { sort(begin(), end()); }

void Input::loadData(const char* filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Cannot open the File : " << filename << endl;
        exit(1);
    }
    string line;
    while (getline(file, line)) {
        istringstream buf(line);
        float x, y, id;
        buf >> id >> x >> y;
        emplace_back(id, vector<float>({ x, y }));
    }
    file.close();
}