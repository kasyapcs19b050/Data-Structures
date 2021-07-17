/**********************
*
* FILE: StackGraph.cpp
*
*Purpose: can be used to calculate the operations of stacks and graphs classes of the given conditions
*
*Author: G Hithendra Kasyap
*
*Created: Mon 22-Feb-2021
*
********************/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
using namespace std;

typedef struct CellType* Position;  /* pointer of struct type to point nodes in the stack */

struct CellType {
  int value;
  Position next;
};  /* struct which is used to store two values at a node value and pointer to next node */

class Stack{
    private:
        Position listHead;    /* pointer to the top of the stack */
    public:
        void MakeNull();    /* to create an empty stack */
        void Push(int x);   /* to insert one element to the stack */
        int Pop();          /* to extract the top element of the stack */ 
        int Top();          /* to know the top element of the stack */
        int isEmpty();      /* to know whether stack is empty or not */
};

void Stack::MakeNull(){
    listHead=NULL;   /* initialising head pointer to null */
}

void Stack::Push(int x){
    struct CellType* temp = new CellType(); /* creating and allocating space to a new node */
    temp->value=x;         /* value space is assigned by x */
    temp->next=listHead;   /* next part is assigned by the the head of the previous linked list */
    listHead=temp;       /* new linked list is such that first node's element is new value which is charcateristic of stack */
}

int Stack::Pop(){
    if(listHead==NULL)
        return -1;        /* if head points to null then stack is empty so returns -1 */
    int temp=listHead->value;
    listHead=listHead->next;       /* deleting the top value after storing it in a new variable temp */
    return temp;
}

int Stack::Top(){
    if(listHead==NULL)
        return -1;      /* if head points to null then stack is empty so returns -1 */
    return listHead->value;        /* returning top element */
}

int Stack::isEmpty(){
    if(listHead==NULL)
        return 1;            /* if head points to null then stack is empty so returns 1 */
    return 0;  /* else returns 0 */
}

class Graph{
    private:
        int** arr;        
        int nodes;        /* private variable adjacency matrix and no.of nodes variables */
    public:
        Graph(int n){      /* Constructor */
            nodes=n;
            arr=new int*[n];
            int i,j;
            for(i=0;i<n;i++)
                arr[i]=new int[n];
            for(i=0;i<n;i++){
                for(j=0;j<n;j++)
                    arr[i][j]=0;
            }
        }    /* In this constructor we are initialising thenodes variable and allocating space for array by using new and initialising all values in adjacency matrix to 0 */
        void operator += (pair<int,int> Pair){  /* pair in-built variable which store a pair of values */
            int i,j;
            i=Pair.first;
            j=Pair.second;
            arr[i][j]=1;
            arr[j][i]=1;         /* operating overloading func to add an edge between two nodes of the graph by denoting the both ij and ji values by 1 ,we use operator += to overload */
        }
        void operator -= (pair<int,int> Pair){
            arr[Pair.first][Pair.second]=0;
            arr[Pair.second][Pair.first]=0;
        }                          /* operating overloading func to delete an edge between two nodes of the graph by denoting the both ij and ji values by 0 ,we use operator -= to overload */
        int detectCycle();  
        int dfs_cycle(int* mark,int i,int p);   /* both above two funcs are used to detect a cycle in the graph */ 
        int components();
        void dfs_comp(Stack s,int* mark,int i); /* both above two funcs are used to calculate no.of connected component in the graph */ 
        int reach(int u,int v);
        void dfs_reach(Stack s,int* mark,int u,int v); /* these last two funcs are used to know if there is a path between u and v in the graph */
};

int Graph::detectCycle(){
    int mark[nodes];     /* array to know if the nodes are visited or not */
    int i;
    for(i=0;i<nodes;i++)
        mark[i]=0;       /* initialising all values of array to zero */
    for(i=0;i<nodes;i++){
        if(mark[i]==0&&dfs_cycle(mark,i,-1)==1){
            return 1;   /* if the declared function becomes true at given condition then the func is true */
        }
    }
    return 0; /* else returning 0 if there is no cycle as calculated from above */
}

int Graph::dfs_cycle(int* mark, int i,int p){
    int j;
    mark[i]=1;        /* making the node visited */
    for(j=0;j<nodes;j++){
        if(arr[i][j]!=0){
            if(mark[j]==0){
                if(dfs_cycle(mark,j,i)==1)
                    return 1;
            }
            else if(j!=p)
                return 1;
        }
     }     /* we first seek the adjacent element to the value i from the adjacency matrix and if any one of them is unvisited then calling the func again if it is true then total func is true,here there is one thing to note parent of i is also visited when we look at the adjacent elements so we have to exclude that in order to find if there is a cycle or not */
    return 0;
}

int Graph::components(){
    int mark[nodes];           /* array to know if the nodes are visited or not */
    int i;
    Stack s;      /* defining a stack to store the desired values */
    s.MakeNull();
    int count=0;
    for(i=0;i<nodes;i++)
        mark[i]=0;          /* initialising all values of array to zero */
    for(i=0;i<nodes;i++){
        if(mark[i]==0){
            dfs_comp(s,mark,i);
            count+=1;  /* incrementing the count value which is declared to keep trace of the no.of connected components which we calculate as for one whole component we compute the bfs_comp function */
        }
    }
    return count;  /* returning the output */
}

void Graph::dfs_comp(Stack s,int* mark,int i){
    int x;
    int j;
    mark[i]=1;        /* making the node visited */
    for(j=0;j<nodes;j++){
        if(mark[j]==0&&arr[i][j]!=0){
            s.Push(j);
            dfs_comp(s,mark,j);
        }
    }    /* here we are pushing all the adjacent nodes of the given node into the stack other than parent node so that we can pop out one at each time */ 
    while(!s.isEmpty()){
        x=s.Pop();
        dfs_comp(s,mark,x);
    } /* popping out  top element, pushing all adjacent elements by calling same func again until stack is not empty */
}
int count_reach=0;
int Graph::reach(int u, int v){
    Stack s;           /* defining a stack to store the desired values */
    s.MakeNull();
    int mark[nodes];
    int i;
    for(i=0;i<nodes;i++)
        mark[i]=0;
    dfs_reach(s,mark,u,v);  /* func to know if there is a path or not by calling another func single time because if there exists a path then u,v must be both in a single connected component */
    return count_reach;
}

void Graph::dfs_reach(Stack s,int* mark,int i,int v){
    int j;
    int x;
    mark[i]=1;
    for(j=0;j<nodes;j++){
        if(arr[i][j]!=0&&mark[j]==0){
            s.Push(j);
            dfs_reach(s,mark,j,v);
        }
    }  /* here we are pushing all the adjacent nodes of the given node into the stack other than parent node so that we can pop out one at each time */ 
    while(!s.isEmpty()){
        x=s.Pop();
        if(x==v)
            count_reach=1;
        dfs_reach(s,mark,x,v);
    } /* popping out  top element, pushing all adjacent elements by calling same func again until stack is not empty and if we encounter v in the process we exit from func and return 1 indicating that there is a path from u to v */
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    Stack S;              /* defining stack object */
    int queries1;         /* defining no,of queries for stack operations */
    string stack_query;   /* string to note stack queries */
    int x;
    int queries2;         /* defining no,of queries for graph operations */
    int num_nodes;        /* variable to store no.of nodes */
    string graph_query;   /* string to note graph queries */
    int y,z;
    int i;
    pair<int,int> Pair;  /* variable to store a pair of values */
    cin>>queries1;
    S.MakeNull();
    for(i=0;i<queries1;i++){
        cin>>stack_query;      /* taking one query at a time */
        if(stack_query=="push"){
            cin>>x;
            S.Push(x);
        }
        else if(stack_query=="pop")
            cout<<S.Pop()<<endl;
        else if(stack_query=="top")
            cout<<S.Top()<<endl;
        else
            cout<<S.isEmpty()<<endl;
    }          /* operating the queries as requested by calling the funcs of stack object */
    cin>>num_nodes;
    cin>>queries2;
    Graph G(num_nodes);         /* defining Graph object with a value to initialise the obj in constructor */
    for(i=0;i<queries2;i++){
        cin>>graph_query;
        if(graph_query=="add"){
            cin>>y>>z;
            Pair.first=y;
            Pair.second=z;
            G+=(Pair);    /* operator overloading func call as we call it with the operator in between the obj and arguments */ 
        }
        else if(graph_query=="cycle")
            cout<<G.detectCycle()<<endl;
        else if(graph_query=="del"){
            cin>>y>>z;
            Pair.first=y;
            Pair.second=z;
            G-=(Pair);  /* operator overloading func call as we call it with the operator in between the obj and arguments */
        }
        else if(graph_query=="components")
            cout<<G.components()<<endl;
        else{
            cin>>y>>z;
            cout<<G.reach(y,z)<<endl;
        }
    }         /* operating the queries as requested by calling the funcs of graph object */
    return 0;
}

