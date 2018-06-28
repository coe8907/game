#include "World.h"


World::World()
{
	xoffset = 0;
	yoffset = 0;
	/* get the level information from file */
	World_Gen* Temp = new World_Gen();
	vector<int>* temp_level = Temp->Load_world("assets/fire_fire_tiles.bmp");
	vector<int>* temp_objects = Temp->Load_objects("assets/fire_fire_objects.bmp");
	vector<World_Gen::area>*temp_areas = Temp->get_tiles("assets/game_master_sprites.bmp");
	
	/* add chunk to fit level*/
    chunks = new vector<chunk>;
	chunk t;
    t.x_pos = -100; t.y_pos = -100; t.width = Temp->get_width()*tile_draw_size +100; t.height = Temp->get_width()*tile_draw_size + 100;
    t.box = new Object(bitmap_manager.create_bitmap("assets/black.bmp", 100, 100,true),false);
	chunks->push_back(t);

	/*split the chunk to 4*/
	Split_Chunk(&t);

	for (int x = 0; x < Temp->get_width(); x++) {
		for (int y = 0; y < Temp->get_width(); y++) {
			int temp_tile_id = temp_level->at(y*Temp->get_width() + x);
			if (temp_tile_id == 16711935) {
				temp_tile_id = 0;
			}
			else {
				World_Gen::area Area = temp_areas->at(temp_tile_id);
				wall = new Object(bitmap_manager.create_bitmap("assets/game_master_sprites.bmp", 200, 200, false), false);
				wall->get_bitmap()->set_Load_Position(Area.x, Area.y, Area.endx - Area.x, Area.endy - Area.y);
				wall->get_bitmap()->set_Draw_Dimensions(tile_draw_size, tile_draw_size);
				wall->get_bitmap()->set_Draw_Position(x *tile_draw_size, y *tile_draw_size);
				place_object_in_chunk(wall);
			}
		}
	}
	temp_areas = Temp->get_objects("assets/game_objects.bmp");
	for (int x = 0; x < Temp->get_width(); x++) {
		for (int y = 0; y < Temp->get_width(); y++) {
			int temp_tile_id = temp_objects->at(y*Temp->get_width() + x);
			if (temp_tile_id == 16711935) {
				temp_tile_id = 0;
			}
			else {
				World_Gen::area Area = temp_areas->at(temp_tile_id);
				wall = new Object(bitmap_manager.create_bitmap("assets/game_objects.bmp", 200, 200, true), true);
				wall->get_bitmap()->set_Load_Position(Area.x, Area.y, Area.endx - Area.x, Area.endy - Area.y);
				wall->get_bitmap()->set_Draw_Dimensions(tile_draw_size, tile_draw_size);
				wall->get_bitmap()->set_Draw_Position(x *tile_draw_size, y *tile_draw_size);
				place_object_in_chunk(wall);
			}
		}
	}
	player = new Player(bitmap_manager.create_bitmap("assets/black.bmp", 200, 200, true), true,0);
	player->get_bitmap()->set_Load_Position(0,0, 50,50);
	player->get_bitmap()->set_Draw_Dimensions(50,50);
	player->get_bitmap()->set_Draw_Position(200,200);
	place_object_in_chunk(player);

	Enemy = new enemy(bitmap_manager.create_bitmap("assets/black.bmp", 200, 200, true), true,player);
	Enemy->get_bitmap()->set_Load_Position(0, 0, 50, 50);
	Enemy->get_bitmap()->set_Draw_Dimensions(50, 50);
	Enemy->get_bitmap()->set_Draw_Position(10, 10);
	place_object_in_chunk(Enemy);

	Enemy->findObjects(get_all_objects());
	Enemy->findPath(maths::vector2(Enemy->get_x()/50, Enemy->get_y()/50), maths::vector2(player->get_x()/50, player->get_y()/50));
}


World::~World()
{
    chunks->clear();
   // box = nullptr;
}

void World::paint()
{
	draw_chunks();
    for(int i = 0; i < chunks->size(); i ++){
		for (int j = 0; j < chunks->at(i).no_colision_objects.size(); j++) {
			chunks->at(i).no_colision_objects.at(j)->draw();
		}
        for(int j = 0; j < chunks->at(i).objects.size(); j ++){
            chunks->at(i).objects.at(j)->draw();
        }
    }
	
}
vector<Object*> World::get_all_objects() {
	vector<Object*> return_obj;
	for (int i = 0; i < chunks->size(); i++) {
		for (int j = 0; j < chunks->at(i).objects.size(); j++) {
            if(chunks->at(i).objects.at(j)->name == 'O'){return_obj.push_back(chunks->at(i).objects.at(j));}
		}
	}
	return return_obj;
}
void World::update()
{
	for (int i = 0; i < chunks->size(); i++) {
		for (int j = 0; j < chunks->at(i).no_colision_objects.size(); j++) {
			chunks->at(i).no_colision_objects.at(j)->update(xoffset, yoffset);
			//chunks->at(i).no_colision_objects.at(j)->get_bitmap()->set_xoffset(xoffset);
			//chunks->at(i).no_colision_objects.at(j)->get_bitmap()->set_yoffset(yoffset);
		}
		for (int j = 0; j < chunks->at(i).objects.size(); j++) {
			chunks->at(i).objects.at(j)->update(xoffset, yoffset);
			//chunks->at(i).objects.at(j)->get_bitmap()->set_xoffset(xoffset);
			//chunks->at(i).objects.at(j)->get_bitmap()->set_yoffset(yoffset);
		}
	}
    check_colision();
	check_chunks();
	// Enemy->executePath(); <<< no bad ed .... you should have used the vertial update funtion 
	
}

void World::create_world(string level_url)
{
    
}
void World::check_colision()
{
    int total = 0;
    for (int i = 0; i < chunks->size(); i++) {
        total = chunks->at(i).objects.size();
        //	std::cout << "chunk count " << chunks->at(i).objects.size()<<std::endl;
        if (chunks->at(i).objects.size() > 0) {
            for (int a = 0; a < total; a++) {
                for (int b = 0; b < total; b++) {
                    Object * test1 = chunks->at(i).objects.at(a);
                    Object * test2 = chunks->at(i).objects.at(b);
                    if (test1 != test2) {
                        if (check_for_overlap_center(test1->get_bitmap()->getxpos() + test1->xspeed, test1->get_bitmap()->getypos() + test1->yspeed, test1->get_bitmap()->getwidth(), test1->get_bitmap()->getheight(), test2->get_bitmap()->getxpos() + test2->xspeed, test2->get_bitmap()->getypos() + test2->yspeed, test2->get_bitmap()->getwidth(), test2->get_bitmap()->getheight())) {
                            if (test1->get_bitmap()->get_trans() && test2->get_bitmap()->get_trans()) {
                              
                                if (Colision_with_trans(chunks->at(i).objects.at(a), chunks->at(i).objects.at(b)) ) {
                                    //test1->colision(test2);
                                    test2->colision(test1);
                                }
                            }
                            else {
                                //test1->colision(test2);
                                test2->colision(test1);
                            }
                        }
                    }
                }
            }
        }
    }
    //std::cout << "chunk object count = " << total << endl;
}
bool World::Colision_with_trans(Object * test1, Object * test2) {
    if (test1->xspeed > -11 && test1->xspeed < 11) {
        int com_mask[Max_image_size * 2  + 5][Max_image_size * 2 +5];
        for (int x = 0; x < Max_image_size * 2 +5; x++) {
            for (int y = 0; y < Max_image_size * 2+5; y++) {
                com_mask[x][y] = 0;
                
            }
        }
        int dif = abs(test1->get_x() - test2->get_x());
        int dify = abs(test1->get_y() - test2->get_y());
        for (int x = 0; x < Max_image_size-1; x++) {
            for (int y = 0; y < Max_image_size-1; y++) {
                if (test1->get_x() > test2->get_x() && test1->get_y() > test2->get_y()) {
                    com_mask[x][y] += test1->get_bitmap()->get_colision_mask()->at(x + y*Max_image_size);
                    com_mask[x + dif][y + dify] += test2->get_bitmap()->get_colision_mask()->at(x + y*Max_image_size);
                }
                if (test1->get_x() > test2->get_x() && test1->get_y() < test2->get_y()) {
                    com_mask[x][y + dify] += test1->get_bitmap()->get_colision_mask()->at(x + y*Max_image_size);
                    com_mask[x + dif][y] += test2->get_bitmap()->get_colision_mask()->at(x + y*Max_image_size);
                }
                if (test1->get_x() < test2->get_x() && test1->get_y() > test2->get_y()) {
                    com_mask[x + dif][y] += test1->get_bitmap()->get_colision_mask()->at(x + y*Max_image_size);
                    com_mask[x][y + dify] += test2->get_bitmap()->get_colision_mask()->at(x + y*Max_image_size);
                }
                if (test1->get_x() < test2->get_x() && test1->get_y() < test2->get_y()) {
                    com_mask[x][y] += test2->get_bitmap()->get_colision_mask()->at(x + y*Max_image_size);
                    com_mask[x + dif][y + dify] += test1->get_bitmap()->get_colision_mask()->at(x + y*Max_image_size);
                }	
            }
        }
        for (int x = 0; x < Max_image_size * 2; x++) {
            for (int y = 0; y < Max_image_size * 2; y++) {
                if (com_mask[x][y] > 1) {
                    return true;
                }
            }
        }
    }
    else {
        cout << "wtf" << endl;
    }
    
    return false;
}

/* returns true if there is a overlap */
bool World::check_for_overlap(int x1,int y1,int w1, int h1, int x2,int y2,int w2,int h2) {
	if (x2 + w2 < x1) { return false; }
	if (y2 + h2 < y1) { return false; }
	int xdif = abs(x1 -x2);
	int ydif = abs(y1-y2); 
	int wid = w1 +w2;
	int hig = h1 +h2;
	if (xdif < wid && ydif < hig) { return true; }
	
	
	return false;
}
bool World::check_for_overlap_center(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
	int xdif = abs(x1 - x2);
	int ydif = abs(y1 - y2);
	int wid = w1 + w2;
	int hig = h1 + h2;
	if (xdif < wid / 2 && ydif < hig / 2) { return true; }
	return false;
}



/* Merges all the objects from chunk 2 in to chunk 1 and resizes chunk 1 to cover the old area of chunk 2 */
void World::merge_chunks(chunk * chunk_1, chunk * chunk_2)
{
	if (chunk_1->x_pos == chunk_2->x_pos || chunk_1->y_pos == chunk_2->y_pos) { // is it posable to merge the chunks
		if (chunk_1->x_pos == chunk_2->x_pos) {
			chunk_1->y_pos += chunk_2->height;
		}
		if (chunk_1->y_pos == chunk_2->y_pos) {
			chunk_1->x_pos += chunk_2->height;
		}
		for (int i = 0; i < chunk_2->objects.size(); i++) {
			chunk_1->objects.push_back(chunk_2->objects.at(i));
		}
		remove_chunk(chunk_2);
	}
	else {
		// not posable to merge chunks//
	}
}
void World::Split_Chunk(chunk* chunk_to_split){
    int x = chunk_to_split->x_pos;
    int y = chunk_to_split->y_pos;
    int w = chunk_to_split->width;
    int h = chunk_to_split->height;
    create_chunk(x + w/2,y,w/2,h/2);
    create_chunk(x + w/2,y + h/2,w/2,h/2);
    create_chunk(x,y + h/2,w/2,h/2);
}

/* checks that the chunk contains only the needed objects */
/* it then moves the uneeded objects to the needed chunk  */
void World::check_chunks()
{
	vector<Object* > unchunked_objects;

	chunk * current_test_chunk;
	for (int a = 0; a < chunks->size(); a++) {
		current_test_chunk = &chunks->at(a);

		for (int i = 0; i < current_test_chunk->objects.size(); i++) {
			if (check_for_overlap(current_test_chunk->x_pos, current_test_chunk->y_pos, current_test_chunk->width, current_test_chunk->height, current_test_chunk->objects.at(i)->get_bitmap()->getxpos(), current_test_chunk->objects.at(i)->get_bitmap()->getypos(), current_test_chunk->objects.at(i)->get_bitmap()->getwidth(), current_test_chunk->objects.at(i)->get_bitmap()->getheight())) {
				
			}
			else {
				unchunked_objects.push_back(current_test_chunk->objects.at(i));
				current_test_chunk->objects.erase(current_test_chunk->objects.begin() + i);
			}
		}

		for (int i = 0; i < current_test_chunk->no_colision_objects.size(); i++) {
			if (check_for_overlap(current_test_chunk->x_pos, current_test_chunk->y_pos, current_test_chunk->width, current_test_chunk->height, current_test_chunk->no_colision_objects.at(i)->get_bitmap()->getxpos(), current_test_chunk->no_colision_objects.at(i)->get_bitmap()->getypos(), current_test_chunk->no_colision_objects.at(i)->get_bitmap()->getwidth(), current_test_chunk->no_colision_objects.at(i)->get_bitmap()->getheight())) {

			}
			else {
				unchunked_objects.push_back(current_test_chunk->no_colision_objects.at(i));
				current_test_chunk->no_colision_objects.erase(current_test_chunk->no_colision_objects.begin() + i);
			}
		}
		current_test_chunk->objects.shrink_to_fit();
		current_test_chunk->no_colision_objects.shrink_to_fit();
	}
	for (int i = 0; i < unchunked_objects.size(); i++) {
		place_object_in_chunk(unchunked_objects.at(i));
		//unchunked_objects.erase(unchunked_objects.begin() + i);
	}
	
}
/* checks that the chunk contains only the needed objects */
/* Warning :Does not check if a object exsits in a other chunk */
void World::check_chunk(chunk * test_chunk)
{
	for (int i = 0; i < test_chunk->objects.size(); i++) {
		if (check_for_overlap(test_chunk->x_pos, test_chunk->y_pos, test_chunk->width, test_chunk->height, test_chunk->objects.at(i)->get_bitmap()->getxpos(), test_chunk->objects.at(i)->get_bitmap()->getypos(), test_chunk->objects.at(i)->get_bitmap()->getwidth(), test_chunk->objects.at(i)->get_bitmap()->getheight())) {
			
		}
		else {
			test_chunk->objects.erase(test_chunk->objects.begin() + i);
		}
	}
	test_chunk->objects.shrink_to_fit();
	for (int i = 0; i < test_chunk->no_colision_objects.size(); i++) {
		if (check_for_overlap(test_chunk->x_pos, test_chunk->y_pos, test_chunk->width, test_chunk->height, test_chunk->no_colision_objects.at(i)->get_bitmap()->getxpos(), test_chunk->no_colision_objects.at(i)->get_bitmap()->getypos(), test_chunk->no_colision_objects.at(i)->get_bitmap()->getwidth(), test_chunk->no_colision_objects.at(i)->get_bitmap()->getheight())) {

		}
		else {
			test_chunk->no_colision_objects.erase(test_chunk->no_colision_objects.begin() + i);
		}
	}
	test_chunk->no_colision_objects.shrink_to_fit();
}
/* Creates a chunk, will automaticly resize near by chunks and move the objects to the new chunk */
void World::create_chunk(int x_pos, int y_pos, int width, int height)
{
	chunk * altered_chunk;
	for (int i = 0; i < chunks->size(); i++) {
		if (check_for_overlap(chunks->at(i).x_pos, chunks->at(i).y_pos, chunks->at(i).width, chunks->at(i).height, x_pos, y_pos, width, height)) {
			altered_chunk = &chunks->at(i);
			chunk temp;
			temp.x_pos = x_pos;
			temp.y_pos = y_pos;
			temp.width = width;
			temp.height = height;
			/* FOR DEBUG */temp.box = new Object(bitmap_manager.create_bitmap("assets/black.bmp", 100, 100,false),false);
			if (chunks->at(i).x_pos == x_pos) {
				chunks->at(i).height -= height;
			}
			if (chunks->at(i).y_pos == y_pos) {
				chunks->at(i).width -= width;
			}
            chunks->push_back(temp);
            
            if(chunks->at(i+1).objects.size() > 0){
            temp.objects = chunks->at(i).objects;
			temp.no_colision_objects = chunks->at(i).no_colision_objects;
			check_chunk(altered_chunk);
			check_chunk(&chunks->front());
            }
           
            
            break;

		}
	}
}

/* Removes the chunk */
/* Warning has no safety to check if the chunk contains objects */
void World::remove_chunk(chunk * test_chunk)
{
	for (int i = 0; i < chunks->size(); i++) {
		if (&chunks->at(i) == test_chunk) {
			chunks->erase(chunks->begin() + i);
			chunks->shrink_to_fit();
		}
	}
}

/* Moves an object from one chunk  to the target chunk */
void World::move_object(Object * object, chunk * from_chunk, chunk * to_chunk)
{
	for (int i = 0; i < chunks->size(); i++) {
		if (from_chunk->objects.at(i) == object) {
			from_chunk->objects.erase(from_chunk->objects.begin() + i);
			from_chunk->objects.shrink_to_fit();
			
			to_chunk->objects.push_back(object);
		}
	}
}

/* Will check all the chunks to find which chunk they should be in */
/* It then adds the object to the chunk*/
void World::place_object_in_chunk(Object * object)
{
	bool placed = false;
	chunk * current_test_chunk;
	for (int i = 0; i < chunks->size(); i++) {
		current_test_chunk = &chunks->at(i);

		if (check_for_overlap(current_test_chunk->x_pos, current_test_chunk->y_pos, current_test_chunk->width, current_test_chunk->height, object->get_bitmap()->getxpos(), object->get_bitmap()->getypos(), object->get_bitmap()->getwidth(), object->get_bitmap()->getheight())) {
			
			if (object->is_solid()) {
				chunks->at(i).objects.push_back(object);
			}
			else {
				chunks->at(i).no_colision_objects.push_back(object);
			}
			placed = true;
			break;
		}
	}
	if (!placed) {
		cout << "object not placed ..... " << endl;
	}
}

/* Checks all the current chunks to find dead chunks (chunks with no object in) */
/* Then merges the chunk if needed */
void World::clean_chunks()
{
    
}

/* ******Used For Debuging******* */
/* Creates a bitmap to reprsent the chunks area */
/**/
void World::draw_chunks()
{
	for (int i = 0; i < chunks->size(); i++) {
		//Object * temp = new Object(bitmap_manager.create_bitmap("assets/test_block.bmp", chunks->at(i).x_pos, chunks->at(i).y_pos,false),false);
        chunks->at(i).box->get_bitmap()->set_Draw_Position(chunks->at(i).x_pos, chunks->at(i).y_pos);
		chunks->at(i).box->get_bitmap()->set_Draw_Dimensions(chunks->at(i).width, chunks->at(i).height);
        chunks->at(i).box->draw();
       
	}
}
