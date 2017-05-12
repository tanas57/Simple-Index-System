#include "index.c"

/* INDEX FILE OPERATIONS */
void saveIndexFile();
void listIndex();

/* DATA FILE OPERATIONS */
void initial();
void insertRecord();
void updateRecord(char first[], char last[]);
void deleteRecord(char first[], char last[]);
void listAll();
/* DATA FILE OPERATIONS */

int ID = 0; // row number is unique (for row * struct size to read from data file)

// DATA Folder is created
// data and index files are created, and controled
// ID is controled, and loaded
void initial()
{
	mkdir("DATA", 0755);
	
	FILE *file;
 
    if(!fopen(dataFileName, "r")) {
        file = fopen(dataFileName, "wb");
        fclose(file);
    }
	
	if(!fopen(indexFileName, "r")) {
        file = fopen(indexFileName, "wb");
        fclose(file);
    }
    
    // read index file to linklist
    
    bool flag = isCreated();
    
    // there is no synchronization error, read index.dat file to load RAM
    if(!flag){
		FILE *fp = NULL;
    
		LINK s, *record;
		record = &s;
		
		fp = fopen(indexFileName, "rb");
		
		
		while (fread(record, sizeof(*record), 1, fp))
		{
			readIndex(record); // add to list
		}
		fclose(fp);
	}
	// there is a synchronization error. read data file, and create a new index file
    else{
		FILE *fp = NULL;
    
		PERSON s, *record;
		record = &s;
		
		fp = fopen(dataFileName, "rb");
		
		while (fread(record, sizeof(*record), 1, fp))
		{
			if(!record->isDeleted)
			{
				insertIndex(record);
			}
			
		}
		fclose(fp);
		
	}
    if(fopen(IDname, "r")) ID = getID();
    
}

// index from RAM is saved as file
void saveIndexFile()
{
	FILE *file;
	LINK s, *record;
	record = &s;
	
	file = fopen(indexFileName, "r+b");
	LINK *current = getHead();
	while(current != NULL)
	{
		fwrite(current, sizeof(*current), 1, file);
		current = current->next;
	}
	fseek(file, 0, SEEK_END);      // set file position at the end of file
	
	
	
	fclose(file);
	
}
// print list from RAM
void listIndex() { printList(); }

/* DATA FILE OPERATIONS */
// print data file from disk
void listAll()
{
    FILE *fp = NULL;
    
    PERSON s, *record;
	record = &s;
	
    fp = fopen(dataFileName, "rb");
    
	printf("\nID  NAME  ADDRESS  AGE  DEPARTMENT\n");
	
	fseek(fp, 0, SEEK_SET); 
	
	while (fread(record, sizeof(*record), 1, fp))
	{
		if(!record->isDeleted)
		{
			printf("%d", record->id);
			printf("    %s", record->firstName);
			printf(" %s", record->lastName);
			printf("    %s", record->address);
			printf("    %d    ", record->age);
			printf("    %s\n", record->dept);
		}
		
	}
    fclose(fp);
}

// update a record both data file in disk and index file in RAM
void updateRecord(char first[], char last[])
{	
    PERSON s;
    PERSON *record = &s;
    FILE *file;
 
    file = fopen(dataFileName, "r+b");
	upper_string(first); upper_string(last);
	int id = searchIndexName(first, last);
	if(id >= 0){
		
        fseek(file, (id-1) * sizeof(*record), SEEK_SET);
 
        fread(record, sizeof(*record), 1, file);
		
		LINK * current = findIndex(record->firstName, record->lastName);
		
		printf("\nEnter new Informations:\n\n");
		
		char answer;
		printf("Can you change firstname ? (Y/N) : "); scanf(" %c", &answer);
		if(answer == 'y' || answer == 'Y' )
		{
			printf("\nEnter first name : ");
			scanf("%s", record->firstName);
			upper_string(record->firstName);
			strcpy(current->firstName, record->firstName);
		}
		printf("Can you change lastname ? (Y/N) : "); scanf(" %c", &answer);
		if(answer == 'y' || answer == 'Y' )
		{
			printf("\nEnter last name : ");
			scanf("%s", record->lastName);
			upper_string(record->lastName);
			strcpy(current->lastName, record->lastName);
		}
		printf("Can you change address ? (Y/N) : "); scanf(" %c", &answer);
		if(answer == 'y' || answer == 'Y' )
		{
			printf("\nEnter address : ");
			scanf("%s", record->address);
			upper_string(record->address);
		}
		printf("Can you change age ? (Y/N) : "); scanf(" %c", &answer);
		if(answer == 'y' || answer == 'Y' )
		{
			printf("\nEnter age : ");
			scanf("%d", &record->age);
		}
		printf("Can you change department ? (Y/N) : "); scanf(" %c", &answer);
		if(answer == 'y' || answer == 'Y' )
		{
			printf("\nEnter department : ");
			scanf("%s", record->dept);
			upper_string(record->dept);
		}
		
		
		fseek(file, (id - 1) * sizeof(*record), SEEK_SET);
		fwrite(record, sizeof(*record), 1, file);
		
		fclose(file);
		
		printf("\n\nRecord has been updated !\n\n");
		
	}
	else{
		printf("\n\nERROR: Record does not exist\n\n");
	}
}

// delete a record from index in RAM
// give a flag for deleted record
// insert a record
void deleteRecord(char first[], char last[])
{
	PERSON s;
    PERSON *record = &s;
    FILE *file;
 
    file = fopen(dataFileName, "r+b");
    
    // first, find link and delete it
    // second give a flag to data file in disk
    
    upper_string(first); upper_string(last);
    
    LINK * current = findIndex(first, last);
    
    if(current != NULL)
    {
		int id = current->id;
  
		deleteIndex(current); // delete link
		
		fseek(file, (id-1) * sizeof(*record), SEEK_SET);
	 
		fread(record, sizeof(*record), 1, file);
		
		record->isDeleted = true;
		
		// update this record
		fseek(file, (id - 1) * sizeof(*record), SEEK_SET);
		fwrite(record, sizeof(*record), 1, file);
		printf("\nRecord has been deleted\n");
	}
	else{
		printf("a problem is occured\n");
	}
	
	fclose(file);
}
void insertRecord()
{
	FILE *file;
	PERSON s, *record;
	record = &s;
	
	printf("Enter first name : ");
	scanf("%s", record->firstName);
	
	printf("Enter last name : ");
	scanf("%s", record->lastName);
	
	printf("Enter address : ");
	scanf("%s", record->address);
	
	printf("Enter age : ");
	scanf("%d", &record->age);
	
	printf("Enter department : ");
	scanf("%s", record->dept);
	
	upper_string(record->firstName); upper_string(record->lastName);
	upper_string(record->address); upper_string(record->dept);
	
	file = fopen(dataFileName, "r+b");
	
	fseek(file, 0, SEEK_END);      // set file position at the end of file
	
	ID++;
	
	record->id = ID;
	
	if( strcmp(record->firstName, "") != 0 && strcmp(record->lastName, "") != 0 &&
	strcmp(record->address, "") != 0 && strcmp(record->dept, "") != 0 &&
	record->age > 0 )
	{
		//a record name must be identical
		if(searchIndex(record->firstName, record->lastName) == -1)
		{
			if (fwrite(record, sizeof(*record), 1, file))      // write the record at the end of file
			{
				fseek(file, 0, SEEK_END);
				
				insertIndex(record);
				updateID(ID);
			}
			else
			{
				printf("\n\nCould NOT add !!!");
				ID--;
			}
			fclose(file);
		}
		else{ printf("\nThis record has already added"); }
		
	}
	
}
/* DATA FILE OPERATIONS */
