/* File: Exercise2.c */
#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE !FALSE
#define OK 0
#define ERROR -1
#define UnsuccessfulCreation 42

typedef struct nodetag *nodeptr;

typedef struct nodetag {
  nodeptr previous;
  int value;
  nodeptr next;
} nodetype;

typedef struct listtag {
  nodeptr head;
  nodeptr tail;
} listtype;

typedef listtype *listptr;

int Create(listptr *);
int Size(listptr);
int IsEmpty(listptr);
nodeptr GetFirst (listptr);
nodeptr GetLast (listptr);
nodeptr GetPrev(nodeptr);
nodeptr GetNext(nodeptr);
void AddBefore(nodeptr, nodeptr, listptr);
void AddAfter(nodeptr, nodeptr, listptr);
void AddFirst(nodeptr, listptr);
void AddLast(nodeptr, listptr);
void Remove (nodeptr, listptr);
int CreateNode(nodeptr *);
void PrintList(listptr);


int main(void) {
  listptr List;
  nodeptr Node1, Node2, Node3, Node4;
  
  if (printf("Create operation finished %s.\n", Create(&List) ? "successfully" : "unsuccessfully") == UnsuccessfulCreation) {
    return ERROR;
  }
  printf("List is%s empty.\n", IsEmpty(List) ? "" : " not");
  if(CreateNode(&Node1)) {
    printf("Insert an integer as value for Node1: ");
    scanf("%d", &(Node1->value));
  }
  if(CreateNode(&Node2)) {
    printf("Insert an integer as value for Node2: ");
    scanf("%d", &(Node2->value));
  }
  if(CreateNode(&Node3)) {
    printf("Insert an integer as value for Node3: ");
    scanf("%d", &(Node3->value));
  }
  if(CreateNode(&Node4)) {
    printf("Insert an integer as value for Node4: ");
    scanf("%d", &(Node4->value));
  }
  printf("List has %d nodes.\n", Size(List));
  GetFirst(List);
  GetLast(List);
  PrintList(List);
  AddFirst(Node1, List);
  PrintList(List);
  AddBefore(Node2, Node1, List);
  PrintList(List);
  AddAfter(Node3, Node2, List);
  PrintList(List);
  AddLast(Node4, List);
  PrintList(List);
  printf("List has %d nodes.\n", Size(List));
  printf("The value of first node in List is: %d\n", GetFirst(List)->value);
  printf("The value of its next node is: %d\n", GetNext(GetFirst(List))->value);
  printf("The value of last node is: %d\n", GetLast(List)->value);
  printf("The value of its previous node is: %d\n", GetPrev(GetLast(List))->value);
  PrintList(List);
  Remove(Node1, List);
  PrintList(List);
  Remove(Node2, List);
  PrintList(List);
  Remove(Node3, List);
  PrintList(List);
  Remove(Node4, List);
  PrintList(List);
  return OK;
}

int Create(listptr *ptr) {  //Ï(1)
  *ptr = malloc(sizeof(listtype));
  if ((*ptr) == NULL) {
    printf("Memory allocation failed!\n");
    return FALSE;
  }
  (*ptr)->head = NULL;
  (*ptr)->tail = NULL;
  return TRUE;
}

int Size(listptr list) {  //Ï(n)
  int counter = 0;
  nodeptr temp;
  if (IsEmpty(list));
  else {
    temp = list->head;
    counter++;
    while(temp->next != NULL) {
      counter++;
      temp = temp->next;
    }
  }
  return counter;
}

int IsEmpty(listptr list) {  //Ï(1)
  if (list->head == NULL || list->tail == NULL) {
    return TRUE;
  }
  return FALSE;
}

nodeptr GetFirst (listptr list) {  //Ï(1)
  if (!IsEmpty(list)) {
    return list->head;
  }
  printf("Attemp to get the first node of an empty list.\n");
}

nodeptr GetLast (listptr list) {  //Ï(1)
  if (!IsEmpty(list)) {
    return list->tail;
  }
  printf("Attemp to get the last node of an empty list.\n");
}

nodeptr GetPrev(nodeptr GivenNode) {  //Ï(1)
  if (GivenNode->previous != NULL) {
    return GivenNode->previous;
  }
  printf("This node does not have a previous one.\n");
}

nodeptr GetNext(nodeptr GivenNode) {  //Ï(1)
  if (GivenNode->next != NULL) {
    return GivenNode->next;
  }
  printf("This node does not have a next one.\n");
}

void AddBefore(nodeptr z, nodeptr v, listptr list) {  //Ï(1)
  if (v->previous != NULL) {
    z->next = v;
    z->previous = v->previous;
    v->previous->next = z;
    v->previous = z;
  }
  else {
    AddFirst(z, list);
  }
}

void AddAfter(nodeptr z, nodeptr v, listptr list) {  //Ï(1)
  if (v->next != NULL) {
  z->previous = v;
  z->next = v->next;
  v->next->previous = z;
  v->next = z;
  }
  else {
    AddLast(z, list);
  }
}

void AddFirst(nodeptr GivenNode, listptr list) {  //Ï(1)
  GivenNode->previous = NULL;
  GivenNode->next = list->head;
  if (!IsEmpty(list)) {
    list->head->previous = GivenNode;
  }
  else {
    list->tail = GivenNode;
  }
  list->head = GivenNode;
}

void AddLast(nodeptr GivenNode, listptr list) {  //Ï(1)
  GivenNode->next = NULL;
  GivenNode->previous = list->tail;
  if (!IsEmpty(list)) {
    list->tail->next = GivenNode;
  }
  else {
    list->head = GivenNode;
  }
  list->tail = GivenNode;
}

void Remove (nodeptr GivenNode, listptr list) {  //Ï(1)
  if (GivenNode == list->head) {
    if (GivenNode->next != NULL) {
      GivenNode->next->previous = NULL;
      list->head = GivenNode->next;
    }
    else {
      list->head = NULL;
    }
  }
  else if(GivenNode == list->tail) {
    if (GivenNode->previous != NULL) {
      GivenNode->previous->next = NULL;
      list->tail = GivenNode->previous;
    }
    else {
      list->tail = NULL;
    }
  }
  else {
    GivenNode->previous->next = GivenNode->next;
    GivenNode->next->previous = GivenNode->previous;
  }
  free(GivenNode);
}

int CreateNode(nodeptr *ptr) {
  (*ptr) = malloc(sizeof(nodetype));
  if ((*ptr) == NULL) {
    printf("Memory allocation failed!\n");
    return FALSE;
  }
  return TRUE;
}

void PrintList(listptr list) {
  nodeptr temp;
  if (IsEmpty(list)) {
    printf("List is empty.");
  }
  else {
    printf("%d", list->head->value);
    temp = list->head;
    while(temp->next != NULL) {
      printf(" -> %d", temp->next->value);
      temp = temp->next;
    }
  }
  printf("\n");
}
