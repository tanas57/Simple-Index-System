#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "file.c"
void menu();
void ChooseProcces(int choice);

void menu()
{
	int choice;
	while(1)
	{
		printf("--- MENU ---\n1-Insert a new record\n2-Update a record\n3-Delete a record\n4-Search record(s)\n5-List all records\n6-Show Index File(Sorted)\n7-Exit");
		
		printf("\n\n Choice => ");
		
		scanf("%d", &choice);
		
		if(choice >= 1 && choice <= 7) ChooseProcces(choice);
		else printf("\n\n ERROR : INVALID CHOICE\n\n");
	}
}

void ChooseProcces(int choice)
{
	printf("\nYour choice %d \n", choice);
	if(choice == 1) { insertRecord(); createFlag(); }
	else if(choice == 2) { 
		printf("\n\n### First search record ###\n\n");
		char word[20];
		printf("\nEnter a letter : ");
		scanf("%s", word);
		if(searchIndex2(word) == 1)
		{
			printf("\n\nEnter PK to update (EX: Tayyip Muslu)");
			printf("\nPK : ");
			char first[20], last[20];
			scanf("%s %s", first, last);
			updateRecord(first, last);
			createFlag();
		}
	}
	else if(choice == 3)
	{
		printf("\n\n### First search record ###\n\n");
		char word[20];
		printf("\nEnter a letter : ");
		scanf("%s", word);
		if(searchIndex2(word) == 1)
		{
			printf("\n\nEnter PK to delete (EX: Tayyip Muslu)");
			printf("\nPK : ");
			char first[20], last[20];
			scanf("%s %s", first, last);
			deleteRecord(first, last);
			createFlag();
		}
	}
	else if(choice == 4) {
		char word[20];
		printf("\nEnter a letter : ");
		scanf("%s", word);
		searchIndex2(word);
	 }
	else if(choice == 5) listAll();
	else if(choice == 6) listIndex();
	else if(choice == 7) {
		
		// save index file
		saveIndexFile();
		deleteFlag();
		// terminate this program
		kill(getppid(), SIGKILL);
	}
	else
	{
		printf("\nError : invalid command \n\n");
	}
}
