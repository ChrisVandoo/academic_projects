#include "text.h"

/********************************************************************
name: Chris VanDoodewaard
student ID#: 1053471
uoguelp email: cvandood@uoguelph.ca

This file contains the required functions for assignment 2. It has the 
functionality to read in a text file, search the file, copy a section
of the file, sort the file and remove repeating words from the file.
********************************************************************/

/*
This function parses the input file, creating a linked list containing
individual words. A pointer to the beginning of the linked list is 
returned.
*/
struct node_struct *txt2words(FILE *fp) {
  int j = 0;
  int len = 0;
  char *lineText;
  char *top;
  char **textToParse;
  char *word;
  struct node_struct *head;
  struct node_struct **current;

  current = &head;
  
  textToParse = &lineText;
  *textToParse = malloc((sizeof(char) * 256));
  top = *textToParse;
 
  /*reads in one line of text from the file at a time until
  the end of file is reached*/
  while (fgets(*textToParse, 256, fp) != NULL)
  {
    j = 0;    
    len = strlen(*textToParse);
    
    while (j < len) 
    {
      word = get_word(textToParse, &j);
      /*creates a node in the linked list */ 
      if (word != NULL){
        *current = malloc(sizeof(struct node_struct));
        (*current)->data = word;
        current = &((*current)->next);
      }          
    }
    *textToParse = NULL;
    free(top);
    *textToParse = malloc((sizeof(char) * 256));
    top = *textToParse;
  }

  
  free(*textToParse);

  *current = NULL;
  return head;
}

/*
This function prints out a linked list, formatting the text 
to not exceed 80 characters per line, and retaining all other 
original formatting.
*/
void ftext(FILE *fp, struct node_struct *list) {
  int wordType;
  int nextWordType;
  int lineLen = 0;
  char * word;
  char * nextWord;

  word = list->data;

  while (list != NULL) {
    lineLen = 0;
    /*this loop prints out 80 characters, but not more*/
    while(((lineLen + strlen(word)) < 80) && (list != NULL)){
      if (list->data != NULL){
        word = list->data;

        if(list->next != NULL) {
          nextWord = (list->next)->data;
        }

        wordType = charType(word);
        nextWordType = charType(nextWord);
        
        /* printf("currWordType: %d\n", currWordType); */
        /*this formats the output according to the type of word*/
        if (wordType == 1)
        {
          fprintf(fp, " %s", (char *)(list->data));
        }
        else if (wordType == 2)
        {
          fprintf(fp, "%s", (char *)(list->data));
        }
        else if ((wordType == 3) && (nextWordType == 3))
        {
          lineLen = 81;
        }
        else if (wordType == 4){
          /*do nothing...*/
        }
        else if (wordType == 5) {
          fprintf(fp, "%s", (char*)(list->data));
        }
        else if (wordType == 3){
          /*do nothing...*/
        }
        else
        {
          fprintf(fp, "%s ", (char *)(list->data));
        }

        lineLen = lineLen + strlen(word) + 1;
        list = list->next;
      } else {
        list = list->next;
      }
    }
    fprintf(fp, "\n");  
  }
}

/*a helper function that defines the type of word*/
int charType (char * myChar) {
  char nextChar;
  char doubleNextChar;
  int wordType;

  nextChar = *myChar;
  doubleNextChar = *(myChar + 1);

  if ((isalnum(nextChar)) != 0)
  {
    wordType = 1;
  }
  /*if the next two chars are punct is true*/
  else if ((ispunct(nextChar)) && (ispunct(doubleNextChar)) && (nextChar != ' '))
  {
    wordType = 2;
  }
  /*checks if char contains newline, should be careful of OS system diff on end of line chars
  -the double new line should ensure the second newline is a blank line */
  else if ((nextChar == '\n') || ((nextChar == '\r') && (doubleNextChar == '\n')))
  {
    wordType = 3;
  }
  else if (nextChar == ' ')
  {
    wordType = 4;
  }
  else if (ispunct(nextChar)){
    wordType = 5;
  }
  else
  {
    wordType = 1;
  }

  return wordType;
}

/*******************************************************************************
The purpose of this function is to take a double pointer (this should be a
sentence) and will return a malloced string containing the first word of the
input string. The double pointer will be incremented to point to the next word
in the sentence.
*******************************************************************************/
char *get_word(char **inputString, int *j) {
  #ifdef ERROR1
    printf("initial mem address, inputString: %p\n", *inputString);
    /*printf("made it into get_word\n");
    printf("first char: %c\n", **inputString);*/
  #endif

  char *word;
  int wordType;
  char nextChar;
  char doubleNextChar;
  int i;
  char *opString;
  /*if i = 1, ie only one character in the string, doublenextchar doesnt = anything
  and i should incorporate a special case for this!!!*/

  /*use a temp string to avoid losing start of line of text for copying later*/
  opString = *inputString;
  /*nextChar = the first character in the input string*/
  nextChar = *opString;
  /*increments the opString to point to the next char in the array*/
  opString = opString + 1;
  /*sets the 2nd char in the input Array = doubleNextChar*/
  doubleNextChar = *opString;

  #ifdef D
    printf("NextChar: %c\n", nextChar);
    printf("doubleNextChar: %c\n", doubleNextChar);
  #endif

  /*checks if character is a number or letter*/
  if ((isalnum(nextChar)) != 0)
  {
    wordType = 1;
  }
  /*if the next two chars are punct is true*/
  else if ((ispunct(nextChar)) && (ispunct(doubleNextChar)))
  {
    wordType = 2;
  }
  /*checks if char contains newline, should be careful of OS system diff on end of line chars
  -the double new line should ensure the second newline is a blank line */
  else if (nextChar == '\n') 
  {
    wordType = 3;
  }
  else if (nextChar == ' ')
  {
    wordType = 4;
  }
  else
  {
    wordType = 1;
  }

  #ifdef D
    printf("wordType: %d\n", wordType);
  #endif

  /* should read in an entire word from the input string or continous serious of
  punctuation. i = the number of characters contained in the new word */
   switch (wordType) {
    case 1:
      i = 0;
      

      /*if the next character is a letter, or a single dash or hyphen add that
      char to the newword*/
      while ((isalnum(nextChar)) || ((nextChar == '\'') && (isalnum(doubleNextChar))) ||
              ((nextChar == '-') && (isalnum(doubleNextChar))))
      {
        /*printf("i in case 1: %d\n", i);*/
        nextChar = doubleNextChar;
        opString = opString + 1;
        doubleNextChar = *opString;

        #ifdef D
          printf("In Case 1 Loop:\n");
          printf("nextchar = %c\n", nextChar);
          printf("doubleNextChar = %c\n", doubleNextChar);
        #endif

        i++;
      }
      break;

    /* word 2 is continuous punctuation, and should be treated as a single word while
    the punctuation type does not change */
    case 2:
      i = 1;
      /*nextChar = *opString;*/
      while( nextChar == doubleNextChar) {
        opString = opString + 1;
        doubleNextChar = *opString;
        i++;
      }
      break;

    case 3:
      i = 1;
      break;

    case 4:
      i = -1;
      break;

    default:
      printf("something went wrong in the switch statement.\n");
      i = -1;

  }
  /*mallocs a char string long enough to hold the new word and copies that word
  using strncpy appending a newline at the end of the word */
 
  /*this is for a word w one char, makes room for null terminator*/
  if (i == 0) {
    i = i + 2;
  } else if (i == -1) {
    *j = *j +1;
    *inputString = *inputString + 1;
    return NULL;
  }

  word = (char*)malloc((i+1) * sizeof(char));

  #ifdef D
    printf("val of memAddres, inputString, EOF: %p\n", inputString);
    printf("val of **inputString, %c \n", **inputString);
  #endif

  strncpy(word, *inputString, i);
   

#ifdef S
    printf("Word (in get_word): %s, i: %d \n", word, i);
  #endif

  *(word + (i + 1)) = '\0';

  /*increments the input string to point at the start of the next word */
  *inputString = *inputString + i;
  *j = *j + i;

  #ifdef ERROR1
    printf("j: %d\n", *j);
  #endif
  return word;
}

/*This function searches throught the linked list looking for values matching target and
returns a shallow copy of the matching values in a linked list*/
struct node_struct *search(struct node_struct *list, char *target, int(*compar)(const void *, const void *)){
  struct node_struct *head, **ptr;
  int compVal = -1;
  int match = 0;
  /* int mallocs = 0; */
  const void * searchVal;

  searchVal = target;

  ptr = &head; 

  while (list != NULL) {
    /*search function is case sensitive*/
    if (list->data != NULL){
      compVal = (*compar)(searchVal, list->data);
    } else {
      compVal = -1;
    }
    
    if (compVal == 0){
      match++;
      #ifdef D
        printf("compVal: %d\n", compVal);
      #endif

      *ptr = malloc(sizeof(struct node_struct));
      /* mallocs++; */
      
      if (ptr == NULL) {
        printf("malloc failed, search()\n");
      }
      (*ptr)->data = list;
      (*ptr)->next = NULL;
      ptr = &((*ptr)->next);
    }
    list = list->next;
  }
  if (match == 0) {
    free(*ptr);
    head = NULL;
  }
  /* printf("search: mallocs: %d\n", mallocs); */
  return head;
}

/*this function accepts a start and end parameter and iterates through the linked list
creating a copy beginning at the start pointer and continuing to the end pointer*/
struct node_struct *copy(struct node_struct *start, struct node_struct *end)
{
  /* int i = 0; */
  /* int mallocs = 0; */
  struct node_struct *head, **other;
  head = NULL;
  other = &head;

  if (start != NULL) {
    while (start != end){
      /* i++; */
      *other = malloc(sizeof(struct node_struct));
      /* mallocs++; */
      if (other == NULL) {
        printf("malloc failed, copy()\n");
      }
      (*other)->data = start->data;
      (*other)->next = NULL;
      other = &((*other)->next);
      
      start = start->next;
      /* printf("i: %d\n", i); */
    }
  }
 /*  printf("exits*textToParse the loop\n");
  printf("copy: mallocs: %d\n", mallocs); */

  return head;
}

/*this is the sort function, it has 3 helper functions, split, alternate, mini_sort and 
uses a merge sort algorithm to sort a linked list*/
struct node_struct *sort(struct node_struct *list, int(*compar)(const void *, const void *)) {
  int section = 1;
  struct node_struct *myLists[2];

  split(list, myLists);

  while ((myLists[0] != NULL) && (myLists[1] != NULL)) {
    alternate(myLists, myLists, (myLists + 1),section, compar);
    /* ftext(stdout, myLists[0]);
    printf("\n");
    ftext(stdout, myLists[1]);
    printf("\n\n"); */
    section = section * 2;
  }

  if (myLists[0] != NULL) {
    return myLists[0];
  } else {
    return myLists[1];
  }
}

/*this function splits a linked list into two equal lists*/
void split(struct node_struct * mainList, struct node_struct *split[2]) {
  struct node_struct **temp1, **temp2;
  struct node_struct *head1, *head2;
  /* int mallocs = 0; */
  int toggle = 0;

  if (mainList != NULL) {
    temp1 = &head1;
    temp2 = &head2;

    while (mainList)
    {
      if (toggle == 0){
        *temp1 = malloc(sizeof(struct node_struct));
       /*  mallocs++; */
        (*temp1)->data = mainList->data;
        (*temp1)->next = NULL;
        temp1 = &((*temp1)->next);
        toggle = 1;

        mainList = mainList->next;
      } else {        
        *temp2 = malloc(sizeof(struct node_struct));
        /* mallocs++; */
        (*temp2)->data = mainList->data;
        (*temp2)->next = NULL;
        temp2 = &((*temp2)->next);
        toggle = 0;

        mainList = mainList->next;
      }
    }
    
    split[0] = head1;
    split[1] = head2;
  } 
  /* printf("split: mallocs: %d\n", mallocs);    */
}

/*this function takes two inputs lists and sorts numPop items from each list, creating two new sorted output lists*/
struct queue *mini_sort(struct node_struct **listA, struct node_struct **listB, int numPop, int (*compar)(const void *, const void *))
{
  struct node_struct *head, **sortList;
  struct queue * sort;
  int numNodeA = 0;
  int numNodeB = 0;
  /*if negative: A<B, if pos: B<A, if 0: A=B*/
  int compVal;

  sort = malloc(sizeof(struct queue));

  sortList = &head;

  while ((numNodeA < numPop) && (*listA != NULL) && (numNodeB < numPop) && (*listB != NULL)) {
    compVal = (*compar)((*listA)->data, (*listB)->data);
    
    if (compVal < 0){
      *sortList = *listA;
      *listA = (*listA)->next;
      (*sortList)->next = NULL;
      sortList = &((*sortList)->next);
      numNodeA++;
    } else {
      *sortList = *listB;
      *listB = (*listB)->next;
      (*sortList)->next = NULL;
      sortList = &((*sortList)->next);
      numNodeB++;
    }
  }

  /*these loops finish adding any extra nodes to the sortedList*/
  while ((numNodeA < numPop) && (*listA != NULL)) {
    *sortList = *listA;
    *listA = (*listA)->next;
    (*sortList)->next = NULL;
    sortList = &((*sortList)->next);
    numNodeA++;
  }

  while ((numNodeB < numPop) && (*listB != NULL)) {
    *sortList = *listB;
    *listB = (*listB)->next;
    (*sortList)->next = NULL;
    sortList = &((*sortList)->next);
    numNodeB++;
  }

  sort->head = head;
  sort->tail = sortList;

  return sort;
}

/*this function takes the partially sorted lists from mini_sort and combines them back into one list until the two lists are completely sorted*/
void alternate(struct node_struct *result[2], struct node_struct **listA, struct node_struct **listB, int target, int (*compar)(const void *, const void *))
{
  struct queue sortArray[2]; 
  struct queue *temp;
  int numPop;
  int toggle = 1;

  numPop = target;

  sortArray->head = NULL;
  sortArray->tail = &(sortArray->head);

  (sortArray + 1)->head = NULL;
  (sortArray + 1)->tail = &((sortArray + 1)->head);

  /*this iterates through the entire two linked lists*/
  while(((*listA) != NULL) || ((*listB) != NULL)) {
    temp = mini_sort(listA, listB, numPop, compar);
    if (toggle == 1) {
      *(sortArray->tail) = temp->head;
      sortArray->tail = temp->tail;
      toggle = 0;
    } else {
      *((sortArray + 1)->tail) = temp->head;
      (sortArray + 1)->tail = temp->tail;
      toggle = 1;
    }
    free(temp);
  }

 
  result[0] =  sortArray->head;
  result[1] = (sortArray + 1)->head;
}

/*this function removes all repeating words from the inputted list*/
void remove_repeats(struct node_struct *list, int(*compar)(const void *, const void *)) {
  int comp;
  struct node_struct * temp;

  while (list->next != NULL) {
    
    comp = (*compar)(list->data, (list->next)->data);

    
    if (comp == 0){
      temp = list->next;
      list->next = temp->next;
      free(temp);
    } else {
      list = list->next;
    }
  }

}

/*this returns the length of an inputted list*/
int length(struct node_struct *list) {
  int i = 0;

  while (list != NULL){
    list = list->next;
    i++;
  }
  return i;
}

/*this frees the list*/
void free_list(struct node_struct *list, int free_data) {
  struct node_struct *temp;
  /* int frees = 0; */
  /* int i = 0; */

  while (list != NULL){
    temp = list;
    list = list->next;
    if (free_data != 0)
    {
      free(temp->data);
     /*  frees++; */
    }
    free(temp);
    /* frees++; */
    /* i++;
    printf("i: %d\n", i); */
  }

  /* printf("free_list: frees: %d\n", frees);*/
} 
