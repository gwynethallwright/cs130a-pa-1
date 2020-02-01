#include <iostream>
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

void display(struct node * head) { 
   struct node* ptr;
   ptr = head;
   while (ptr != NULL) { 
      cout<< ptr->coeff <<" "; 
      ptr = ptr->next; 
   } 
}

int main() { 
   struct node * head;
   struct node * ptr;
   head->coeff = 30;
   head->next = NULL;
   ptr = head;
   for (int i = 0; i < 10; ++i){
      insert_at_end(ptr, i, i);
      ptr = ptr->next;
   }
   cout<<"The linked list is: ";
   display(head);
   return 0; 
} 