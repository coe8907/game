#include "node.h"

node::node(bool _walkable, maths::vector2 pos)
{
	walkable = _walkable;
	position.x = pos.x;
    position.y = pos.y;
}

node::~node()
{
}
