/* 
 *  name Vishnu;		memory.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
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
    printf("Address of x: %p\n", &x);

    // print out the addresses of f2_p, and f2_x
    printf("Address of f2_p: %p\n", &f2_p);
    printf("Address of f2_x: %p\n", &f2_x);  

    // print out the starting address of the dynamically allocated memory
    printf("*********Dynamic Heap******");
    for(int i=0; i<sizeof(f2_p); i++){
        printf("Addresses of f2_p[%d]: %p\n", i, &f2_p[i]);    
    }

    printf("starting address of f2_p %p\n", &f2_p[0]); 
    printf("*********End of Dynamic Heap******");
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

    printf("\n*******Local variables******\n");
    // print out the addresses of x1, x2, x3, x4, x5, x6
    printf("x1: %p\n", &x1);
    printf("x2: %p\n", &x2);
    printf("x3: %p\n", &x3);
    printf("x4: %p\n", &x4);
    printf("x5: %p\n", &x5);
    printf("x6: %p\n", &x6);  
    // print out the addresses of f1_x, f1_y, f1_p2
    printf("f1_x: %p\n", &f1_x);
    printf("f1_y: %p\n", &f1_y);

    // print out the address of f1_p1
    printf("f1_P1: %p\n", &f1_p1);
    printf("\n*******END OF Local variables******\n");

    printf("\n*******ON HEAP******\n");
    // print out the address of f1_p2
    for(int i=0; i<sizeof(f1_p2); i++){
        printf("f1_p2[%d]: %p\n", i, &f1_p2); 
    }  
        printf("\n*******END OF ON HEAP******\n");
    // print out the address of the string literal "This is inside f1"
        for(int i=0; i<sizeof(f1_p1); i++){
        printf("f1_p1[%d]: %p\n", i, &f1_p1); 
    }  

    f1_y = f2(10);
    return;
}

int main(int argc, char *argv[])
{
     
    printf("My OS bit size: %lu\n", sizeof(void *) * 8);
    printf("\n*******COMMAND LINE********\n");
    // print out the addresses of argc, argv
    printf("address of argc: %p\n", &argc); 

    for(int i=0; i< sizeof(argc); i++){
        printf("address of argv[%d]: %p\n", i, argv[i]); 
    }

    // print out the starting address and end address of the command line arguments of this process
    
    printf("first address command line argument : %p\n", &argv[0]);
    printf("end address of command line argument: %p\n", &argv[sizeof(**argv)-1]); 
    printf("\n*******E-O-COMMAND LINE********\n");
    // print out the starting address and end address of the environment of this process
    printf("\n*******ENVIRONMENT********\n");
    printf("first address of environment  : %p\n", &environ[0]);
    printf("last address of environment   : %p\n", &environ[sizeof(environ)-1]);
    printf("\n*******END OF ENVIRONMENT********\n");

    // print out the addresses of global_x, global_y, global_array1, global_array2,
    // global_pointer1,
    printf("\n*************GLOBALS*******\n");
    printf("global_x : %p\n", &global_x);
    printf("global_y : %p\n", &global_y);

    for(int i=0; i<sizeof(global_array1); i++){
        printf("global_array1[%d]: %p\n", i, &global_array1[i]);
    }
     
    for(int i=0; i<sizeof(global_array2); i++){
        printf("global_array2[%d]: %p\n", i, &global_array2[i]);
    }
    
    
    //global_pointer2, global_float, global_double
    printf("global_pointer2 %p\n", &global_pointer2);
    printf("global_float %p\n", &global_float);
    printf("global_double %p\n", &global_double);
    // print out the addresses of string literals "Hello, world!" and "bye" 
    printf("addresses of the string literal \'Hello World\'\n");
    for(int i=0; i<sizeof(global_array1); i++){
        printf("[%c]-global_array1[%d]: %p\n",global_array1[i], i, &global_array1[i]); 
    }

    printf("address of the string literal \'bye\'\n"); 
        printf("global_pointer2 (string literal 'bye'): %p\n", &global_pointer2); 

    printf("\n*****END OF GLOBALS*****\n"); 
    
    // print out the starting addresses of function main, f1, and f2
    printf("\n*******FUNCTIONS********\n"); 
    printf("main address : %p\n", main);
    printf("f1   address : %p\n", f1);
    printf("f2   address : %p\n", f2); 
    printf("\n*******END OF FUNCTIONS********\n");
    
    // call function f1 with suitable arguments such as 12, -5, 33.7, 'A', 1.896e-10, 100 
    f1(12, -5, 33.7, 'A', 1.0, 100);

    exit(0);
}