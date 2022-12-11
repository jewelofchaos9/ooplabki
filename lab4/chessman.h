#include <set>

namespace chess{

class ColourChessman{
public:
  ColourChessman();
  ~ColourChessman();
  ColourChessman getColour();
};

class Coordinates{
private:
  int x;
  int y;
public:
  Coordinates();
  ~Coordinates();
  Coordinates getCoordinates();
};

class Movement{
private:
  Coordinates from;
  Coordinates to;
public:
  Movement(Coordinates from, Coordinates to);
  ~Movement();
};

class Chessman{
private:
  ColourChessman color;
  Coordinates coordinates;
public:
  Chessman(ColourChessman, Coordinates);
  ~Chessman();
  virtual bool checkMove(Movement);
  virtual std::set<Movement> possibleMoves();
  Coordinates getCoordinates();
};

}
