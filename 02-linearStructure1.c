#include <stdio.h>
#include <stdlib.h>

typedef struct PolyFormular
{
    int par;
    int pow;
    struct PolyFormular* next;
}tPF;

typedef struct PFTable
{
    tPF* head;
    tPF* tail;
    int count;
}tPFT;

/*
 * input data as string, and then transfer them into tPf;
 */
tPFT* getInput();

/*
 * delete the poly formular table
 */
void deletePFT(tPFT* inputPFT);

/*
 * compute derivate of the given data
 */
void computeDerivate(tPF* input);

/*
 * compute derivate of the given poly formular table
 */
void computeDerivateTable(tPFT* inputTable);

/*
 * print the computation result
 */
int printResult(tPFT* inputTable);

int main()
{
    tPFT* inputData;
    inputData = getInput();
    computeDerivateTable(inputData);
    printResult(inputData);
    deletePFT(inputData);
    return 0;
}


/*
 * input data as string, and then transfer them into tPf;
 */
tPFT* getInput()
{
    int tmp1, tmp2;
    tPFT* res = (tPFT *)malloc(sizeof(tPFT));
    res->head = NULL;
    res->tail = NULL;
    res->count = 0;
    do{
        scanf("%d %d", &tmp1, &tmp2);
        tPF* tmpPF = (tPF *)malloc(sizeof(tPF));
        tmpPF->par = tmp1;
        tmpPF->pow = tmp2;
        tmpPF->next = NULL;
        res->count++;
        if(res->head == NULL)
        {
            res->head = tmpPF;
            res->tail = tmpPF;
        }
        else
        {
            res->tail->next = tmpPF;
            res->tail = tmpPF;
        }
    }while(getchar() != '\n');
    return res;
}

/*
 * delete the poly formular table
 */
void deletePFT(tPFT* inputPFT)
{
    tPF* tmp = inputPFT->head;
    while(tmp != NULL)
    {
        tPF* p = tmp;
        tmp = tmp->next;
        free(p);
    }
    free(inputPFT);
}


tPF* searchZeroNode(tPFT* inputTable)
{
    tPF* pTmpNode = inputTable->head;
    while(pTmpNode != NULL)
    {
        if(pTmpNode->par == 0)
        {
            return pTmpNode;
        }
        pTmpNode = pTmpNode->next;
    }
    return NULL;
}

int deleteZeroNode(tPFT* inputTable, tPF* zeroNode)
{
    if(zeroNode == NULL)
    {
        return 1;
    }
    if(inputTable->head == zeroNode)
    {
        tPF* pTmp = inputTable->head;
        inputTable->head = pTmp->next;
        inputTable->count--;
        if(inputTable->count == 0)
        {
            inputTable->tail = NULL;
        }
        free(pTmp);
        return 1;
    }
    tPF* pTmpNode = inputTable->head;
    while(pTmpNode != NULL)
    {
        if(pTmpNode->next == zeroNode)
        {
            tPF* tmp = pTmpNode->next;
            if(tmp == inputTable->tail)
            {
                inputTable->tail = pTmpNode;
                pTmpNode->next == NULL;
                free(tmp);
            }
            pTmpNode->next = tmp->next;
            inputTable->count--;
            return 1;
        }
        pTmpNode = pTmpNode->next;
    }
    return 0;
}


            

/*
 * compute derivate of the given data
 */
void computeDerivate(tPF* input)
{
    if(input->pow == 0)
    {
        input->par = 0;
        input->pow = 0;
    }
    else
    {
        input->par = input->par * input->pow;
        input->pow--;
    }
}

/*
 * compute derivate of the given poly formular table
 */
void computeDerivateTable(tPFT* inputTable)
{
    tPF* tmp = inputTable->head;
    while(tmp != NULL)
    {
        computeDerivate(tmp);
        tmp = tmp->next;
    }
    tPF* pZero = searchZeroNode(inputTable);
    deleteZeroNode(inputTable, pZero);
}

/*
 * print the computation result
 */
int printResult(tPFT* inputTable)
{
    tPF* tmp = inputTable->head;
    if(inputTable->count == 0)
    {
        printf("0 0");
        return 0;
    }
    while(tmp != NULL)
    {   
        if(tmp->par == 0)
        {
            tmp = tmp->next;
            continue;
        }
        printf("%d %d", tmp->par, tmp->pow);
        if(tmp != inputTable->tail)
        {
            printf(" ");
        }
        tmp = tmp->next;
    }
    return 0;
}

