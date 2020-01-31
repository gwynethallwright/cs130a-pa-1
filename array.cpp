#include <iostream>
#include <sstream>
#include <string>
using namespace std;

void writePoly(long * coeffs){
  for (int i = 0; i < 10000; ++i){
    if (coeffs[i] != 0){
      cout << coeffs[i] << " " << i << " ";
    }
  }
  cout << "\n";
}

long * addPoly(long ** coeffs){
  static long * poly;
  poly = new long[10000];
  for (int i = 0; i < 10000; ++i){
    poly[i] = (poly[i] + coeffs[0][i] + coeffs[1][i])%1000000;
  }
  return poly;
}

long * mulPoly(long ** coeffs){
  static long * poly;
  poly = new long[10000];
  for (int i = 0; i < 10000; ++i){
    for (int j = 0; j < 10000; ++j){
      poly[(i+j)%10000] = (poly[(i+j)%10000] + coeffs[0][i] * coeffs[1][j])%1000000;
    }
  }
  return poly;
}

long * sqPoly(long ** coeffs){
  static long * poly;
  poly = new long[10000];
  for (int i = 0; i < 10000; ++i){
    for (int j = 0; j < 10000; ++j){
      poly[(i+j)%10000] = (poly[(i+j)%10000] + coeffs[0][i]*coeffs[0][j])%1000000;
    }
  }
  return poly;
}

auto readPoly(string input){
  string current;
  long power;
  static long ** poly;
  poly = new long * [2];
  poly[0] = new long[10000];
  poly[1] = new long[10000];
  int i = 0;
  int add = 1;
  istringstream iss(input);
  iss >> current;
  while (iss){
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
      poly[i][power%10000] = (poly[i][power%10000] + stoi(current))%1000000;
    }
    iss >> current;
  }
  struct result {long ** polynomial; int operation;};
  return result {poly, add};
}

int main(int argc, char** argv){
  auto [poly, operation] = readPoly(argv[1]);
  long * poly_result;
  if (operation == 0){
    poly_result = mulPoly(poly);
  }
  else if (operation == 1){
    poly_result = addPoly(poly);
  }
  else {
    poly_result = sqPoly(poly);
  }
  writePoly(poly_result);
  return 0;
  delete (poly);
  delete (poly_result);
}
