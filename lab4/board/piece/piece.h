#pragma once
#include <vector>
#include <string>
#include "chessboard.h"
#include "movement.h"
enum colors{
  BLACK, 
  WHITE
};

enum pieces{
  KING,
  QUEEN, 
  KNIGHT, 
  ROOK,
  BISHOP, 
  PAWN
};

class Piece{
private:
  Position position;
  int color;
public:
  Piece(){}
  Piece(Position pos, int color);
  ~Piece(){};

  Position getPosition();
  int getColor();
  
  virtual void move(Position target);
  virtual void setBoardHandle(ChessBoard *board){}
  virtual std::vector<Position> getTreathenedPositions(ChessBoard *board)=0;
  virtual std::vector<Position> getMovablePositions(ChessBoard *board)=0;

  std::string symbol();
  virtual std::string piece_symbol()=0;
};

class King: public Piece{
private:
  std::vector<Movement> SPOT_INCREMENTS{
    Movement(1,-1), Movement(1,0), Movement(1,1),
    Movement(0,1), Movement(-1,1), Movement(-1,0),
    Movement(-1,-1), Movement(0,-1)};
    ChessBoard *board_handle;
public:
  void setBoardHandle(ChessBoard *) override;
  void move(Position target) override;
  std::vector<Position> getTreathenedPositions(ChessBoard *board) override;
  std::vector<Position> getMovablePositions(ChessBoard *board) override;
  std::string piece_symbol() override;
  King(Position pos, int col) : Piece(pos, col){};
  ~King(){}
};

class Queen: public Piece{
private:
  std::vector<Movement> BEAM_INCREMENTS{
    Movement(1,-1), Movement(1,0), Movement(1,1),
    Movement(0,1), Movement(-1,1), Movement(-1,0),
    Movement(-1,-1), Movement(0,-1)};
public:
  void move(Position target) override {Piece::move(target);};
  std::vector<Position> getTreathenedPositions(ChessBoard *board) override;
  std::vector<Position> getMovablePositions(ChessBoard *board) override;
  std::string piece_symbol() override;
  Queen(Position pos, int col) : Piece(pos, col){};
  ~Queen(){}
};

class Knight: public Piece{
private:
  std::vector<Movement> SPOT_INCREMENTS{
    Movement(2,1), Movement(2,-1),Movement(-2,1),
    Movement(-2,-1), Movement(1,2), Movement(1,-2),
    Movement(-1,2), Movement(-1,-2)
  };
public:
  void move(Position target) override {Piece::move(target);};
  std::vector<Position> getTreathenedPositions(ChessBoard *board) override;
  std::vector<Position> getMovablePositions(ChessBoard *board) override;
  std::string piece_symbol() override;
  Knight(Position pos, int col) : Piece(pos, col){};
  ~Knight(){}
};

class Rook:public Piece{
private:
  std::vector<Movement> BEAM_INCREMENTS{
    Movement(0,1), Movement(0,-1), Movement(1,0), Movement(-1,0)
  };
public:
  void move(Position target) override {Piece::move(target);};
  std::vector<Position> getTreathenedPositions(ChessBoard *board) override;
  std::vector<Position> getMovablePositions(ChessBoard *board) override;
  std::string piece_symbol() override;
  Rook(Position pos, int col) : Piece(pos,col){};
  ~Rook(){}
};

class Bishop:public Piece{
private:
  std::vector<Movement> BEAM_INCREMENTS{
    Movement(1,1), Movement(1,-1), Movement(-1,1), Movement(-1,-1)
  };
public:
  void move(Position target) override {Piece::move(target);};
  std::vector<Position> getTreathenedPositions(ChessBoard *board) override;
  std::vector<Position> getMovablePositions(ChessBoard *board) override;
  std::string piece_symbol() override;
  Bishop(Position pos, int col) : Piece(pos,col){};
  ~Bishop(){}
};

class Pawn:public Piece{
private:
  std::vector<Movement> SPOT_INCREMENTS_MOVE{Movement(0,1)};
  std::vector<Movement> SPOT_INCREMENTS_MOVE_FIRST{Movement(0,1), Movement(0,2)};
  std::vector<Movement> SPOT_INCREMENTS_TAKE{Movement(-1,1), Movement(1,1)};
  bool moved = false;
public:
  void move(Position target) override;
  std::vector<Position> getTreathenedPositions(ChessBoard *board) override;
  std::vector<Position> getMovablePositions(ChessBoard *board) override;
  std::string piece_symbol() override;
  Pawn(Position pos, int col) : Piece(pos, col){};
  ~Pawn(){}
};

class PieceFactory{
public:
  PieceFactory(){};
  ~PieceFactory(){};
  Piece *create(int type, Position, int color);
};
