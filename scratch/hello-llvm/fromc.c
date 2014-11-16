#include <stdio.h>
#include <stdlib.h>

int calc(int n)
{
    int a = n + 5;
    return a;
}

void myprint_char(char *message)
{
    puts(message);
}

void myprint(int a)
{
    // "output = #{i}"
    char* output = malloc(60);
    sprintf(output, "output = %i", a);
    myprint_char(output);
    free(output);
}

int main(int argc, char *argv[])
{
    puts("hello world");
    puts(argv[1]);

    int n = atoi(argv[2]);
    int a = calc(n);

    myprint(a);

    return a;
}


