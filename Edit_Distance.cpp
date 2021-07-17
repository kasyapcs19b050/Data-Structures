/**********************
*
* FILE: EditDistance.cpp
*
*Purpose: can be used to calculate distance between two strings (edit distance)
*
*Author: G Hithendra Kasyap
*
*Created: Mon 12-April-2021
*
********************/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class EED{               /* class to compute distance between two strings dynamic programming */
    private:
        string s1,s2;    /* variables used to store strings */
        int** arr;       /* variable to store the distances in array */
        int n1=0,n2=0;   /* variables to store string sizes,initialising them to zero */
        string s="NO";    /* variable to store status of assign func */
        int d;           /* variable to store distance between strings given */
    public:
        void assign(string a,string b);      /* func to assign values to strings */
        void compdist();                     /* func to compute distance between strings */
        int dist();                          /* func to return distance */
        void table();                        /* func to print array */
};

void EED::assign(string a, string b){     
    s1=a;               
    s2=b;          /* initialsing s1 and s2 to a and b */
    n1=s1.size();  
    n2=s2.size();  /* assigning lengths to n1 and n2 */
    s="YES";      /* making string s bit to YES */
    arr=new int*[n1+1];      
    for(int i=0;i<=n1;i++)
        arr[i]=new int[n2+1];   /* allocating space to array */
}

void EED::compdist(){
    if(n1==0||n2==0)              
        throw "strings not found!";     /* if n1 is zero or n2 is zero then throwing an exception */
    s=="NO";                           /* making update bit to 1 */
    int i,j;
    int insertions,deletions,substitutions;   /* variables to store if insertion or deletion or replacement is made */ 
    for(j=0;j<=n2;j++)
        arr[0][j]=j;            /* initialising all elements of first row to its coloumn value */
    for(i=1;i<=n1;i++){
        arr[i][0]=i;           /* initialising all elements of first column to its row value */
        for(j=1;j<=n2;j++){
            insertions=arr[i][j-1]+1;    /* if an element in first string is not present then we have to insert so we                                              write extra 1 and distance becomes arr[i][j-1] */ 
            deletions=arr[i-1][j]+1;     /* if an element in second string is not present then we have to delete so we                                              write extra 1 and distance becomes arr[i-1][j] */
            if(s1[i-1]==s2[j-1])
                substitutions=arr[i-1][j-1];   
            else
                substitutions=arr[i-1][j-1]+1;  /* if both elements are present then we check if they are equal or not                                                      if equal then distance is arr[i-1][j-1] else it is arr[i-1][j-1]+1 as                                                       we have to make them equal by replacement */
            if(insertions<=deletions&&insertions<=substitutions)
                arr[i][j]=insertions;              
            else if(deletions<=insertions&&deletions<=substitutions)
                arr[i][j]=deletions;
            else
                arr[i][j]=substitutions;     /* finding minimum of the three elements and assigning it to arr */
        }
    }
    d=arr[n1][n2];           /* assigning arr[n1][n2] to d */
}

int EED::dist(){
    if(n1==0||n2==0)
        throw "strings not found!";  /* if n1 is zero or n2 is zero then throwing an exception */
    if(s=="YES")
        compdist();           /* if compdist is not called before we call it so we can get distance b/w strings */ 
    return d;                  
}

void EED::table(){
    if(n1==0||n2==0)
        throw "strings not found!";  /* if n1 is zero or n2 is zero then throwing an exception */
    if(s=="YES")
        compdist();               /* if compdist is not called before we call it so we can get distance b/w strings */
    for(int i=1;i<=n1;i++){
        for(int j=1;j<=n2;j++)
            cout<<arr[i][j]<<" ";
        cout<<endl;
    }                       /* printing element of the matrix */
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    string a,b;       /* variables to take input strings coming after exception */
    int queries;      /* variable to store no.of queries */
    string st;        /* variable to store query */
    int distance;     /* variable to store distance */
    EED E;            /* object E of class EED */
    cin>>queries;           
    for(int i=0;i<queries;i++){
        cin>>st;
        if(st=="assign"){
            cin>>a>>b;
            E.assign(a,b);       /* if query is assign then we do assign(a,b) func */
        }
        if(st=="table"){
            try{E.table();}
            catch(const char* s1){
                 cout<<s1<<endl;        /* if exception is thrown by func we write error message as shown */
            }                
        }
        if(st=="compdist"){
            try{E.compdist();}
            catch(const char* s1){
                cout<<s1<<endl;    /* if exception is thrown by func we write error message as shown */
            }
        }
        if(st=="dist"){
            try{
                distance=E.dist();
                cout<<distance<<endl; /* printing the distance returned by dist function */
            }
            catch(const char* s1){
                cout<<s1<<endl;     /* if exception is thrown by func we write error message as shown */
            }
        }
    }
    return 0;
}
