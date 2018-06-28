#pragma once
#include <string>
#include <vector>
#include "Object.h"
#include"Bitmap_manager.h"
#include "bitmap.h"
#include "Player.h"
#include "enemy.h"
#include <iostream>
#include "World_Gen.h"
#include "defines.h"
using namespace std;

class World
{
	
private:
	int xoffset;
	int yoffset;
	const int tile_draw_size = 50;

    Object * wall;
    Player * player;
	enemy* Enemy;

	struct chunk{
		vector<Object *> objects;
		vector<Object *> no_colision_objects;
		bool deadspace = false;
		int x_pos = 0;
		int y_pos = 0;
		int width = 0;
		int height = 0;
        Object * box;
	};
	
	vector<chunk> * chunks;

	void create_world(string level_url);
	bool check_for_overlap(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
	bool check_for_overlap_center(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
	void check_colision();

	bool Colision_with_trans(Object * test1, Object * test2);

	
	void merge_chunks(chunk * chunk_1, chunk * chunk_2);
	void check_chunks();
	void check_chunk(chunk * test_chunk);

	void create_chunk(int x_pos,int y_pos,int width,int height);
	void remove_chunk(chunk * test_chunk);
	void move_object(Object * object, chunk * from_chunk, chunk* to_chunk);
	void place_object_in_chunk(Object * object);


	void clean_chunks();
	void draw_chunks();
    Bitmap_manager bitmap_manager;
    void Split_Chunk(chunk* chunk_to_split);
	

	 
public:
	
	World();
	~World();
	void paint();
	vector<Object*> get_all_objects();
	void update();
	
};

