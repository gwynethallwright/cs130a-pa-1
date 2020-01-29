#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int * addPoly(int ** coeffs){
  static int * poly;
  poly = new int[100];
  for (int i = 0; i < 100; ++i){
    poly[i] = coeffs[0][i] + coeffs[1][i];
  }
  return poly;
}

int ** readPoly(string input){
  string current;
  int power;
  static int ** poly;
  poly = new int * [2];
  poly[0] = new int[100];
  poly[1] = new int[100];
  int i = 0;
  int add = 1;
  istringstream iss(input);
  do{
    iss >> current;
    if (current == "+"){
      i = i+1;
    }
    else if (current == "*"){
      i = i+1;
      add = 0;
    }
    else {
      iss >> power;
      poly[i][stoi(current)] = power;
    }
  } while (iss);
  return poly;
}

int main(int argc, char** argv){
  int ** poly;
  poly = readPoly(argv[1]);
  int * poly_result;
  poly_result = addPoly(poly);
  return 0;
}
