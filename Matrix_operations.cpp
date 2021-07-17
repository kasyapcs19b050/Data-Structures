//**********************
*
* FILE: matrixop.cpp
*
*Purpose: can be used to calculate the operations on the matrix of the given conditions
*
*Author: G Hithendra Kasyap
*
*Created: Mon 16-Feb-2021
*
********************/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Matrix{   /* Base class */
    protected:
        int rows;  /* protected variable to represent rows */
        int cols;  /* protected variable to represent coloumns */
        int **arr; /* variable to store matrix */
    public:
        void setrocols(int n,int m);   /* func to intialise no.of rows and coloumns */
        void initialiseMatrix();     /* func to initialise size of the matrix */
        void addelement(int i,int j,int elem);  /* func to add an element to the matrix */
        int binarySearch(int x,int k);   /* func to search an element in logn time complexity */
        int* matrixSearch(int x);     /* func to find an element in the matrix */
};

void Matrix::setrocols(int n,int m){
    rows=n;
    cols=m; /* assigning values to rows and cols */
}

void Matrix::initialiseMatrix(){
    int i;
    arr=new int*[rows];   /* first allocatng space for n rows */
    for(i=0;i<rows;i++){
        arr[i]=new int[cols];  /* allocating space for m elements in each row iteratively */
    }
}

void Matrix::addelement(int i,int j,int elem){
    arr[i][j]=elem;   /* assigning element to the matrix */
}

int Matrix::binarySearch(int x,int k){
    int l=0,h=cols-1,m;   
    int p=-1; /* variable to be returned initialised to -1 */
    if(arr[k][0]<=x){  
        while(l<=h){
            m=l+(h-l)/2;
            if(arr[k][m]>x)
                h=m-1;
            else{
                l=m+1;
                p=m;
            }
        }
    }     /* if atleast one element is less thaan or equal to x then we perfrm binary search as shown to find the                            desired index */
    else{
        p=-1;
    }       /* else we return -1 */
    return p;
}

int* Matrix::matrixSearch(int x){
    int i;
    int l,h,m;     /* variables to indicate the left right and middle of an array */
    static int b[2]; /* satic variable array is used to maintain the same values for array values throughout the code */
    b[0]=-1;
    b[1]=-1;  /* initialising the array values */
    int p=0;  /* flag variable */
    for(i=0;i<rows;i++){
        l=0;
        h=cols-1;    
        while(l<=h){  
            m=l+(h-l)/2;
            if(arr[i][m]==x){
                b[0]=i;
                b[1]=m;
                p=1;
                h=m-1;
            }
            else if(arr[i][m]>x)
                h=m-1;
            else
                l=m+1;
        }    /* for each row we perform binary search and find if element present in that row if present we compare it                      to the flag bit assigned and exiting the loop first time wee see the element */
        if(p==1)
            break;
    }
    return b;  /* returning the base address of the array */
}

class MatrixMedian: public Matrix{  /* Derived class from class Matrix */
    public:
        int upperbound(int x,int k);  /* func to find the count of no.of elements less than given element */
        int findMedian();  /* func to find median of the given matrix */
};

int MatrixMedian::upperbound(int x,int k){
    int p=binarySearch(x,k); /* calling binary search func to find greatest index such that it is <= x so no.of elements                                  less than x are p+1 */ 
    if(p+1<=cols-1)
        return p+1;   
    else
        return -1;  /* if p+1=cols then all the elements in array are less than x so we find no index such that it is                               greater than x so returning -1 */
}

int MatrixMedian::findMedian(){
    int l,h;      /* variables to denote the indices of the left and right elements of the array */
    int median;   /* variabe to store median */
    int real_count,count;
    int i;
    l=arr[0][0];
    h=arr[0][cols-1]; /* initialising the l,h variables */ 
    i=1;
    while(i<=rows-1){
        if(arr[i][0]<l)
            l=arr[i][0];
        if(arr[i][cols-1]>h)
            h=arr[i][cols-1];
        i++;
    }   /* finding minimum and maximum elemnts of the matrix */
    real_count=(rows*cols+1)/2;  /* median index */
    while(l<h){
        count=0;
        median=l+(h-l)/2;
        i=0;
        while(i<=rows-1){
            if(upperbound(median,i)==-1)
                count+=cols;
            else
                count+=upperbound(median,i);
            i++;
        }
        if(count<real_count)
            l=median+1;
        else
            h=median;
    }  /* loop to calculate median using binary search type of method we first initailise the median variable and see                  how many elements less than that in the matrix if the number is less than half then median should be                     higher so we shift variable l and if number is greater than median we shift r and we return l or h finally */
    return h;
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n,m;  /* variables to store no.of rows and cols */
    int el;       /* variable to store the size of matrix */
    int i,j;      /* loop variables */
    string s;     /* string to store the given query */
    int queries;  /* variable to store no.of queries */
    MatrixMedian M;  /* object defined as M */
    int x,z,k;    /* variables to store values of numbers come after query */
    int *p;       /* array to store the return of matrix search func */
    cin>>n>>m;
    M.setrocols(n,m);   /* initialisng the M */
    M.initialiseMatrix();
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            cin>>el;
            M.addelement(i,j,el);
        }
    }   /* taking elements into the matrix */
    cin>>queries;
    for(i=0;i<queries;i++){
        cin>>s;     /* taking string query */
        if(s=="MS"){
            cin>>x;
            p=M.matrixSearch(x);   /* assigning the base address returning to the variable array base address */
            cout<<*p<<" "<<*(p+1)<<endl;  /* printing the elements in array */
            }
        if(s=="Median"){
            cout<<M.findMedian()<<endl; /* printing median */
        }
        if(s=="BS"){
            cin>>z>>k;  /* if query is BS then taking the numbers after it and printing the output */
            cout<<M.binarySearch(z,k)<<endl;
        }
    }
    return 0;
}
