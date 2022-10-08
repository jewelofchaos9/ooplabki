#include "binary.hpp"
#include <string>
#include <cmath>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <time.h>
namespace binary{


Binary::Binary(std::string number){
  bool is_binary= true;

  for(int i = 0; i < number.size(); i++){
    is_binary = is_binary & (number[i] == '0' | number[i] == '1');
  }

  if(!is_binary){
    throw std::runtime_error("Not binary");
  }

  this->number = number;
}

std::string Binary::toBinary(long int number){
  if(number == 0){
    return std::string(1,'0');
  }
    


  this->degree = (long int)std::log2(std::abs(number)) + 2;
  // +2 is a magis number because of log2 in log2 returns the rational number, e.g log2(12)= 3, to 
  // we need to keep sign bit and the log2 + 1, so it is log2(12) + 2
  std::string answer = std::string(this->degree,'0');
  if(number < 0){
    answer[0] = '1';
    number = std::abs(number);
  }
  int i = 0;
  while(number > 0){
    answer[this->degree - 1 - i] = std::to_string(number % 2)[0];
    i++;
    number /= 2;
  }
  return answer;
}

Binary::Binary(long int number) : Binary(toBinary(number)){
  try{
  }
  catch(...){
    throw std::runtime_error("Cannot fit this number");
  }
}

Binary::Binary() : Binary(toBinary(0)){
  try{

  }
  catch(...){
    throw std::runtime_error("Cannot fir this number");
  }
}

std::string Binary::str(){
  return this->number;
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

  for(int i = this->number.size() - 1; i > 0; i--){
    if(this->number[i] == '0'){
      this->number[i] = '1';
      break;
    }
    else if (this->number[i] == '1'){
      this->number[i] = '0';
    }
  }
  return *this;
}


Binary Binary::additionalCode(){
  /*
   * Standart additional code from computer science. 
   * We return same Binary type number but in additional code
   */
  if(number[0] == '0'){
    return *this;
  }

  std::string additionalCode = std::string(number.length(), '1');
  for(int i = 1; i < number.length(); i++){
    if(number[i] == '0'){
      additionalCode[i] = '1';
    }
    else if(number[i] == '1'){
      additionalCode[i] = '0';
    }
  }

  Binary ans = Binary(additionalCode);
  ans++;
  return ans; 
}

Binary& Binary::operator--(int){
  for(int i = this->number.size(); i > 0; i--){
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
    return (this->number);
  }

  Binary straightCode = Binary(*this);
  straightCode--;
  for(int i = this->number.size() - 1; i > 0; i--){
    if(straightCode.number[i] == '0'){
      straightCode.number[i] = '1';
    }
    else if(straightCode.number[i] == '1'){
      straightCode.number[i] = '0';
    }
  }
  return straightCode;
}

std::string Binary::numberWithoutSign(){
  std::string num = std::string(this->number.length() - 1,'0');
  for(int i = 1; i < this->number.length(); i++){
    num[i-1] = this->number[i];
  }
  return num;

}
void Binary::stabalizeLength(Binary &first, Binary &second){
  int pad_length = std::max(first.number.length(), second.number.length()) + 3;

  while(first.number.length() < pad_length){
    first.number = std::string(1,first.number[0]) + "0" + first.numberWithoutSign();
  }
  while(second.number.length() < pad_length){
    second.number = std::string(1,second.number[0]) + "0" + second.numberWithoutSign();
  }
}


Binary Binary::operator+(Binary other){
  Binary res = Binary(*this);
  Binary otherCopy(other);
  this->stabalizeLength(res, otherCopy);
  

  res = res.additionalCode();// at first we take a copy of binary
  Binary otherAdditional = otherCopy.additionalCode();
  
  for(int i = res.number.length() - 1; i >= 0; i--){
    if(otherAdditional.number[i] == '1'){
      res.addByIndex(i);
    }
  }
  
  return res.fromAdditionalCode();
}

long int Binary::fromBinary(){
  if(number.length() >= 64){
    return 0;
  }

  long coef = 1;
  long ans = 0;

  for(int i = number.length() - 1; i > 0; i--){
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

std::ostream& operator<<(std::ostream &out, binary::Binary i){
  return out << i.str() << std::endl;
}

struct KekTest: testing::Test{

};
TEST_F(KekTest,sub_operator){
  srand(time(nullptr));
  for(int _ = 0; _ < 10000; _++){
    long int first = -rand();
    long int second = rand();
    binary::Binary *a = new binary::Binary(first);
    binary::Binary *b = new binary::Binary(second);

    EXPECT_EQ(a->fromBinary(), first);
    EXPECT_EQ(b->fromBinary(), second);
    EXPECT_EQ((*a + *b).fromBinary(), first + second);

    delete(a);
    delete(b);

  }
}
struct KekTest2: testing::Test{

};

TEST_F(KekTest2,add_operator){
  for(int i = 0; i < 10000; i++){
    long int first = rand();
    long int second = rand();

    binary::Binary *a = new binary::Binary(first);
    binary::Binary *b = new binary::Binary(second);

    EXPECT_EQ(a->fromBinary(), first);
    EXPECT_EQ(b->fromBinary(), second);
    EXPECT_EQ((*a + *b).fromBinary(), first + second);

    delete(a);
    delete(b);

  }
}
}
