#include "binary.hpp"
#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
class Main{
private:
  std::string input_menu = "Consrtuct binary number by\n[1] String\n[2] Number\n[3] Nothing\n";
  std::string number_menu = "[1] Add with other\n[2] Increase by 1\n[3] Print\n[4] Recreate\n";

  template <class T>
  T get_stdin(std::istream& in = std::cin, std::ostream &out = std::cout){
    bool finish = 0;
    T res;
    while(!finish){
      in >> res;
      if(in.bad() || in.eof()){
        throw std::runtime_error("Bad, try again");
      }
      if(!in.good()){
        in.clear();
        std::string ignore;
        std::getline(in,ignore);
      }
      else{
        finish = true;
      }
    }
    return res;
  }
public:
  Main(){

  }
  binary::Binary menu(){
    binary::Binary number = construct_binary();
    binary::Binary other;
    int choice;
    while(true){
      std::cout << number_menu << ">";
      choice = get_stdin<int>();
      switch(choice){
        case 1:
          other = construct_binary();
          number = number + other;
          break;
        case 2:
          number++;
          break;
        case 3:
          std::cout << number << "Or " << number.fromBinary() << " in decimal\n";
          break;
        case 4:
          number = construct_binary();
      }
    }
  }
  binary::Binary construct_binary(){
    try{
      std::cout << input_menu << ">";
      int choice;
      std::cin >> choice;

      binary::Binary res;
      std::string binary_string;
      long int number;

      switch(choice){
        case 1:
          binary_string = get_stdin<std::string>();
          res = binary::Binary(binary_string);
          break;
        case 2:
          number = get_stdin<long int>();
          res = binary::Binary(number);
          break;
        case 3:
          res = binary::Binary();
        default:
          throw std::runtime_error("Unknown command");
      }
      return res;
    }
    catch(const std::exception &exc){
      std::cerr << exc.what() << std::endl;
      exit(0);
    }
  }


  
};

int main(){
  testing::InitGoogleTest();
  RUN_ALL_TESTS();
  Main main = Main();
  main.menu();
  return 0;
}
