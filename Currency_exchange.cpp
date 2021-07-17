/**********************
*
* FILE: Currency.cpp
*
*Purpose: can be used to calculate distance the currency changes between countries
*
*Author: G Hithendra Kasyap
*
*Created: Mon 19-April-2021
*
********************/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
#include <iomanip>
#include <utility>
using namespace std;

class Colours{
    private:
        int colours;         /* variable to store number of colours */
        int currencies;      /* variable to store no.of currencies or countries */
        int** c;             /* matrix to store edges b/w colors */
        vector<int> v;       /* matrix to store colors of vertices of the graph */
        vector<pair<pair<int,int>,float>> arr;    /* array to store attributes of an edge */
        int edges=0;         /* variable to count no.of edges in the graph */
    public:
        void create(int n);        /* func to create matrix c and colours variable */
        void initialise(int p);    /* func to initialise currency and w matrix */
        void AddE(int a,int b);    /* func to add an edge in matrix c */ 
        void add(int a,int b,float z);  /* func to add an edge in graph matrix */
        void know_colours(int x);  /* func to add element to array v */
        void money(int s,int t,float X);  /* func which calculates total final money */
        int isCycle(float* p);   /* func to assist money function */
}; 

void Colours::create(int n){
    colours=n;           /* assigning value n to colours variable */
    c=new int*[n];       
    for(int i=0;i<n;i++)
        c[i]=new int[n];  /* allocating space to matrix c */
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            c[i][j]=0;
    }          /* initialising all elements of matrix c to 0 */
}

void Colours::initialise(int p){
    currencies=p;           /* assigning value p to currencies variable */
}

void Colours::know_colours(int x){
    v.push_back(x);           /* adding element to array v */
}
void Colours::AddE(int a,int b){
    c[a][b]=1;
    c[b][a]=1;       /* making both c[a][b] and c[b][a] as 1 as both are present */
}

void Colours::add(int a,int b,float z){
    float k=-1*log(z);        /* initialisng value k */
    int x,y;       
    x=v[a]; 
    y=v[b];              /* finding colours of a and b and storing them in x and y respectively */
    if(a==b||c[x][y]!=0||c[x]==c[y]){
        arr.resize(edges+1);     /* making size of array arr as edges+1 each time */
        arr[edges].first.first=a;
        arr[edges].first.second=b;
        arr[edges].second=k;   /* initialising the last value of array arr */
        edges++;          /* incrementing the no.of edges */
        
    } 
}

int Colours::isCycle(float* p){
    int i=0;
    int x,y;
    float z;
    while(i<edges){
        x=arr[i].first.first;
        y=arr[i].first.second;
        z=arr[i].second;
        if(p[x]!=INT_MAX && p[x]+z<p[y])
            return 1;
        i++; /* Our update for loop in the below func make sures to minimise all the -logn values if there is further minimisation possible it means we have to go through cycle in the graph obviously,so we are returning INF as -logn can further be minimised and total money product n can be maximised without any limit */
    }
    return 0;
}

void Colours::money(int s, int t, float X){
    float dist[currencies];        /* array to store distances */
    int i,j;
    int x,y;
    float z;
    for(i=0;i<currencies;i++)
        dist[i]=INT_MAX;
    dist[s]=0;       /* initialising all the array dist values to infty and source value to zero */
    i=1;
    int cycle;
    while(i<=currencies-1){
        j=0;
        while(j<edges){
            x=arr[j].first.first;
            y=arr[j].first.second;
            z=arr[j].second;
            if(dist[x]!=INT_MAX && dist[x]+z<dist[y])
                dist[y]=dist[x]+z;
            j++;
        }
        i++;
    }   /* here we are doing simple shortest path algorithm like Dijkstra but we are doing that -logn values as we want to maximise products of n, that means we have to maximise sum of logn which means to minimise -logn value,which we can find out using Dijkstra algorithm */ 
    if(dist[t]==INT_MAX){
        cout<<"-1"<<endl;
        return;         /* If distance is still infty after all updating we return -1 */
    }
    cycle=isCycle(dist);
    if(cycle==1){
        cout<<"INF"<<endl;
        return;     /* if cycle is present we print INF */
    }
    cout<<fixed<<setprecision(3)<<exp(-1*dist[t])*X<<endl;      /* if the above two doesnot happen then we print the final rate as shown upto three decimal points*/
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int cols;            /* variable to store no.of coloumns */
    int col_eds;         /* variable to store coloumn_edges */
    int crncy;           /* variable to shown no.of countries */
    int queries;         /* variable to store no.of queries */
    int i,j;
    int x,y,z;          
    float l;
    int k,m;             /* all the above variables are used to store intermediate values */
    float a;
    Colours C;          /* object C */
    cin>>cols;
    cin>>col_eds;
    C.create(cols);    /* creating matrix c */
    i=0;
    while(i<col_eds){
        cin>>x>>y;
        C.AddE(x,y);
        i++;
    }        /* adding edge to matrix c one by one */
    cin>>crncy;
    C.initialise(crncy);
    i=0;
    while(i<crncy){
        cin>>z;
        C.know_colours(z);   /* taking elements into array v one by one */
        i++;
    }
    i=0;
    while(i<crncy){
        j=0;
        while(j<crncy){
            cin>>l;
            C.add(i,j,l);
            j++;
        }           /* adding edge to graph one by one */
        i++;
    }
    cin>>queries;
    i=0;
    while(i<queries){
        cin>>k>>m>>a;
        C.money(k,m,a);   /* finding maximum transfer rate */
        i++;
    }
    return 0;
}

