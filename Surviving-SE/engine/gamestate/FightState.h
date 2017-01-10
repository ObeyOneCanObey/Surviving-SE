#ifndef FIGHTSTATE_H
#define FIGHTSTATE_H

#include <string>

#include "GameState.h"
#include "../gamelogic/monsterFight/MonsterFight.h"

class FightState : public GameState {
public:
  void init(Window window);
  void updateState(enum Input input, GameStateManager *gameStateManager);
  void renderState(Window window);
  void createBossSprite(Sprite *sprite, std::string verticesDataFile, std::string texCoordsDataFile, std::string indicesDataFile, std::string textureFile);
  //Set current level and type of monster encountered to generate appropriate monster
  void setFightParams(int level, int monsterEncounter);
  void renderHealthBars(int *currentPlayerHealth, int *currentMonsterHealth, Renderer *renderer);
  void renderFightMenu();
  //Update global game state based on results of fight
  void updateGameStateParams(GameStateManager *gameStateManager, int monsterEncounter, int level, int numMonsterEncounters, bool isNewLevel, bool isFight);
  //Move cursors within the menus
  void moveMenuCursors(enum Input input, int *cursorValue, Sprite *cursor, float cursorMovement[2][2]);
  //Resets menu cursors after option is selected
  void resetCursor(Sprite *cursor, int cursorValue, float cursorMovement[2][2]);
  
private:
  MonsterFight fight;
  int currentPlayerHealth = 100;
  int maxPlayerHealth = 100;
  int currentMonsterHealth;
  int maxMonsterHealth;
  
  int attackCursor = 0;
  int potionsCursor = 0;
  
  bool isFirstMove = true;
  bool inMainMenu = true;
  bool inAttackMenu = false;
  bool inPotionsMenu = false;
  bool cursorOnFight = true;
  
  Sprite playerAvatar;
  Sprite mansour;
  Sprite lam;
  Sprite andre;
  Sprite morton;
  Sprite seMonster;
  Sprite csMonster;
  Sprite mathMonster;
  Sprite eceMonster;
  Sprite monsterHPBar;
  Sprite playerHPBar;
  Sprite playerFightMenu;
  Sprite mainMenuArrow;
  Sprite attackMenuArrow;
  Sprite potionsMenuArrow;
  std::string weapons[12] = { "Pencil", "Energia", "SVN", "BASH", "<assert.h>", "PageRank", "Integration", "Cramer's Rule", "ERO", "OPAMP", "Superposition", "Inertia" };
  std::string potions[3] = { "Heal 25HP", "Heal 35HP", "Heal 45HP" };
  int potionValues[3] = { 25, 35, 45 };
  float attackCursorMovement[2][2] = { {0.0f, 40.0f}, {-110.0f, -40.0f} };
  float potionsCursorMovement[2][2] = { {0.0f, 40.0f}, {-130.0f, -40.0f} };
};

#endif
