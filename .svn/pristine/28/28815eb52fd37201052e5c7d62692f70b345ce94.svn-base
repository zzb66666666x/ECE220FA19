#include <stdlib.h>
#include <stdio.h>

#define NofS 3

#define EQUAL 0
#define NOTEQUAL 1

struct studentStruct
{
    char name[100];
    int ID;
    char grade;
};
typedef struct studentStruct Student;

/* these functions are provided, do not modify them */
void enterRecords(Student s[], int n);
void writeRecordsToFile(Student s[], int n, char *fname);

/* these functions need to be implemented */
void readRecordsFromFile(Student s[], int n, char *fname);
int compareRecords(Student s1[], Student s2[], int n);


int main()
{
    Student S1[NofS];
    Student S2[NofS];
	//the S1 here is an address because it's actually an array of structs
    enterRecords(S1, NofS);
    writeRecordsToFile(S1, NofS, "ece220.dat");

    readRecordsFromFile(S2, NofS, "ece220.dat");

    if (compareRecords(S1, S2, NofS) == EQUAL)
        printf("Records are identical\n");
    else    
        printf("Records are different\n");

    return 0;
}

/*
 * enterRecords - reads the information from keyboard and store it into the struct
 * INTPUTS: Student s[] - an array of struct with the type "Student"
 *          int n - number of students: NofS = 3
 * OUTPUTS: array S1 full of students' information
 * RETURN VALUE: none
 */
void enterRecords(Student s[], int n)
{
    int i;
    char temp[8];
    for (i = 0; i < n; i++)
    {
        printf("Enter student's name: ");
        fgets(s[i].name, 100, stdin);
		//will store the "\n" into the name
        printf("Enter student's ID: ");
        scanf("%d", &(s[i].ID));
  
        printf("Enter student's grade: ");
        scanf("\n%c", &(s[i].grade));
        fgets(temp, 8, stdin);
    }
}

/*
 * writeRecords - write the information from array of struct s[] to file
 * INTPUTS: Student s[] - an array of struct with the type "Student"
 *          int n - number of students: NofS = 3
			char *fname - a pointer to the const array of char (a string which is the file name)
 * OUTPUTS: ece220.dat 
 * RETURN VALUE: none
 */
void writeRecordsToFile(Student s[], int n, char *fname)
{
    FILE *f;
    int i;

    if ((f = fopen(fname, "w")) == NULL)
    {
        fprintf(stderr, "Unable to open file %s\n", fname);
        exit(1);
		//end of program
    }
    for (i = 0; i < n; i++)
        fprintf(f, "%s%d\n%c\n", s[i].name, s[i].ID, s[i].grade);
		//fprintf will store the "\n" of the string into the file because the fgets store it into the struct
    fclose(f);
}


/*
 * readRecords - reads the information from file and store it into array of structs, and in this case, it's S2
 * INTPUTS: Student s[] - an array of struct with the type "Student"
 *          int n - number of students: NofS = 3
			char *fname - a pointer to the const array of char (a string which is the file name)
 * OUTPUTS: array S2 full of students' information from file 
 * RETURN VALUE: none
 */
void readRecordsFromFile(Student s[], int n, char *fname)
{
	FILE *f;
	if ((f = fopen(fname,"r")) == NULL)
	{
		fprintf(stderr,"Unable to open file %s\n",fname);
		//pass the error message to the std stream
	}
	for (int i = 0; i < n; i++)
	{
		fgets(s[i].name, 100, f);
		fscanf(f,"%d\n%c\n", &s[i].ID, &s[i].grade);
	}
	fclose(f);
}


/*
 * compareRecords - compare the information of two arrays of struct
 * INTPUTS: Student s1[] - an array of struct with the type "Student"
 * 			Student s2[] - an array of struct with the type "Student"
 *          int n - number of students: NofS = 3
 * OUTPUTS: none
 * RETURN VALUE: 0 / 1
 */
int compareRecords(Student s1[], Student s2[], int n)
{
	for (int i = 0; i < n; i++)
	{//for the ith student
		for (int j = 0; j < 100; j++)
			{
			if (s1[i].name[j] != s2[i].name[j]){
				return NOTEQUAL;
				}
			if ((s1[i].name[j] == '\0') && (s2[i].name[j] == '\0')){
				//here the '\0' means an empty character which tells the end of an string
				break;			
				}
			}
		if (s1[i].ID != s2[i].ID){
			return NOTEQUAL;
			}
		if (s1[i].grade != s2[i].grade){
			return NOTEQUAL;
			}		
	}
    return EQUAL;
}

