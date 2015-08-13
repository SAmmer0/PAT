#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int children_num;
    int *children;
    int level;
}tNode;

typedef struct QNode{
    int id;
    struct QNode *next;
}tQNode;

typedef struct Queue{
    tQNode* head;
    tQNode* tail;
    int count;
}tQueue;

tQueue* init_queue(){
    tQueue *result = (tQueue *)malloc(sizeof(tQueue));
    result->head = NULL;
    result->tail = NULL;
    result->count = 0;
    return result;
}

void enqueue(tQueue* queue, int id){
    if(id > 100 || id < 0){
        puts("Error, wrong tree node id \n");
        exit(0);
    }
    tQNode *tmp = (tQNode *)malloc(sizeof(tQNode));
    tmp->id = id;
    tmp->next = NULL;
    if(queue->count == 0){
        queue->head = tmp;
        queue->tail = tmp;
        queue->count++;
    }
    else{
        queue->tail->next = tmp;
        queue->tail = tmp;
        queue->count++;
    }
}

int dequeue(tQueue* queue){
    if(queue->count == 0){
        puts("Error, thie queue is empty\n");
        exit(0);
    }
    int result = queue->head->id;
    tQNode* tmp = queue->head;
    queue->head = queue->head->next;
    if(tmp != NULL)
        free(tmp);
    queue->count--;
    if(queue->count == 0){
        queue->head = NULL;
        queue->tail = NULL;
    }
    return result;
}

int is_empty(tQueue* queue){
    return queue->count == 0;
}

tNode* init_nodes(int nodes_num){
    tNode* result = (tNode *)malloc(sizeof(tNode) * nodes_num);
    int i;
    for(i = 0; i < nodes_num; i++){
        result[i].children_num = 0;
        result[i].children = NULL;
        result[i].level = 0;
    }
    return result;
}

void get_input(const int nleaf_num, tNode* data){
    int i;
    for(i = 0; i < nleaf_num; i++){
        int this_node;
        scanf("%d", &this_node);
        this_node--;
        int children_num;
        scanf("%d", &children_num);
        (data + this_node)->children_num = children_num;
        int j;
        int *child_array = (int *)malloc(sizeof(int) * children_num);
        for(j = 0; j < children_num; j++){
            int tmp;
            scanf("%d", &tmp);
            tmp--;
            child_array[j] = tmp;
        }
        (data + this_node)->children = child_array;
    }
}

int bfs_walk(tNode *tree_data){
    int max_level = 0;
    tQueue *queue = init_queue();
    enqueue(queue, 0);
    while(!is_empty(queue)){
        int this_node = dequeue(queue);
        int i;
        for(i = 0; i < tree_data[this_node].children_num; i++){
            int tmp_child = (tree_data[this_node].children)[i];
            tree_data[tmp_child].level = tree_data[this_node].level + 1;
            enqueue(queue, tmp_child);
        }
        if(tree_data[this_node].level > max_level)
            max_level = tree_data[this_node].level;
    }
    return max_level;
}

int is_leaf(tNode* tree_data, int id){
    return tree_data[id].children_num == 0;
}

int* count_leaf(tNode* tree_data, int node_num, int max_level){
    int* result = (int *)malloc(sizeof(int) * max_level + 1);
    int i;
    for(i = 0; i < max_level; i++)
        result[i] = 0;

    for(i = 0; i < node_num; i++){
        int this_level = tree_data[i].level;
        if(is_leaf(tree_data, i)){
            result[this_level]++;
        }
    }
    return result;
}

void print_result(int* leaf_result, int max_level){
    int i;
    for(i = 0; i < max_level + 1; i++){
        if(i != 0){
            printf(" ");
        }
        printf("%d", leaf_result[i]);
    }
}

int main(){
    int node_num;
    int nleaf_num;
    int max_level;
    scanf("%d %d", &node_num, &nleaf_num);
    tNode* tree = init_nodes(node_num);
    get_input(nleaf_num, tree);
    max_level = bfs_walk(tree);
    int* leaf_result = count_leaf(tree, node_num, max_level);
    print_result(leaf_result, max_level);
    return 0;
}