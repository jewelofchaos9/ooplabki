#include "game.h"

int main(){
  Renderer rend = Renderer();
  ChessGame game = ChessGame(rend);
  game.run();
}
