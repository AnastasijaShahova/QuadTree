#include "QuadTree.h"

QuadTreeNode::QuadTreeNode(vector<float> _boundary, int _level) {
    box = _boundary;
    level = _level;
}

//���������: �������� �� ������
bool QuadTreeNode::isLeaf() {
    if (children[NW] == NULL)
        return true;
    return false;
}

//������� ���������� ��������
void QuadTreeNode::insert(Record r) {
    if (isLeaf()) {
        data.push_back(r);
        if (data.size() > CAPACITY) {
            divide();
            for (auto rec : data) {
                auto c = children.begin();
                while (!(*c)->intersects(rec))
                    c++;
                (*c)->data.push_back(rec);
            }
            data.clear();
        }
    }
    else {
        auto c = children.begin();
        while (!(*c)->intersects(r))
            c++;
        (*c)->insert(r);
    }
}

//�����
void QuadTreeNode::divide() {

    float xMid, yMid;
    //��������� ������� �� ������� �����
    if (POINT_SPLIT) {
        data.sortData();
        auto median = data[data.size() / 2];
        xMid = median.box[XLOW];
        yMid = median.box[YLOW];
    }
    //����� ������� �� ������� ����������� �������
    else {
        xMid = (box[XHIGH] + box[XLOW]) / 2.0;
        yMid = (box[YHIGH] + box[YLOW]) / 2.0;
    }

    vector<float> northWest = { box[XLOW], yMid, xMid, box[YHIGH] };
    children[NW] = new QuadTreeNode(northWest, level + 1);

    vector<float> northEast = { xMid, yMid, box[XHIGH], box[YHIGH] };
    children[NE] = new QuadTreeNode(northEast, level + 1);

    vector<float> southWest = { box[XLOW], box[YLOW], xMid, yMid };
    children[SW] = new QuadTreeNode(southWest, level + 1);

    vector<float> southEast = { xMid, box[YLOW], box[XHIGH], yMid };
    children[SE] = new QuadTreeNode(southEast, level + 1);
}

bool QuadTreeNode::intersects(Record q) {
    return ((box[XLOW] < q.box[XHIGH] && q.box[XLOW] < box[XHIGH]) && (box[YLOW] < q.box[YHIGH] && q.box[YLOW] < box[YHIGH]));
}

//��������� ��� ��������� � ��������������� ���������� ���������
typedef struct rangePoint {
    array<float, 2> pt;
    int id;
    bool operator<(const rangePoint& second) const { return id > second.id; }
} rangePoint;

void QuadTreeNode::rangeQuery(Record q) {

    vector<rangePoint> tempPts(COUNT_NEIGHBOR);
    priority_queue<rangePoint, vector<rangePoint>> rngPts;

    //���������: �������� �� ������
    if (isLeaf()) {
        //���������: �������� �� �������� ������� ���  ���� (-90:90) � (-180:180)
        if (intersects(q)) {
            //���������� �� ���� ��������� ������ � ���������: ����� �� ��� ������ ��������� ���� � ���� ��: ��������� � �������
            for (auto r : data) {
                if (q.intersects(r)) {
                    rangePoint kPt;
                    kPt.pt = r.toKNNPoint();
                    kPt.id = r.id;
                    rngPts.push(kPt);
                }
            }
        }
    }
    //���� �� ����: �� �������� ������� ����������:���� �� ������ �� ������
    else {
        for (auto c : children) {
            if (c->intersects(q))
                c->rangeQuery(q);
        }
    }

    //����� ����������
    int size = 0;
    if (rngPts.size() > COUNT_NEIGHBOR) {
        size = rngPts.size() - COUNT_NEIGHBOR;
    }

    while(rngPts.size() != size ){
        cout << rngPts.top().pt[0] << " " << rngPts.top().pt[1] << " id:" << rngPts.top().id << endl;
        rngPts.pop();
    }
    return;
}