#include <stdbool.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

char * dataFileName = "DATA/data.dat";
char * indexFileName= "DATA/index.dat";
char * flagNAme= "DATA/flag";
char * IDname= "DATA/ID";

typedef struct link
{
	int id;
	char firstName[20];
	char lastName[20];
	char address[100];
	int age;
	char dept[30];
	bool isDeleted;
} PERSON;

void upper_string(char s[]);
void updateID(int id);
int getID();
void getPersonInf(int id);

/* DATA FILE AND INDEX FILE CONTROL */
void createFlag();
void deleteFlag();
bool isCreated();
/* DATA FILE AND INDEX FILE CONTROL */

/* FLAG OPERATION */
// flag : create a file
void createFlag()
{
	FILE * file = fopen(flagNAme, "wb");
	fclose(file);
}

void deleteFlag()
{
	remove(flagNAme);
}

bool isCreated() {
	FILE * file;
	
	if(!fopen(flagNAme, "r")) return 0;
	else return 1;
}
/* FLAG OPERATION */

// make upper case related string
void upper_string(char s[]) {
   int c = 0;
 
   while (s[c] != '\0') {
      if (s[c] >= 'a' && s[c] <= 'z') {
         s[c] = s[c] - 32;
      }
      c++;
   }
}

// record is read from data file
void getPersonInf(int id)
{
	PERSON s;
    PERSON *s2 = &s;
    FILE *file;
 
    file = fopen(dataFileName, "r+b");
    
    fseek(file, (id-1) * sizeof(*s2), SEEK_SET);
 
    fread(s2, sizeof(*s2), 1, file);
		
	printf("%s", s2->firstName);
	printf(" %s", s2->lastName);
	printf("\t%s", s2->address);
	printf("\t%d", s2->age);
	printf("\t%s\n", s2->dept);
    
    fclose(file);
}

// ID is written to ID file
void updateID(int id)
{
	FILE * file = fopen(IDname, "w");
	fprintf(file,"%d",id);
	fclose(file);
}
// ID is read from ID file
int getID()
{
	FILE * file = fopen(IDname, "r");
	int id;
	fscanf(file,"%d",&id);
	fclose(file);
	return id;
}
