#pragma once
#include "vector2.h"

class node
{
    struct positions{
        int x;
        int y;
    };
public:
	node(bool _walkable, maths::vector2 pos);
	bool walkable;
	positions position;

	int gCost = 0;
	int hCost = 0;
	int fcost;

	node* parent = nullptr;

	~node();
};


