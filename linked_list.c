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
  struct list_node *nd = malloc(sizeof(struct list_node));
  nd -> value = value;
  nd -> next = NULL;
  return nd; 
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node * ptr = new_node (value);
  ptr -> next = list;
  return ptr;
}

void insert_at_tail(struct linked_list *list, size_t value) {
  if (list == NULL) {
    return new_node (value);
  }
  struct list_node * p = list;
  while ((p->next) != NULL) {
    p = p -> next;
  }
  p -> next = new_node (value);
  return list;
}

size_t remove_from_head(struct linked_list *list) { 
  struct list_node * q = list->head;
  if (q == NULL){
    return NULL;
  }
  if (q->value==list->head->value){
    list->head = list->head->next;
    free (q);
    return list->head;
  }
}

size_t remove_from_tail(struct linked_list *list) { 
  return 0;
}

void free_list(struct linked_list list) {
  while (list.head != NULL){
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
