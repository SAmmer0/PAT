#include <stdio.h>
#include <stdlib.h>

#define INF 1000

typedef struct Dict
{
    char* label;
    int num;
}tDict;


/*
 * initiaization of the dictionary
 */
tDict* initialization(int size, char* cardStr[]);


/*
 * Using given number array set dictionary
 */
void setCardsNum(tDict* cards, int*, int size);

void mergeSort(tDict*, int, int);

void merge(tDict*, int, int, int);

/*
 * shuffle the dictionary for one time
 */
void shuffle(tDict*, int*, int);
/*
 * shuffle the dictionary for n times
 */
void shuffleN(tDict*, int*, int, int);

void printCards(tDict* cards, int);


int main()
{
    int nTimes;
    int* numOrder = (int *)malloc(sizeof(int)*54);

    scanf("%d", &nTimes);
    int i;
    for(i = 0; i < 54; i++)
    {
        scanf("%d", &numOrder[i]);
    }
    char* cards[] = {"S1", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "S10", "S11", "S12", "S13",
                    "H1", "H2", "H3", "H4", "H5", "H6", "H7", "H8", "H9", "H10", "H11", "H12", "H13",
                    "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "C10", "C11", "C12", "C13",
                    "D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "D10", "D11", "D12", "D13",
                    "J1", "J2"};
    tDict* iniCards;
    iniCards = initialization(54, cards);
    shuffleN(iniCards, numOrder, 54, nTimes);
    printCards(iniCards, 54);
    return 0;
}


/*
 * initiaization of the dictionary
 */
tDict* initialization(int size, char* cardStr[])
{
    int i;
    tDict* res = (tDict *)malloc(sizeof(tDict) * size);
    for(i = 0; i < size; i++)
    {
        res[i].label = cardStr[i];
        res[i].num = i + 1;
    }
    return res;
}


/*
 * Using given number array set dictionary
 */
void setCardsNum(tDict* cards, int* numList, int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        cards[i].num = numList[i];
    }
}

void merge(tDict* input, int start, int mid, int end)
{
    int leftNum = mid - start + 1;
    int rightNum = end - mid;
    tDict* leftDict = (tDict *)malloc(sizeof(tDict) * ( leftNum + 1));
    tDict* rightDict = (tDict *)malloc(sizeof(tDict) * (rightNum + 1));
    int i;
    for(i = 0; i < leftNum; i++)
    {
        leftDict[i] = input[start + i];
    }
    for(i = 0; i < rightNum; i++)
    {
        rightDict[i] = input[mid + i + 1];
    }
    leftDict[leftNum].label = NULL;
    leftDict[leftNum].num = INF;
    rightDict[rightNum].label = NULL;
    rightDict[rightNum].num = INF;
    int k;
    int l = 0;
    int r = 0;
    for(k = start; k <= end; k++)
    {
        if(leftDict[l].num <= rightDict[r].num)
        {
            input[k] = leftDict[l];
            l++;
        }
        else{
            input[k] = rightDict[r];
            r++;
        }
    }
    free(leftDict);
    free(rightDict);
}



void mergeSort(tDict* input, int start, int end)
{
    if(start < end)
    {
        int mid = (start + end) /2;
        mergeSort(input, start, mid);
        mergeSort(input, mid + 1, end);
        merge(input, start, mid, end);
    }
}

/*
 * shuffle the dictionary for one time
 */
void shuffle(tDict* cards, int* numList, int size)
{
    setCardsNum(cards, numList, size);
    mergeSort(cards, 0, size - 1);
}


/*
 * shuffle the dictionary for n times
 */
void shuffleN(tDict* cards, int* numList, int size, int shuffleTimes)
{
    int i;
    for(i = 0; i < shuffleTimes; i++)
    {
        shuffle(cards, numList, size);
    }
}

void printCards(tDict* cards, int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        printf("%s", cards[i].label);
        if(i != size -1)
        {
            printf(" ");
        }
        else{
            printf("\n");
        }
    }
}

