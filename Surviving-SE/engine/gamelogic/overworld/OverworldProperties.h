#ifndef CHARACTERPROPERTIES_H
#define CHARACTERPROPERTIES_H

#define MAP_HEIGHT 25
#define MAP_WIDTH 25

#define INITIALPLAYERXPOS 12
#define INITIALPLAYERYPOS 12

#define INITIALGRIDXPOS 131
#define INITIALGRIDYPOS 567

enum movementOption {
  NOMOVEMENT = 0,
  MOVE_UP = -1,
  MOVE_DOWN = 1,
  MOVE_LEFT = -2,
  MOVE_RIGHT = 2,
  MOVE_UPLEFT = -4,
  MOVE_UPRIGHT = 4,
  MOVE_DOWNLEFT = -3,
  MOVE_DOWNRIGHT = 3
};

struct position {
  int xpos;
  int ypos;
};

#endif
