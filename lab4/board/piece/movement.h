#pragma once
#include <string>
class Position{
private:
  int x;
  int y;
public:
  Position(int x, int y){
    this->x = x;
    this->y = y;
  }
  Position(){
    x = 0;
    y = 0;
  }
  ~Position(){}
  void setPosition(int x, int y){
    this->x = x;
    this->y = y;
  }
  int getX(){
    return x;
  }
  int getY(){
    return y;
  }
  bool equals(Position other){
    return other.getX() == x && other.getY() == y;
  }
  std::string to_string();
  Position(std::string);
};

class Movement{
private:
  int x;
  int y;
public:
  Movement(){}
  Movement(int x,int y){
    this->x = x;
    this->y = y;
  }
  ~Movement(){}
  int getX(){
    return x;
  }
  int getY(){
    return y;
  }
};

class MoveCommand{
private:
  Position src;
  Position dst;
public:
  MoveCommand(Position src, Position dst){
    this->src = src;
    this->dst = dst;
  }
  ~MoveCommand(){}
  Position getSrc(){
    return Position(this->src.getX(), this->src.getY());
  }
  Position getDst(){
    return Position(this->dst.getX(), this->dst.getY());
  }
  MoveCommand(std::string);
};

