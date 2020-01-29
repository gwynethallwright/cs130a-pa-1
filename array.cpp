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
  string coeffs;
  string current;
  int * poly_1;
  int * poly_2;
  istringstream iss(argv[1]);
  do{
    iss >> current;
    if (strcmp(current.c_str(), "+") == 0){
      poly_1 = readPoly(coeffs);
      coeffs = "";
    }
    else if (strcmp(current.c_str(), "*") == 0){
      poly_1 = readPoly(coeffs);
      coeffs = "";
    }
    else {
      coeffs = coeffs + current;
    }
  } while (iss);
  poly_2 = readPoly(coeffs);
  return 0;
}
