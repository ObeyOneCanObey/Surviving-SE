#ifndef CUTSCENE_H
#define CUTSCENE_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

//Base class provides functions for loading cut scene text data from .txt
class CutScene {
protected:
  std::stringstream loadResources(std::string filename) {
    std::stringstream buffer;
    std::ifstream stream((std::string("res/cutscenes/") + filename).c_str());
    if (!(stream.peek() == std::ifstream::traits_type::eof()))
      buffer << stream.rdbuf();
    return buffer;
  }
  
  //Loads file and stores each line into a string vector
  void loadMessage(std::string filename, std::vector<std::string> *message) {
    std::stringstream buffer = loadResources(filename);
    std::string str;
    
    while (!buffer.eof()) {
      std::getline(buffer, str, '\n');
      message->push_back(str);
    }
  }
};

#endif
