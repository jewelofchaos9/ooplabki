#include <iostream>
#include <string>

namespace binary{
const int MAX=8;
class Binary{

private:
  std::string number;
  std::string toBinary(long int number);
  void addByIndex(int);
  Binary fromAdditionalCode();
  int gtmod(Binary);
public:
  Binary();
  Binary(long);
  Binary(std::string);
  
  std::string str();
  Binary additionalCode();

  Binary operator+ (Binary);
  Binary& operator++ (int);
  Binary& operator--(int);

  long fromBinary();
  char numeral();
};
std::ostream& operator<<(std::ostream &out, binary::Binary i);
}
