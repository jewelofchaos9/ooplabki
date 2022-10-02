#include "binary.hpp"
#include <string>
#include <cmath>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
namespace binary{

std::string Binary::toBinary(long int number){
  std::string answer(binary::MAX,'0');
  if(number == 0){
    return answer;
  }
  if (std::log2(std::abs(number)) > binary::MAX - 1){
    throw std::runtime_error("Number is larger then maximmal!");
  }

  if(number < 0){
    answer[0] = '1';
    number = std::abs(number);
  }
  int i = 0;
  while(number > 0){
    answer[binary::MAX - 1 - i] = std::to_string(number % 2)[0];
    i++;
    number /= 2;
  }
  return answer;
}

Binary::Binary(std::string number){
  if(number.length() > binary::MAX){
    throw std::runtime_error("Cannot fit this number");
  }
  while(number.length() < binary::MAX){
    number += "0";
  }
  this->number = number;
}

Binary::Binary(long int number) : Binary(toBinary(number)){
  try{
  }
  catch(...){
    throw std::runtime_error("Cannot fit this number");
  }
}

Binary::Binary() : Binary(0){
  try{
  }
  catch(...){
    throw std::runtime_error("Cannot fit this number");
  }
}

Binary Binary::additionalCode(){
  /*
   * Standart additional code from computer science. 
   * We return same Binary type number but in additional code
   */
  if(number[0] == '0'){
    return *this;
  }

  std::string additionalCode = std::string(binary::MAX, '1');
  for(int i = 1; i < number.size(); i++){
    if(number[i] == '0'){
      additionalCode[i] = '1';
    }
    else{
      additionalCode[i] = '0';
    }
  }

  Binary ans = Binary(additionalCode);
  ans++;
  return ans; 
}


Binary& Binary::operator++(int){
  /*
  * Going from last bit to first not signifant.
  * If we see 0, its the end, we can and 0
  * Else we rewrite 1 to 0 and go to next step waiting for 0
  *
  * If we dont see 0 we receive SIGNBIT | 000000......., as a int overflow
  * I dont have to catch it, its a normal pratcive to overflow int in C-like languages :D
  *
  * If we try to increase negative it will increase by mod!!!! 
  * e.g. -5++ = -6
  */

  for(int i = binary::MAX - 1; i > 0; i--){
    if(this->number[i] == '0'){
      this->number[i] = '1';
      break;
    }
    this->number[i] = '0';
  }
  return *this;
}
Binary& Binary::operator--(int){
  for(int i = binary::MAX - 1; i > 0; i--){
    if(this->number[i] == '1'){
      this->number[i] = '0';
      break;
    }
    this->number[i] = '1';
  }
  return *this;
}

void Binary::addByIndex(int index){
  for(int i = index; i >= 0; i--){
    if(this->number[i] == '0'){
      this->number[i] = '1';
      break;
    }

    this->number[i] = '0';
  }
}

Binary Binary::fromAdditionalCode(){
  if(number[0] == '0'){
    return *this;
  }
  Binary straightCode = Binary(*this);
  straightCode--;
  for(int i = binary::MAX - 1; i > 0; i--){
    if(straightCode.number[i] == '0'){
      straightCode.number[i] = '1';
    }
    else if(straightCode.number[i] == '1'){
      straightCode.number[i] = '0';
    }
  }
  return straightCode;
}

Binary Binary::operator+(Binary other){
  Binary res = this->additionalCode();// at first we take a copy of binary
  Binary otherAdditional = other.additionalCode();
    
  for(int i = binary::MAX - 1; i >= 0; i--){
    if(otherAdditional.number[i] == '1'){
      res.addByIndex(i);
    }
  }
  return res.fromAdditionalCode();

}

long Binary::fromBinary(){
  if(binary::MAX > 64){
    return -1;
  }
  long coef = 1;
  long ans = 0;

  for(int i = binary::MAX - 1; i > 0; i--){
    if(number[i] == '1'){
      ans += coef;
    }
    coef *= 2;
  }
  
  if(number[0] == '1'){
    return -ans;
  }
  
  return ans;
}

char Binary::numeral(){
  if(number[0] == '0'){
    return '+';
  }
  return '-';
}

std::string Binary::str(){
  return this->number;
}

std::ostream& operator<<(std::ostream &out, binary::Binary i){
  return out << i.str() << std::endl;
}

}



struct TestBinary1: testing::Test{
  binary::Binary *a;
  binary::Binary *b;
  TestBinary1() {
    a = new binary::Binary(5);
    b = new binary::Binary(-6);
  }
  ~TestBinary1() {
    delete a;
    delete b;
  }
};

TEST_F(TestBinary1, add_operator){
  if(binary::MAX < 64){
    EXPECT_EQ(a->fromBinary(), 5);
    EXPECT_EQ(b->fromBinary(), -6);
    EXPECT_EQ((*a + *b).fromBinary(), -1);
    EXPECT_EQ(((*a)++ + *b).fromBinary(), 0);
  }
}

struct TestBinary2: testing::Test{
  binary::Binary *a;
  binary::Binary *b;
  TestBinary2() {
    a = new binary::Binary(-5);
    b = new binary::Binary(-6);
  }
  ~TestBinary2() {
    delete a;
    delete b;
  }
};

TEST_F(TestBinary2, add_operator){
  if(binary::MAX < 64){
    EXPECT_EQ(a->fromBinary(), -5);
    EXPECT_EQ(b->fromBinary(), -6);
    EXPECT_EQ((*a + *b).fromBinary(), -11);
    EXPECT_EQ(((*a)++ + *b).fromBinary(), -12);
  }
}
