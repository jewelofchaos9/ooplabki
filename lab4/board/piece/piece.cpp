#include "piece.h"
#include "movement.h"
#include <vector>
#include <exception>
#include <string>
#include <iostream>


Piece::Piece(Position pos, int color){
  this->position = pos;
  this->color = color;
}

int Piece::getColor(){
  return this->color;
}

Position Piece::getPosition(){
  return this->position;
}

void Piece::move(Position pos){
  this->position = pos;
}

std::string Piece::symbol(){
  std::string ans = std::string("");
  if(this->color == BLACK){
    ans += "B_";
  }
  else{
    ans += "W_";
  }
  return ans + this->piece_symbol();
}

//**KING**// 

void King::setBoardHandle(ChessBoard *cb){
  this->board_handle = cb;
}

void King::move(Position target){
  Piece::move(target);
  board_handle->registerKingPosition(target, Piece::getColor());
}

std::vector<Position> King::getTreathenedPositions(ChessBoard *board){
  std::vector<Position> ans;
  for(auto i = this->SPOT_INCREMENTS.begin(); i != this->SPOT_INCREMENTS.end(); i++){
    ans.push_back(board->spotSearchThreat(Piece::getPosition(), Piece::getColor(), i->getX(), i->getY()));
  }
  for(auto i = ans.begin(); i != ans.end(); i++){
    if((*i).getX() == Piece::getPosition().getX() && (*i).getY() == Piece::getPosition().getY()){
      ans.erase(i);
    }
  }
  return ans;
}

std::vector<Position> King::getMovablePositions(ChessBoard *board){
  return this->getTreathenedPositions(board);
}

std::string King::piece_symbol(){
  return std::string("KI");
}

//**QUEEN**//
std::vector<Position> Queen::getTreathenedPositions(ChessBoard *board){
  std::vector<Position> ans;
  std::vector<Position> temp;
  for(auto i = this->BEAM_INCREMENTS.begin(); i != this->BEAM_INCREMENTS.end(); i++){
    temp = board->beamSearchThreat(Piece::getPosition(), Piece::getColor(), i->getX(), i->getY());
    ans.insert(ans.end(), temp.begin(), temp.end());
  }
  return ans;
}
std::vector<Position> Queen::getMovablePositions(ChessBoard *board){
  return this->getTreathenedPositions(board);
}

std::string Queen::piece_symbol(){
  return std::string("QU");
}

/**KNIGHT*/

std::vector<Position> Knight::getTreathenedPositions(ChessBoard *board){
  std::vector<Position> ans;
  for(auto i = this->SPOT_INCREMENTS.begin(); i != this->SPOT_INCREMENTS.end(); i++){
    ans.push_back(board->spotSearchThreat(Piece::getPosition(), Piece::getColor(), i->getX(), i->getY()));
  }
  for(auto i = ans.begin(); i != ans.end(); i++){
    if((*i).getX() == Piece::getPosition().getX() && (*i).getY() == Piece::getPosition().getY()){
      ans.erase(i);
    }
  }
  return ans;
}

std::vector<Position> Knight::getMovablePositions(ChessBoard *board){
  return this->getTreathenedPositions(board);
}

std::string Knight::piece_symbol(){
  return std::string("KN");
}

/**ROOK**/

std::vector<Position> Rook::getTreathenedPositions(ChessBoard *board){
  std::vector<Position> ans;
  std::vector<Position> temp;
  for(auto i = this->BEAM_INCREMENTS.begin(); i != this->BEAM_INCREMENTS.end(); i++){
    temp = board->beamSearchThreat(Piece::getPosition(), Piece::getColor(), i->getX(), i->getY());
    ans.insert(ans.end(), temp.begin(), temp.end());
  }
  return ans;
}
std::vector<Position> Rook::getMovablePositions(ChessBoard *board){
  return this->getTreathenedPositions(board);
}

std::string Rook::piece_symbol(){
  return std::string("RO");
}

/**BISHOP**/

std::vector<Position> Bishop::getTreathenedPositions(ChessBoard *board){
  std::vector<Position> ans;
  std::vector<Position> temp;
  for(auto i = this->BEAM_INCREMENTS.begin(); i != this->BEAM_INCREMENTS.end(); i++){
    temp = board->beamSearchThreat(Piece::getPosition(), Piece::getColor(), i->getX(), i->getY());
    ans.insert(ans.end(), temp.begin(), temp.end());
  }
  return ans;
}
std::vector<Position> Bishop::getMovablePositions(ChessBoard *board){
  return this->getTreathenedPositions(board);
}

std::string Bishop::piece_symbol(){
  return std::string("BI");
}

/**PAWN**/
std::vector<Position> Pawn::getTreathenedPositions(ChessBoard *board){
  std::vector<Position> ans;
  for(auto i = this->SPOT_INCREMENTS_TAKE.begin(); i != this->SPOT_INCREMENTS_TAKE.end(); i++){
    if(Piece::getColor()== WHITE){
      ans.push_back(board->spotSearchThreat(Piece::getPosition(), Piece::getColor(), i->getX(), i->getY()));
    }
    else{
      ans.push_back(board->spotSearchThreat(Piece::getPosition(), Piece::getColor(), i->getX(), (-1) * i->getY()));
    }
  }
  for(auto i = ans.begin(); i != ans.end(); i++){
    if((*i).getX() == Piece::getPosition().getX() && (*i).getY() == Piece::getPosition().getY()){
      ans.erase(i);
    }
  }
  return ans;
}

std::vector<Position> Pawn::getMovablePositions(ChessBoard *board){
  std::vector<Position> ans;
  std::vector<Movement> spot;
  if(this->moved){
    spot = SPOT_INCREMENTS_MOVE;
  }
  else{
    spot = SPOT_INCREMENTS_MOVE_FIRST;
  }
  for(auto i = spot.begin(); i != spot.end(); i++){
    if(Piece::getColor()== WHITE){
      ans.push_back(board->spotSearchThreat(Piece::getPosition(), Piece::getColor(), i->getX(), i->getY(), false,true));
    }
    else{
      ans.push_back(board->spotSearchThreat(Piece::getPosition(), Piece::getColor(), i->getX(), (-1) * i->getY(),false, true));
    }
  }
  for(auto i = this->SPOT_INCREMENTS_TAKE.begin(); i != this->SPOT_INCREMENTS_TAKE.end(); i++){
    if(Piece::getColor()== WHITE){
      ans.push_back(board->spotSearchThreat(Piece::getPosition(), Piece::getColor(), i->getX(), i->getY(), true,false));
    }
    else{
      ans.push_back(board->spotSearchThreat(Piece::getPosition(), Piece::getColor(), i->getX(), (-1) * i->getY(), true, false));
    }
  }
  for(auto i = ans.begin(); i != ans.end(); i++){
    if((*i).getX() == Piece::getPosition().getX() && (*i).getY() == Piece::getPosition().getY()){
      ans.erase(i);
    }
  }
  return ans;
}

void Pawn::move(Position target){
  Piece::move(target);
  this->moved = true;
}

std::string Pawn::piece_symbol(){
  return std::string("PA");
}

/**FACTORY PATTERN**/

Piece *PieceFactory::create(int type, Position pos, int color){
  if(type == KING){
    return new King(pos, color);
  }
  if(type == QUEEN){
    return new Queen(pos, color);
  }
  if(type == ROOK){
    return new Rook(pos,color);
  }
  if(type == PAWN){
    return new Pawn(pos,color);
  }
  if(type == KNIGHT){
    return new Knight(pos,color);
  }
  if(type == BISHOP){
    return new Bishop(pos,color);
  }
    
}
