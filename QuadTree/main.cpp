#include "Input.h"
#include "QuadTree.h"
#include <random>

const vector<float> boundary = { -180.0, -90.0, 180.0, 90.0 };

int main(int argc, char** argv) {

	float x, y;
    QuadTreeNode* tree = new QuadTreeNode(boundary, 0);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist_x(-180, 180);
	std::uniform_real_distribution<> dist_y(-90, 90);

    for (int i = 0; i < CAPACITY; i++) {
        x = dist_x(gen);
        y = dist_y(gen);
        tree->insert({ i + 1, vector<float>({ x, y }) });
        cout << x << " " << y << " id:" << i + 1 << endl;
    }

    float xl, yl, xh, yh;
    std::cout << "Enter x1,y1,x2,y2 for region" << std::endl;
    //-80.1 10.2 1.3563 -10.8542 
    std::cin >> xl >> yl >> xh >> yh;
    Record query { vector<float>({ xl, yl, xh, yh })};

    tree->rangeQuery(query);

    return 0;
}
