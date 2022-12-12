#include "Vector.h"
#include <iostream>

int main(){
  Vector<int> a;
  a.pushBack(5);
  a.pushBack(3);
  a.pushBack(2);
  for(auto i = a.begin(); i != a.end(); i++){
    std::cout << *i << "\n";

  }


}
