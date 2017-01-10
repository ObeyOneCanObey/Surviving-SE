#include "SaveStateManager.h"

void SaveStateManager::recordSaveData(int level, int playerX, int playerY, int health, int gridX, int gridY, int numMonsterEncounters) {
  std::ofstream saveData;
  saveData.open("res/savestates/saveData.txt");
  saveData << "level=" << std::to_string(level) << std::endl;
  saveData << "playerX=" << std::to_string(playerX) << std::endl;
  saveData << "playerY=" << std::to_string(playerY) << std::endl;
  saveData << "health=" << std::to_string(health) << std::endl;
  saveData << "gridX=" << std::to_string(gridX) << std::endl;
  saveData << "gridY=" << std::to_string(gridY) << std::endl;
  saveData << "numMonsterEncounters=" << std::to_string(numMonsterEncounters) << std::endl;
}

void SaveStateManager::deleteSaveData() {
  std::ofstream saveData;
  saveData.open("res/savestates/saveData.txt");
  saveData << "level=" << std::to_string(0) << std::endl;
  saveData << "playerX=" << std::to_string(12) << std::endl;
  saveData << "playerY=" << std::to_string(12) << std::endl;
  saveData << "health=" << std::to_string(100) << std::endl;
  saveData << "gridX=" << std::to_string(131) << std::endl;
  saveData << "gridY=" << std::to_string(567) << std::endl;
  saveData << "numMonsterEncounters=" << std::to_string(0) << std::endl;
}

void SaveStateManager::loadSaveData(int *level, int *playerX, int *playerY, int *health, int *gridX, int *gridY, int *numMonsterEncounters) {
  std::ifstream saveDataStream;
  saveDataStream.open("res/savestates/saveData.txt");
  
  if (saveDataStream.fail()) {
    std::cout << "ERROR:COULD_NOT_OPEN_SAVE_FILE" << std::endl;
  }
  std::string delimiter = "=";
  std::string returnString;
  std::string line;
  std::string token;
  
  size_t pos = 0;
  
  while (!saveDataStream.eof()) {
    getline(saveDataStream, line);
    pos = line.find(delimiter);
    token = line.substr(0, pos);
    if (strcmp(token.c_str(), "level") == 0) {
      returnString = line.substr(pos + 1, line.npos);
      *level = std::stoi(returnString);
    }
    if (strcmp(token.c_str(), "playerX") == 0) {
      returnString = line.substr(pos + 1, line.npos);
      *playerX = std::stoi(returnString);
    }
    if (strcmp(token.c_str(), "playerY") == 0) {
      returnString = line.substr(pos + 1, line.npos);
      *playerY = std::stoi(returnString);
    }
    if (strcmp(token.c_str(), "health") == 0) {
      returnString = line.substr(pos + 1, line.npos);
      *health = std::stoi(returnString);
    }
    if (strcmp(token.c_str(), "gridX") == 0) {
      returnString = line.substr(pos + 1, line.npos);
      *gridX = std::stoi(returnString);
    }
    if (strcmp(token.c_str(), "gridY") == 0) {
      returnString = line.substr(pos + 1, line.npos);
      *gridY = std::stoi(returnString);
    }
    if (strcmp(token.c_str(), "numMonsterEncounters") == 0) {
      returnString = line.substr(pos + 1, line.npos);
      *numMonsterEncounters = std::stoi(returnString);
    }
  }

  
}
