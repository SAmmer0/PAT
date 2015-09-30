#include <stdlib.h>
#include <stdio.h>

#define DOWN_TIME 4
#define UP_TIME 6
#define STOP_TIME 5

int* get_input(int num){
    int* res = (int *)malloc(sizeof(int) * (num + 1));
    int* tmp = res;
    *tmp = 0;
    tmp++;
    for(; tmp < res + num + 1; tmp++){
        scanf("%d", tmp);
    }
    return res;
}

int cpt_time(int this_floor, int next_floor){
    int floor_gap;
    int move_time;
    if(this_floor <= next_floor){
        floor_gap = next_floor - this_floor;
        move_time = UP_TIME;
    }
    else{
        floor_gap = this_floor - next_floor;
        move_time = DOWN_TIME;
    }
    return floor_gap * move_time + STOP_TIME;
}

int main(){
    int floor_num;
    scanf("%d", &floor_num);
    int* request_list = get_input(floor_num);
    int sum_time = 0;
    int* tmp;
    for(tmp = request_list; tmp < request_list + floor_num; tmp++){
        sum_time += cpt_time(*tmp, *(tmp + 1));
    }
    printf("%d", sum_time);
    return 0;
}