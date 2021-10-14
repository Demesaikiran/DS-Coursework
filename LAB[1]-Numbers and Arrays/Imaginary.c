#include<stdio.h>
#include<stdlib.h>

struct ImagNum
{
    int rp;
    int ip;
};

struct ImagNum addImaginary1(struct ImagNum, struct ImagNum);
struct ImagNum * addImaginary2(struct ImagNum *, struct ImagNum *);

int main()
{
    struct ImagNum n1, n2;
    printf("Enter an imaginary number in a+bi format:");
    scanf("%d+%di", &n1.rp, &n1.ip);

    printf("Enter another imaginary number in a+bi format:");
    scanf("%d+%di", &n2.rp, &n2.ip);

    struct ImagNum sum = addImaginary1(n1, n2);
    printf("(%d+%di) + (%d+%di) = (%d+%di)\n", n1.rp, n1.ip, n2.rp, n2.ip, sum.rp, sum.ip);
    

    struct ImagNum *sumPtr = addImaginary2(&n1, &n2);
    printf("(%d+%di) + (%d+%di) = (%d+%di)\n", n1.rp, n1.ip, n2.rp, n2.ip, sumPtr->rp, sumPtr->ip);
    free(sumPtr); //dynamically allocated memory should be freed after use
}

//Passing structure by value and return structure as value
struct ImagNum addImaginary1(struct ImagNum n1, struct ImagNum n2)
{
    struct ImagNum sum;
    sum.rp = n1.rp + n2.rp;
    sum.ip = n1.ip + n2.ip;
    return sum;
}


//Passing structure by reference and return structure as reference
struct ImagNum * addImaginary2(struct ImagNum * n1, struct ImagNum * n2)
{
    struct ImagNum * sumPtr = malloc(sizeof(struct ImagNum));
    sumPtr->rp = n1->rp + n2->rp;
    sumPtr->ip = n1->ip + n2->ip;
    return sumPtr;
}
