#include "chessboard.h"
#include "piece.h"
#include <iostream>
class Setup{
public:
  int type;
  int x;
  int y;
  Setup(int type, int x, int y){
    this->type = type; this->x = x;
    this->y = y;
  }
  ~Setup(){}
};

void ChessBoard::initPieces(){
  std::vector<class Setup> INITIAL_PIECE_SET_SINGLE{
    Setup(ROOK, 0, 0),
    Setup(KNIGHT, 1, 0),
    Setup(BISHOP, 2, 0),
    Setup(QUEEN, 3, 0),
    Setup(KING, 4, 0),
    Setup(BISHOP, 5, 0),
    Setup(KNIGHT, 6, 0),
    Setup(ROOK, 7, 0),
    Setup(PAWN, 0, 1),
    Setup(PAWN, 1, 1),
    Setup(PAWN, 2, 1),
    Setup(PAWN, 3, 1),
    Setup(PAWN, 4, 1),
    Setup(PAWN, 5, 1),
    Setup(PAWN, 6, 1),
    Setup(PAWN, 7, 1)
  };
  int type,x,y;
  PieceFactory factory;
  Piece *piece_white;
  Piece *piece_black;
  for(auto i = INITIAL_PIECE_SET_SINGLE.begin(); i != INITIAL_PIECE_SET_SINGLE.end(); i++){
    type = i->type;
    x = i->x;
    y = i->y;
    piece_white = factory.create(type, Position(x,y), WHITE);
    this->pieces.push_back(piece_white);
    piece_black = factory.create(type, Position(this->size - x - 1, this->size - y - 1), BLACK);
    this->pieces.push_back(piece_black);
    if(type == KING){
      piece_white->setBoardHandle(this);
      piece_black->setBoardHandle(this);
    }
  }
}
ChessBoard::ChessBoard(){
  this->initPieces();
}
ChessBoard::ChessBoard(const ChessBoard& other){
  this->pieces = other.pieces;
  this->_whiteKingPosition = other._whiteKingPosition;
  this->_blackKingPosition = other._blackKingPosition; 

}
ChessBoard::~ChessBoard(){
}
std::vector <Piece *> ChessBoard::getPieces(){
  return this->pieces;
}

Piece *ChessBoard::getPiece(Position pos){
  Position temp;
  for(auto i = pieces.begin(); i != pieces.end(); i++){
    temp = (*i)->getPosition();
    if(temp.getX() == pos.getX() &&  temp.getY() == pos.getY()){
      return *i;
    }
  }
  return nullptr;
}

std::vector<Position> ChessBoard::beamSearchThreat(Position start, int own_color, int increment_x, int increment_y){
  std::vector<Position> threatened_positions;
  Position curr_position;
  Piece *curr_piece;
  int curr_x = start.getX();
  int curr_y = start.getY();
  curr_x += increment_x;
  curr_y += increment_y;
  while(curr_x >= 0 && curr_y >= 0 && curr_x < size && curr_y < size){
    curr_position = Position(curr_x, curr_y);
    curr_piece = getPiece(curr_position);
    if(curr_piece != nullptr){
      if(curr_piece->getColor() != own_color){
        threatened_positions.push_back(curr_position);
      }
      break;
    }
    threatened_positions.push_back(curr_position);
    curr_x += increment_x;
    curr_y += increment_y;
  }
  return threatened_positions;
}

Position ChessBoard::spotSearchThreat(Position start, int own_color, int increment_x, int increment_y, bool threat_only, bool free_only){
  int curr_x = start.getX() + increment_x;
  int curr_y = start.getY() + increment_y; 
  if(curr_x >= size || curr_y >= size || curr_x < 0 || curr_y < 0){
    return start;
  }
  Position curr_position = Position(curr_x, curr_y);
  Piece *curr_piece = getPiece(curr_position);
  if(curr_piece != nullptr){
    if(free_only){
      return start;
    }
    if(curr_piece->getColor() != own_color){
      return curr_position;
    }
    else{
      return start;
    }
  }
  if(!threat_only){
    return curr_position;
  }
  return start;
}

void ChessBoard::registerKingPosition(Position pos, int color){
  if(color == WHITE){
    this->_whiteKingPosition = pos;
  }
  else if (color == BLACK){
    this->_blackKingPosition = pos;
  }
  else{
    throw std::runtime_error("Uknown color");
  }
}
Position ChessBoard::getWhiteKingPosition(){
  return this->_whiteKingPosition;
}

Position ChessBoard::getBlackKingPosition(){
  return this->_blackKingPosition;
}

void ChessBoard::executeMove(MoveCommand command){
  Piece *source_piece = getPiece(command.getSrc());
  Piece *temp;
  for(auto i = pieces.begin(); i != pieces.end(); i++){
    if((*i)->getPosition().equals(command.getDst())){
      temp = *i;
      pieces.erase(i);
      break;
    }
  }
}

