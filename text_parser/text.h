/********************************************************************
name: Chris VanDoodewaard
student ID#: 1053471
uoguelp email: cvandood@uoguelph.ca

This file contains the header functions for assignment 2. 
********************************************************************/

#ifndef __DEFT__
#define __DEFT__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node_struct {
  void *data;
  struct node_struct *next;
};

struct queue {
  struct node_struct *head;
  struct node_struct **tail;
};

struct node_struct *txt2words(FILE *fp);
char *get_word(char **inputString, int *j);

struct node_struct *search(struct node_struct *list, char *target, int(*compar)(const void *, const void *));

struct node_struct *copy(struct node_struct *start, struct node_struct *end);

void ftext(FILE *fp, struct node_struct *list);

struct node_struct *sort(struct node_struct *list, int(*compar)(const void *, const void *));

void split(struct node_struct *mainList, struct node_struct *(split[1]));

struct queue *mini_sort(struct node_struct **listA, struct node_struct **listB, int numPop, int (*compar)(const void *, const void *));

void alternate(struct node_struct *result[1], struct node_struct **listA, struct node_struct **listB, int target, int (*compar)(const void *, const void *));

void remove_repeats(struct node_struct *list, int (*compar)(const void *, const void *));

int length(struct node_struct *list);

void free_list(struct node_struct *list, int free_data);

int charType(char *myChar);

#endif
