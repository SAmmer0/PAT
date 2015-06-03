#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define INF 1000000000

typedef struct Node
{
    int value;
    struct Node* left;
    struct Node* right;
}tNode;

typedef struct LinkListNode
{
    tNode* value;
    struct LinkListNode* next;
}tLLNode;

typedef struct Queue
{
    tLLNode* head;
    tLLNode* tail;
}tQueue;

void queuePush(tQueue* queue, tNode* node)
{
    printf("in push %d\n", node->value);
    if(node == NULL)
    {
        return;
    }
    tLLNode* thisNode = (tLLNode *)malloc(sizeof(tLLNode));
    thisNode->value = node;
    thisNode->next = NULL;
    if(queue->head == NULL)
    {
        queue->head = thisNode;
        queue->tail = thisNode;
        return;
    }
    queue->tail->next = thisNode;
    queue->tail = thisNode;
}

tNode* queuePop(tQueue* queue)
{
    if(queue->head == NULL)
    {
        printf("pop null\n");
        return NULL;
    }
    tLLNode* tmpNode = queue->head;
    queue->head = queue->head->next;
    if(queue->head == NULL)
    {
        queue->tail = NULL;
    }
    printf("pop %d\n", tmpNode->value->value);
    return tmpNode->value;
}

int* getInput(int n)
{
    int i;
    int* res = (int *)malloc(sizeof(int) * n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &res[i]);
    }
    return res;
}

void merge(int* numArray, int start, int mid, int end)
{
    int leftSize = mid - start + 1;
    int rightSize = end - mid;
    int* left= (int *)malloc(sizeof(int) * (leftSize + 1));
    int* right = (int *)malloc(sizeof(int) * (rightSize + 1));
    int i;
    int j;
    left[leftSize] = INF;
    right[rightSize] = INF;
    for(i = 0; i < leftSize; i++)
    {
        left[i] = numArray[start + i];
    }
    for(j = 0; j < rightSize; j++)
    {
        right[j] = numArray[mid + j + 1];
    }
    int k;
    i = 0;
    j = 0;
    for(k = start; k <= end; k++)
    {
        if(left[i] <= right[j])
        {
            numArray[k] = left[i];
            i++;
        }
        else{
            numArray[k] = right[j];
            j++;
        }
    }
    free(left);
    free(right);
}

void mergeSort(int* numArray, int start, int end)
{
    if(start < end)
    {
        int mid = (end + start)/2;
        mergeSort(numArray, start, mid);
        mergeSort(numArray, mid + 1, end);
        merge(numArray, start, mid, end);
    }
}

double log2(double n)
{
    return log(n)/log(2);
}

int pow2(n)
{
    return 2<<(n - 1);
}

int cptRootIdx(int start, int end)
{
    if(start >= end)
    {
        return start;
    }
    int idx;
    int n = end - start + 1;
    int hight = (int)log2(n);
    printf("in cpt \nhight =  %d\nn = %d\n", hight, n);
    int rest = n - pow2(hight) + 1;
    printf("rest = %d\n", rest);
    if(rest > pow2(hight - 1))
    {
        idx = pow2(hight) - 1;
    }
    else{
        idx = pow2(hight - 1) - 1 + rest;
        printf("idx = %d\n", idx);
    }
    idx += start;
    return idx;
}


void buildCBT(int* numArray, int start, int end, tNode** root)
{
    if(start == end)
    {
        (*root) = (tNode *)malloc(sizeof(tNode));
        (*root)->value = start;
        (*root)->left = NULL;
        (*root)->right = NULL;
        return;
    }
    else if(start > end)
    {
        return;
    }
    int rootIdx = cptRootIdx(start, end);
    (*root) = (tNode *)malloc(sizeof(tNode));
    (*root)->value = numArray[rootIdx];
    (*root)->left = NULL;
    (*root)->right = NULL;
    buildCBT(numArray, start, rootIdx - 1, &((*root)->left));
    buildCBT(numArray, rootIdx + 1, end, &((*root)->right));
}

int* BFSTraversal(tNode* root, int capacity)
{
    tQueue* queue = (tQueue *)malloc(sizeof(tQueue));
    queue->head = NULL;
    queue->tail = NULL;
    queuePush(queue, root);
    int* result = (int *)malloc(sizeof(int) * capacity);
    int i = 0;
    int j = 1;
    while(queue->head != NULL)
    {
        printf("in while loop %d\n", j);
        j++;
        tNode* thisNode;
        thisNode = queuePop(queue);
        result[i] = thisNode->value;
        i++;
        if(thisNode->left != NULL)
        {
            queuePush(queue, thisNode->left);
        }
        if(thisNode->right != NULL)
        {
            queuePush(queue, thisNode->right);
        }
    }
    free(queue);
    return result;
}

void printResult(int* data, int cap)
{
    int i;
    for(i = 0; i < cap; i++)
    {
        if(i == 0)
        {
            printf("%d", data[i]);
        }
        else{
            printf(" %d", data[i]);
        }
    }
}

void printTree(tNode* root)
{
    if(root == NULL)
    {
        return;
    }
    printf("%d ", root->value);
    printTree(root->left);
    printTree(root->right);
}

void main()
{
    int numNode;
    scanf("%d", &numNode);
    printf("input numNode %d\n", numNode);
    int* inputData = getInput(numNode);
    printf("get input data\n");
    mergeSort(inputData, 0, numNode - 1);
    printf("MergeSort DONE\n");
    tNode* root = NULL;
    buildCBT(inputData, 0, numNode - 1, &root);
    printf("build CBT done\n");
    printTree(root);
    int* result = BFSTraversal(root, numNode);
    printf("BFS done\n");
    printResult(result, numNode);
}
    
