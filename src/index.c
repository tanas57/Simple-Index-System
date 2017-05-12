#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.c"

struct node
{
	int id;
	char firstName[20];
	char lastName[20];
	struct node *next;
} typedef LINK;

/* INDEX FILE OPERATIONS */
LINK *head = NULL;
//struct node *current = NULL;

LINK * getHead();
char * combineName(LINK * nod);

void printList();
void insertIndex(PERSON * record);
void readIndex(LINK * record);

int searchIndexName(char * first,  char * last);
int searchIndex(char * first, char * last);
int searchIndex2(char word[]);

LINK * findIndex(char * first, char * last);
void deleteIndex(LINK * index);
void bubbleSort(LINK *start);
void swap(LINK *a, LINK *b);

LINK * getHead() { return head; }

/* INDEX FILE OPERATIONS */
void printList() {
   
   struct node *ptr = head;
   
   printf("\n");
   //start from the beginning
   while(ptr != NULL) {
      printf("%s %s\n", ptr->firstName, ptr->lastName);
      ptr = ptr->next;
   }
}

// add a record to index file
void insertIndex(PERSON * record) {
   //create a link
   LINK *link = (LINK*) malloc(sizeof(LINK));
   
   strcpy(link->firstName, record->firstName);
   strcpy(link->lastName, record->lastName);
   link->id = record->id;
   //point it to old first node
   link->next = head;
   
   //point first to new first node
   head = link;
   
   // sort
   bubbleSort(head);
}

// read from data file to write to index file
void readIndex(LINK * record) {
   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
   
   strcpy(link->firstName, record->firstName);
   strcpy(link->lastName, record->lastName);
   link->id = record->id;
   
   //point it to old first node
   link->next = head;
   
   //point first to new first node
   head = link;
   
   bubbleSort(head);
}

// get a link according to record information
LINK * findIndex(char * first, char * last)
{
   LINK * current = head;

   //navigate through list
   while(current != NULL) {
		
		if(strcmp(current->firstName, first) == 0 && strcmp(current->lastName, last) == 0) return current;

		current = current->next;
   }      
   
   return NULL;
}

// delete a record from index file
void deleteIndex(LINK * index)
{
	LINK * current = head;
	LINK * parent;
	while(current != NULL)
	{
		if(current == index) // find link that will delete
		{
			if(index->next != NULL) 
			{
				parent->next = index->next;
				free(index);
				break;
			}
		}
		parent = current;
		current = current->next;
	}
}
//find a link with given first and last name
int searchIndex(char * first, char * last) {

   //start from the first link
   LINK * current = head;

   //navigate through list
   while(current != NULL) {
		//printf("seach : (%s %s) (%s %s)\n", current->firstName, current->lastName, first, last);
		if(strcmp(current->firstName, first) == 0 && strcmp(current->lastName, last) == 0) return current->id;

		current = current->next;
   }      
	
   //if data found, return the current Link
   return -1;
}

int searchIndexName(char * first,  char * last) {

   //start from the first link
   LINK * current = head;
   
   //navigate through list
   while(current != NULL) {
		//printf("seach : %s %s", current->firstName, current->lastName);
		if(strcmp(current->firstName, first) == 0 && strcmp(current->lastName, last) == 0) return current->id;

		current = current->next;
   }      
	
   //if data found, return the current Link
   return -1;
}

// search in linkedlist and PRINT list
int searchIndex2(char word[]) {

   //start from the first link
   LINK * current = head;
   
   printf("\n\n-----Search results-----\n");
   int count = 0;
   //navigate through list
   while(current != NULL) {
		
		upper_string(word);
		
		// record found
		if(strncmp(current->firstName, word, strlen(word)) == 0)
		{
			// show all information !!!
			getPersonInf(current->id);
			count++;
		}
		current = current->next;
   }      
   if(count < 1) { printf("Any record has not found, try again\n\n"); return 0; }
   else return 1;
   //if data found, return the current Link
}

// combine name and surname
char * combineName(LINK* nod)
{
	char* combine = malloc(sizeof(nod->firstName) + sizeof(nod->lastName) + 1);
	strcpy(combine, nod->firstName);
	strcat(combine, " ");
	strcat(combine, nod->lastName);
	return combine;
}

/* Bubble sort the given linked lsit */
void bubbleSort(LINK *start)
{
    int swapped, i;
    struct node *ptr1 = start;
    struct node *lptr = NULL;
 
    //Checking for empty list
    if (ptr1 == NULL)
        return;
 
    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr)
        {
            if (strcmp(combineName(ptr1),combineName(ptr1->next)) > 0)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}
 
/* function to swap data of two nodes a and b*/
void swap(LINK *a, LINK *b)
{
    char tempFirstname[20], tempLastname[20];
    strcpy(tempFirstname, a->firstName);
    strcpy(tempLastname, a->lastName);
    int tempID = a->id;
    
    strcpy(a->firstName, b->firstName);
    strcpy(a->lastName, b->lastName);
    a->id = b->id;
    
    strcpy(b->firstName, tempFirstname);
    strcpy(b->lastName, tempLastname);
    b->id = tempID;
}

/* INDEX FILE OPERATIONS */
