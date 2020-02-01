#include <iostream>
#include <sstream>
#include <string>
using namespace std;

const unsigned long max_coeff = 1000000;
const unsigned long max_power = 10000;

void writePoly(long * coeffs){
  for (int i = 0; i < max_power; ++i){
    if (coeffs[i] != 0){
      cout << coeffs[i] << " " << i << " ";
    }
  }
  cout << "\n";
}

long * addPoly(long ** coeffs){
  static long polynomial [max_power];
  long * poly;
  poly = polynomial;
  for (int i = 0; i < max_power; ++i){
    polynomial[i] = (polynomial[i] + coeffs[0][i] + coeffs[1][i])%max_coeff;
  }
  return poly;
}

long * mulPoly(long ** coeffs){
  static long polynomial [max_power];
  long * poly;
  poly = polynomial;
  for (int i = 0; i < max_power; ++i){
    for (int j = 0; j < max_power; ++j){
      poly[(i+j)%max_power] = (poly[(i+j)%max_power] + coeffs[0][i] * coeffs[1][j])%max_coeff;
    }
  }
  return poly;
}

long * sqPoly(long ** coeffs){
  static long polynomial [max_power];
  long * poly;
  poly = polynomial;
  for (int i = 0; i < max_power; ++i){
    for (int j = 0; j < max_power; ++j){
      poly[(i+j)%max_power] = (poly[(i+j)%max_power] + coeffs[0][i]*coeffs[0][j])%max_coeff;
    }
  }
  return poly;
}

auto readPoly(string input){
  string current;
  long power;
  static long polynomial_1[max_power];
  static long polynomial_2[max_power];
  long * poly_1;
  long * poly_2;
  long ** poly;
  poly_1 = polynomial_1;
  poly_2 = polynomial_2;
  static long * big_polynomial[2];
  big_polynomial[0] = poly_1;
  big_polynomial[1] = poly_2;
  poly = big_polynomial;

  int i = 0;
  int operation = 1;
  istringstream iss(input);
  iss >> current;

  while (iss){
    if (current == "+"){
      i = i+1;
    }
    else if (current == "*"){
      i = i+1;
      operation = 0;
    }
    else if (current == "**"){
      operation = 2;
      break;
    }
    else {
      iss >> power;
      poly[i][power%max_power] = (poly[i][power%max_power] + stoi(current))%max_coeff;
    }
    iss >> current;
  }
  struct result {long ** polynomial; int operation;};
  return result {poly, operation};
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
