/*
Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
Output: true
Explanation: There are two paths from vertex 0 to vertex 2:
- 0 → 1 → 2
- 0 → 2

*/
typedef struct _node{
    int vert;
    int count;
    struct _node* next ;
}node;

typedef struct _que{
    int vert;
    struct _que* next;
}queue;

node* createNewNode (int vert){
    node *ret = NULL;
    ret = calloc(1,sizeof(node));
    ret->vert = vert;
    ret->count = 0;
    ret->next = NULL;
    return ret;
}

queue* createNewQue (int vert){
    queue *ret = NULL;
    ret = calloc(1,sizeof(queue));
    ret->vert = vert;
    ret->next = NULL;
    return ret;
}

void Push (queue** head , queue** tail, int vert){
    queue *tmp = NULL;
    //printf(" Pushed %d \n",vert);
    tmp = createNewQue(vert);
    if (*tail == NULL){
        *head = tmp;
        *tail = *head;
        //  printf("Created tail %p\n", *tail);
    } else {
        (*tail)->next = tmp;
        *(tail) = tmp;
    }
} 

int Pop (queue** head, queue** tail){
    queue *tmp = NULL;
    int ret = 0;
    tmp = *head;
    if (tmp){
        ret = tmp->vert;
        *head = tmp->next;
        free(tmp);
    }
    //printf(" Popd %d \n", ret);
    return ret;
}
void createGraph (node *root, int size , int **edges , int edgesSize){
    int i = 0;
    for (i ; i < edgesSize ; i++){
        int src = edges[i][0];
        int dest = edges[i][1];
        /* for src side */
        root[src].vert = src;
        node *tmp = root[src].next;
        if (tmp == NULL){
            tmp = createNewNode(dest);
            root[src].next = tmp;
        } else {
            while (tmp->next != NULL){
                tmp = tmp->next;
            }
            tmp->next = createNewNode(dest);
        }   
        root[src].count += 1;
        //printf("%s 1 src %d neigh %d count %d next %p next %d \n",__func__,root[src].vert,tmp->vert,root[src].count, tmp ,tmp->vert);
        /* for dest side */
        root[dest].vert = dest;
        node *tmp1 = root[dest].next;
        if (tmp1 == NULL){
            tmp1 = createNewNode(src);
            root[dest].next = tmp1;
        } else {
            while (tmp1->next != NULL){
                tmp1 = tmp1->next;
            }
            tmp1->next = createNewNode(src);
        }      
       root[dest].count += 1;
        //printf("%s 2 src %d neigh %d count %d next %p next %d \n",__func__,root[dest].vert,tmp1->vert,root[dest].count,tmp1, tmp1->vert);
    }   
}

bool validPath(int n, int** edges, int edgesSize, int* edgesColSize, int source, int destination){
    int i = 0 ;
    int *visited = NULL;
    node *graph = NULL;
    visited = calloc(n,sizeof(int));
    graph = calloc(n, sizeof(node));
    createGraph(graph , n, edges, edgesSize);
    /*
       while (i < n){
       printf(" graph vert %d count %d next %p  \n",
       graph[i].vert, graph[i].count, graph[i].next);
       i++;
       }*/

    queue *head = NULL;
    queue *tail = NULL;

    Push(&head, &tail , source);
    // printf("MAin Created tail %p\n", tail);


    while (head != NULL){
        int cur = head->vert;

        if (visited[cur] == 0){
            if (cur == destination){
                return true;
            }
            node *v = NULL;
            v = &graph[cur];
            // printf("Curr V %d count %d next %p\n",v->vert, v->count, v->next);
            int iter = 0;
            node *next = v->next;
            i = 0;
            while ((i < v->count) && (next != NULL)) {
                Push(&head, &tail, next->vert);
                next = next->next;
                i++;
            }
        }  
        visited[cur] += 1; 
        int popd = Pop (&head, &tail);
    }

    return false;
}
