#include <iostream>
namespace matrix{

struct Edge{
  int index;
  double number;
  Edge *next;
};

struct Line{
  Edge *first;
};

struct Matrix{
  Line *lines;
  int lines_count;
  int line_len;
};

template <class T>

T getNum(std::istream& in = std::cin, std::ostream &out = std::cout){
  bool finish = 0;
  T res;
  while(!finish){
    in >> res;
    if(in.bad() || in.eof()){
      throw std::runtime_error("Bad, try again");
    }
    if(!in.good()){
      out << "Wrong number\n";
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

int getPositiveNum(std::istream& in = std::cin, std::ostream &out = std::cout){
  int res = getNum<int>();
  if (res <= 0){
    throw std::runtime_error("Thats not how mafia works");
  }
  return res;
}

void addEdge(Line &line, Edge *edge){
  if(line.first != nullptr){
    edge->next = line.first->next;
    line.first->next = edge;
    return;
  }
  line.first = edge;
}

Matrix getMatrix(std::istream& in = std::cin, std::ostream& out= std::cout){
  int lines_count, lines_len;
  try{
    std::cout << "Number of lines:\n>";
    lines_count = getPositiveNum(in,out); 
    std::cout << "Number of elements for each line:\n>";
    lines_len = getPositiveNum(in,out);
  }

  catch(...){
    throw std::runtime_error("User is mudak:(. Cannot create matrix");
  }
  
  Line *lines = new Line[lines_count];
  double to_add;
  for(int i = 0; i < lines_count; i++){
    for(int j = 0; j < lines_len; j++){
      try{
        to_add = getNum<double>();
        if(to_add != 0){
          Edge *new_edge = new Edge;
          new_edge->index = j;
          new_edge->number = to_add;
          addEdge(lines[i], new_edge);
        }
      }
      catch(...){
        throw std::runtime_error("Everything is broken");
      }
    }
  }
  Matrix matrix;
  matrix.line_len = lines_len;
  matrix.lines_count = lines_count;
  matrix.lines = lines;
  return matrix;
}

void printMatrix(Matrix matrix){
  for(int i = 0; i < matrix.lines_count; i++){
    Line line = matrix.lines[i];
    std::cout << "Line " << i << ":";
    for(Edge *edge = line.first; edge != nullptr; edge = edge->next){
      std::cout << "{" << edge->index << ":" << edge->number << "} ";
    }
    std::cout << std::endl;
  }
}

void erase(Matrix matrix){
  for(int i = 0; i < matrix.lines_count; i++){
    Edge *to_delete= matrix.lines[i].first;
    while(to_delete != nullptr){
      Edge *temp = to_delete->next;
      delete to_delete;
      to_delete = temp;
    }
  }
  delete[] matrix.lines;
}
double getFirstNum(Line line){
  if(line.first->index != 0){// First point is 0 
    return 0;
  }
  return line.first->number;
}
bool positive_cmp(Line line1, Line line2){
  return getFirstNum(line1) > getFirstNum(line2);
}
bool negative_cmp(Line line1, Line line2){
  return !(positive_cmp(line1,line2));
}
void sort(Matrix &matrix){//bubble sort lol
  if(matrix.lines[0].first == nullptr){
    return;
  }
  bool (*cmp)(Line,Line);
  if(matrix.lines[0].first->number > 0 && matrix.lines[0].first->index == 0){
    cmp = negative_cmp;
  }
  else{
    cmp = positive_cmp;
  }
  for(int step = 0; step < matrix.lines_count; ++step){
    for(int i = 0; i < matrix.lines_count - step - 1; ++i){
      if(cmp(matrix.lines[i], matrix.lines[i+1])){
        Line temp = matrix.lines[i];
        matrix.lines[i] = matrix.lines[i+1];
        matrix.lines[i+1] = temp;
      }
    }
  }
}
}
int main(){
  try{
    matrix::Matrix matrix = matrix::getMatrix();
    matrix::printMatrix(matrix);
    matrix::sort(matrix);
    std::cout << "=================\n";
    matrix::printMatrix(matrix);
    matrix::erase(matrix);
  }
  catch(...){
    std::cout << "huu\n";
  }
  return 0;
}
