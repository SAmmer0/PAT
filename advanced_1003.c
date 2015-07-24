#include <stdio.h>
#include <stdlib.h>

#define INF 100000000

enum color {WHITE, BLACK};

typedef struct PiNode tPiNode;

typedef struct CityNode{
    int team_num;
    int city_id;
    tPiNode* pis;
    int max_team_num;
    int d;
    int heap_pos;
    enum color visit;
}tCityNode;

struct PiNode{
    tCityNode* city;
    struct PiNode * next;
};

typedef struct AdjNode{
    int city_id;
    int dist;
    struct AdjNode* next;
}tAdjNode;

typedef struct Graph{
    tCityNode* vertexes;
    tAdjNode** edges;
    int city_num;
}tGraph;

typedef struct CityHeap{
    tCityNode** citys;
    int size;
}tCityHeap;


void add_pi(tCityNode* u, tCityNode* v){
    tPiNode* tmp_pi = (tPiNode *)malloc(sizeof(tPiNode));
    tmp_pi->city = v;
    tmp_pi->next = NULL;
    if(u->pis == NULL){
        u->pis = tmp_pi;
    }
    else{
        tPiNode* tmp = u->pis;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = tmp_pi;
    }
}
void replace_pi(tCityNode* u, tCityNode* v){
    tPiNode* pi = u->pis;
    tPiNode* new_pi = (tPiNode *)malloc(sizeof(tPiNode));
    new_pi->city = v;
    new_pi->next = NULL;
    u->pis = new_pi;
    while(pi != NULL){
        tPiNode* tmp = pi;
        pi = pi->next;
        free(tmp);
    }
}

int get_dist(tAdjNode** data, int a, int b){
    tAdjNode* tmp = data[a];
    while(tmp != NULL){
        if(tmp->city_id == b){
            return tmp->dist;
        }
        else{
            tmp = tmp->next;
        }
    }
    printf("The city %d does not have neighbor %d\n", a, b);
    return -1;
}

void add_edge(tAdjNode** data, int a, int b, int distant){
    tAdjNode* edge = (tAdjNode *)malloc(sizeof(tAdjNode));
    edge->city_id = b;
    edge->dist = distant;
    edge->next = NULL;
    tAdjNode* tmp = data[a];
    if(tmp == NULL){
        data[a] = edge;
    }
    else{
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = edge; 
    }
}

tAdjNode** init_adjlist(int len){
    tAdjNode** res = (tAdjNode **)malloc(sizeof(tAdjNode(*)) * len);
    int i;
    for(i=0; i<len; i++){
        res[i] = NULL;
    }
    return res;
}

tGraph* get_input(int city_num, int edge_num, int source){
    tGraph* res = (tGraph *)malloc(sizeof(tGraph));
    res->city_num = city_num;
    tAdjNode** edges = init_adjlist(edge_num);
    tCityNode* citys = (tCityNode *)malloc(sizeof(tCityNode)*city_num);
    int i;
    for(i=0; i<city_num; i++){
        citys[i].city_id = i;
        citys[i].heap_pos = i;
        int tmp;
        scanf("%d", &tmp);
        citys[i].team_num = tmp;
        citys[i].pis = NULL;
        citys[i].visit = WHITE;
        citys[i].max_team_num = tmp;
        if(i == source)
            citys[i].d = 0;
        else
            citys[i].d = INF;
    }
    for(i=0; i<edge_num; i++){
        int city1, city2, dist;
        scanf("%d %d %d", &city1, &city2, &dist);
        add_edge(edges, city1, city2, dist);
        add_edge(edges, city2, city1, dist);
    }
    res->vertexes = citys;
    res->edges = edges;
    return res;
}

int get_left(int i){
    return ((i + 1)<<1) - 1;
}

int get_right(int i){
    return (i + 1)<<1;
}

int get_parent(int i){
    return ((i + 1)>>1) - 1;
}

tCityHeap* create_heap(tGraph* graph){
    tCityHeap* res = (tCityHeap *)malloc(sizeof(tCityHeap));
    tCityNode** citys = (tCityNode **)malloc(sizeof(tCityNode(*))*graph->city_num);
    res->size = graph->city_num;
    res->citys = citys;
    int i;
    tCityNode* tmp = graph->vertexes;
    for(i=0; i<graph->city_num; i++){
        citys[i] = &(tmp[i]);
    }
    return res;
}

void min_heapify(tCityHeap* heap, int idx){
    int left = get_left(idx);
    int right = get_right(idx);
    tCityNode** tmpCitys = heap->citys;
    int least;
    if((left < heap->size) && (tmpCitys[left]->d < tmpCitys[idx]->d)){
        least = left;
    }
    else
        least = idx;
    if((right < heap->size) && (tmpCitys[right]->d < tmpCitys[least]->d)){
        least = right;
    }
    if(least != idx){
        tCityNode* tmp = tmpCitys[idx];
        tmp->heap_pos = least;
        tmpCitys[idx] = tmpCitys[least];
        tmpCitys[idx]->heap_pos = idx;
        tmpCitys[least] = tmp;
        min_heapify(heap, least);
    }
}

void build_min_heap(tCityHeap* heap){
    int i;
    for(i = (heap->size>>1) - 1; i >= 0; i--){
        min_heapify(heap, i);
    }
}

tCityNode* extract_min(tCityHeap* heap){
    tCityNode** tmpCity = heap->citys;
    tCityNode* min;
    min = tmpCity[0];
    min->heap_pos = -1;
    tmpCity[0] = tmpCity[heap->size - 1];
    tmpCity[0]->heap_pos = 0;
    heap->size--;
    min_heapify(heap, 0);
    return min;
}

void decrease_key(tCityHeap* heap, int idx, int new_dist){
    tCityNode** tmp = heap->citys;
    if(idx == -1){
        printf("Error, the given index is wrong\n");
    }
    else if(tmp[idx]->d < new_dist){
        printf("Error, the given distance is greater than the original\n");
    }
    else{
        tmp[idx]->d = new_dist;
        while(idx > 0 && (tmp[idx]->d < tmp[get_parent(idx)]->d)){
            tCityNode* tmpNode = tmp[idx];
            tmpNode->heap_pos = get_parent(idx);
            tmp[idx] = tmp[get_parent(idx)];
            tmp[idx]->heap_pos = idx;
            tmp[get_parent(idx)] = tmpNode;
            idx = get_parent(idx);
        }
    }
}

void relax(tCityNode* v, tCityNode* u, tAdjNode** weight, tCityHeap* heap){
    int dist = get_dist(weight, v->city_id, u->city_id);
    if(u->d > dist + v->d){
        replace_pi(u, v);
        u->max_team_num = v->max_team_num + u->team_num;
        decrease_key(heap, u->heap_pos, dist + v->d);

    }
    else if(u->d == dist + v->d){
        add_pi(u, v);
        if(u->max_team_num < v->max_team_num + u->team_num){
            u->max_team_num = v->max_team_num + u->team_num;
        }
    }
}

void dijkstra(tGraph* graph, int source){
    tCityHeap* heap= create_heap(graph);
    tAdjNode** weight = graph->edges;
    tCityNode* vertexes = graph->vertexes;
    build_min_heap(heap);
    while(heap->size > 0){
        tCityNode* this_city = extract_min(heap);
        int city_id = this_city->city_id;
        tAdjNode* adj_head = weight[city_id];
        while(adj_head != NULL){
            int this_adj = adj_head->city_id;
            if(vertexes[this_adj].visit == BLACK){
                adj_head = adj_head->next;
                continue;
            }
            relax(this_city, &(vertexes[this_adj]), weight, heap);
            adj_head = adj_head->next;
        }
        this_city->visit = BLACK;
    }
    free(heap);
}

int get_path_num(tCityNode* citys, int destination, int source){
    if(destination == source){
        return 1;
    }
    int sum = 0;
    tPiNode* pi = citys[destination].pis;
    while(pi != NULL){
        int city_id = pi->city->city_id;
        sum += get_path_num(citys, city_id, source);
        pi = pi->next;
    }
    return sum;
}

int main(){
    int source;
    int destination;
    int city_num;
    int road_num;
    scanf("%d %d %d %d", &city_num, &road_num, &source, &destination);
    tGraph* graph = get_input(city_num, road_num, source);
    dijkstra(graph, source);
    int path_num = get_path_num(graph->vertexes, destination, source);
    printf("%d %d\n", path_num, (graph->vertexes)[destination].max_team_num);
    return 0;
}
