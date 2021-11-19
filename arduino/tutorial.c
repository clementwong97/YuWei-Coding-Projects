#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>




void main(void)
{
    bool a = 1;
    bool b = false;
    int c = 0;
    float var = 1.234567;
    char word[10] = ' Debra';

    if (a == 1 & b == 1)
    {
        c = 1;
        // %d stands for integer value (int)
        printf("c is equal to %d\n", c);
    }
    else 
    {
        c = 0;
        printf("c is equal to %d\n", c);
    }

    //char var[100];
    //printf("Please enter your name: ");
    //scanf("%s", var);
    //printf("Hello World!\n");
    //printf("Your name is %s\n", var);
    //printf("\n");
    //printf("I add %d and %d equals to %d \n", a, b, c);

}

/*
c programming

data types
- int -> integer 
- char -> characters
- long, short -> strings
- bool -> boolean (true or false | 0 or 1)


boolean algebra 
n = AND (intersect)
u = OR (union)

A = 1
B = 1 
A n B = 1

A = 1
B = 0
A n B = 0

bool A = 0, B = 1;
//when both A and B is set to 1 then return C is 1
if (A == 1 & B == 1)
{
    C = 1
}
else 
{
    C = 0 
}


*/