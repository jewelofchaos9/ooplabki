#include "movement.h"
#include <string>

std::string Position::to_string(){
  return std::string(1, 'a' + this->x) + std::string(1, '1' + this->y);
}

Position::Position(std::string str){
  this->x = str[0] - 'a';
  this->y = str[1] - '1';
}

MoveCommand::MoveCommand(std::string str){
  std::string delimiter = " ";
  std::string token = str.substr(0, str.find(delimiter));
  this->src = Position(token);
  token = str.substr(str.find(delimiter) + 1, str.size());
  this->dst = Position(token);
}
