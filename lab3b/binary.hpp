#include <iostream>
#include <string>

namespace binary{
class Binary{
private:
  long int degree;

  std::string number;
  std::string toBinary(long int number);
  void addByIndex(int);
  Binary fromAdditionalCode();
  void stabalizeLength(Binary &, Binary &);
  std::string numberWithoutSign();

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

