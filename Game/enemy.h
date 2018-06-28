#pragma once
#include "Object.h"
#include "node.h"
#include <list>
#include <algorithm>
using namespace std;
class enemy :
	public Object
{

	

public:
    void update(int xoffset, int yoffset);

	enemy(bitmap * passed_bitmap, bool p_solid,Object * target);
	~enemy();

	void findPath(maths::vector2 startPos, maths::vector2 targetPos);
	void findObjects(std::vector<Object*> _collidableObjects);

	float distance(node* a, node* b);
	void retracePath(node* start, node* target);
	std::vector<maths::vector2*> path;
	
	void executePath();
private:
    Object * target;
	std::vector<node*> openSet;
	std::vector<node*> closedSet;

	std::vector<node*>collidableObjectsPos;
	vector<node*> * final_path;

	static const int sizeX = 30;
	static const int sizeY = 30;

	std::vector<node*> getNodes(node* pos);
	
	bool findingPath = false;
	node* startNode = nullptr;
	node* targetNode = nullptr;
	node* Nodes[sizeX][sizeY];
	int pathIncrementer = 0;
};

