#include <vector>
#include "chessboard.h"
#include "renderer.h"
enum moves{
  STATUS_WHITE_MOVE,
  STATUS_BLACK_MOVE,
  STATUS_WHITE_VICTORY,
  STATUS_BLACK_VICTORY
};
class Piece;
class ChessGameState{
private:
  std::vector<Piece *> pieces;
public:
  ChessGameState(std::vector<Piece *>pieces){
    this->pieces = pieces;
  }
  std::vector<Piece  *> getPieces(){
    return this->pieces;
  }
};

class Renderer{
private:

public:
  Renderer(){}
  ~Renderer(){}
  void render(ChessGameState);
  MoveCommand parse_command();
  void error(std::string);
  void end(int);
};

class ChessGame{
private:
  bool _finished;
  ChessBoard board;
  Renderer renderer;
  int status;
  bool _try_move(MoveCommand);
public:
  ChessGame(Renderer rend){
    _finished = false;
    board = ChessBoard();
    renderer = rend;
    status = STATUS_WHITE_MOVE;
  }
  ~ChessGame(){}
  ChessGameState getGameState();
  void run();
};
