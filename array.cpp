#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int * addPoly(int coeffs[2][100]){
  static int poly[100] = {};
  for (int i = 0; i < 100; ++i){
    poly[i] = coeffs[0][i] + coeffs[1][i];
    cout << poly[i] << "\n";
  }
  return poly;
}

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
  int * poly_result;
  int i = 0;
  int add = 1;
  istringstream iss(argv[1]);
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
  poly_result = addPoly(poly);
  return 0;
}
