#include <iostream>
#include <sstream>
#include <string>
#include <set>
using namespace std;

void writePoly(int * coeffs){
  for (int i = 0; i < 10000; ++i){
    if (coeffs[i] != 0){
      cout << coeffs[i] << " " << i << " ";
    }
  }
  cout << "\n";
}

void writePoly2(int * coeffs, set <int> * to_display){
  std::set<int>::iterator it = to_display->begin();
  while (it != to_display->end()){
    cout << coeffs[(*it)] << " " << (*it) << " ";
    it++;
  }
  cout << "\n";
}

int * addPoly(int ** coeffs, set <int> * accessed){
  static int * poly;
  poly = new int[10000];
  std::set<int>::iterator it = accessed->begin();
  while (it != accessed->end()){
    poly[*it] = (coeffs[0][*it] + coeffs[1][*it])%1000000;
    it++;
  }
  return poly;
}

int * mulPoly(int ** coeffs, set <int> * accessed){
  static int * poly;
  poly = new int[10000];
  std::set<int>::iterator it = accessed->begin();
  while (it != accessed->end()){
    std::set<int>::iterator it2 = accessed->begin();
    while (it2 != accessed->end()){
      poly[((*it)+(*it2))%10000] = poly[((*it)+(*it2))%10000] + (coeffs[0][*it]*coeffs[1][*it2])%1000000;
      it2++;
    }
    it++;
  }
  return poly;
}

int * sqPoly(int ** coeffs, set <int> * accessed){
  static int * poly;
  poly = new int[10000];
  std::set<int>::iterator it = accessed->begin();
  while (it != accessed->end()){
    std::set<int>::iterator it2 = accessed->begin();
    while (it2 != accessed->end()){
      poly[((*it)+(*it2))%10000] = poly[((*it)+(*it2))%10000] + (coeffs[0][*it]*coeffs[0][*it2])%1000000;
      it2++;
    }
    it++;
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
  set <int> * accessed;
  accessed = new set <int>;
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
      accessed->insert(power%10000);
    }
  } while (iss);
  struct result {int ** polynomial; int operation; set <int> * accessed;};
  return result {poly, add, accessed};
}

int main(int argc, char** argv){
  auto [poly, operation, accessed] = readPoly(argv[1]);
  int * poly_result;
  if (operation == 0){
    poly_result = mulPoly(poly, accessed);
  }
  else if (operation == 1){
    poly_result = addPoly(poly, accessed);
  }
  else {
    poly_result = sqPoly(poly, accessed);
  }
  writePoly2(poly_result, accessed);
  return 0;
}
