
#define TILE_SIZE 64
#define MAX_MAP_X 7
#define MAX_MAP_Y 5
#include "GameObject.h"
#define MAX_TILE 20 
#include "Background.h"

typedef struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;
	char* file_name_;
	
	int tile[MAX_MAP_Y][MAX_MAP_X];

};

//class TileMap : CGameObject 
//{
//public :
//	TileMap() { ; };
//	~TileMap() { ; };
//	void GetBoundingBox(float &left, float &top, float &right, float &bottom) { ; }
//	void Render() { ; }
//
//};

class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }

	void LoadMap(char* name);
	void LoadTiles();
	void DrawMap();
private:
	Map game_map_;       // save position number
	CBackground* tile_map[];   // save image


};



