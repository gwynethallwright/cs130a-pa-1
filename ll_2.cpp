#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct node { 
   int coeff;
   int power; 
   struct node * next; 
}; 

void insert_at_end(struct node * prev, int new_coeff, int new_power) { 
   struct node * new_node = (struct node*) malloc(sizeof(struct node));
   new_node->coeff = new_coeff;
   new_node->power = new_power;
   new_node->next = NULL;
   prev->next = new_node;
}

void insert_in_middle(struct node * prev, int new_coeff, int new_power) { 
   struct node * new_node = (struct node*) malloc(sizeof(struct node));
   new_node->coeff = new_coeff;
   new_node->power = new_power;
   new_node->next = (prev->next)->next;
   prev->next = new_node;
}

void delete_in_middle(struct node * prev) {
   struct node * temp = prev->next;
   prev->next = (prev->next)->next;
   free(temp);
}

void delete_at_end(struct node * prev) {
   struct node * temp = prev->next;
   prev->next = NULL;
   free(temp);
}

void writePoly(struct node * head) { 
   struct node * ptr = head->next;
   while (ptr != NULL) { 
      cout << ptr->coeff << " " << ptr->power << " "; 
      ptr = ptr->next; 
   }
   cout << "\n";
}

auto readPoly(string input){
  static struct node actual_1;
  static struct node actual_2;
  static struct node * poly_1 = &actual_1;
  static struct node * poly_2 = &actual_2;
  string current;
  istringstream iss(input);
  iss >> current;
  long power;
  int operation = 1;
  struct node * ptr = poly_1;
  while (iss){
    if (current == "+"){
      ptr = poly_2;
    }
    else if (current == "*"){
      ptr = poly_2;
      operation = 0;
    }
    else if (current == "**"){
      operation = 2;
      break;
    }
    else {
      iss >> power;
      insert_at_end(ptr, stoi(current), power);
      ptr = ptr->next;
    }
    iss >> current;
  }
  struct result {struct node * polynomial_1; struct node * polynomial_2; int operation;};
  return result {poly_1, poly_2, operation};
}

struct node * mulPoly(struct node * poly_1, struct node * poly_2) {
   struct node * ptr_1 = poly_1->next;
   struct node * ptr_2 = poly_2->next;
   static struct node return_poly;
   static struct node * address = &return_poly;
   struct node * ptr_3 = &return_poly;
   while (ptr_1 != NULL) {
      while (ptr_2 != NULL) {

      }
      ptr_2 = poly_2->next;
   }
   return address;
}

struct node * addPoly(struct node * poly_1, struct node * poly_2) {
   struct node * ptr_1 = poly_1->next;
   struct node * ptr_2 = poly_2->next;
   static struct node return_poly;
   static struct node * address = &return_poly;
   struct node * ptr_3 = &return_poly;
   while ((ptr_1 != NULL) && (ptr_2 != NULL)) {
      if ((ptr_1->power) < (ptr_2->power)){
         insert_at_end(ptr_3, ptr_1->coeff, ptr_1->power);
         ptr_1 = ptr_1->next;
         ptr_3 = ptr_3->next;
      }
      else if ((ptr_2->power) < (ptr_1->power)){
         insert_at_end(ptr_3, ptr_2->coeff, ptr_2->power);
         ptr_2 = ptr_2->next;
         ptr_3 = ptr_3->next;
      }
      else if (((ptr_1->coeff+ptr_2->coeff)%1000000) != 0) {
         insert_at_end(ptr_3, (ptr_1->coeff+ptr_2->coeff)%1000000, ptr_1->power);
         ptr_1 = ptr_1->next;
         ptr_2 = ptr_2->next;
         ptr_3 = ptr_3->next;
      }
      else {
         ptr_1 = ptr_1->next;
         ptr_2 = ptr_2->next;
      }
   }
   while (ptr_1 != NULL) {
      insert_at_end(ptr_3, ptr_1->coeff, ptr_1->power);
      ptr_3 = ptr_3->next;
      ptr_1 = ptr_1->next;
   }
   while (ptr_2 != NULL) {
      insert_at_end(ptr_3, ptr_2->coeff, ptr_2->power);
      ptr_3 = ptr_3->next;
      ptr_2 = ptr_2->next;
   }
   return address;
}

int main(int argc, char** argv) { 
   auto [poly_1, poly_2, operation] = readPoly(argv[1]);
   writePoly(poly_1);
   writePoly(poly_2);
   struct node * new_poly = addPoly(poly_1, poly_2);
   writePoly(new_poly);
   return 0; 
} 