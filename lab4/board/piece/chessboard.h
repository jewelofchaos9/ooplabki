#pragma once
#include <vector>
#include "movement.h"
class Piece;
class ChessBoard{
private:
  void initPieces();
  std::vector <Piece *> pieces;
  Position _whiteKingPosition;
  Position _blackKingPosition;
  int size = 8;
public:
  ChessBoard();
  ~ChessBoard();
  ChessBoard(const ChessBoard& other);
  Piece *getPiece(Position position);
  std::vector <Piece *> getPieces();
  Position getWhiteKingPosition();
  Position getBlackKingPosition();

  std::vector<Position> beamSearchThreat(Position start, int own_color, int increment_x, int increment_y);
  Position spotSearchThreat(Position start, int own_color, int increment_x, int increment_y, bool threat_only = false, bool free_onle = false);

  void executeMove(MoveCommand command);
  void registerKingPosition(Position, int color);

};
