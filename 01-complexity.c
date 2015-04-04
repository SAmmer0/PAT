#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/*
 * return true if all the value in the array is negetive
 * argument: input array, size of array
 */
int isNeg(int*, int);

/*
 * return the maximun number of the two input
 * argument: number one, number two
 */
int maxNum(int x, int y);


/*
 * return the maximum sum of the child array
 * argument: input array, size of the array
 */
int maxSum(int*, int);

int main()
{
    int arraySize;
    int* inputArray;
    scanf("%d", &arraySize);
    inputArray = (int *)malloc(sizeof(int) * arraySize);
    int i;
    for(i = 0; i < arraySize; i++)
    {
        scanf("%d", &inputArray[i]);
    }
    if(isNeg(inputArray, arraySize) == TRUE)
    {
        printf("0\n");
        return 0;
    }
    int max = maxSum(inputArray, arraySize);
    printf("%d\n", max);
    return 0;
}

int isNeg(int* numArray, int size)
{
    int i = 0;
    for(; i < size; i++)
    {
        if(numArray[i] >= 0)
        {
            return FALSE;
        }
    }
    return TRUE;
}


int maxNum(int x, int y)
{
    if(x >= y)
    {
        return x;
    }
    else{
        return y;
    }
}

int maxSum(int* numArray, int size)
{
    int startN = numArray[size - 1];
    int allN = numArray[size - 1];
    int i;
    for(i = size - 2; i >= 0; i--)
    {
        startN = maxNum(numArray[i], numArray[i] + startN);
        allN = maxNum(startN, allN);
    }
    return allN;
}