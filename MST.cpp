/**********************
*
* FILE: MST.cpp
*
*Purpose: can be used to find the minimum spanning tree of a graph as shown below 
*
*Author: G Hithendra Kasyap
*
*Created: Mon 5-April-2021
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

typedef struct Node N;  /* user defined data type N */

class Graph{
    protected:
        int vertices;    /* private variable to store no.of vertices */
        list <struct Node> L[500];  /* array of lists to store adjacency lists */ 
        string s="NO";   /* variable string to store the status of tree update */
    public:
        void create(int n);  /* func to initialise no.of vertices */
        void AddV();        /* func to add a vertex */
        void AddE(int a,int b,int w);  /* func to add an edge into the graph if possible */
        void DelE(int a,int b);   /* func to delete an edge in the graph if possible */     
};

void Graph::create(int n){
    vertices=n;     /* initialising vertices to n */
}

void Graph::AddE(int a, int b, int w){
    if(a>=vertices||b>=vertices){
        cerr<<"invalid indices"<<endl;
        return; /* if a or b one of them is out of range of no.of vertices then writing error message to error stream */
    }
    s="NO";
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

void Graph::DelE(int a, int b){
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
    s="NO";
    return;
}

void Graph::AddV(){
    vertices++;   /* we just increment no.of vertices */
    s="NO";
}

class MST : public Graph{   /* derived class from base class graph */
    private:
         list<struct Node> tree[500];  /* adjacency list to denote tree */
         vector<int> parent;   /* array to store parent of a vertex */
         int n;
    public:
        void initialise(int x);  /* variable func to initialise no.of vrtices the adjacency lists */
        void Add(int a,int b,int w);  /* func to add an edge to tree */
        void Prims(int v);  /* prims algorithmic func to calc total cost of minimum spanning tree */ 
        void Kruskal();    /* kruskal algorithmic func to calc total cost of minimum spanning tree */
        int check_parent(int a);  /* func to check if two vertices have same parent */
        void TreeUptoDate();   /* func to know status of the tree */
        void DisplayTree();   /* func to print edges in the desirable fashion */
};

void MST::initialise(int x){
    n=x;   /* assigning x to variable n */
}

void MST::Add(int a, int b, int w){
    if(a>=n||b>=n){
        cerr<<"invalid indices"<<endl;
        return; /* if a or b one of them is out of range of no.of vertices then writing error message to error stream */
    }
    list <N> ::iterator it1,it2;  /* iterators it1,it2 */
    N temp1,temp2;     /* temp1 and temp2 of struct type */
    temp1.node=b;       
    temp1.weight=w;   /* giving values of node and weight to temp1 */
    N x;
    for(it1=tree[a].end();it1 != tree[a].begin();it1--){
        if(it1==tree[a].end())
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
    if(it1==tree[a].begin()){
        x=*it1;
        if(x.weight==w){
            if(x.node>b)
                it1--;
        }
        if(x.weight>w)
            it1--;       /* if iterator is at begin() then we are checking for that element also */
    }    
    it1++;
    tree[a].insert(it1,temp1);  /* inserting element at correct position,after this all nodes adjacent to a are in ascending order of their weights */
    temp2.node=a;
    temp2.weight=w;   /* we calculate same for node b also as if there is an edge b/w a and b then there is an edge b/w                               b and a and we follow same procedure as we did for node a */  
    for(it2=tree[b].end();it2 != tree[b].begin();it2--){
        if(it2==tree[b].end())
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
    if(it2==tree[b].begin()){
        x=*it2;
        if(x.weight==w){
            if(x.node>a)
                it2--;
        }
        if(x.weight>w)
            it2--;
    }
    it2++;
    tree[b].insert(it2,temp2); /* inserting a at its correct position in the adjacency list of b */
}

typedef pair<int,pair<int,int>> p1;   /* here we define a user define variable p1 of argument as a pair which consists of a integer and another pair of integers */
void MST::DisplayTree(){
    int i;
    priority_queue< p1, vector <p1> , greater<p1> > q;  /* priority queue q */
    N x;
    int a,b,c;
    list <N>::iterator it;
    for(i=0;i<n;i++){
        for(it=tree[i].begin();it!=tree[i].end();it++){
            x=*it;
            if(x.node>i)
                q.push(make_pair(x.weight,make_pair(i,x.node)));
        }    /* here we are pushing the all edges into the priority queue by pushing the vertices with greater index than original index so we avid repitition of edges and now all the elements i queue are in ascending order of their weights */
    }
    while(!q.empty()){
        a=q.top().first;
        b=q.top().second.first;
        c=q.top().second.second;
        cout<<b<<" "<<c<<" "<<a<<endl;  
        q.pop();  /* popping the top element after printing the edge in u v w fashion */
    }
}

typedef pair<int,int> p;
void MST::Prims(int v){
    s="YES";
    for(int i=0;i<500;i++)
        tree[i].clear();
    initialise(vertices);    /* clearing and initialising list and no.of vertices at begining of each func call prims */
    priority_queue< p, vector <p> , greater<p> > q; /* priority queue q */
    vector<int> dist;     /* array to store weigts */
    vector<int> marked;    /* array to tell a vertex is visited or not */
    vector<int> arr;      /* array to eliminate duplicate elements from the tree */
    int i;
    int cost=0;
    int x,y,w,z;
    dist.resize(n);
    parent.resize(n);
    marked.resize(n);  /* initialisng all arrays to n size */ 
    arr.resize(n);
    for(i=0;i<n;i++)
        arr[i]=0;      /* all elemnts to 0s */
    for(i=0;i<n;i++)
        dist[i]=INT_MAX;  /* all elements to infinity */
    for(i=0;i<n;i++)
        parent[i]=-1;  /* all parents to -1 */
    for(i=0;i<n;i++)
        marked[i]=0;   /* all are unvisited */
    dist[v]=0;
    q.push(make_pair(0,v));   /* pushing the vertex by making its weight as zero */
    while(!q.empty()){
        x=q.top().second;
        z=q.top().first;
        if(arr[x]==0){
            cost+=z;
            if(parent[x]!=-1)
                Add(x,parent[x],z);
            arr[x]=1;
        }   /* storing top element pair into x and z and if the element is not duplicate we add weight to cost and we add edge to the tree by giving vertex ,parent of that vertex and z as arguments */
        q.pop();   /* popping top element */
        marked[x]=1;     /* marking it as visited */
        for(auto it=L[x].begin();it!=L[x].end();it++){
            y=(*it).node;
            w=(*it).weight;
            if(marked[y]==0&&dist[y]>w){
                q.push(make_pair(w,y));
                dist[y]=w;
                parent[y]=x;
            }
        } /* for every adj element to x we check if it is unvisited and if dist is greater than w we update the dist and we also update the parent of that vertex and we push that element into queue */
    }
    cout<<cost<<endl;  /* printing the cost of MST */
}

int MST::check_parent(int a){
    while(a!=parent[a])
        a=parent[a];
    return a;     /* we are equalling a to parent of a and returning it */
}

void MST::Kruskal(){
    s="YES";
    for(int i=0;i<500;i++)
        tree[i].clear();
    initialise(vertices); /* clearing and initialising list and no.of vertices at begining of each func call kruskal */
    priority_queue< p1, vector <p1> , greater<p1> > q;  /* priority queue q */ 
    int i;
    int a,b,c;
    list <N>::iterator it;
    N x;
    int l,m;
    int cost=0;
    parent.resize(n);  
    for(i=0;i<n;i++)
        parent[i]=i;  /* resizing and initialisng all elements of parent array to itself */
    for(i=0;i<vertices;i++){
        for(it=L[i].begin();it!=L[i].end();it++){
            x=*it;
            if(x.node>i)
                q.push(make_pair(x.weight,make_pair(i,x.node)));
        }  /* here we are pushing the all edges into the priority queue by pushing the vertices with greater index than original index so we avid repitition of edges and now all the elements i queue are in ascending order of their weights */
    }
    while(!q.empty()){
        a=q.top().first;
        b=q.top().second.first;
        c=q.top().second.second;
        if(check_parent(b)==check_parent(c))
            q.pop();   /* if two vetices parent is same then if we add edge it wil form a cycle we avoid that */
        else{
            l=check_parent(b);
            m=check_parent(c);
            parent[m]=l;
            Add(b,c,a);  /* if both parents are different then updatig parent of one of the elements and adding edge to tree */
            cost+=a;  /* incrementing cost */
            q.pop();  /* popping the element */
        }
    }
    cout<<cost<<endl;  /* printing the cost of MST */
}

void MST::TreeUptoDate(){
    cout<<s<<endl;  /* printing s is sufficient to tell status of tree */
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int vertices;   /* variable to store no.of vertices */ 
    int queries;    /* variable to store no.of queries */
    string st;      /* string to store query */
    MST tree;       /* object tree */
    int x,y,z,w;
    cin>>vertices; 
    tree.create(vertices);  /* initialising no.of vertices in graph class even though we call through object of derived class */  
    cin>>queries;
    for(int i=0;i<queries;i++){
        cin>>st;
        if(st=="ADDE"){
            cin>>x>>y>>w;
            tree.AddE(x,y,w); /* if query is ADDE adding an edge to the graph if possible */
        }
        if(st=="DELE"){
            cin>>x>>y;
            tree.DelE(x,y); /* if query is dele then deleting an edge from graph if exists */
        }
        if(st=="ADDV")
            tree.AddV();   /* if query is ADDV then adding vertex to graph */
        if(st=="Prims"){
            cin>>z;
            tree.Prims(z);  /* if query is prims then taking the following element and calling prims(v) func */
        }
        if(st=="DisplayTree")
            tree.DisplayTree();  /* if query is display tree then calling appropriate func */
        if(st=="Kruskal") 
            tree.Kruskal();      /* if query is kruskal then calling appropriate func for obj tree */
        if(st=="TreeUptodate")
            tree.TreeUptoDate(); /* if query is treeuptodate which wants status of the tree then calling that func */
    }
    return 0;
}

