#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int * addPoly(int ** coeffs){
  static int * poly;
  poly = new int[10000];
  for (int i = 0; i < 10000; ++i){
    poly[i] = (coeffs[0][i] + coeffs[1][i])%1000000;
  }
  return poly;
}

int * mulPoly(int ** coeffs){
  static int * poly;
  poly = new int[10000];
  for (int i = 0; i < 10000; ++i){
    for (int j = 0; j < 10000; ++j){
      poly[(i+j)%1000000] = (coeffs[0][i]*coeffs[1][j])%1000000;
    }
  }
  return poly;
}

int * sqPoly(int ** coeffs){
  static int * poly;
  poly = new int[10000];
  for (int i = 0; i < 10000; ++i){
    for (int j = 0; j < 10000; ++j){
      poly[(i+j)%1000000] = (coeffs[0][i]*coeffs[1][j])%1000000;
    }
  }
  return poly;
}

auto readPoly(string input){
  string current;
  int power;
  static int ** poly;
  poly = new int * [2];
  poly[0] = new int[10000];
  poly[1] = new int[10000];
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
    else if (current == "**"){
      add = 2;
      break;
    }
    else {
      iss >> power;
      poly[i][power%10000] = stoi(current)%1000000;
    }
  } while (iss);
  struct result {int ** polynomial; int operation;};
  return result {poly, add};
}

void writePoly(int * coeffs){
  for (int i = 0; i < 10000; ++i){
    if (coeffs[i] != 0){
      cout << to_string(coeffs[i]) << " " << to_string(i) << " ";
    }
  }
  cout << "\n";
}

int main(int argc, char** argv){
  auto [poly, operation] = readPoly(argv[1]);
  int * poly_result;
  if (operation == 0){
    poly_result = mulPoly(poly);
  }
  else if (operation == 1){
    poly_result = addPoly(poly);
  }
  else{
    poly_result = sqPoly(poly);
  }
  writePoly(poly_result);
  return 0;
}
