#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int * readPoly(string input){
  static int poly[100] = {};
  istringstream iss(input);
  int index;
  int power;
  do{
    iss >> index;
    iss >> power;
    poly[index] = power;
      
  } while (iss);
  return poly;
}

int main(int argc, char** argv){
  string current;
  int power;
  int poly[2][100] = {};
  int i = 0;
  istringstream iss(argv[1]);
  do{
    iss >> current;
    if (current == "+"){
      i = i+1;
    }
    else if (current == "*"){
      i = i+1;
    }
    else {
      iss >> power;
      poly[i][stoi(current)] = power;
    }
  } while (iss);
  return 0;
}
