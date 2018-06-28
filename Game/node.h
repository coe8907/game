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

	float gCost = 0;
	float hCost = 0;
	float fcost;

	node* parent = nullptr;

	~node();
};


