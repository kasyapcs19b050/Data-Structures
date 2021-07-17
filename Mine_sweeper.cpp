/**********************
*
* FILE: Currency.cpp
*
*Purpose: can be used to play the game find_mines
*
*Author: G Hithendra Kasyap
*
*Created: Mon 26-April-2021
*
********************/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int take_input=1;        /* variable to know the status of the game */
class Mine{
    private:
        int n;           /* variable to store size of the array */
        int m=0;         /* variable to finally store no.of mines in matrix */
        int** arr;       /* matrix to store all the mines and normal places */
        int total_count=0;   /* variable to store score in the game */
    public:
        void create(int x);              /* func to initiliase value n and allocate and initialise matrix arr */
        void AddMine(int x);             /* func to add mine in array */
        void CheckMine(int a,int b);     /* func to check if position has mine or not */
        int Reveal(int a,int b);        /* func to clacuate no.of reveals if mine is not discovered at given position */
        int Neighbour_mines(int a,int b);  /* func to calculate no.of mines in the neighbour of position a,b */
};

void Mine::create(int x){
    n=x;                  /* initialsing variable n */
    arr = new int*[n];       
    for(int i=0;i<n;i++)
        arr[i]=new int[n];    /* allocating space to matrix arr */
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            arr[i][j]=-3;        /* making all the values in array to -3 */
    }
}

void Mine::AddMine(int x){
    int i=x/n;        
    int j=x%n;
    arr[i][j]=-1;  /* storing the given mine value at i,j position which are calculated as shown as -1 */
    m++;          /* incrementing no.of mines */
}

void Mine::CheckMine(int a,int b){
    if(arr[a][b]==-1){
        take_input=0;
        cout<<"Lost"<<endl;
        return;       /* if the position is a mine then we lost the game so we print it and we do not take further inputs so making bit to 0 */
    }
    total_count+=Reveal(a,b); /* total score is previous score + present scre which can be calculated by reveal func */
    if(total_count==n*n-m){
        take_input=0;
        cout<<"Won"<<endl;
        return;  /* if all the places are revealed except mines then we print won as we won the game */
    }
    cout<<total_count<<endl;  /* printing the total score if above both cases are not satisfied */
}

int Mine::Neighbour_mines(int a,int b){
    int i,j;
    int count=0;     /* variable to store no.of mines in the neighbour of  a,b */
    for(i=a-1;i<=a+1;i++){
        for(j=b-1;j<=b+1;j++){
            if(i>=0&&i<=n-1&&j>=0&&j<=n-1){
                if(arr[i][j]==-1)
                    count++;
            }
        } /* for valid i and j we check with matrix if mine is present or not and increase the count if mine is found */
    }
    return count;  /* returning count */
}

int Mine::Reveal(int a, int b){
    int i,j;
    int reveal=1;        /* making reveal as 1 initially */
    if(arr[a][b]>=0)
        return 0;       /* if the position is already revealed we return 0 */
    arr[a][b]=Neighbour_mines(a,b);         /* modify the matrix value at given position */
    if(arr[a][b]>0){
        return reveal;  /* if no.of mines surrounding position a,b are greater than 0 we return reveal */
    }
    for(i=a-1;i<=a+1;i++){
        for(j=b-1;j<=b+1;j++){
            if(i>=0&&i<=n-1&&j>=0&&j<=n-1){
                if(arr[i][j]<0){
                    reveal+=Reveal(i,j);
                }
            }
        }   /* if no.of mines surrounding position a,b are zero then we have to recursively find the no.of revealations for the positions which are not revealed initially */
    }
    return reveal;   /* we return final reveal value */
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int x,y;          /* variable to store n and m values in x and y */
    int k;            /* variable to store the mine position */
    int a,b;          /* variable to store the position */
    int i;
    Mine M;          /* object M of class Mine */
    cin>>x>>y;
    M.create(x);     /* calling create func */
    for(i=0;i<y;i++){
        cin>>k;
        M.AddMine(k);  /* taking each position of mine one by one into matrix in class through AddMine func */
    }
    while(cin>>a>>b){
        M.CheckMine(a,b);
        if(take_input==0)
            break;             /* While not endoffile we take the inputs until game is Won or Lost */
    }
    return 0;
}

