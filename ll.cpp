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
  struct node * poly_1;
  struct node * poly_2;
  string current;
  istringstream iss(input);
  iss >> current;
  long power;
  int operation = 1;
  struct node * ptr = poly_1;
  while (iss){
    if (current == "+"){
      ptr = poly_2;
      i = i+1;
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

int main(int argc, char** argv) { 
   auto [poly_1, poly_2, operation] = readPoly(argv[1]);
   /*
   struct node * ptr;
   head->coeff = 30;
   head->next = NULL;
   ptr = head;
   for (int i = 0; i < 10; ++i){
      insert_at_end(ptr, i, i);
      ptr = ptr->next;
   }
   delete_in_middle(head->next->next->next);
   delete_at_end(head->next->next->next->next->next->next);
   cout<<"The linked list is: ";
   */
   writePoly(poly_1);
   writePoly(poly_2);
   return 0; 
} 