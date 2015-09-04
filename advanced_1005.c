#include<stdlib.h>
#include<string.h>
#include<stdio.h>

char digit_table[10][10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
typedef struct ChDigit{
    char* digit;
    struct ChDigit* next;
    struct ChDigit* last;
}tChDigit;

typedef struct Digits{
    tChDigit* head;
    tChDigit* tail;
}tDigits;

int get_sum(char* ch, int len);
tDigits* trans_sum(int sum);
void reverse_print_res(tDigits* res);

int main(){
    char input_num[102];
    scanf("%s", input_num);
    int sum = get_sum(input_num, strlen(input_num));
    tDigits* result = trans_sum(sum);
    reverse_print_res(result);
    return 0;
}

int get_sum(char* ch, int len){
    int res = 0;
    int i;
    for(i = 0; i < len; i++){
        res += ch[i] - '0';
    }
    return res;
}

tDigits* trans_sum(int sum){
    tDigits* res = (tDigits *)malloc(sizeof(res));
    int count = 0;
    tChDigit* last = NULL;
    while(1){
        tChDigit* tmp = (tChDigit *)malloc(sizeof(tmp));
        tmp->last = last;
        if(last != NULL){
            last->next = tmp;
        }
        last = tmp;
        int this_num = sum % 10;
        sum /= 10;
        tmp->digit = digit_table[this_num];
        if(count == 0){
            res->head = tmp;
            count = 1;
        }
        if(sum == 0){
            res->tail = tmp;
            tmp->next = NULL;
            break;
        }
    }
    return res;
}

void reverse_print_res(tDigits* res){
    tChDigit* tmp = res->tail;
    while(1){
        if(tmp != res->tail){
            printf(" ");
        }
        printf("%s", tmp->digit);
        if(tmp == res->head)
            break;
        tmp = tmp->last;
    }
}

