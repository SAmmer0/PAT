#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
}tNode;

typedef struct CircleList
{
    tNode* head;
    int num;
}tCircleList;

tCircleList* constructList(int*, int);

int main()
{
    int totalNum;
    int move;
    scanf("%d %d", &totalNum, &move);
    int i = 0;
    int* dataList = (int *)malloc(sizeof(int)*totalNum);
    for(i = 0; i < totalNum; i++)
    {
        scanf("%d", &dataList[i]);
    }
    tCircleList* data;
    data = constructList(dataList, totalNum);
    for(i = 0; i < totalNum - move % totalNum; i++)
    {
        data->head = data->head->next;
    }
    i = 0;
    tNode* p = data->head;
    while(i < data->num)
    {
        printf("%d", p->data);
        if(p->next != data->head)
        {
            printf(" ");
        }
        p = p->next;
        i++;
    }
    printf("\n");
    return 0;
}

tCircleList* constructList(int* data, int n)
{
    tNode* head  = (tNode *)malloc(sizeof(tNode));
    head->data = data[0];
    head->next = NULL;
    int i = 1;
    tNode *p = head;
    while(i < n)
    {
       tNode *tmp = (tNode *)malloc(sizeof(tNode));
       tmp->data = data[i];
       tmp->next = NULL;
       p->next = tmp;
       p = p->next;
       i++;
    }
    p->next = head;
    tCircleList* dataList = (tCircleList *)malloc(sizeof(tCircleList));
    dataList->head = head;
    dataList->num = n;
    return dataList;
}


