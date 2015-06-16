#include <stdlib.h>
#include <stdio.h>

typedef struct Formula{
    int exp;
    double coeff;
}tFormula;

typedef struct LinkList{
    tFormula data;
    struct LinkList* next;
}tLinkList;

typedef struct LinkListTable{
    tLinkList* head;
    tLinkList* tail;
    int count;
}tLinkListTable;

void addNode(tLinkListTable* table, tLinkList* node){
    if(table->head == NULL){
        table->head = node;
        table->tail = node;
        table->count++;
    }
    else{
        table->tail->next = node;
        table->tail = node;
        table->count++;
    }
}

tFormula* getLineInput(int count){
    int i;
    tFormula* res = (tFormula *)malloc(sizeof(tFormula)*count);
    for(i = 0; i < count; i++){
        int exp;
        double coeff;
        scanf("%d %lf", &exp, &coeff);
        res[i].exp = exp;
        res[i].coeff = coeff;
    }
    return res;
}

tLinkListTable* addPolynomial(tFormula* formula1, int count1, tFormula* formula2, int count2){
    int i = 0;
    int j = 0;
    tLinkListTable* res = (tLinkListTable *)malloc(sizeof(tLinkListTable));
    res->head = NULL;
    res->tail = NULL;
    res->count = 0;
    while(i + j < count1 + count2){
        tLinkList* tmpNode = (tLinkList *)malloc(sizeof(tLinkList));
        tmpNode->next = NULL;
        if(i == count1){
            tmpNode->data = formula2[j];
            j++;
        }
        else if(j == count2){
            tmpNode->data = formula1[i];
            i++;
        }
        else if(formula1[i].exp == formula2[j].exp){
            if(formula1[i].coeff + formula2[j].coeff == 0){
                i++;
                j++;
                free(tmpNode);
                continue;
            }
            tFormula* tmpFormula = (tFormula *)malloc(sizeof(tFormula));
            tmpFormula->exp = formula1[i].exp;
            tmpFormula->coeff = formula1[i].coeff + formula2[j].coeff;
            tmpNode->data = *tmpFormula;
            i++;
            j++;
        }
        else if(formula1[i].exp > formula2[j].exp){
            tmpNode->data = formula1[i];
            i++;
        }
        else{
            tmpNode->data = formula2[j];
            j++;
        }
        addNode(res, tmpNode);
    }
    return res;
}


void printPolynomial(tLinkListTable* formula){
    tLinkList* node = formula->head;
    printf("%d", formula->count);
    while(node != NULL){
        printf(" %d %.1f", node->data.exp, node->data.coeff);
        node = node->next;
    }
}

int main(){
    int count1;
    int count2;
    tFormula* f1;
    tFormula* f2;
    scanf("%d", &count1);
    f1 = getLineInput(count1);
    scanf("%d", &count2);
    f2 = getLineInput(count2);
    tLinkListTable* result = addPolynomial(f1, count1, f2, count2);
    printPolynomial(result);
    return 0;
}

