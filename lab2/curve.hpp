namespace curves{
class Point{
private:
  double _x;
  double _y;
public:
  Point(double x, double y);
  ~Point();

  void setX(double x);
  void setY(double y);

  double getX();
  double getY();

  double distance(Point &point);
};

class Conchoid{
private:
  double _a;
  double _l;
  Point getCenter();
public:
  double getA();
  double getL();
  void setA(double a);
  void setL(double l);

  Conchoid(double a, double l);
  Conchoid();
  ~Conchoid();
  
  double yFromX(double x);
  double distanceFromCenter(double phi);
  double radiusOfCurvature();
  double loopArea();
};
}
