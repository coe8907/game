#include "enemy.h"



enemy::enemy(bitmap * passed_bitmap, bool p_solid,Object* t_target) : Object(passed_bitmap, p_solid)
{
    target = t_target;
    name = 'E';
}


enemy::~enemy()
{
	if (startNode)
	{
		delete startNode;
		startNode = nullptr;
	}
	if (targetNode)
	{
		delete targetNode;
		targetNode = nullptr;
	}
}

void enemy::findPath(maths::vector2 startPos, maths::vector2 targetPos)
{
    Uint32 start_time = SDL_GetTicks();
    if(startNode!=nullptr)delete startNode;
    if(targetNode!=nullptr)delete targetNode;
    
	startNode = new node(true, startPos);
	targetNode = new node(true, targetPos);



	startNode->gCost = 0;
	startNode->hCost = distance(startNode, targetNode);
	startNode->fcost = startNode->gCost + startNode->hCost + 1;
	openSet.push_back(startNode);

	//openSet.push_back(targetNode);

   

	while (openSet.size() > 0)
	{
        node* currentNode = openSet.back();
        for (int i = 1; i < openSet.size(); i++)
		{
			if (openSet[i]->fcost < currentNode->fcost) //|| openSet[i]->fcost == currentNode->fcost && openSet[i]->hCost < currentNode->hCost)
			{
				currentNode = openSet[i];
              
				
            }else{
                
            }
        }

		closedSet.push_back(currentNode);
       
        openSet.erase(std::find(openSet.begin(), openSet.end(), currentNode));
        
		if (currentNode->position.x == targetNode->position.x && currentNode->position.y == targetNode->position.y)
		{
			retracePath(startNode, currentNode);
            Uint32 time_taken = SDL_GetTicks() - start_time;
            closedSet.clear();
            openSet.clear();
            cout<< "time to find path = " << time_taken <<endl;
			return;
		}
        
       vector<node*> naihbours = getNodes(currentNode);
        for (int g = 0; g < naihbours.size(); g++){
		{
            node* neihbour = naihbours.at(g);
			auto findClosed = std::find(closedSet.begin(), closedSet.end(), neihbour);
			if (findClosed == closedSet.end())
			{
				int nextMoveCost = currentNode->gCost + distance(currentNode, neihbour);

				neihbour->fcost = nextMoveCost + distance(neihbour, targetNode);
				neihbour->parent = currentNode;

				auto findOpen = std::find(openSet.begin(), openSet.end(), neihbour);
				if (findOpen == openSet.end())
				{
					openSet.push_back(neihbour);
				}
			}
        }
		}

	}
}






void enemy::findObjects(std::vector<Object*> _collidableObjects)
{
    
	for (int i = 0; i < _collidableObjects.size(); i++)
	{
		collidableObjectsPos.push_back(new node(false, maths::vector2((int)(_collidableObjects[i]->get_x()/50),(int)( _collidableObjects[i]->get_y()/50))));
	}
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
            
        //    if(Nodes[i][j] != nullptr)delete Nodes[i][j];
         //   Nodes[i][j] = nullptr;
            Nodes[i][j] = new node(true, maths::vector2(i, j));
						
		}
	}
    for (int x = 0; x < collidableObjectsPos.size(); x++){
            Nodes[(int)collidableObjectsPos[x]->position.x][(int)collidableObjectsPos[x]->position.y]->walkable = false;
        
    }
}

float enemy::distance(node* a, node* b)
{
	float diffX = fabsf(b->position.x - a->position.x);
	float diffY = fabsf(b->position.y - a->position.y);

	return sqrt((diffX * diffX) + (diffY* diffY));

	//return abs(a->position.x - b->position.x) + abs(a->position.y - b->position.y);
}

void enemy::retracePath(node* start, node* t_target)
{
	
	//currentNode->parent = target->parent;
   
	while (t_target->position.x != start->position.x && t_target->position.y != start->position.y)
	{
        path.push_back(new maths::vector2(t_target->position.x,t_target->position.y));
		t_target= t_target->parent;
        if(t_target){
            
        }else{
            break;
        }
    }

	std::reverse(path.begin(), path.end());
    
}
void enemy::update(int xoffset, int yoffset) {
    m_bitmap->set_xoffset(xoffset);
    m_bitmap->set_yoffset(yoffset);
    executePath();
}

void enemy::executePath()
{
	if (pathIncrementer < path.size())
	{
        int t = 4;
        
       
        if((int)path[pathIncrementer]->x * 50 > (int)get_x()){
            get_bitmap()->move_Draw_Position(1,0);
            t--;
        }
        if((int)path[pathIncrementer]->x * 50 < (int)get_x()){
            get_bitmap()->move_Draw_Position(-1,0);
            t--;
        }
        if((int)path[pathIncrementer]->y * 50 > (int)get_y()){
            get_bitmap()->move_Draw_Position(0,1);
            t--;
        }
        if((int)path[pathIncrementer]->y * 50 < (int)get_y()){
            get_bitmap()->move_Draw_Position(0,-1);
            t--;
        }
        if(t >= 4){
            pathIncrementer++;
        }
        
    }
        path.clear();
        findPath(maths::vector2(get_x()/50,get_y()/50), maths::vector2(target->get_x()/50,target->get_y()/50));
        pathIncrementer = 0;
    
}



std::vector<node*> enemy::getNodes(node* pos)
{
	std::vector<node*> neighbourPos;
	

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0)
			{
				continue;
			}
			else {
                bool f = true;
				int checkPosX = pos->position.x + i;
				int checkPosY = pos->position.y + j;
                if(checkPosX >= 0 && checkPosX < sizeX){
                    if(checkPosY >= 0 && checkPosY < sizeY){
                        for (int i = 0; i < collidableObjectsPos.size(); i++)
                        {
                            if (checkPosX == collidableObjectsPos[i]->position.x && checkPosY == collidableObjectsPos[i]->position.y)
                            {
                                f = false;
                            }
                        }
                        if(f)neighbourPos.push_back(Nodes[checkPosX][checkPosY]);
                    }
                }
			}
		}
	}

	return neighbourPos;
}



