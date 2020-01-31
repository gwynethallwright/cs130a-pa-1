#include <iostream>
#include <sstream>
#include <string>
#include <set>
using namespace std;

void writePoly(long * coeffs){
  for (int i = 0; i < 10000; ++i){
    if (coeffs[i] != 0){
      cout << coeffs[i] << " " << i << " ";
    }
  }
  cout << "\n";
}

void writePoly2(long * coeffs, set <int> * to_display){
  std::set<int>::iterator it = to_display->begin();
  while (it != to_display->end()){
    cout << coeffs[*it] << " " << (*it) << " ";
    it++;
  }
  cout << "\n";
}

long * addPoly(long ** coeffs, set <int> * accessed){
  static long polynomial [10000];
  long * poly;
  poly = polynomial;
  set <int> add_to_accessed;
  std::set<int>::iterator it = accessed->begin();
  while (it != accessed->end()){
    poly[*it] = (poly[*it] + coeffs[0][*it] + coeffs[1][*it])%1000000;
    if ((poly[*it] + coeffs[0][*it] + coeffs[1][*it]) != 0){
      add_to_accessed.insert(*it);
    }
    it++;
  }
  return poly;
}

long * mulPoly(long ** coeffs, set <int> * accessed){
  static long polynomial [10000];
  long * poly;
  poly = polynomial;
  set <int> add_to_accessed;
  set <int> remove_from_accessed;

  std::set<int>::iterator it = accessed->begin();
  while (it != accessed->end()){
    std::set<int>::iterator it2 = accessed->begin();
    while (it2 != accessed->end()){
      poly[((*it)+(*it2))%10000] = (poly[((*it)+(*it2))%10000] + coeffs[0][*it]*coeffs[1][*it2])%1000000;
      if ((poly[((*it)+(*it2))%10000] + coeffs[0][*it]*coeffs[1][*it2]) != 0){
        add_to_accessed.insert(((*it)+(*it2))%10000);
      }
      remove_from_accessed.insert(*it2);
      it2++;
    }
    remove_from_accessed.insert(*it);
    it++;
  }
  std::set<int>::iterator it3 = remove_from_accessed.begin();
  while (it3 != remove_from_accessed.end()){
    accessed->erase(*it3);
    it3++;
  }
  accessed->insert(add_to_accessed.begin(), add_to_accessed.end());
  return poly;
}

long * sqPoly(long ** coeffs, set <int> * accessed){
  static long polynomial [10000];
  long * poly;
  poly = polynomial;
  set <int> add_to_accessed;
  set <int> remove_from_accessed;

  std::set<int>::iterator it = accessed->begin();
  while (it != accessed->end()){
    std::set<int>::iterator it2 = accessed->begin();
    while (it2 != accessed->end()){
      poly[((*it)+(*it2))%10000] = (poly[((*it)+(*it2))%10000] + coeffs[0][*it]*coeffs[0][*it2])%1000000;
      if ((poly[((*it)+(*it2))%10000] + coeffs[0][*it]*coeffs[0][*it2]) != 0){
        add_to_accessed.insert(((*it)+(*it2))%10000);
      }
      remove_from_accessed.insert(*it2);
      it2++;
    }
    remove_from_accessed.insert(*it);
    it++;
  }
  std::set<int>::iterator it3 = remove_from_accessed.begin();
  while (it3 != remove_from_accessed.end()){
    accessed->erase(*it3);
    it3++;
  }
  accessed->insert(add_to_accessed.begin(), add_to_accessed.end());
  return poly;
}

auto readPoly(string input){
  string current;
  long power;
  static long polynomial_1 [10000];
  static long polynomial_2 [10000];
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
  int add = 1;
  set <int> * accessed;
  static set <int> access;
  accessed = &access;
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
      if (((poly[i][power%10000] + stoi(current))%10000) != 0){
        accessed->insert(power%10000);
      }
    }
    iss >> current;
  }
  struct result {long ** polynomial; int operation; set <int> * accessed;};
  return result {poly, add, accessed};
}

int main(int argc, char** argv){
  auto [poly, operation, accessed] = readPoly(argv[1]);
  long * poly_result;
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
