/* 
 *  name;		memory.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

extern char **environ;

int global_x = 10;  				// initialised global variable
int global_y;       				// un-initialised global variable
char global_array1[] = "Hello, world!"; 	// initialised global array 
char global_array2[10];  			// un-initialised global array
char *global_pointer1 = "bye!";  		// global pointer to a string literal 
char *global_pointer2;  			// un-initialised global pointer 
float global_float = 100.1;			// initialised global variable
double global_double;				// un-initialised global variable

int f2(int x)
{
    char * f2_p;
    int f2_x = 21;

    f2_p = malloc(1000);         // dynamically allocated memory
 
    // print out the address of x
    printf("x location = %p \n", &x); 
    
    // print out the addresses of f2_p and f2_x
    printf("f2_p location = %p\n", &f2_p);

    printf("f2_x location = %p\n", &f2_x); 

    // print out the starting address of the dynamically allocated memory
    printf("f2_p location = %p \n", &f2_p[0]); 
   
    L: f2_x = 10;
    return f2_x;
}

void f1(int x1, int x2, float x3, char x4, double x5, int x6)
{
    int f1_x = 10;
    int f1_y;
    char *f1_p1 = "This is inside f1";   // pointer to another string literal 
    char *f1_p2;

    f1_p2 = malloc(100);         // dynamically allocated memory

    // print out the addresses of x1, x2, x3, x4, x5, x6
    printf("location x1 = %p\n location x2 = %p\n location x3 = %p\n location x4 = %p\n location x5 = %p\n location x6 = %p\n", &x1, &x2, &x3, &x4, &x5, &x6); 
    // print out the addresses of f1_x, f1_y, f1_p1, f1_p2
    printf("f1_x address = %p\n f1_y address %p\n f1_p1 address = %p\n f1_p2 address = %p\n", &f1_x,  &f1_y, &f1_p1, &f1_p2); 
    // print out the address of the string literal "This is inside f1"
    printf("Address of string literal (this is a string) %p\n", &f1_p1); 

    f1_y = f2(10);
    return;
}

int main(int argc, char *argv[])
{
    int i; 
    printf("My OS bit size: %lu\n", sizeof(void *) * 8);

    // print out the addresses of argc, argv
    printf("Address of argc %p \n", &argc); 
    printf("Address of all elements in argv \n");
    
    for(int i = 0; i < argc; i++){
        printf("address from argv element %d = %p\n", i, &argv[i]); 
    }

    // print out the starting address and end address of the command line arguments of this process
    printf("Address of the first command line arguments %p \n", &argv[0]); 
    printf(" Address of the last command line arguments %p \n", &argv[argc-1]); 

    // print out the starting address and end address of the environment of this process
    printf("First address of environment variable %p \n", &environ[0]);
    
    printf("Last address of environment variable %p \n", &environ[sizeof(environ)-1]); 

    // print out the starting addresses of function main, f1, and f2
    printf("Starting address of function main = %p\n", &main); 
        printf("Starting address of function f1   = %p\n", &f1);
            printf("Starting address of function f2   = %p\n", &f2);

    // print out the addresses of global_x, global_y, global_array1, global_array2, global_pointer1,
    printf("address of global_x = %p\n", &global_x);
        printf("address of global_y = %p\n", &global_y);
            printf("address of global_array1 = %p\n", &global_array1);
                printf("address of global_array2 = %p\n", &global_array2);
                    printf("address of global_pointer1 = %p\n", &global_pointer1); 

    // global_pointer2, global_float, global_double
    printf("address of global_pointer2 = %p\n", &global_pointer2);
        printf("address of global_float = %p\n", &global_float);
            printf("address of global_double = %p\n", &global_double);

    // print out the addresses of string literals "Hello, world!" and "bye" 
    printf("Address of string literal hello   = %p\n", &global_array1); 
        printf("Address of string literal bye = %p \n", &global_pointer1); 

    // call function f1 with suitable arguments such as 12, -5, 33.7, 'A', 1.896e-10, 100 
    f1(12, -5, 33.7, 'A', 1.896e-10, 100);

    exit(0);
}
