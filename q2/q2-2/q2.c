/** name; memory.c */

#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 
#include <string.h>

extern char **environ;

int global_x = 10;
// initialised global int variable

int global_y;
// un-initialised global int variable;

char global_array1[] = "Hello, world!";
// initialised global array

char global_array2[10];
// un-initialised

/*lobal_array2 = */
char *global_pointer1 = "bye!";
// global pointer to a string literal

char *global_pointer2;
// un-initialised global pointer

float global_float = 100.1;
// initialised float global variable

double global_double;
// un-initialised global double


int f2(int x)
{
	//declaring variables
	char *f2_p;
	int f2_x = 21;
	
	//allocating memory dynamicly
	f2_p = malloc(1000);

    printf("The address of \n x = %p \n", &x);
    printf("The addresses of \n f2_p = %p, \n f2_x = %p \n", &f2_p, &f2_x); 
    printf("The address of the dynamically allocated memory \n f2_p = %p \n", &f2_p);

	L: f2_x = 10; 

	return f2_x;

}


void f1(int x1, int x2, float x3, char x4, double x5, int x6)
{

	//declaring variables
	int f1_x = 10;
	int f1_y;
	
	char *f1_p1 = "This is inside f1";
	// pointer to another string literal
	
	char *f1_p2;

	f1_p2 = malloc(100);
	// dynamically allocated memory

		printf("The addresses of \n x1 = %p, \n x2 = %p, \n x3 = %p, \n x4 = %p, \n x5 = %p, \n x6 = %p \n", &x1, &x2, &x3, &x4, &x5, &x6); 
		printf("The addresses of \n f1_x = %p,\n f1_y = %p,\n f1_p1 = %p,\n f1_p2 = %p \n ", &f1_x, &f1_y, &f1_p1, &f1_p2);
		printf("The address of the string literal (This is inside f1) is at \n f1_p1 = %p \n", f1_p1);
		printf("The address of the string (dynamic) \n f1_p2 %p\n", f1_p2);		

	f1_y = f2(10); 

}


int main(int argc, char *argv[])
{

	printf("My OS bit size: %lu \n", sizeof(void *) * 8);

	printf("The addresses of  \n argc = %p \n ", &argc);

	printf("The starting address of \n 1st argument argv = %p , \n last argument address argv = %p of the command line arguments of this process \n ", &argv[0], &argv[argc-1] );

		//getting the size of environment variable
 		int count = 0;
  		for (environ= environ; *environ != 0; environ++)
  		{
			count++;   
  		}

	printf("The size of environ variable processor is : %d bytes \n", (count*8) ); 

	printf("The starting address environ = %p \n The Ending address environ = %p of the environment of this process (values and variables) \n ", &environ[0], &environ[count] );

	printf("The starting addresses of function main = %p \n function f1 = %p \n function f2 = 		%p \n", &main, &f1, &f2);

	printf("The addresses \n global_x = %p \n global_y = %p \n global_array1 = %p \n global_array2 = %p \n global_pointer1 = %p \n global_pointer2 = %p \n global_float = %p \n global_double = %p \n", &global_x, &global_y, &global_array1, &global_array2, 	&global_pointer1, &global_pointer2, &global_float, &global_double);

	printf("The addresses of string literals (Hello, world!) is at global_array = %p \n", &global_array1);
	
	printf("The addresses of string literals (bye!) is at global_pointer1 = %p \n ", &global_pointer1);
	
	f1(12,-5,33.7,'A',1.896e-10,100);

   	exit(0);

}

