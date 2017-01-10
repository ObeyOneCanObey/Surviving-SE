#include "Wall.h"

int wall[6][3];
int wallNum[2];

bool NoWall(int x, int y, int Grid[], enum movementOption move) {
  if(move == MOVE_DOWN){ return Grid[x * MAP_WIDTH + y + 1] == WALL;}
  else if(move == MOVE_UP){ return Grid[x * MAP_WIDTH + y - 1] == WALL;}
  else if(move == MOVE_RIGHT){ return Grid[(x + 1) * MAP_WIDTH + y] == WALL;}
  else if(move == MOVE_LEFT){ return Grid[(x - 1) * MAP_WIDTH + y] == WALL;}
  else if(move == MOVE_DOWNRIGHT){ return Grid[(x + 1) * MAP_WIDTH + y + 1] == WALL;}
  else if(move == MOVE_DOWNLEFT){ return Grid[(x - 1) * MAP_WIDTH + y + 1] == WALL;}
  else if(move == MOVE_UPRIGHT){ return Grid[(x + 1) * MAP_WIDTH + y - 1] == WALL;}
  else if(move == MOVE_UPLEFT){ return Grid[(x - 1) * MAP_WIDTH + y - 1] == WALL;}
  else{ return 0;}
}

void buildWall(int xCoord, int yCoord) {
  srand(xCoord * xCoord - yCoord * yCoord);
  wallNum[0] = rand()%2 + 2;
  wallNum[1] = rand()%2 + 2;
  for(int i = 0; i < wallNum[0] + wallNum[1]; i+=1){
    wall[i][0] = (rand()%15) + 5;
    wall[i][1] = (rand()%(22-wall[i][0])) + 2;
    wall[i][2] = (rand()%2) + 2;
  }
}

void updateWall(int xCoord, int yCoord, int Grid[]) {
  buildWall(xCoord, yCoord);
  int num = 3;
  for(int i = 0; i < 25; i+=1){
    for(int j = 0; j < 25; j+=1){
      Grid[i * MAP_WIDTH + j] = 0;
    }
  }
  for(int i = 0; i < wallNum[0]; i+=1){
    for(int j = wall[i][1]; j < wall[i][1]+ wall[i][0]; j+=1){
      Grid[j * MAP_WIDTH + wall[i][2] + num] = WALL;
    }
    num+=6;
  }
  num = 3;
  for(int i = wallNum[0]; i < wallNum[0]+wallNum[1]; i+=1){
    for(int j = wall[i][1]; j <  wall[i][1] + wall[i][0]; j+=1){
      Grid[(wall[i][2] + num) * MAP_WIDTH + j] = WALL;
    }
    num+=6;
  }
}
