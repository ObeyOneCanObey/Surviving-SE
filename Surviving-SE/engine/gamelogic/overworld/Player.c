#include "Player.h"

void doMovement(enum movementOption move, struct position *currentPlayerPos, struct position *gridCoords, int Grid[], int *monsterEncounters) {
  if ((currentPlayerPos->xpos > X_LEFT_BOUND && currentPlayerPos->xpos < X_RIGHT_BOUND) && (currentPlayerPos->ypos > Y_LOWER_BOUND && currentPlayerPos->ypos < Y_UPPER_BOUND) && !(NoWall(currentPlayerPos->xpos, currentPlayerPos->ypos, Grid, move))) {
    
    switch (move) {
      case MOVE_UP:
        currentPlayerPos->ypos = currentPlayerPos->ypos - 1;
        monsterFollow(currentPlayerPos->xpos, currentPlayerPos->ypos, Grid, monsterEncounters);
        break;
      
      case MOVE_DOWN:
        currentPlayerPos->ypos = currentPlayerPos->ypos + 1;
        monsterFollow(currentPlayerPos->xpos, currentPlayerPos->ypos, Grid, monsterEncounters);
        break;
      
      case MOVE_LEFT:
        currentPlayerPos->xpos = currentPlayerPos->xpos - 1;
        monsterFollow(currentPlayerPos->xpos, currentPlayerPos->ypos, Grid, monsterEncounters);
        break;
      
      case MOVE_RIGHT:
        currentPlayerPos->xpos = currentPlayerPos->xpos + 1;
        monsterFollow(currentPlayerPos->xpos, currentPlayerPos->ypos, Grid, monsterEncounters);
        break;
        
      case MOVE_UPLEFT:
        currentPlayerPos->xpos = currentPlayerPos->xpos - 1;
        currentPlayerPos->ypos = currentPlayerPos->ypos - 1;
        monsterFollow(currentPlayerPos->xpos, currentPlayerPos->ypos, Grid, monsterEncounters);
        break;
        
      case MOVE_UPRIGHT:
        currentPlayerPos->xpos = currentPlayerPos->xpos + 1;
        currentPlayerPos->ypos = currentPlayerPos->ypos - 1;
        monsterFollow(currentPlayerPos->xpos, currentPlayerPos->ypos, Grid, monsterEncounters);
        break;
        
      case MOVE_DOWNLEFT:
        currentPlayerPos->xpos = currentPlayerPos->xpos - 1;
        currentPlayerPos->ypos = currentPlayerPos->ypos + 1;
        monsterFollow(currentPlayerPos->xpos, currentPlayerPos->ypos, Grid, monsterEncounters);
        break;
        
      case MOVE_DOWNRIGHT:
        currentPlayerPos->xpos = currentPlayerPos->xpos + 1;
        currentPlayerPos->ypos = currentPlayerPos->ypos + 1;
        monsterFollow(currentPlayerPos->xpos, currentPlayerPos->ypos, Grid, monsterEncounters);
        break;
      
      default:
      break;
    }
  } else {
    if (currentPlayerPos->xpos == X_LEFT_BOUND) {
      currentPlayerPos->xpos = X_RIGHT_BOUND - 1;
      gridCoords->xpos -= 1;
      generateNewMapContents(currentPlayerPos->xpos, currentPlayerPos->ypos, Grid, monsterEncounters);
    } else if (currentPlayerPos->xpos == X_RIGHT_BOUND) {
      currentPlayerPos->xpos = X_LEFT_BOUND + 1;
      gridCoords->xpos += 1;
      generateNewMapContents(currentPlayerPos->xpos, currentPlayerPos->ypos, Grid, monsterEncounters);
    } else if (currentPlayerPos->ypos == Y_LOWER_BOUND) {
      currentPlayerPos->ypos = Y_UPPER_BOUND - 1;
      gridCoords->ypos -= 1;
      generateNewMapContents(currentPlayerPos->xpos, currentPlayerPos->ypos, Grid, monsterEncounters);
    } else if (currentPlayerPos->ypos == Y_UPPER_BOUND) {
      currentPlayerPos->ypos = Y_LOWER_BOUND + 1;
      gridCoords->ypos += 1;
      generateNewMapContents(currentPlayerPos->xpos, currentPlayerPos->ypos, Grid, monsterEncounters);
    }
  }
}

void generateNewMapContents(int xPos, int yPos, int Grid[], int *monsterEncounters) {
  updateWall(xPos, yPos, Grid);
  monsterGenerator(Grid);
  Grid[xPos * MAP_WIDTH + yPos] = 0;
  monsterUpdate(xPos, yPos, Grid, monsterEncounters);
}
