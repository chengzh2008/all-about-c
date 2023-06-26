#include <stdio.h>
#include <stdlib.h>

// #define MIN(A, B) (A < B ? A : B)
#define MIN(A, B) ({    \
    typeof(A) _a = (A); \
    typeof(B) _b = (B); \
    _a < _b ? _a : _b;  \
})

int getnextnum()
{
    int nextnum = rand() % 100;
    printf("next -> %d\n", nextnum);
    return nextnum;
}

int main()
{
    printf("testing MIN macro 1 %d\n", MIN(45, 32));
    printf("testing MIN macro 2 %f\n", MIN(45.0, 32.0));
    int n1, n2, n3;
    n3 = MIN((n1 = getnextnum()), (n2 = getnextnum()));
    printf("next num test %d\n", n3);
}