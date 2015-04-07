#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct SumIdx{
    int sum;
    int start;
    int end;
}tSumIdx;

/*
 * return true if all the value in the array is negetive
 * argument: input array, size of array
 */
int isNeg(int*, int);

/*
 * return the maximun number of the two input
 * argument: number one, number two
 */
tSumIdx maxNum(tSumIdx x, tSumIdx y);


/*
 * return the maximum sum of the child array
 * argument: input array, size of the array
 */
tSumIdx* maxSum(int*, int);

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
        printf("0 %d %d\n", inputArray[0], inputArray[arraySize - 1]);
        return 0;
    }
    tSumIdx* max;
    max = maxSum(inputArray, arraySize);
    printf("%d %d %d\n", max->sum, max->start, max->end);
    free(max);
    free(inputArray);
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


tSumIdx maxNum(tSumIdx x, tSumIdx y)
{
    if(x.sum >= y.sum)
    {
        return x;
    }
    else{
        return y;
    }
}

tSumIdx* maxSum(int* numArray, int size)
{
    tSumIdx startN;
    tSumIdx allN;
    startN.sum = numArray[size - 1];
    startN.start = numArray[size - 1];
    startN.end = numArray[size - 1];
    allN.sum = numArray[size - 1];
    allN.start = numArray[size - 1];
    allN.end = numArray[size - 1];
    int i;
    tSumIdx tmp;
    tSumIdx tmpThis;
    for(i = size - 2; i >= 0; i--)
    {
        tmp.sum = numArray[i] + startN.sum;
        tmp.start = numArray[i];
        tmp.end = startN.end;
        tmpThis.sum = numArray[i];
        tmpThis.start = numArray[i];
        tmpThis.end = numArray[i];
        startN = maxNum(tmpThis, tmp);
        allN = maxNum(startN, allN);
    }
    tSumIdx* result = (tSumIdx *)malloc(sizeof(tSumIdx));
    result->sum = allN.sum;
    result->start = allN.start;
    result->end = allN.end;
    return result;
}