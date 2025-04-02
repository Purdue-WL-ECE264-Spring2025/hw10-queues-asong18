#include "linked_list.h"

#include <stdlib.h>

/*
  struct list_node {
  size_t value;
  struct list_node *next;
  };

  struct linked_list {
  struct list_node *head;
  };
*/
struct list_node *new_node(size_t value) { 
  struct list_node * NewNode = malloc(sizeof(struct list_node));
  NewNode->value = value;
  NewNode->next = NULL;
  return NewNode;
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node * ptr = new_node (value);
  list -> head -> next = ptr;
}

void insert_at_tail(struct linked_list *list, size_t value) {
  if (list->head == NULL) {
    list->head = new_node (value);
  }
  struct list_node * p = list->head;
  while ((p -> next) != NULL) {
    p = p->next;
  }
  p -> next = new_node (value);
}

size_t remove_from_head(struct linked_list *list) { 
  struct list_node * q = list -> head;
  // if (q == NULL) {
  //   return NULL;
  // }
  if (q -> value == list->head->value){
    list->head = list->head->next;
    free (q);
    return list -> head -> value;
  }
}

size_t remove_from_tail(struct linked_list *list) { 
  struct list_node * q;
  struct list_node * p =list ->head;
  q = p -> next;
  while ((q != NULL) && ((q -> value) != list->head->value)) {
    p = p->next;
    q = q->next;
  }
  if (q!=NULL){
    p->next = q->next;
    free (q);
  }
  return list->head->value;
}

void free_list(struct linked_list list) {
  while (list.head != NULL) {
    struct list_node * p = list.head->next;
    free (list.head);
    list.head = p;
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
