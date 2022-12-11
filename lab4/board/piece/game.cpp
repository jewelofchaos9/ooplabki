#include "game.h"
#include "piece.h"
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

struct cmp{
  Position pos;
  cmp(const Position& i): pos(i){}
  bool operator()(const Position& i){
    return pos.equals(i);
  }
};

bool ChessGame::_try_move(MoveCommand moveCommand){
  ChessBoard board_copy = this->board;
  std::cout << moveCommand.getDst().to_string() << "\n";
  std::cout << moveCommand.getSrc().to_string() << "\n";
  Piece *src_piece = board_copy.getPiece(moveCommand.getSrc());
  if(src_piece == nullptr){
    return false;
  }
  if( (this->status == STATUS_WHITE_MOVE && src_piece->getColor() == BLACK)
   || (this->status == STATUS_BLACK_MOVE && src_piece->getColor() == WHITE)){
    return false;
  }
  std::vector<Position> positions = src_piece->getMovablePositions(&board_copy);
  for(auto i = positions.begin(); i != positions.end(); i++){
    std::cout << (*i).to_string() << "\n";
  }
  if(!(std::any_of(src_piece->getMovablePositions(&board_copy).begin(), 
                    src_piece->getMovablePositions(&board_copy).end(), 
                    cmp(moveCommand.getDst())))
                    &&
    !(std::any_of(src_piece->getTreathenedPositions(&board_copy).begin(), 
                    src_piece->getTreathenedPositions(&board_copy).end(), 
                    cmp(moveCommand.getDst())))){
    std::cout << "HUI3\n";
    return false;
  }

  board_copy.executeMove(moveCommand);
  for(auto i = board_copy.getPieces().begin(); i != board_copy.getPieces().end(); i++){
    if(this->status == STATUS_WHITE_MOVE && 
       std::any_of((*i)->getTreathenedPositions(&board_copy).begin(),
                   (*i)->getTreathenedPositions(&board_copy).end(),
                   cmp(board_copy.getWhiteKingPosition()))){
    std::cout << "HUI4\n";
        return false;
      }
    if(this->status == STATUS_BLACK_MOVE && 
       std::any_of((*i)->getTreathenedPositions(&board_copy).begin(),
                   (*i)->getTreathenedPositions(&board_copy).end(),
                   cmp(board_copy.getBlackKingPosition()))){
    std::cout << "HUI5\n";
        return false;
      }
  }
  return true;
}

void ChessGame::run(){
  this->renderer.render(this->getGameState());
  while(not this->_finished){
    MoveCommand command = this->renderer.parse_command();
    if(!this->_try_move(command)){
      this->renderer.error("Input error");
      continue;
    }
    this->board.executeMove(command);
    if(this->status == STATUS_BLACK_MOVE){
      this->status = STATUS_WHITE_MOVE;
    }
    else if(this->status == STATUS_WHITE_MOVE){
      this->status = STATUS_BLACK_MOVE;
    }
    this->renderer.render(this->getGameState());
  }
  return this->renderer.end(this->status);
}

void Renderer::render(ChessGameState state){
  std::vector <Piece *>pieces = state.getPieces();
  for(int i = 0; i < pieces.size(); i++){
    std::cout << pieces[i]->symbol() << " " << pieces[i]->getPosition().to_string() << "\n";
  }
}

ChessGameState ChessGame::getGameState(){
  return ChessGameState(this->board.getPieces());
}

MoveCommand Renderer::parse_command(){
  std::cout << "Command >";
  std::string s;
  std::getline(std::cin, s);
  return MoveCommand(s);
}
void Renderer::error(std::string s){
  std::cout << s << "\n";
}
void Renderer::end(int s){
  std::cout << s << "\n";
}
