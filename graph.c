/*graph.c
Fuente: http://simplestcodings.blogspot.com/2013/09/graphs.html
*/
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "queue.c"
#include <stdio.h>
#include "stack.c"

graph_p dir_graph;
struct node* head = NULL;
int num;
char* name;
bool mira =true;
/* Function to create an adjacency list node*/
adjlist_node_p createNode(int v)
{
    adjlist_node_p newNode = (adjlist_node_p)malloc(sizeof(adjlist_node_t));
    if(!newNode)
        printf("%s", "ADIOS");
        //err_exit("Unable to allocate memory for new node");
 
    newNode->vertex = v;
    newNode->next = NULL;
    newNode->nodeId = getName(v);
    newNode->visited = false;
    newNode->busy = false;
    newNode->bridge = true;
 
    return newNode;
}
 
/* Function to create a graph with n vertices; Creates both directed and undirected graphs*/
graph_p createGraph(int n, graph_type_e type)
{
    int i;
    graph_p graph = (graph_p)malloc(sizeof(graph_t));
    if(!graph)
        printf("%s", "HOLA");
        //err_exit("Unable to allocate memory for graph");
    graph->num_vertices = n;
    graph->type = type;
 
    /* Create an array of adjacency lists*/
    graph->adjListArr = (adjlist_p)malloc(n * sizeof(adjlist_t));
    if(!graph->adjListArr)
        printf("%s", "MIERDA");
        //err_exit("Unable to allocate memory for adjacency list array");
 
    for(i = 0; i < n; i++)
    {
        graph->adjListArr[i].head = NULL;
        graph->adjListArr[i].num_members = 0;
    }
 
    return graph;
}
 
/*Destroys the graph*/
void destroyGraph(graph_p graph)
{
    if(graph)
    {
        if(graph->adjListArr)
        {
            int v;
            /*Free up the nodes*/
            for (v = 0; v < graph->num_vertices; v++)
            {
                adjlist_node_p adjListPtr = graph->adjListArr[v].head;
                while (adjListPtr)
                {
                    adjlist_node_p tmp = adjListPtr;
                    adjListPtr = adjListPtr->next;
                    free(tmp);
                }
            }
            /*Free the adjacency list array*/
            free(graph->adjListArr);
        }
        /*Free the graph*/
        free(graph);
    }
}
 
/* Adds an edge to a graph*/
void addEdge(graph_t *graph, int src, int dest)
{
    /* Add an edge from src to dst in the adjacency list*/
    adjlist_node_p newNode = createNode(dest);
    newNode->next = graph->adjListArr[src].head;
    graph->adjListArr[src].head = newNode;
    graph->adjListArr[src].num_members++;
 
    if(graph->type == UNDIRECTED)
    {
        /* Add an edge from dest to src also*/
        newNode = createNode(src);
        newNode->next = graph->adjListArr[dest].head;
        graph->adjListArr[dest].head = newNode;
        graph->adjListArr[dest].num_members++;
    }
}
 
 adjlist_p getListOfNodes(){
    return dir_graph->adjListArr;
 }

/* Function to print the adjacency list of graph*/
void displayGraph(graph_p graph)
{
    int i;
    for (i = 0; i < graph->num_vertices; i++)
    {
        adjlist_node_p adjListPtr = dir_graph->adjListArr[i].head;
        printf("\n%s: ", getName(i));
        while (adjListPtr)
        {
            printf("%s-> ", getName(adjListPtr->vertex));
            //printf("%d->", adjListPtr->vertex);
            adjListPtr = adjListPtr->next;
        }
        printf("NULL\n");
    }
}



bool searchAndAssignNode(char * nodeId, pthread_t thread){
    int i;
    bool flag = false;
    for (i = 0; i < dir_graph->num_vertices; i++)
    {
        adjlist_node_p adjListPtr = dir_graph->adjListArr[i].head;
        while (adjListPtr)
        {
            if(adjListPtr->nodeId==nodeId){
                if(adjListPtr->busy==false){
                    adjListPtr->thread=thread;
                    adjListPtr->busy=true;
                }
                flag = true;
                break;
            }
            adjListPtr = adjListPtr->next;
        }
       if (flag == true){
        break;
       }
    }
    return flag;
}

bool changeNodeBridgeState(char * nodeId, bool value){
    int i;
    bool flag = false;
    for (i = 0; i < dir_graph->num_vertices; i++)
    {
        adjlist_node_p adjListPtr = dir_graph->adjListArr[i].head;
        while (adjListPtr)
        {
            if(adjListPtr->nodeId==nodeId){
                    adjListPtr->bridge=value;
                flag = true;
                break;
            }
            adjListPtr = adjListPtr->next;
        }
       if (flag == true){
        break;
       }
    }
    return flag;
}

bool printCarInfo(char * nodeId){
    int i;
    bool flag = false;
    for (i = 0; i < dir_graph->num_vertices; i++)
    {
        adjlist_node_p adjListPtr = dir_graph->adjListArr[i].head;
        while (adjListPtr)
        {
            if(adjListPtr->nodeId==nodeId){
                printf("%ld\n",  adjListPtr->thread);
                if(adjListPtr->busy==true){
                    printf("%ld\n",  adjListPtr->thread);
                }
                flag = true;
                break;
            }
            adjListPtr = adjListPtr->next;
        }
       if (flag == true){
        break;
       }
    }
    return flag;
}

void makeEdges(){
    dir_graph = createGraph(567, DIRECTED);
    addEdge(dir_graph, searchNumByName("Y1"), searchNumByName("Y2"));
    addEdge(dir_graph, searchNumByName ("Y2"), searchNumByName ("Y3"));
    addEdge(dir_graph, searchNumByName ("Y3"), searchNumByName ("Y4"));
    addEdge(dir_graph, searchNumByName ("Y4"), searchNumByName ("Y5"));
    addEdge(dir_graph, searchNumByName ("Y5"), searchNumByName ("Y6"));
    addEdge(dir_graph, searchNumByName ("Y6"), searchNumByName ("Y7"));
    addEdge(dir_graph, searchNumByName ("Y7"), searchNumByName ("Y8"));
    addEdge(dir_graph, searchNumByName ("Y8"), searchNumByName ("C4"));
    addEdge(dir_graph, searchNumByName ("C4"), searchNumByName ("_A16"));
    addEdge(dir_graph, searchNumByName ("_A16"), searchNumByName ("_A17"));
    addEdge(dir_graph, searchNumByName ("_A17"), searchNumByName ("_A18"));
    addEdge(dir_graph, searchNumByName ("_A18"), searchNumByName ("D1"));
    addEdge(dir_graph, searchNumByName ("D1"), searchNumByName ("Y9"));
    addEdge(dir_graph, searchNumByName ("Y9"), searchNumByName ("Y10"));
    addEdge(dir_graph, searchNumByName ("Y10"), searchNumByName ("Y11"));
    addEdge(dir_graph, searchNumByName ("Y11"), searchNumByName ("Y12"));
    addEdge(dir_graph, searchNumByName ("Y12"), searchNumByName ("Y13"));
    addEdge(dir_graph, searchNumByName ("Y13"), searchNumByName ("Y14"));
    addEdge(dir_graph, searchNumByName ("Y14"), searchNumByName ("Y15"));
    addEdge(dir_graph, searchNumByName ("Y15"), searchNumByName ("Y1"));
    addEdge(dir_graph, searchNumByName ("D1"), searchNumByName ("_A19"));
    addEdge(dir_graph, searchNumByName ("_A19"), searchNumByName ("_A20"));
    addEdge(dir_graph, searchNumByName ("_A20"), searchNumByName ("_A21"));
    addEdge(dir_graph, searchNumByName ("_A21"), searchNumByName ("_A22"));
    addEdge(dir_graph, searchNumByName ("_A22"), searchNumByName ("_A23"));
    addEdge(dir_graph, searchNumByName ("_A23"), searchNumByName ("D4"));
    addEdge(dir_graph, searchNumByName ("_A23"), searchNumByName ("E1"));
    addEdge(dir_graph, searchNumByName ("D4"), searchNumByName ("_A24"));
    addEdge(dir_graph, searchNumByName ("E1"), searchNumByName ("_A24"));
    addEdge(dir_graph, searchNumByName ("_A24"), searchNumByName ("_A25"));
    addEdge(dir_graph, searchNumByName ("_A25"), searchNumByName ("_A26"));
    addEdge(dir_graph, searchNumByName ("_A26"), searchNumByName ("_A27"));
    addEdge(dir_graph, searchNumByName ("_A27"), searchNumByName ("_A28"));
    addEdge(dir_graph, searchNumByName ("_A28"), searchNumByName ("E4"));
    addEdge(dir_graph, searchNumByName ("_A28"), searchNumByName ("F1"));
    addEdge(dir_graph, searchNumByName ("E4"), searchNumByName ("_A29"));
    addEdge(dir_graph, searchNumByName ("F1"), searchNumByName ("_A29"));
    addEdge(dir_graph, searchNumByName ("_A29"), searchNumByName ("_A30"));
    addEdge(dir_graph, searchNumByName ("_A30"), searchNumByName ("_A31"));
    addEdge(dir_graph, searchNumByName ("_A31"), searchNumByName ("_A322"));
    addEdge(dir_graph, searchNumByName ("_A32"), searchNumByName ("_A33"));
    addEdge(dir_graph, searchNumByName ("_A33"), searchNumByName ("_F4"));
    addEdge(dir_graph, searchNumByName ("F4"), searchNumByName ("_S1"));
    addEdge(dir_graph, searchNumByName ("_S1"), searchNumByName ("_S2"));
    addEdge(dir_graph, searchNumByName ("_S2"), searchNumByName ("_S3"));
    addEdge(dir_graph, searchNumByName ("_S3"), searchNumByName ("_S4"));
    addEdge(dir_graph, searchNumByName ("_S4"), searchNumByName ("_S5"));
    addEdge(dir_graph, searchNumByName ("_S5"), searchNumByName ("F3"));
    addEdge(dir_graph, searchNumByName ("F3"), searchNumByName ("L4"));
    addEdge(dir_graph, searchNumByName ("L4"), searchNumByName ("_S6"));
    addEdge(dir_graph, searchNumByName ("_S6"), searchNumByName ("_S7"));
    addEdge(dir_graph, searchNumByName ("_S7"), searchNumByName ("_S8"));
    addEdge(dir_graph, searchNumByName ("_S8"), searchNumByName ("_S9"));
    addEdge(dir_graph, searchNumByName ("_S9"), searchNumByName ("_S10"));
    addEdge(dir_graph, searchNumByName ("_S10"), searchNumByName ("L3"));
    addEdge(dir_graph, searchNumByName ("L3"), searchNumByName ("R4"));
    addEdge(dir_graph, searchNumByName ("R4"), searchNumByName ("_S11"));
    addEdge(dir_graph, searchNumByName ("_S11"), searchNumByName ("_S12"));
    addEdge(dir_graph, searchNumByName ("_S12"), searchNumByName ("_S13"));
    addEdge(dir_graph, searchNumByName ("_S13"), searchNumByName ("_S14"));
    addEdge(dir_graph, searchNumByName ("_S14"), searchNumByName ("_S15"));
    addEdge(dir_graph, searchNumByName ("_S15"), searchNumByName ("R3"));
    addEdge(dir_graph, searchNumByName ("R3"), searchNumByName ("X4"));
    addEdge(dir_graph, searchNumByName ("X4"), searchNumByName ("_S16"));
    addEdge(dir_graph, searchNumByName ("_S16"), searchNumByName ("_S17"));
    addEdge(dir_graph, searchNumByName ("_S17"), searchNumByName ("_S18"));
    addEdge(dir_graph, searchNumByName ("_S18"), searchNumByName ("_S19"));
    addEdge(dir_graph, searchNumByName ("_S19"), searchNumByName ("_S20"));
    addEdge(dir_graph, searchNumByName ("_S20"), searchNumByName ("X3"));
    addEdge(dir_graph, searchNumByName ("X3"), searchNumByName ("_H33"));
    addEdge(dir_graph, searchNumByName ("_H33"), searchNumByName ("_H32"));
    addEdge(dir_graph, searchNumByName ("_H32"), searchNumByName ("_H31"));
    addEdge(dir_graph, searchNumByName ("_H31"), searchNumByName ("_H30"));
    addEdge(dir_graph, searchNumByName ("_H30"), searchNumByName ("_H29"));
    addEdge(dir_graph, searchNumByName ("_H29"), searchNumByName ("X2"));
    addEdge(dir_graph, searchNumByName ("_H29"), searchNumByName ("W3"));
    addEdge(dir_graph, searchNumByName ("X2"), searchNumByName ("_H28"));
    addEdge(dir_graph, searchNumByName ("W3"), searchNumByName ("_H28"));
    addEdge(dir_graph, searchNumByName ("_H28"), searchNumByName ("_H27"));
    addEdge(dir_graph, searchNumByName ("_H27"), searchNumByName ("_H26"));
    addEdge(dir_graph, searchNumByName ("_H26"), searchNumByName ("_H25"));
    addEdge(dir_graph, searchNumByName ("_H25"), searchNumByName ("_H24"));
    addEdge(dir_graph, searchNumByName ("_H24"), searchNumByName ("W2"));
    addEdge(dir_graph, searchNumByName ("_H24"), searchNumByName ("V3"));
    addEdge(dir_graph, searchNumByName ("W2"), searchNumByName ("_H23"));
    addEdge(dir_graph, searchNumByName ("V3"), searchNumByName ("_H23"));
    addEdge(dir_graph, searchNumByName ("_H23"), searchNumByName ("_H22"));
    addEdge(dir_graph, searchNumByName ("_H22"), searchNumByName ("_H21"));
    addEdge(dir_graph, searchNumByName ("_H21"), searchNumByName ("_H20"));
    addEdge(dir_graph, searchNumByName ("_H20"), searchNumByName ("_H19"));
    addEdge(dir_graph, searchNumByName ("_H19"), searchNumByName ("V2"));
    addEdge(dir_graph, searchNumByName ("V2"), searchNumByName ("_H18"));
    addEdge(dir_graph, searchNumByName ("_H18"), searchNumByName ("_H17"));
    addEdge(dir_graph, searchNumByName ("_H17"), searchNumByName ("_H16"));
    addEdge(dir_graph, searchNumByName ("_H16"), searchNumByName ("U3"));
    addEdge(dir_graph, searchNumByName ("U3"), searchNumByName ("_H15"));
    addEdge(dir_graph, searchNumByName ("_H15"), searchNumByName ("_H14"));
    addEdge(dir_graph, searchNumByName ("_H14"), searchNumByName ("_H13"));
    addEdge(dir_graph, searchNumByName ("_H13"), searchNumByName ("_H12"));
    addEdge(dir_graph, searchNumByName ("_H12"), searchNumByName ("_H11"));
    addEdge(dir_graph, searchNumByName ("_H11"), searchNumByName ("U2"));
    addEdge(dir_graph, searchNumByName ("_H11"), searchNumByName ("T3"));
    addEdge(dir_graph, searchNumByName ("U2"), searchNumByName ("_H10"));
    addEdge(dir_graph, searchNumByName ("T3"), searchNumByName ("_H10"));
    addEdge(dir_graph, searchNumByName ("_H10"), searchNumByName ("_H19"));
    addEdge(dir_graph, searchNumByName ("_H9"), searchNumByName ("_H8"));
    addEdge(dir_graph, searchNumByName ("_H8"), searchNumByName ("_H7"));
    addEdge(dir_graph, searchNumByName ("_H7"), searchNumByName ("_H6"));
    addEdge(dir_graph, searchNumByName ("_H6"), searchNumByName ("T2"));
    addEdge(dir_graph, searchNumByName ("_H6"), searchNumByName ("S3"));
    addEdge(dir_graph, searchNumByName ("T2"), searchNumByName ("_H5"));
    addEdge(dir_graph, searchNumByName ("S3"), searchNumByName ("_H5"));
    addEdge(dir_graph, searchNumByName ("_H5"), searchNumByName ("_H4"));
    addEdge(dir_graph, searchNumByName ("_H4"), searchNumByName ("_H3"));
    addEdge(dir_graph, searchNumByName ("_H3"), searchNumByName ("_H2"));
    addEdge(dir_graph, searchNumByName ("_H2"), searchNumByName ("_H1"));
    addEdge(dir_graph, searchNumByName ("_H1"), searchNumByName ("S2"));
    addEdge(dir_graph, searchNumByName ("S2"), searchNumByName ("_I20"));
    addEdge(dir_graph, searchNumByName ("_I20"), searchNumByName ("_I19"));
    addEdge(dir_graph, searchNumByName ("_I19"), searchNumByName ("_I18"));
    addEdge(dir_graph, searchNumByName ("_I18"), searchNumByName ("_I17"));
    addEdge(dir_graph, searchNumByName ("_I17"), searchNumByName ("_I16"));
    addEdge(dir_graph, searchNumByName ("_I16"), searchNumByName ("S1"));
    addEdge(dir_graph, searchNumByName ("S1"), searchNumByName ("M2"));
    addEdge(dir_graph, searchNumByName ("M2"), searchNumByName ("_I15"));
    addEdge(dir_graph, searchNumByName ("_I15"), searchNumByName ("_I14"));
    addEdge(dir_graph, searchNumByName ("_I14"), searchNumByName ("_I13"));
    addEdge(dir_graph, searchNumByName ("_I13"), searchNumByName ("_I12"));
    addEdge(dir_graph, searchNumByName ("_I12"), searchNumByName ("_I11"));
    addEdge(dir_graph, searchNumByName ("_I11"), searchNumByName ("_M1"));
    addEdge(dir_graph, searchNumByName ("M1"), searchNumByName ("G2"));
    addEdge(dir_graph, searchNumByName ("G2"), searchNumByName ("_I10"));
    addEdge(dir_graph, searchNumByName ("_I10"), searchNumByName ("_I9"));
    addEdge(dir_graph, searchNumByName ("_I9"), searchNumByName ("_I8"));
    addEdge(dir_graph, searchNumByName ("_I8"), searchNumByName ("_I7"));
    addEdge(dir_graph, searchNumByName ("_I7"), searchNumByName ("_I6"));
    addEdge(dir_graph, searchNumByName ("_I6"), searchNumByName ("G1"));
    addEdge(dir_graph, searchNumByName ("G1"), searchNumByName ("A2"));
    addEdge(dir_graph, searchNumByName ("A2"), searchNumByName ("_I5"));
    addEdge(dir_graph, searchNumByName ("_I5"), searchNumByName ("_I4"));
    addEdge(dir_graph, searchNumByName ("_I4"), searchNumByName ("_I3"));
    addEdge(dir_graph, searchNumByName ("_I3"), searchNumByName ("_I2"));
    addEdge(dir_graph, searchNumByName ("_I2"), searchNumByName ("_I1"));
    addEdge(dir_graph, searchNumByName ("_I1"), searchNumByName ("A1"));
    addEdge(dir_graph, searchNumByName ("A1"), searchNumByName ("_A1"));
    addEdge(dir_graph, searchNumByName ("_A1"), searchNumByName ("_A2"));
    addEdge(dir_graph, searchNumByName ("_A2"), searchNumByName ("_A3"));
    addEdge(dir_graph, searchNumByName ("_A3"), searchNumByName ("_A4"));
    addEdge(dir_graph, searchNumByName ("_A4"), searchNumByName ("_A5"));
    addEdge(dir_graph, searchNumByName ("_A5"), searchNumByName ("A4"));
    addEdge(dir_graph, searchNumByName ("_A5"), searchNumByName ("B1"));
    addEdge(dir_graph, searchNumByName ("A4"), searchNumByName ("_A6"));
    addEdge(dir_graph, searchNumByName ("B1"), searchNumByName ("_A6"));
    addEdge(dir_graph, searchNumByName ("_A6"), searchNumByName ("_A7"));
    addEdge(dir_graph, searchNumByName ("_A7"), searchNumByName ("_A8"));
    addEdge(dir_graph, searchNumByName ("_A8"), searchNumByName ("_A9"));
    addEdge(dir_graph, searchNumByName ("_A9"), searchNumByName ("_A10"));
    addEdge(dir_graph, searchNumByName ("_A10"), searchNumByName ("B4"));
    addEdge(dir_graph, searchNumByName ("_A10"), searchNumByName ("C1"));
    addEdge(dir_graph, searchNumByName ("B4"), searchNumByName ("_A11"));
    addEdge(dir_graph, searchNumByName ("C1"), searchNumByName ("_A11"));
    addEdge(dir_graph, searchNumByName ("_A11"), searchNumByName ("_A12"));
    addEdge(dir_graph, searchNumByName ("_A12"), searchNumByName ("_A13"));
    addEdge(dir_graph, searchNumByName ("_A13"), searchNumByName ("_A14"));
    addEdge(dir_graph, searchNumByName ("_A14"), searchNumByName ("_A15"));
    addEdge(dir_graph, searchNumByName ("_A15"), searchNumByName ("C4"));
    addEdge(dir_graph, searchNumByName ("C4"), searchNumByName ("_L1"));
    addEdge(dir_graph, searchNumByName ("C4"), searchNumByName ("_M1"));
    addEdge(dir_graph, searchNumByName ("_L1"), searchNumByName ("_L2"));
    addEdge(dir_graph, searchNumByName ("_L1"), searchNumByName ("_M2"));
    addEdge(dir_graph, searchNumByName ("_M1"), searchNumByName ("_M2"));
    addEdge(dir_graph, searchNumByName ("_M1"), searchNumByName ("_L2"));
    addEdge(dir_graph, searchNumByName ("_L2"), searchNumByName ("_L3"));
    addEdge(dir_graph, searchNumByName ("_L2"), searchNumByName ("_M3"));
    addEdge(dir_graph, searchNumByName ("_M2"), searchNumByName ("_M3"));
    addEdge(dir_graph, searchNumByName ("_M2"), searchNumByName ("_L3"));
    addEdge(dir_graph, searchNumByName ("_L3"), searchNumByName ("_L4"));
    addEdge(dir_graph, searchNumByName ("_L3"), searchNumByName ("_M4"));
    addEdge(dir_graph, searchNumByName ("_M3"), searchNumByName ("_L4"));
    addEdge(dir_graph, searchNumByName ("_M3"), searchNumByName ("_M4"));
    addEdge(dir_graph, searchNumByName ("_L4"), searchNumByName ("_L5"));
    addEdge(dir_graph, searchNumByName ("_L4"), searchNumByName ("_M5"));
    addEdge(dir_graph, searchNumByName ("_M4"), searchNumByName ("_L5"));
    addEdge(dir_graph, searchNumByName ("_M4"), searchNumByName ("_M5"));
    addEdge(dir_graph, searchNumByName ("_L5"), searchNumByName ("_L6"));
    addEdge(dir_graph, searchNumByName ("_L5"), searchNumByName ("_M6"));
    addEdge(dir_graph, searchNumByName ("_M5"), searchNumByName ("_L6"));
    addEdge(dir_graph, searchNumByName ("_M5"), searchNumByName ("_M6"));
    addEdge(dir_graph, searchNumByName ("_L6"), searchNumByName ("_L7"));
    addEdge(dir_graph, searchNumByName ("_L6"), searchNumByName ("_M7"));
    addEdge(dir_graph, searchNumByName ("_M6"), searchNumByName ("_L7"));
    addEdge(dir_graph, searchNumByName ("_M6"), searchNumByName ("_M7"));
    addEdge(dir_graph, searchNumByName ("_L7"), searchNumByName ("_L8"));
    addEdge(dir_graph, searchNumByName ("_L7"), searchNumByName ("_M8"));
    addEdge(dir_graph, searchNumByName ("_M7"), searchNumByName ("_L8"));
    addEdge(dir_graph, searchNumByName ("_M7"), searchNumByName ("_M8"));
    addEdge(dir_graph, searchNumByName ("_L8"), searchNumByName ("_L9"));
    addEdge(dir_graph, searchNumByName ("_L8"), searchNumByName ("_M9"));
    addEdge(dir_graph, searchNumByName ("_M8"), searchNumByName ("_L9"));
    addEdge(dir_graph, searchNumByName ("_M8"), searchNumByName ("_M9"));
    addEdge(dir_graph, searchNumByName ("_L9"), searchNumByName ("_L10"));
    addEdge(dir_graph, searchNumByName ("_L9"), searchNumByName ("_M10"));
    addEdge(dir_graph, searchNumByName ("_M9"), searchNumByName ("_L10"));
    addEdge(dir_graph, searchNumByName ("_M9"), searchNumByName ("_M10"));
    addEdge(dir_graph, searchNumByName ("_L10"), searchNumByName ("_L11"));
    addEdge(dir_graph, searchNumByName ("_L10"), searchNumByName ("_M11"));
    addEdge(dir_graph, searchNumByName ("_M10"), searchNumByName ("_L11"));
    addEdge(dir_graph, searchNumByName ("_M10"), searchNumByName ("_M11"));
    addEdge(dir_graph, searchNumByName ("_L11"), searchNumByName ("_L12"));
    addEdge(dir_graph, searchNumByName ("_L11"), searchNumByName ("_M12"));
    addEdge(dir_graph, searchNumByName ("_M11"), searchNumByName ("_L12"));
    addEdge(dir_graph, searchNumByName ("_M11"), searchNumByName ("_M12"));
    addEdge(dir_graph, searchNumByName ("_L12"), searchNumByName ("_L13"));
    addEdge(dir_graph, searchNumByName ("_L12"), searchNumByName ("_M13"));
    addEdge(dir_graph, searchNumByName ("_M12"), searchNumByName ("_L13"));
    addEdge(dir_graph, searchNumByName ("_M12"), searchNumByName ("_M13"));
    addEdge(dir_graph, searchNumByName ("_L13"), searchNumByName ("_L14"));
    addEdge(dir_graph, searchNumByName ("_L13"), searchNumByName ("_M14"));
    addEdge(dir_graph, searchNumByName ("_M13"), searchNumByName ("_L14"));
    addEdge(dir_graph, searchNumByName ("_M13"), searchNumByName ("_M14"));
    addEdge(dir_graph, searchNumByName ("_L14"), searchNumByName ("_L15"));
    addEdge(dir_graph, searchNumByName ("_L14"), searchNumByName ("_M15"));
    addEdge(dir_graph, searchNumByName ("_M14"), searchNumByName ("_L15"));
    addEdge(dir_graph, searchNumByName ("_M14"), searchNumByName ("_M15"));
    addEdge(dir_graph, searchNumByName ("_L15"), searchNumByName ("_L16"));
    addEdge(dir_graph, searchNumByName ("_L15"), searchNumByName ("_M16"));
    addEdge(dir_graph, searchNumByName ("_M15"), searchNumByName ("_L16"));
    addEdge(dir_graph, searchNumByName ("_M15"), searchNumByName ("_M16"));
    addEdge(dir_graph, searchNumByName ("_L16"), searchNumByName ("_L17"));
    addEdge(dir_graph, searchNumByName ("_L16"), searchNumByName ("_M17"));
    addEdge(dir_graph, searchNumByName ("_M16"), searchNumByName ("_L17"));
    addEdge(dir_graph, searchNumByName ("_M16"), searchNumByName ("_M17"));
    addEdge(dir_graph, searchNumByName ("_L17"), searchNumByName ("_L18"));
    addEdge(dir_graph, searchNumByName ("_L17"), searchNumByName ("_M18"));
    addEdge(dir_graph, searchNumByName ("_M17"), searchNumByName ("_L18"));
    addEdge(dir_graph, searchNumByName ("_M17"), searchNumByName ("_M18"));
    addEdge(dir_graph, searchNumByName ("_L18"), searchNumByName ("_L19"));
    addEdge(dir_graph, searchNumByName ("_L18"), searchNumByName ("_M19"));
    addEdge(dir_graph, searchNumByName ("_M18"), searchNumByName ("_L19"));
    addEdge(dir_graph, searchNumByName ("_M18"), searchNumByName ("_M19"));
    addEdge(dir_graph, searchNumByName ("_L19"), searchNumByName ("_L20"));
    addEdge(dir_graph, searchNumByName ("_L19"), searchNumByName ("_M20"));
    addEdge(dir_graph, searchNumByName ("_M19"), searchNumByName ("_L20"));
    addEdge(dir_graph, searchNumByName ("_M19"), searchNumByName ("_M20"));
    addEdge(dir_graph, searchNumByName ("_L20"), searchNumByName ("_L21"));
    addEdge(dir_graph, searchNumByName ("_L20"), searchNumByName ("_M21"));
    addEdge(dir_graph, searchNumByName ("_M20"), searchNumByName ("_L21"));
    addEdge(dir_graph, searchNumByName ("_M20"), searchNumByName ("_M21"));
    addEdge(dir_graph, searchNumByName ("_L21"), searchNumByName ("_L22"));
    addEdge(dir_graph, searchNumByName ("_L21"), searchNumByName ("_M22"));
    addEdge(dir_graph, searchNumByName ("_M21"), searchNumByName ("_L22"));
    addEdge(dir_graph, searchNumByName ("_M21"), searchNumByName ("_M22"));
    addEdge(dir_graph, searchNumByName ("_L22"), searchNumByName ("_L23"));
    addEdge(dir_graph, searchNumByName ("_L22"), searchNumByName ("_M23"));
    addEdge(dir_graph, searchNumByName ("_M22"), searchNumByName ("_L23"));
    addEdge(dir_graph, searchNumByName ("_M22"), searchNumByName ("_M23"));
    addEdge(dir_graph, searchNumByName ("_L23"), searchNumByName ("_L24"));
    addEdge(dir_graph, searchNumByName ("_L23"), searchNumByName ("_M24"));
    addEdge(dir_graph, searchNumByName ("_M23"), searchNumByName ("_L24"));
    addEdge(dir_graph, searchNumByName ("_M23"), searchNumByName ("_M24"));
    addEdge(dir_graph, searchNumByName ("_L24"), searchNumByName ("_L25"));
    addEdge(dir_graph, searchNumByName ("_L24"), searchNumByName ("_M25"));
    addEdge(dir_graph, searchNumByName ("_M24"), searchNumByName ("_L25"));
    addEdge(dir_graph, searchNumByName ("_M24"), searchNumByName ("_M25"));
    addEdge(dir_graph, searchNumByName ("_L25"), searchNumByName ("_L26"));
    addEdge(dir_graph, searchNumByName ("_L25"), searchNumByName ("_M26"));
    addEdge(dir_graph, searchNumByName ("_M25"), searchNumByName ("_L26"));
    addEdge(dir_graph, searchNumByName ("_M25"), searchNumByName ("_M26"));
    addEdge(dir_graph, searchNumByName ("_L26"), searchNumByName ("U3"));
    addEdge(dir_graph, searchNumByName ("_M26"), searchNumByName ("U3"));
    addEdge(dir_graph, searchNumByName ("U3"), searchNumByName ("Z9"));
    addEdge(dir_graph, searchNumByName ("Z9"), searchNumByName ("Z10"));
    addEdge(dir_graph, searchNumByName ("Z10"), searchNumByName ("Z11"));
    addEdge(dir_graph, searchNumByName ("Z11"), searchNumByName ("Z12"));
    addEdge(dir_graph, searchNumByName ("Z12"), searchNumByName ("Z13"));
    addEdge(dir_graph, searchNumByName ("Z13"), searchNumByName ("Z14"));
    addEdge(dir_graph, searchNumByName ("Z14"), searchNumByName ("Z15"));
    addEdge(dir_graph, searchNumByName ("Z15"), searchNumByName ("Z1"));
    addEdge(dir_graph, searchNumByName ("Z1"), searchNumByName ("Z2"));
    addEdge(dir_graph, searchNumByName ("Z2"), searchNumByName ("Z3"));
    addEdge(dir_graph, searchNumByName ("Z3"), searchNumByName ("Z4"));
    addEdge(dir_graph, searchNumByName ("Z4"), searchNumByName ("Z5"));
    addEdge(dir_graph, searchNumByName ("Z5"), searchNumByName ("Z6"));
    addEdge(dir_graph, searchNumByName ("Z6"), searchNumByName ("Z7"));
    addEdge(dir_graph, searchNumByName ("Z7"), searchNumByName ("Z8"));
    addEdge(dir_graph, searchNumByName ("Z8"), searchNumByName ("V2"));
    addEdge(dir_graph, searchNumByName ("V2"), searchNumByName ("_N26"));
    addEdge(dir_graph, searchNumByName ("V2"), searchNumByName ("_O26"));
    addEdge(dir_graph, searchNumByName ("_N26"), searchNumByName ("_N25"));
    addEdge(dir_graph, searchNumByName ("_N26"), searchNumByName ("_O25"));
    addEdge(dir_graph, searchNumByName ("_O26"), searchNumByName ("_N25"));
    addEdge(dir_graph, searchNumByName ("_O26"), searchNumByName ("_O25"));
    addEdge(dir_graph, searchNumByName ("_N25"), searchNumByName ("_N24"));
    addEdge(dir_graph, searchNumByName ("_N25"), searchNumByName ("_O24"));
    addEdge(dir_graph, searchNumByName ("_O25"), searchNumByName ("_N24"));
    addEdge(dir_graph, searchNumByName ("_O25"), searchNumByName ("_O24"));
    addEdge(dir_graph, searchNumByName ("_N24"), searchNumByName ("_N23"));
    addEdge(dir_graph, searchNumByName ("_N24"), searchNumByName ("_O23"));
    addEdge(dir_graph, searchNumByName ("_O24"), searchNumByName ("_N23"));
    addEdge(dir_graph, searchNumByName ("_O24"), searchNumByName ("_O23"));
    addEdge(dir_graph, searchNumByName ("_N23"), searchNumByName ("_N22"));
    addEdge(dir_graph, searchNumByName ("_N23"), searchNumByName ("_O22"));
    addEdge(dir_graph, searchNumByName ("_O23"), searchNumByName ("_N22"));
    addEdge(dir_graph, searchNumByName ("_O23"), searchNumByName ("_O22"));
    addEdge(dir_graph, searchNumByName ("_N22"), searchNumByName ("_N21"));
    addEdge(dir_graph, searchNumByName ("_N22"), searchNumByName ("_O21"));
    addEdge(dir_graph, searchNumByName ("_O22"), searchNumByName ("_N21"));
    addEdge(dir_graph, searchNumByName ("_O22"), searchNumByName ("_O21"));
    addEdge(dir_graph, searchNumByName ("_N21"), searchNumByName ("_N20"));
    addEdge(dir_graph, searchNumByName ("_N21"), searchNumByName ("_O20"));
    addEdge(dir_graph, searchNumByName ("_O21"), searchNumByName ("_N20"));
    addEdge(dir_graph, searchNumByName ("_O21"), searchNumByName ("_O20"));
    addEdge(dir_graph, searchNumByName ("_N20"), searchNumByName ("_N19"));
    addEdge(dir_graph, searchNumByName ("_N20"), searchNumByName ("_O19"));
    addEdge(dir_graph, searchNumByName ("_O20"), searchNumByName ("_N19"));
    addEdge(dir_graph, searchNumByName ("_O20"), searchNumByName ("_O19"));
    addEdge(dir_graph, searchNumByName ("_N19"), searchNumByName ("_N18"));
    addEdge(dir_graph, searchNumByName ("_N19"), searchNumByName ("_O18"));
    addEdge(dir_graph, searchNumByName ("_O19"), searchNumByName ("_N18"));
    addEdge(dir_graph, searchNumByName ("_O19"), searchNumByName ("_O18"));
    addEdge(dir_graph, searchNumByName ("_N18"), searchNumByName ("_N17"));
    addEdge(dir_graph, searchNumByName ("_N18"), searchNumByName ("_O17"));
    addEdge(dir_graph, searchNumByName ("_O18"), searchNumByName ("_N17"));
    addEdge(dir_graph, searchNumByName ("_O18"), searchNumByName ("_O17"));
    addEdge(dir_graph, searchNumByName ("_N17"), searchNumByName ("_N16"));
    addEdge(dir_graph, searchNumByName ("_N17"), searchNumByName ("_O16"));
    addEdge(dir_graph, searchNumByName ("_O17"), searchNumByName ("_N16"));
    addEdge(dir_graph, searchNumByName ("_O17"), searchNumByName ("_O16"));
    addEdge(dir_graph, searchNumByName ("_N16"), searchNumByName ("_N15"));
    addEdge(dir_graph, searchNumByName ("_N16"), searchNumByName ("_O15"));
    addEdge(dir_graph, searchNumByName ("_O16"), searchNumByName ("_N15"));
    addEdge(dir_graph, searchNumByName ("_O16"), searchNumByName ("_O15"));
    addEdge(dir_graph, searchNumByName ("_N15"), searchNumByName ("_N14"));
    addEdge(dir_graph, searchNumByName ("_N15"), searchNumByName ("_O14"));
    addEdge(dir_graph, searchNumByName ("_O15"), searchNumByName ("_N14"));
    addEdge(dir_graph, searchNumByName ("_O15"), searchNumByName ("_O14"));
    addEdge(dir_graph, searchNumByName ("_N14"), searchNumByName ("_N13"));
    addEdge(dir_graph, searchNumByName ("_N14"), searchNumByName ("_O13"));
    addEdge(dir_graph, searchNumByName ("_O14"), searchNumByName ("_N13"));
    addEdge(dir_graph, searchNumByName ("_O14"), searchNumByName ("_O13"));
    addEdge(dir_graph, searchNumByName ("_N13"), searchNumByName ("_N12"));
    addEdge(dir_graph, searchNumByName ("_N13"), searchNumByName ("_O12"));
    addEdge(dir_graph, searchNumByName ("_O13"), searchNumByName ("_N12"));
    addEdge(dir_graph, searchNumByName ("_O13"), searchNumByName ("_O12"));
    addEdge(dir_graph, searchNumByName ("_N12"), searchNumByName ("_N11"));
    addEdge(dir_graph, searchNumByName ("_N12"), searchNumByName ("_O11"));
    addEdge(dir_graph, searchNumByName ("_O12"), searchNumByName ("_N11"));
    addEdge(dir_graph, searchNumByName ("_O12"), searchNumByName ("_O11"));
    addEdge(dir_graph, searchNumByName ("_N11"), searchNumByName ("_N10"));
    addEdge(dir_graph, searchNumByName ("_N11"), searchNumByName ("_O10"));
    addEdge(dir_graph, searchNumByName ("_O11"), searchNumByName ("_N10"));
    addEdge(dir_graph, searchNumByName ("_O11"), searchNumByName ("_O10"));
    addEdge(dir_graph, searchNumByName ("_N10"), searchNumByName ("_N9"));
    addEdge(dir_graph, searchNumByName ("_N10"), searchNumByName ("_O9"));
    addEdge(dir_graph, searchNumByName ("_O10"), searchNumByName ("_N9"));
    addEdge(dir_graph, searchNumByName ("_O10"), searchNumByName ("_O9"));
    addEdge(dir_graph, searchNumByName ("_N9"), searchNumByName ("_N8"));
    addEdge(dir_graph, searchNumByName ("_N9"), searchNumByName ("_O8"));
    addEdge(dir_graph, searchNumByName ("_O9"), searchNumByName ("_N8"));
    addEdge(dir_graph, searchNumByName ("_O9"), searchNumByName ("_O8"));
    addEdge(dir_graph, searchNumByName ("_N8"), searchNumByName ("_N7"));
    addEdge(dir_graph, searchNumByName ("_N8"), searchNumByName ("_O7"));
    addEdge(dir_graph, searchNumByName ("_O8"), searchNumByName ("_N7"));
    addEdge(dir_graph, searchNumByName ("_O8"), searchNumByName ("_O7"));
    addEdge(dir_graph, searchNumByName ("_N7"), searchNumByName ("_N6"));
    addEdge(dir_graph, searchNumByName ("_N7"), searchNumByName ("_O6"));
    addEdge(dir_graph, searchNumByName ("_O7"), searchNumByName ("_N6"));
    addEdge(dir_graph, searchNumByName ("_O7"), searchNumByName ("_O6"));
    addEdge(dir_graph, searchNumByName ("_N6"), searchNumByName ("_N5"));
    addEdge(dir_graph, searchNumByName ("_N6"), searchNumByName ("_O5"));
    addEdge(dir_graph, searchNumByName ("_O6"), searchNumByName ("_N5"));
    addEdge(dir_graph, searchNumByName ("_O6"), searchNumByName ("_O5"));
    addEdge(dir_graph, searchNumByName ("_N5"), searchNumByName ("_N4"));
    addEdge(dir_graph, searchNumByName ("_N5"), searchNumByName ("_O4"));
    addEdge(dir_graph, searchNumByName ("_O5"), searchNumByName ("_N4"));
    addEdge(dir_graph, searchNumByName ("_O5"), searchNumByName ("_O4"));
    addEdge(dir_graph, searchNumByName ("_N4"), searchNumByName ("_N3"));
    addEdge(dir_graph, searchNumByName ("_N4"), searchNumByName ("_O3"));
    addEdge(dir_graph, searchNumByName ("_O4"), searchNumByName ("_N3"));
    addEdge(dir_graph, searchNumByName ("_O4"), searchNumByName ("_O3"));
    addEdge(dir_graph, searchNumByName ("_N3"), searchNumByName ("_N2"));
    addEdge(dir_graph, searchNumByName ("_N3"), searchNumByName ("_O2"));
    addEdge(dir_graph, searchNumByName ("_O3"), searchNumByName ("_N2"));
    addEdge(dir_graph, searchNumByName ("_O3"), searchNumByName ("_O2"));
    addEdge(dir_graph, searchNumByName ("_N2"), searchNumByName ("_N1"));
    addEdge(dir_graph, searchNumByName ("_N2"), searchNumByName ("_O1"));
    addEdge(dir_graph, searchNumByName ("_O2"), searchNumByName ("_N1"));
    addEdge(dir_graph, searchNumByName ("_O2"), searchNumByName ("_O1"));
    addEdge(dir_graph, searchNumByName ("_O1"), searchNumByName ("D1"));
    addEdge(dir_graph, searchNumByName ("_N1"), searchNumByName ("D1"));
    addEdge(dir_graph, searchNumByName ("A4"), searchNumByName ("_J1"));
    addEdge(dir_graph, searchNumByName ("B1"), searchNumByName ("_J1"));
    addEdge(dir_graph, searchNumByName ("_J1"), searchNumByName ("_J2"));
    addEdge(dir_graph, searchNumByName ("_J2"), searchNumByName ("_J3"));
    addEdge(dir_graph, searchNumByName ("_J3"), searchNumByName ("_J4"));
    addEdge(dir_graph, searchNumByName ("_J4"), searchNumByName ("_J5"));
    addEdge(dir_graph, searchNumByName ("_J5"), searchNumByName ("A3"));
    addEdge(dir_graph, searchNumByName ("_J5"), searchNumByName ("B2"));
    addEdge(dir_graph, searchNumByName ("A3"), searchNumByName ("G4"));
    addEdge(dir_graph, searchNumByName ("A3"), searchNumByName ("H1"));
    addEdge(dir_graph, searchNumByName ("B2"), searchNumByName ("G4"));
    addEdge(dir_graph, searchNumByName ("B2"), searchNumByName ("H1"));
    addEdge(dir_graph, searchNumByName ("G4"), searchNumByName ("_J6"));
    addEdge(dir_graph, searchNumByName ("H1"), searchNumByName ("_J6"));
    addEdge(dir_graph, searchNumByName ("_J6"), searchNumByName ("_J7"));
    addEdge(dir_graph, searchNumByName ("_J7"), searchNumByName ("_J8"));
    addEdge(dir_graph, searchNumByName ("_J8"), searchNumByName ("_J9"));
    addEdge(dir_graph, searchNumByName ("_J9"), searchNumByName ("_J10"));
    addEdge(dir_graph, searchNumByName ("_J10"), searchNumByName ("G3"));
    addEdge(dir_graph, searchNumByName ("_J10"), searchNumByName ("H2"));
    addEdge(dir_graph, searchNumByName ("G3"), searchNumByName ("M4"));
    addEdge(dir_graph, searchNumByName ("G3"), searchNumByName ("N1"));
    addEdge(dir_graph, searchNumByName ("H2"), searchNumByName ("M4"));
    addEdge(dir_graph, searchNumByName ("H2"), searchNumByName ("N1"));
    addEdge(dir_graph, searchNumByName ("M4"), searchNumByName ("_J11"));
    addEdge(dir_graph, searchNumByName ("N1"), searchNumByName ("_J11"));
    addEdge(dir_graph, searchNumByName ("_J11"), searchNumByName ("_J12"));
    addEdge(dir_graph, searchNumByName ("_J12"), searchNumByName ("_J13"));
    addEdge(dir_graph, searchNumByName ("_J13"), searchNumByName ("_J14"));
    addEdge(dir_graph, searchNumByName ("_J14"), searchNumByName ("_J15"));
    addEdge(dir_graph, searchNumByName ("_J15"), searchNumByName ("M3"));
    addEdge(dir_graph, searchNumByName ("_J15"), searchNumByName ("N2"));
    addEdge(dir_graph, searchNumByName ("M3"), searchNumByName ("S4"));
    addEdge(dir_graph, searchNumByName ("M3"), searchNumByName ("T1"));
    addEdge(dir_graph, searchNumByName ("N2"), searchNumByName ("S4"));
    addEdge(dir_graph, searchNumByName ("N2"), searchNumByName ("T1"));
    addEdge(dir_graph, searchNumByName ("S4"), searchNumByName ("_J16"));
    addEdge(dir_graph, searchNumByName ("T1"), searchNumByName ("_J16"));
    addEdge(dir_graph, searchNumByName ("_J16"), searchNumByName ("_J17"));
    addEdge(dir_graph, searchNumByName ("_J17"), searchNumByName ("_J18"));
    addEdge(dir_graph, searchNumByName ("_J18"), searchNumByName ("_J19"));
    addEdge(dir_graph, searchNumByName ("_J19"), searchNumByName ("_J20"));
    addEdge(dir_graph, searchNumByName ("_J20"), searchNumByName ("S3"));
    addEdge(dir_graph, searchNumByName ("_J20"), searchNumByName ("T2"));
    addEdge(dir_graph, searchNumByName ("T3"), searchNumByName ("_K20"));
    addEdge(dir_graph, searchNumByName ("U2"), searchNumByName ("_K20"));
    addEdge(dir_graph, searchNumByName ("_K20"), searchNumByName ("_K19"));
    addEdge(dir_graph, searchNumByName ("_K19"), searchNumByName ("_K18"));
    addEdge(dir_graph, searchNumByName ("_K18"), searchNumByName ("_K17"));
    addEdge(dir_graph, searchNumByName ("_K17"), searchNumByName ("_K16"));
    addEdge(dir_graph, searchNumByName ("_K16"), searchNumByName ("T4"));
    addEdge(dir_graph, searchNumByName ("_K16"), searchNumByName ("U1"));
    addEdge(dir_graph, searchNumByName ("T4"), searchNumByName ("N3"));
    addEdge(dir_graph, searchNumByName ("T4"), searchNumByName ("O2"));
    addEdge(dir_graph, searchNumByName ("U1"), searchNumByName ("N3"));
    addEdge(dir_graph, searchNumByName ("U1"), searchNumByName ("O2"));
    addEdge(dir_graph, searchNumByName ("N3"), searchNumByName ("_K15"));
    addEdge(dir_graph, searchNumByName ("O2"), searchNumByName ("_K15"));
    addEdge(dir_graph, searchNumByName ("_K15"), searchNumByName ("_K14"));
    addEdge(dir_graph, searchNumByName ("_K14"), searchNumByName ("_K13"));
    addEdge(dir_graph, searchNumByName ("_K13"), searchNumByName ("_K12"));
    addEdge(dir_graph, searchNumByName ("_K12"), searchNumByName ("_K11"));
    addEdge(dir_graph, searchNumByName ("_K11"), searchNumByName ("N4"));
    addEdge(dir_graph, searchNumByName ("_K11"), searchNumByName ("O1"));
    addEdge(dir_graph, searchNumByName ("N4"), searchNumByName ("H3"));
    addEdge(dir_graph, searchNumByName ("N4"), searchNumByName ("I2"));
    addEdge(dir_graph, searchNumByName ("O1"), searchNumByName ("H3"));
    addEdge(dir_graph, searchNumByName ("O1"), searchNumByName ("I2"));
    addEdge(dir_graph, searchNumByName ("H3"), searchNumByName ("_K10"));
    addEdge(dir_graph, searchNumByName ("I2"), searchNumByName ("_K10"));
    addEdge(dir_graph, searchNumByName ("_K10"), searchNumByName ("_K9"));
    addEdge(dir_graph, searchNumByName ("_K9"), searchNumByName ("_K8"));
    addEdge(dir_graph, searchNumByName ("_K8"), searchNumByName ("_K7"));
    addEdge(dir_graph, searchNumByName ("_K7"), searchNumByName ("_K6"));
    addEdge(dir_graph, searchNumByName ("_K6"), searchNumByName ("H4"));
    addEdge(dir_graph, searchNumByName ("_K6"), searchNumByName ("I1"));
    addEdge(dir_graph, searchNumByName ("H4"), searchNumByName ("B3"));
    addEdge(dir_graph, searchNumByName ("H4"), searchNumByName ("C2"));
    addEdge(dir_graph, searchNumByName ("I1"), searchNumByName ("B3"));
    addEdge(dir_graph, searchNumByName ("I1"), searchNumByName ("C2"));
    addEdge(dir_graph, searchNumByName ("B3"), searchNumByName ("_K5"));
    addEdge(dir_graph, searchNumByName ("C2"), searchNumByName ("_K5"));
    addEdge(dir_graph, searchNumByName ("_K5"), searchNumByName ("_K4"));
    addEdge(dir_graph, searchNumByName ("_K4"), searchNumByName ("_K3"));
    addEdge(dir_graph, searchNumByName ("_K3"), searchNumByName ("_K2"));
    addEdge(dir_graph, searchNumByName ("_K2"), searchNumByName ("_K1"));
    addEdge(dir_graph, searchNumByName ("_K1"), searchNumByName ("B4"));
    addEdge(dir_graph, searchNumByName ("_K1"), searchNumByName ("C1"));
    addEdge(dir_graph, searchNumByName ("D4"), searchNumByName ("_P1"));
    addEdge(dir_graph, searchNumByName ("E1"), searchNumByName ("_P1"));
    addEdge(dir_graph, searchNumByName ("_P1"), searchNumByName ("_P2"));
    addEdge(dir_graph, searchNumByName ("_P2"), searchNumByName ("_P3"));
    addEdge(dir_graph, searchNumByName ("_P3"), searchNumByName ("_P4"));
    addEdge(dir_graph, searchNumByName ("_P4"), searchNumByName ("_P5"));
    addEdge(dir_graph, searchNumByName ("_P5"), searchNumByName ("D3"));
    addEdge(dir_graph, searchNumByName ("_P5"), searchNumByName ("E2"));
    addEdge(dir_graph, searchNumByName ("D3"), searchNumByName ("J4"));
    addEdge(dir_graph, searchNumByName ("D3"), searchNumByName ("K1"));
    addEdge(dir_graph, searchNumByName ("E2"), searchNumByName ("J4"));
    addEdge(dir_graph, searchNumByName ("E2"), searchNumByName ("K1"));
    addEdge(dir_graph, searchNumByName ("J4"), searchNumByName ("_P6"));
    addEdge(dir_graph, searchNumByName ("K1"), searchNumByName ("_P6"));
    addEdge(dir_graph, searchNumByName ("_P6"), searchNumByName ("_P7"));
    addEdge(dir_graph, searchNumByName ("_P7"), searchNumByName ("_P8"));
    addEdge(dir_graph, searchNumByName ("_P8"), searchNumByName ("_P9"));
    addEdge(dir_graph, searchNumByName ("_P9"), searchNumByName ("_P10"));
    addEdge(dir_graph, searchNumByName ("_P10"), searchNumByName ("J3"));
    addEdge(dir_graph, searchNumByName ("_P10"), searchNumByName ("K2"));
    addEdge(dir_graph, searchNumByName ("J3"), searchNumByName ("P4"));
    addEdge(dir_graph, searchNumByName ("J3"), searchNumByName ("Q1"));
    addEdge(dir_graph, searchNumByName ("K2"), searchNumByName ("P4"));
    addEdge(dir_graph, searchNumByName ("K2"), searchNumByName ("Q1"));
    addEdge(dir_graph, searchNumByName ("P4"), searchNumByName ("_P11"));
    addEdge(dir_graph, searchNumByName ("Q1"), searchNumByName ("_P11"));
    addEdge(dir_graph, searchNumByName ("_P11"), searchNumByName ("_P12"));
    addEdge(dir_graph, searchNumByName ("_P12"), searchNumByName ("_P13"));
    addEdge(dir_graph, searchNumByName ("_P13"), searchNumByName ("_P14"));
    addEdge(dir_graph, searchNumByName ("_P14"), searchNumByName ("_P15"));
    addEdge(dir_graph, searchNumByName ("_P15"), searchNumByName ("P3"));
    addEdge(dir_graph, searchNumByName ("_P15"), searchNumByName ("Q2"));
    addEdge(dir_graph, searchNumByName ("P3"), searchNumByName ("V4"));
    addEdge(dir_graph, searchNumByName ("P3"), searchNumByName ("W1"));
    addEdge(dir_graph, searchNumByName ("Q2"), searchNumByName ("V4"));
    addEdge(dir_graph, searchNumByName ("Q2"), searchNumByName ("W1"));
    addEdge(dir_graph, searchNumByName ("V4"), searchNumByName ("_P16"));
    addEdge(dir_graph, searchNumByName ("W1"), searchNumByName ("_P16"));
    addEdge(dir_graph, searchNumByName ("_P16"), searchNumByName ("_P17"));
    addEdge(dir_graph, searchNumByName ("_P17"), searchNumByName ("_P18"));
    addEdge(dir_graph, searchNumByName ("_P18"), searchNumByName ("_P19"));
    addEdge(dir_graph, searchNumByName ("_P19"), searchNumByName ("_P20"));
    addEdge(dir_graph, searchNumByName ("_P20"), searchNumByName ("V3"));
    addEdge(dir_graph, searchNumByName ("_P20"), searchNumByName ("W2"));
    addEdge(dir_graph, searchNumByName ("W3"), searchNumByName ("_Q20"));
    addEdge(dir_graph, searchNumByName ("X2"), searchNumByName ("_Q20"));
    addEdge(dir_graph, searchNumByName ("_Q20"), searchNumByName ("_Q19"));
    addEdge(dir_graph, searchNumByName ("_Q19"), searchNumByName ("_Q18"));
    addEdge(dir_graph, searchNumByName ("_Q18"), searchNumByName ("_Q17"));
    addEdge(dir_graph, searchNumByName ("_Q17"), searchNumByName ("_Q16"));
    addEdge(dir_graph, searchNumByName ("_Q16"), searchNumByName ("W4"));
    addEdge(dir_graph, searchNumByName ("_Q16"), searchNumByName ("X1"));
    addEdge(dir_graph, searchNumByName ("W4"), searchNumByName ("Q3"));
    addEdge(dir_graph, searchNumByName ("W4"), searchNumByName ("R2"));
    addEdge(dir_graph, searchNumByName ("X1"), searchNumByName ("Q3"));
    addEdge(dir_graph, searchNumByName ("X1"), searchNumByName ("R2"));
    addEdge(dir_graph, searchNumByName ("Q3"), searchNumByName ("_Q15"));
    addEdge(dir_graph, searchNumByName ("R2"), searchNumByName ("_Q15"));
    addEdge(dir_graph, searchNumByName ("_Q15"), searchNumByName ("_Q14"));
    addEdge(dir_graph, searchNumByName ("_Q14"), searchNumByName ("_Q13"));
    addEdge(dir_graph, searchNumByName ("_Q13"), searchNumByName ("_Q12"));
    addEdge(dir_graph, searchNumByName ("_Q12"), searchNumByName ("_Q11"));
    addEdge(dir_graph, searchNumByName ("_Q11"), searchNumByName ("Q4"));
    addEdge(dir_graph, searchNumByName ("_Q11"), searchNumByName ("R1"));
    addEdge(dir_graph, searchNumByName ("Q4"), searchNumByName ("K3"));
    addEdge(dir_graph, searchNumByName ("Q4"), searchNumByName ("L2"));
    addEdge(dir_graph, searchNumByName ("R1"), searchNumByName ("K3"));
    addEdge(dir_graph, searchNumByName ("R1"), searchNumByName ("L2"));
    addEdge(dir_graph, searchNumByName ("H3"), searchNumByName ("_Q10"));
    addEdge(dir_graph, searchNumByName ("I2"), searchNumByName ("_Q10"));
    addEdge(dir_graph, searchNumByName ("_Q10"), searchNumByName ("_Q9"));
    addEdge(dir_graph, searchNumByName ("_Q9"), searchNumByName ("_Q8"));
    addEdge(dir_graph, searchNumByName ("_Q8"), searchNumByName ("_Q7"));
    addEdge(dir_graph, searchNumByName ("_Q7"), searchNumByName ("_Q6"));
    addEdge(dir_graph, searchNumByName ("_Q6"), searchNumByName ("K4"));
    addEdge(dir_graph, searchNumByName ("_Q6"), searchNumByName ("L1"));
    addEdge(dir_graph, searchNumByName ("K4"), searchNumByName ("E3"));
    addEdge(dir_graph, searchNumByName ("K4"), searchNumByName ("F2"));
    addEdge(dir_graph, searchNumByName ("L1"), searchNumByName ("E3"));
    addEdge(dir_graph, searchNumByName ("L1"), searchNumByName ("F2"));
    addEdge(dir_graph, searchNumByName ("E3"), searchNumByName ("_Q5"));
    addEdge(dir_graph, searchNumByName ("F2"), searchNumByName ("_Q5"));
    addEdge(dir_graph, searchNumByName ("_Q5"), searchNumByName ("_Q4"));
    addEdge(dir_graph, searchNumByName ("_Q4"), searchNumByName ("_Q3"));
    addEdge(dir_graph, searchNumByName ("_Q3"), searchNumByName ("_Q2"));
    addEdge(dir_graph, searchNumByName ("_Q2"), searchNumByName ("_Q1"));
    addEdge(dir_graph, searchNumByName ("_Q1"), searchNumByName ("E4"));
    addEdge(dir_graph, searchNumByName ("_Q1"), searchNumByName ("F1"));
    addEdge(dir_graph, searchNumByName ("S1"), searchNumByName ("_G1"));
    addEdge(dir_graph, searchNumByName ("_G1"), searchNumByName ("_G2"));
    addEdge(dir_graph, searchNumByName ("_G2"), searchNumByName ("_G3"));
    addEdge(dir_graph, searchNumByName ("_G3"), searchNumByName ("_G4"));
    addEdge(dir_graph, searchNumByName ("_G4"), searchNumByName ("_G5"));
    addEdge(dir_graph, searchNumByName ("_G5"), searchNumByName ("S4"));
    addEdge(dir_graph, searchNumByName ("_G5"), searchNumByName ("T1"));
    addEdge(dir_graph, searchNumByName ("S4"), searchNumByName ("_G6"));
    addEdge(dir_graph, searchNumByName ("T1"), searchNumByName ("_G6"));
    addEdge(dir_graph, searchNumByName ("_G6"), searchNumByName ("G7"));
    addEdge(dir_graph, searchNumByName ("_G7"), searchNumByName ("_G8"));
    addEdge(dir_graph, searchNumByName ("_G8"), searchNumByName ("_G9"));
    addEdge(dir_graph, searchNumByName ("_G9"), searchNumByName ("_G10"));
    addEdge(dir_graph, searchNumByName ("_G10"), searchNumByName ("T4"));
    addEdge(dir_graph, searchNumByName ("_G10"), searchNumByName ("U1"));
    addEdge(dir_graph, searchNumByName ("T4"), searchNumByName ("_G11"));
    addEdge(dir_graph, searchNumByName ("U1"), searchNumByName ("_G11"));
    addEdge(dir_graph, searchNumByName ("_G11"), searchNumByName ("_G12"));
    addEdge(dir_graph, searchNumByName ("_G12"), searchNumByName ("_G13"));
    addEdge(dir_graph, searchNumByName ("_G13"), searchNumByName ("_G14"));
    addEdge(dir_graph, searchNumByName ("_G14"), searchNumByName ("U4"));
    addEdge(dir_graph, searchNumByName ("U4"), searchNumByName ("_F15"));
    addEdge(dir_graph, searchNumByName ("_F15"), searchNumByName ("_F16"));
    addEdge(dir_graph, searchNumByName ("_F16"), searchNumByName ("_F17"));
    addEdge(dir_graph, searchNumByName ("_F17"), searchNumByName ("_F18"));
    addEdge(dir_graph, searchNumByName ("_F18"), searchNumByName ("_F19"));
    addEdge(dir_graph, searchNumByName ("_F19"), searchNumByName ("V1"));
    addEdge(dir_graph, searchNumByName ("V1"), searchNumByName ("_G20"));
    addEdge(dir_graph, searchNumByName ("_G20"), searchNumByName ("_G21"));
    addEdge(dir_graph, searchNumByName ("_G21"), searchNumByName ("_G22"));
    addEdge(dir_graph, searchNumByName ("_G22"), searchNumByName ("_G23"));
    addEdge(dir_graph, searchNumByName ("_G23"), searchNumByName ("_G24"));
    addEdge(dir_graph, searchNumByName ("_G24"), searchNumByName ("W4"));
    addEdge(dir_graph, searchNumByName ("_G24"), searchNumByName ("X1"));
    addEdge(dir_graph, searchNumByName ("W4"), searchNumByName ("_G25"));
    addEdge(dir_graph, searchNumByName ("X1"), searchNumByName ("_G25"));
    addEdge(dir_graph, searchNumByName ("_G25"), searchNumByName ("_G26"));
    addEdge(dir_graph, searchNumByName ("_G26"), searchNumByName ("_G27"));
    addEdge(dir_graph, searchNumByName ("_G27"), searchNumByName ("_G28"));
    addEdge(dir_graph, searchNumByName ("_G28"), searchNumByName ("_G29"));
    addEdge(dir_graph, searchNumByName ("_G29"), searchNumByName ("W4"));
    addEdge(dir_graph, searchNumByName ("W4"), searchNumByName ("_G30"));
    addEdge(dir_graph, searchNumByName ("X1"), searchNumByName ("_G30"));
    addEdge(dir_graph, searchNumByName ("_G30"), searchNumByName ("_G31"));
    addEdge(dir_graph, searchNumByName ("_G31"), searchNumByName ("_G32"));
    addEdge(dir_graph, searchNumByName ("_G32"), searchNumByName ("_G33"));
    addEdge(dir_graph, searchNumByName ("_G33"), searchNumByName ("_G34"));
    addEdge(dir_graph, searchNumByName ("_G34"), searchNumByName ("_G35"));
    addEdge(dir_graph, searchNumByName ("_G35"), searchNumByName ("X4"));
    addEdge(dir_graph, searchNumByName ("R3"), searchNumByName ("_F33"));
    addEdge(dir_graph, searchNumByName ("R3"), searchNumByName ("_F33"));
    addEdge(dir_graph, searchNumByName ("_F33"), searchNumByName ("_F32"));
    addEdge(dir_graph, searchNumByName ("_F32"), searchNumByName ("_F31"));
    addEdge(dir_graph, searchNumByName ("_F31"), searchNumByName ("_F30"));
    addEdge(dir_graph, searchNumByName ("_F30"), searchNumByName ("_F29"));
    addEdge(dir_graph, searchNumByName ("_F29"), searchNumByName ("R2"));
    addEdge(dir_graph, searchNumByName ("_F29"), searchNumByName ("Q3"));
    addEdge(dir_graph, searchNumByName ("_R2"), searchNumByName ("_F28"));
    addEdge(dir_graph, searchNumByName ("_Q3"), searchNumByName ("_F28"));
    addEdge(dir_graph, searchNumByName ("_F28"), searchNumByName ("_F27"));
    addEdge(dir_graph, searchNumByName ("_F27"), searchNumByName ("_F26"));
    addEdge(dir_graph, searchNumByName ("_F26"), searchNumByName ("_F25"));
    addEdge(dir_graph, searchNumByName ("_F25"), searchNumByName ("_F24"));
    addEdge(dir_graph, searchNumByName ("_F24"), searchNumByName ("Q2"));
    addEdge(dir_graph, searchNumByName ("_F24"), searchNumByName ("P3"));
    addEdge(dir_graph, searchNumByName ("Q2"), searchNumByName ("_F23"));
    addEdge(dir_graph, searchNumByName ("P3"), searchNumByName ("_F23"));
    addEdge(dir_graph, searchNumByName ("_F23"), searchNumByName ("_F22"));
    addEdge(dir_graph, searchNumByName ("_F22"), searchNumByName ("_F21"));
    addEdge(dir_graph, searchNumByName ("_F21"), searchNumByName ("_F20"));
    addEdge(dir_graph, searchNumByName ("_F20"), searchNumByName ("P2"));
    addEdge(dir_graph, searchNumByName ("P2"), searchNumByName ("_F19"));
    addEdge(dir_graph, searchNumByName ("_F19"), searchNumByName ("_F18"));
    addEdge(dir_graph, searchNumByName ("_F18"), searchNumByName ("_F17"));
    addEdge(dir_graph, searchNumByName ("_F17"), searchNumByName ("_F16"));
    addEdge(dir_graph, searchNumByName ("_F16"), searchNumByName ("_F15"));
    addEdge(dir_graph, searchNumByName ("_F15"), searchNumByName ("O3"));
    addEdge(dir_graph, searchNumByName ("O3"), searchNumByName ("_F14"));
    addEdge(dir_graph, searchNumByName ("_F14"), searchNumByName ("_F13"));
    addEdge(dir_graph, searchNumByName ("_F13"), searchNumByName ("_F12"));
    addEdge(dir_graph, searchNumByName ("_F12"), searchNumByName ("_F11"));
    addEdge(dir_graph, searchNumByName ("_F11"), searchNumByName ("O2"));
    addEdge(dir_graph, searchNumByName ("_F11"), searchNumByName ("N3"));
    addEdge(dir_graph, searchNumByName ("O2"), searchNumByName ("_F10"));
    addEdge(dir_graph, searchNumByName ("N3"), searchNumByName ("_F10"));
    addEdge(dir_graph, searchNumByName ("_F10"), searchNumByName ("_F9"));
    addEdge(dir_graph, searchNumByName ("_F9"), searchNumByName ("_F8"));
    addEdge(dir_graph, searchNumByName ("_F8"), searchNumByName ("_F7"));
    addEdge(dir_graph, searchNumByName ("_F7"), searchNumByName ("_F6"));
    addEdge(dir_graph, searchNumByName ("_F6"), searchNumByName ("N2"));
    addEdge(dir_graph, searchNumByName ("_F6"), searchNumByName ("M3"));
    addEdge(dir_graph, searchNumByName ("N2"), searchNumByName ("_F5"));
    addEdge(dir_graph, searchNumByName ("M4"), searchNumByName ("_F5"));
    addEdge(dir_graph, searchNumByName ("_F5"), searchNumByName ("_F4"));
    addEdge(dir_graph, searchNumByName ("_F4"), searchNumByName ("_F3"));
    addEdge(dir_graph, searchNumByName ("_F3"), searchNumByName ("_F2"));
    addEdge(dir_graph, searchNumByName ("_F2"), searchNumByName ("_F1"));
    addEdge(dir_graph, searchNumByName ("_F1"), searchNumByName ("M2"));
    addEdge(dir_graph, searchNumByName ("M1"), searchNumByName ("_E1"));
    addEdge(dir_graph, searchNumByName ("_E1"), searchNumByName ("_E2"));
    addEdge(dir_graph, searchNumByName ("_E2"), searchNumByName ("_E3"));
    addEdge(dir_graph, searchNumByName ("_E3"), searchNumByName ("_E4"));
    addEdge(dir_graph, searchNumByName ("_E4"), searchNumByName ("_E5"));
    addEdge(dir_graph, searchNumByName ("_E5"), searchNumByName ("M4"));
    addEdge(dir_graph, searchNumByName ("_E5"), searchNumByName ("N1"));
    addEdge(dir_graph, searchNumByName ("M4"), searchNumByName ("_E6"));
    addEdge(dir_graph, searchNumByName ("N1"), searchNumByName ("_E6"));
    addEdge(dir_graph, searchNumByName ("_E6"), searchNumByName ("E7"));
    addEdge(dir_graph, searchNumByName ("_E7"), searchNumByName ("_E8"));
    addEdge(dir_graph, searchNumByName ("_E8"), searchNumByName ("_E9"));
    addEdge(dir_graph, searchNumByName ("_E9"), searchNumByName ("_E10"));
    addEdge(dir_graph, searchNumByName ("_E10"), searchNumByName ("N4"));
    addEdge(dir_graph, searchNumByName ("_E10"), searchNumByName ("O1"));
    addEdge(dir_graph, searchNumByName ("N4"), searchNumByName ("_E11"));
    addEdge(dir_graph, searchNumByName ("O1"), searchNumByName ("_E11"));
    addEdge(dir_graph, searchNumByName ("_E11"), searchNumByName ("_E12"));
    addEdge(dir_graph, searchNumByName ("_E12"), searchNumByName ("_E13"));
    addEdge(dir_graph, searchNumByName ("_E13"), searchNumByName ("_E14"));
    addEdge(dir_graph, searchNumByName ("_E14"), searchNumByName ("O4"));
    addEdge(dir_graph, searchNumByName ("O4"), searchNumByName ("_D15"));
    addEdge(dir_graph, searchNumByName ("_D15"), searchNumByName ("_D16"));
    addEdge(dir_graph, searchNumByName ("_D16"), searchNumByName ("_D17"));
    addEdge(dir_graph, searchNumByName ("_D17"), searchNumByName ("_D18"));
    addEdge(dir_graph, searchNumByName ("_D18"), searchNumByName ("_D19"));
    addEdge(dir_graph, searchNumByName ("_D19"), searchNumByName ("P1"));
    addEdge(dir_graph, searchNumByName ("P1"), searchNumByName ("_E20"));
    addEdge(dir_graph, searchNumByName ("_E20"), searchNumByName ("_E21"));
    addEdge(dir_graph, searchNumByName ("_E21"), searchNumByName ("_E22"));
    addEdge(dir_graph, searchNumByName ("_E22"), searchNumByName ("_E23"));
    addEdge(dir_graph, searchNumByName ("_E23"), searchNumByName ("_E24"));
    addEdge(dir_graph, searchNumByName ("_E24"), searchNumByName ("P4"));
    addEdge(dir_graph, searchNumByName ("_E24"), searchNumByName ("Q1"));
    addEdge(dir_graph, searchNumByName ("P4"), searchNumByName ("_E25"));
    addEdge(dir_graph, searchNumByName ("Q1"), searchNumByName ("_E25"));
    addEdge(dir_graph, searchNumByName ("_E25"), searchNumByName ("_E26"));
    addEdge(dir_graph, searchNumByName ("_E26"), searchNumByName ("_E27"));
    addEdge(dir_graph, searchNumByName ("_E27"), searchNumByName ("_E28"));
    addEdge(dir_graph, searchNumByName ("_E28"), searchNumByName ("_E29"));
    addEdge(dir_graph, searchNumByName ("_E29"), searchNumByName ("Q4"));
    addEdge(dir_graph, searchNumByName ("_E29"), searchNumByName ("R1"));
    addEdge(dir_graph, searchNumByName ("Q4"), searchNumByName ("_E30"));
    addEdge(dir_graph, searchNumByName ("R1"), searchNumByName ("_E30"));
    addEdge(dir_graph, searchNumByName ("_E30"), searchNumByName ("_E31"));
    addEdge(dir_graph, searchNumByName ("_E31"), searchNumByName ("_E32"));
    addEdge(dir_graph, searchNumByName ("_E32"), searchNumByName ("_E33"));
    addEdge(dir_graph, searchNumByName ("_E33"), searchNumByName ("_E34"));
    addEdge(dir_graph, searchNumByName ("_E34"), searchNumByName ("_E35"));
    addEdge(dir_graph, searchNumByName ("_E35"), searchNumByName ("R4"));
    addEdge(dir_graph, searchNumByName ("L3"), searchNumByName ("_D33"));
    addEdge(dir_graph, searchNumByName ("_D33"), searchNumByName ("_D32"));
    addEdge(dir_graph, searchNumByName ("_D32"), searchNumByName ("_D31"));
    addEdge(dir_graph, searchNumByName ("_D31"), searchNumByName ("_D30"));
    addEdge(dir_graph, searchNumByName ("_D30"), searchNumByName ("_D29"));
    addEdge(dir_graph, searchNumByName ("_D29"), searchNumByName ("L2"));
    addEdge(dir_graph, searchNumByName ("_D29"), searchNumByName ("K3"));
    addEdge(dir_graph, searchNumByName ("L2"), searchNumByName ("_D28"));
    addEdge(dir_graph, searchNumByName ("K3"), searchNumByName ("_D28"));
    addEdge(dir_graph, searchNumByName ("_D28"), searchNumByName ("_D27"));
    addEdge(dir_graph, searchNumByName ("_D27"), searchNumByName ("_D26"));
    addEdge(dir_graph, searchNumByName ("_D26"), searchNumByName ("_D25"));
    addEdge(dir_graph, searchNumByName ("_D25"), searchNumByName ("_D24"));
    addEdge(dir_graph, searchNumByName ("_D24"), searchNumByName ("K2"));
    addEdge(dir_graph, searchNumByName ("_D24"), searchNumByName ("J3"));
    addEdge(dir_graph, searchNumByName ("K2"), searchNumByName ("_D23"));
    addEdge(dir_graph, searchNumByName ("J3"), searchNumByName ("_D23"));
    addEdge(dir_graph, searchNumByName ("_D23"), searchNumByName ("_D22"));
    addEdge(dir_graph, searchNumByName ("_D22"), searchNumByName ("_D21"));
    addEdge(dir_graph, searchNumByName ("_D21"), searchNumByName ("_D20"));
    addEdge(dir_graph, searchNumByName ("_D20"), searchNumByName ("J2"));
    addEdge(dir_graph, searchNumByName ("J2"), searchNumByName ("_D19"));
    addEdge(dir_graph, searchNumByName ("_D19"), searchNumByName ("_D18"));
    addEdge(dir_graph, searchNumByName ("_D18"), searchNumByName ("_D17"));
    addEdge(dir_graph, searchNumByName ("_D17"), searchNumByName ("_D16"));
    addEdge(dir_graph, searchNumByName ("_D16"), searchNumByName ("_D15"));
    addEdge(dir_graph, searchNumByName ("_D15"), searchNumByName ("I3"));
    addEdge(dir_graph, searchNumByName ("I3"), searchNumByName ("_D14"));
    addEdge(dir_graph, searchNumByName ("_D14"), searchNumByName ("_D13"));
    addEdge(dir_graph, searchNumByName ("_D13"), searchNumByName ("_D12"));
    addEdge(dir_graph, searchNumByName ("_D12"), searchNumByName ("_D11"));
    addEdge(dir_graph, searchNumByName ("_D11"), searchNumByName ("I2"));
    addEdge(dir_graph, searchNumByName ("_D11"), searchNumByName ("H3"));
    addEdge(dir_graph, searchNumByName ("I2"), searchNumByName ("_D10"));
    addEdge(dir_graph, searchNumByName ("H3"), searchNumByName ("_D10"));
    addEdge(dir_graph, searchNumByName ("_D10"), searchNumByName ("_D9"));
    addEdge(dir_graph, searchNumByName ("_D9"), searchNumByName ("_D8"));
    addEdge(dir_graph, searchNumByName ("_D8"), searchNumByName ("_D7"));
    addEdge(dir_graph, searchNumByName ("_D7"), searchNumByName ("_D6"));
    addEdge(dir_graph, searchNumByName ("_D6"), searchNumByName ("H2"));
    addEdge(dir_graph, searchNumByName ("_D6"), searchNumByName ("G3"));
    addEdge(dir_graph, searchNumByName ("H2"), searchNumByName ("_D5"));
    addEdge(dir_graph, searchNumByName ("G3"), searchNumByName ("_D5"));
    addEdge(dir_graph, searchNumByName ("_D5"), searchNumByName ("_D4"));
    addEdge(dir_graph, searchNumByName ("_D4"), searchNumByName ("_D3"));
    addEdge(dir_graph, searchNumByName ("_D3"), searchNumByName ("_D2"));
    addEdge(dir_graph, searchNumByName ("_D2"), searchNumByName ("_D1"));
    addEdge(dir_graph, searchNumByName ("_D1"), searchNumByName ("M2"));
    addEdge(dir_graph, searchNumByName ("G1"), searchNumByName ("_C1"));
    addEdge(dir_graph, searchNumByName ("_C1"), searchNumByName ("_C2"));
    addEdge(dir_graph, searchNumByName ("_C2"), searchNumByName ("_C3"));
    addEdge(dir_graph, searchNumByName ("_C3"), searchNumByName ("_C4"));
    addEdge(dir_graph, searchNumByName ("_C4"), searchNumByName ("_C5"));
    addEdge(dir_graph, searchNumByName ("_C5"), searchNumByName ("G4"));
    addEdge(dir_graph, searchNumByName ("_C5"), searchNumByName ("H1"));
    addEdge(dir_graph, searchNumByName ("G4"), searchNumByName ("_C6"));
    addEdge(dir_graph, searchNumByName ("H1"), searchNumByName ("_C6"));
    addEdge(dir_graph, searchNumByName ("_C6"), searchNumByName ("C7"));
    addEdge(dir_graph, searchNumByName ("_C7"), searchNumByName ("_C8"));
    addEdge(dir_graph, searchNumByName ("_C8"), searchNumByName ("_C9"));
    addEdge(dir_graph, searchNumByName ("_C9"), searchNumByName ("_C10"));
    addEdge(dir_graph, searchNumByName ("_C10"), searchNumByName ("H4"));
    addEdge(dir_graph, searchNumByName ("_C10"), searchNumByName ("I1"));
    addEdge(dir_graph, searchNumByName ("H4"), searchNumByName ("_C11"));
    addEdge(dir_graph, searchNumByName ("I1"), searchNumByName ("_C11"));
    addEdge(dir_graph, searchNumByName ("_C11"), searchNumByName ("_C12"));
    addEdge(dir_graph, searchNumByName ("_C12"), searchNumByName ("_C13"));
    addEdge(dir_graph, searchNumByName ("_C13"), searchNumByName ("_C14"));
    addEdge(dir_graph, searchNumByName ("_C14"), searchNumByName ("I4"));
    addEdge(dir_graph, searchNumByName ("I4"), searchNumByName ("_B15"));
    addEdge(dir_graph, searchNumByName ("_B15"), searchNumByName ("_B16"));
    addEdge(dir_graph, searchNumByName ("_B16"), searchNumByName ("_B17"));
    addEdge(dir_graph, searchNumByName ("_B17"), searchNumByName ("_B18"));
    addEdge(dir_graph, searchNumByName ("_B18"), searchNumByName ("_B19"));
    addEdge(dir_graph, searchNumByName ("_B19"), searchNumByName ("J1"));
    addEdge(dir_graph, searchNumByName ("J1"), searchNumByName ("_C20"));
    addEdge(dir_graph, searchNumByName ("_C20"), searchNumByName ("_C21"));
    addEdge(dir_graph, searchNumByName ("_C21"), searchNumByName ("_C22"));
    addEdge(dir_graph, searchNumByName ("_C22"), searchNumByName ("_C23"));
    addEdge(dir_graph, searchNumByName ("_C23"), searchNumByName ("_C24"));
    addEdge(dir_graph, searchNumByName ("_C24"), searchNumByName ("J4"));
    addEdge(dir_graph, searchNumByName ("_C24"), searchNumByName ("K1"));
    addEdge(dir_graph, searchNumByName ("J4"), searchNumByName ("_C25"));
    addEdge(dir_graph, searchNumByName ("K1"), searchNumByName ("_C25"));
    addEdge(dir_graph, searchNumByName ("_C25"), searchNumByName ("_C26"));
    addEdge(dir_graph, searchNumByName ("_C26"), searchNumByName ("_C27"));
    addEdge(dir_graph, searchNumByName ("_C27"), searchNumByName ("_C28"));
    addEdge(dir_graph, searchNumByName ("_C28"), searchNumByName ("_C29"));
    addEdge(dir_graph, searchNumByName ("_C29"), searchNumByName ("K4"));
    addEdge(dir_graph, searchNumByName ("_C29"), searchNumByName ("L1"));
    addEdge(dir_graph, searchNumByName ("K4"), searchNumByName ("_C30"));
    addEdge(dir_graph, searchNumByName ("L1"), searchNumByName ("_C30"));
    addEdge(dir_graph, searchNumByName ("_C30"), searchNumByName ("_C31"));
    addEdge(dir_graph, searchNumByName ("_C31"), searchNumByName ("_C32"));
    addEdge(dir_graph, searchNumByName ("_C32"), searchNumByName ("_C33"));
    addEdge(dir_graph, searchNumByName ("_C33"), searchNumByName ("_C34"));
    addEdge(dir_graph, searchNumByName ("_C34"), searchNumByName ("_C35"));
    addEdge(dir_graph, searchNumByName ("_C35"), searchNumByName ("L4"));
    addEdge(dir_graph, searchNumByName ("F3"), searchNumByName ("_B33"));
    addEdge(dir_graph, searchNumByName ("_B33"), searchNumByName ("_B32"));
    addEdge(dir_graph, searchNumByName ("_B32"), searchNumByName ("_B31"));
    addEdge(dir_graph, searchNumByName ("_B31"), searchNumByName ("_B30"));
    addEdge(dir_graph, searchNumByName ("_B30"), searchNumByName ("_B29"));
    addEdge(dir_graph, searchNumByName ("_B29"), searchNumByName ("F2"));
    addEdge(dir_graph, searchNumByName ("_B29"), searchNumByName ("E3"));
    addEdge(dir_graph, searchNumByName ("_F2"), searchNumByName ("_B28"));
    addEdge(dir_graph, searchNumByName ("_E3"), searchNumByName ("_B28"));
    addEdge(dir_graph, searchNumByName ("_B28"), searchNumByName ("_B27"));
    addEdge(dir_graph, searchNumByName ("_B27"), searchNumByName ("_B26"));
    addEdge(dir_graph, searchNumByName ("_B26"), searchNumByName ("_B25"));
    addEdge(dir_graph, searchNumByName ("_B25"), searchNumByName ("_B24"));
    addEdge(dir_graph, searchNumByName ("_B24"), searchNumByName ("E2"));
    addEdge(dir_graph, searchNumByName ("_B24"), searchNumByName ("D3"));
    addEdge(dir_graph, searchNumByName ("E2"), searchNumByName ("_B23"));
    addEdge(dir_graph, searchNumByName ("D3"), searchNumByName ("_B23"));
    addEdge(dir_graph, searchNumByName ("_B23"), searchNumByName ("_B22"));
    addEdge(dir_graph, searchNumByName ("_B22"), searchNumByName ("_B21"));
    addEdge(dir_graph, searchNumByName ("_B21"), searchNumByName ("_B20"));
    addEdge(dir_graph, searchNumByName ("_B20"), searchNumByName ("D2"));
    addEdge(dir_graph, searchNumByName ("D2"), searchNumByName ("_B19"));
    addEdge(dir_graph, searchNumByName ("_B19"), searchNumByName ("_B18"));
    addEdge(dir_graph, searchNumByName ("_B18"), searchNumByName ("_B17"));
    addEdge(dir_graph, searchNumByName ("_B17"), searchNumByName ("_B16"));
    addEdge(dir_graph, searchNumByName ("_B16"), searchNumByName ("_B15"));
    addEdge(dir_graph, searchNumByName ("_B15"), searchNumByName ("C3"));
    addEdge(dir_graph, searchNumByName ("C3"), searchNumByName ("_B14"));
    addEdge(dir_graph, searchNumByName ("_B14"), searchNumByName ("_B13"));
    addEdge(dir_graph, searchNumByName ("_B13"), searchNumByName ("_B12"));
    addEdge(dir_graph, searchNumByName ("_B12"), searchNumByName ("_B11"));
    addEdge(dir_graph, searchNumByName ("_B11"), searchNumByName ("C2"));
    addEdge(dir_graph, searchNumByName ("_B11"), searchNumByName ("B3"));
    addEdge(dir_graph, searchNumByName ("C2"), searchNumByName ("_B10"));
    addEdge(dir_graph, searchNumByName ("B3"), searchNumByName ("_B10"));
    addEdge(dir_graph, searchNumByName ("_B10"), searchNumByName ("_B9"));
    addEdge(dir_graph, searchNumByName ("_B9"), searchNumByName ("_B8"));
    addEdge(dir_graph, searchNumByName ("_B8"), searchNumByName ("_B7"));
    addEdge(dir_graph, searchNumByName ("_B7"), searchNumByName ("_B6"));
    addEdge(dir_graph, searchNumByName ("_B6"), searchNumByName ("B2"));
    addEdge(dir_graph, searchNumByName ("_B6"), searchNumByName ("A3"));
    addEdge(dir_graph, searchNumByName ("B2"), searchNumByName ("_B5"));
    addEdge(dir_graph, searchNumByName ("A3"), searchNumByName ("_B5"));
    addEdge(dir_graph, searchNumByName ("_B5"), searchNumByName ("_B4"));
    addEdge(dir_graph, searchNumByName ("_B4"), searchNumByName ("_B3"));
    addEdge(dir_graph, searchNumByName ("_B3"), searchNumByName ("_B2"));
    addEdge(dir_graph, searchNumByName ("_B2"), searchNumByName ("_B1"));
    addEdge(dir_graph, searchNumByName ("_B1"), searchNumByName ("A2"));  
}

void printGraph(){
    printf("\nDIRECTED GRAPH");
    displayGraph(dir_graph);
    destroyGraph(dir_graph);
}

void moveOneNode(){

}

void search(char* nodeId){
    
int i;
    bool flag = false;
    for (i = 0; i < dir_graph->num_vertices; i++)
    {
        adjlist_node_p adjListPtr = dir_graph->adjListArr[i].head;
        while (adjListPtr)
        {
            if(adjListPtr->nodeId==nodeId){
                printf("%d\n",adjListPtr->vertex);
                num= adjListPtr->vertex;
                flag = true;
                break;
            }
            adjListPtr = adjListPtr->next;
        }
       if (flag == true){
        break;
       }
    }
}

char* searchByNum(){
      
            if(dir_graph->adjListArr[num].head!=NULL){
                adjlist_node_p adjListPtr = dir_graph->adjListArr[num].head;
                if (adjListPtr->visited == false){
                    printf("%s\n",adjListPtr->nodeId);
                name =adjListPtr->nodeId;
                adjListPtr->visited = true;
                }else{
                    mira=false;
                }
                
            }                

}





int main()
{
    fillQueue(); 
    makeEdges();
    struct node* head = NULL;
    int size; 
    char* element;
    int counter = 0;
    pthread_t temp;
    name="Y1";
     head = push(head,name);
    char * namend = "A4";
    while(name!=namend && mira){
        search(name);
    searchByNum();
    head = push(head,name);
    }

    display(head);
     //printGraph();
    return 0;
}
