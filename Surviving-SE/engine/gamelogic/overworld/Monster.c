#include "Monster.h"

int monsterCoordinates[NUM_MAX_MONSTERS][2];
int monsterGenerated[NUM_MAX_MONSTERS];
int monsterCreated[NUM_MAX_MONSTERS];

void ifAttackOccurs(int Grid[]) {
  srand(time(NULL));
  for(int i = 0; i < 4; i+=1){
    monsterGenerated[i] = 0;
    if(rand()%2){
      monsterGenerated[i] = 1;
      if(i == 0){
        monsterCoordinates[i][0] = rand()%10 + 2;
        monsterCoordinates[i][1] = rand()%10 + 2;
        while(Grid[monsterCoordinates[i][0] * MAP_WIDTH + monsterCoordinates[i][1]] == 9){
          monsterCoordinates[i][0] +=1;
        }
      }else if(i == 1){
        monsterCoordinates[i][0] = rand()%10 + 13;
        monsterCoordinates[i][1] = rand()%10 + 2;
        while(Grid[monsterCoordinates[i][0] * MAP_WIDTH + monsterCoordinates[i][1]] == 9){
          monsterCoordinates[i][0] +=1;
        }
      }else if(i == 2){
        monsterCoordinates[i][0] = rand()%10 + 2;
        monsterCoordinates[i][1] = rand()%10 + 13;
        while(Grid[monsterCoordinates[i][0] * MAP_WIDTH + monsterCoordinates[i][1]] == 9){
          monsterCoordinates[i][0] +=1;
        }
      }else if(i == 3){
        monsterCoordinates[i][0] = rand()%10 + 13;
        monsterCoordinates[i][1] = rand()%10 + 13;
        while(Grid[monsterCoordinates[i][0] * MAP_WIDTH + monsterCoordinates[i][1]] == 9){
          monsterCoordinates[i][0] +=1;
        }
      }
    }
  }
}

void monsterGenerator(int Grid[])  {
  ifAttackOccurs(Grid);
  for(int m = 0; m<4 ; m+=1){
    if(monsterGenerated[m]){
      monsterCreated[m] = RandomMonsterGenerator();
    }
  }
}

bool RandomMonsterGenerator() {
  int ctr  = 1;
  int n =  1 + (rand()%13);
  if(n > 6){n = n - 6;}
  while(n > ctr*(ctr+1)/2){ctr+=1;}
  return n - ctr*(ctr-1)/2;
}

void monsterFollow(int playerX, int playerY, int Grid[], int *monsterEncounter) {
  for(int m = 0; m < 4; m+=1){
    int monsX = monsterCoordinates[m][0];
    int monsY = monsterCoordinates[m][1];
    if(abs(playerX - monsX) < MONSTER_RANGE && abs(playerY - monsY) < MONSTER_RANGE && monsY < 25 && monsX < 25 && monsterGenerated[m]){
      Grid[monsX * MAP_WIDTH + monsY] = 0;
      if(monsY > playerY && !(NoWall(monsX , monsY, Grid, MOVE_UP))){
        monsY -= 1;
      }else if(monsY < playerY && !(NoWall(monsX , monsY, Grid, MOVE_DOWN))){
        monsY += 1;
      }else if(monsX > playerX && !(NoWall(monsX , monsY, Grid, MOVE_LEFT))){
        monsX -= 1;
      }else if(monsX < playerX && !(NoWall(monsX , monsY, Grid, MOVE_RIGHT))){
        monsX += 1;
      }
      Grid[monsX * MAP_WIDTH + monsY] = 5;
    }
    
    monsterCoordinates[m][0] = monsX;
    monsterCoordinates[m][1] = monsY;
  }
}

void monsterUpdate(int playerX, int playerY, int Grid[], int *monsterEncounter){
  monsterFollow(playerX,playerY, Grid, monsterEncounter);
  for(int m = 0; m < 4; m+=1){
    if(monsterGenerated[m]){
      Grid[monsterCoordinates[m][0] * MAP_WIDTH + monsterCoordinates[m][1]] = monsterCreated[m];
    }
  }
}

bool enterFight(int playerX, int playerY, int Grid[], int *monsterEncounter) {
  bool isMonsterFight = false;
  for(int m = 0; m < 4; m+=1){
    int monsX = monsterCoordinates[m][0];
    int monsY = monsterCoordinates[m][1];
    if(monsX == playerX && monsY == playerY && monsterGenerated[m]){
      *monsterEncounter = monsterCreated[m];
      isMonsterFight = true;
      monsterGenerated[m] = 0;
      Grid[monsX * MAP_WIDTH + monsY] = 0;
    }
  }
  return isMonsterFight;
}

void resetMonsterGrid() {
  for (int i = 0; i < NUM_MAX_MONSTERS; i++) {
    monsterGenerated[i] = 0;
  }
}
