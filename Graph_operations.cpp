/**********************
*
* FILE: Vectorops.cpp
*
*Purpose: can be used to calculate the operations on a graph as shown below 
*
*Author: G Hithendra Kasyap
*
*Created: Mon 22-March-2021
*
********************/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<iterator>
#include<list>    /* library for list */
#include<queue>   /* library for queue */
#include<utility> /* library for pair */
#include<climits> /* library for INT_MAX use */
using namespace std;

struct Node{   /*struct used to store node value and weight value */
    int node;
    int weight;
};

typedef struct Node N; /* user defined data type N */
template<class T>     /* template of parameter T */
class Graph{
    private:
        int vertices;    /* private variable to store no.of vertices */
        list <struct Node> L[500];  /* array of lists to store adjacency lists */
        int* mark;  /* array mark which we use for BFS */
    public:
        void create(int n);  /* func to initialise no.of vertices */
        void AddV();        /* func to add a vertex */
        void AddE(int a,int b,T w);  /* func to add an edge into the graph if possible */
        void DelE(int a,int b);   /* func to delete an edge in the graph if possible */
        void BFS(int a);      /* func to perform BFS starting from paramter a given as argument */
        void bfs(queue <N> q,int a);  /* func to support BFS */
        void marked();  /* func to initialise mark array */
        void SSP(int a);  /* func to calculate min distances of the vertices starting from a */
};

template<class T>
void Graph<T>::marked(){
    mark=new int[vertices];
    for(int i=0;i<vertices;i++)
        mark[i]=0;       /* allocating space for mark array and initialising them all to zero */
}

template<class T>
void Graph<T>::create(int n){
    vertices=n;     /* initialising vertices to n */
}

template<class T>
void Graph<T>::AddE(int a, int b, T w){
    if(a>=vertices||b>=vertices){
        cerr<<"invalid indices"<<endl;
        return; /* if a or b one of them is out of range of no.of vertices then writing error message to error stream */
    }
    list <N> ::iterator it1,it2;  /* iterators it1,it2 */
    N temp1,temp2;     /* temp1 and temp2 of struct type */
    temp1.node=b;       
    temp1.weight=w;   /* giving values of node and weight to temp1 */
    N x;
    for(it1=L[a].end();it1 != L[a].begin();it1--){
        if(it1==L[a].end())
            continue;
        else{
            x=*it1;
            if(x.weight==w){
                if(x.node<b)
                    break;
            }
            if(x.weight<w)
              break;
        }  /* here we are checking for the minmum index to insert the element according to weight values */
    }
    if(it1==L[a].begin()){
        x=*it1;
        if(x.weight==w){
            if(x.node>b)
                it1--;
        }
        if(x.weight>w)
            it1--;
    }     /* if iterator is at begin() then we are checking for theat element also */
    it1++;
    L[a].insert(it1,temp1);  /* inserting element at correct position,after this all nodes adjacent to a are in ascending order of their weights */
    temp2.node=a;
    temp2.weight=w;   /* we calculate same for node b also as if there is an edge b/w a and b then there is an edge b/w                               b and a and we follow same procedure as we did for node a */
    for(it2=L[b].end();it2 != L[b].begin();it2--){
        if(it2==L[b].end())
            continue;
        else{
            x=*it2;
            if(x.weight==w){
                if(x.node<a)
                    break;
            }
            if(x.weight<w)
                break;
        }
    }
    if(it2==L[b].begin()){
        x=*it2;
        if(x.weight==w){
            if(x.node>a)
                it2--;
        }
        if(x.weight>w)
            it2--;
    }
    it2++;
    L[b].insert(it2,temp2);  /* inserting a at its correct position in the adjacency list of b */
}

template<class T>
void Graph<T>::DelE(int a, int b){
    if(a>=vertices||b>=vertices){
        cerr<<"invalid indices"<<endl;
        return; /* if a or b one of them is out of range of no.of vertices then writing error message to error stream */
    }
    auto it=L[a].begin();
    N x;
    for(it=L[a].begin();it!=L[a].end();it++){
        x=*it;
        if(x.node==b){
            break;
        }
    }    /* searching for the element in the adjacency list of node a */
    if(it==L[a].end()){
        cerr<<"invalid edge"<<endl;
        return;  /* if iterator goes to th end then we print an error message to error stream and we exit from func */
    }
    L[a].erase(it);  /* removing it from the list of a */
    auto it1=L[b].begin();
    for(it1=L[b].begin();it1!=L[b].end();it1++){
        x=*it1;
        if(x.node==a){
            break;
        }
    }   /* similarly we look for node a in the adjacency list of b */
    L[b].erase(it1);  /* we are removing it from the list of b */
    return;
}

template<class T>
void Graph<T>::AddV(){
    vertices++;   /* we just increment no.of vertices */
}

template<class T>
void Graph<T>::BFS(int a){
    marked();    /* func to allocate and initialise array mark */
    queue <N> q; /* defining a queue of type struct as defined above */
    bfs(q,a);  /* func call to perform bfs */
    cout<<endl; /* ending the output given in bfs */
    return;
}

template<class T>
void Graph<T>::bfs(queue <N> q,int a){
    cout<<a<<" ";
    mark[a]=1;   /* printing a and marking it as visited by assigning 1 to its position in mark array */
    auto it=L[a].begin();
    for(it=L[a].begin();it!=L[a].end();it++){
            if(mark[(*it).node]==0){
                q.push((*it));
                mark[(*it).node]=1;
            }
        }  /* here we are pushing the unvisited adjacent elements of node a into the queue */
    if(q.empty()==true)
        return;   /* if queue is empty we exit from func */
    N x=q.front(); 
    q.pop();   /* we pop the front element and we perform bfs again recursively by giving the popped element as input */
    int k=x.node;
    bfs(q,k);
}

template<class T>
void Graph<T>::SSP(int a){
    priority_queue<pair<int,int>> q1;  /* priority queue of type pair */
    int d[vertices];  /* array for distance of vertices */
    for(int i=0;i<vertices;i++){
        if(i==a)
            d[i]=0;
        else
            d[i]=INT_MAX;
    }  /* initialising the given element distance to zero and all others to infinity */
    pair<int,int> P;
    P.first=0;
    P.second=a;  /* pair to store distance as first and node value as second */
    int k;
    q1.push(P);  /* pushing the pair P into priority queue */
    pair<int,int> x,z;
    N y;
    while(!q1.empty()){
        x=q1.top();   /* storing the top element */
        k=x.second;
        d[k]=x.first;  /* storing distance and node values into variables defined */
        q1.pop();    /* popping the top element */
        for(auto it=L[k].begin();it!=L[k].end();it++){
            y=*(it);
            if(y.weight+d[k]<d[y.node]){
                d[y.node]=d[k]+y.weight;
                z.first=d[y.node];
                z.second=y.node;
                q1.push(z);
            }
        }  /* traversing through the adjacency list of popped element we update the distance value of its adjacent elements as we found while traversing by condition shown as above and we push them into queue if their distances are updated */
    }
    for(int i=0;i<vertices;i++)
        cout<<d[i]<<" ";
    cout<<endl;  /* printing the distances */
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int vertex;      /* variable to store no.of vertices */
    int queries;     /* variable to store no.of queries */
    string st;       /* string to store queries */
    cin>>vertex;
    Graph <int> G;   /* defining Graph of parameter int */
    G.create(vertex); /* func to initialise no.of vertices */
    int x,y,w,l,m;  /* variables to store values coming after ADDE,DELE,ADDV */
    cin>>queries;
    for(int i=0;i<queries;i++){  
        cin>>st;
        if(st=="ADDE"){     /* if input string is ADDE prforming AddE func */
            cin>>x>>y>>w;
            G.AddE(x,y,w);
        }
        if(st=="ADDV")      /* if input string is ADDV prforming AddV func */
            G.AddV();
        if(st=="DELE"){     /* if input string is DELE prforming DelE func */
            cin>>l>>m;
            G.DelE(l,m);
        }
    }
    int p,q;  /* variables to store values coming after BFS,SSP */
    for(int i=0;i<2;i++){
        cin>>st;
        if(st=="BFS"){      /* if input string is BFS prforming BFS func */
            cin>>p;
            G.BFS(p);
        }
        else{    /* if input string is SSP prforming SSP func */
            cin>>q;
            G.SSP(q);
        }
    }
    return 0;
}

