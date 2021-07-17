/**********************
*
* FILE: arrayoperations.cpp
*
*Purpose: can be used to calculate maximu subarray of an array using given conditions 
*
*Author: G Hithendra Kasyap
*
*Created: Mon 08-March-2021
*
********************/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <limits.h>
#include <algorithm>
using namespace std;

class BloomBrain{       /* class bloombrain which stores funcs as defined below */
    private:
        int* arr;       /* array to store array defined after update */ 
        int size;       /* variable to define size of array */
        int* isempty;   /* array to know the emptiness of each position array */
    public:
        void create(int rooms);  /* func to allocate size of array defined and size */
        void insert(int x);      /* func to insert an element into array */
        long long int update();  /* func to calculate no.of inversions in array */
        int occupied();          /* func to calculate no.of occupied elements in the array */
        void leave(int i);       /* func to delete an element from array by putting it as 1 */
        void join(int s);        /* func to add an element to array */
        long long int play();    /* func to find sum of maximum sub array */
        long long int Sum(int l, int h);  /* func to assist play func */
        long long int MiddleSum(int l, int h, int m); /* func to assist play func */
        long long int inversion(int* b,int* c,int l,int h);   /*func to support update func */ 
        long long int result(int* b,int* c,int l,int m,int h); /*func to support update func */
        void nonempty();  /* func to initialise all values in the isempty array */
};

int BloomBrain::occupied(){   
    int j;
    int count=0;   /* initially count is zero */
    for(j=0;j<size;j++){
        if(isempty[j]==1)
            count++;
    }    /* if we found a occupied position we increment count by 1 */
    return count;  /*returning count */
}

void BloomBrain::leave(int i){
    arr[i]=0;
    isempty[i]=0;    /* both values in array and isempty array is zero as it is unoccupied now */
}

void BloomBrain::join(int s){
    int j;            
    for(j=size-1;j>=0;j--){
        if(arr[j]==0&&isempty[j]==0){
            arr[j]=s;
            isempty[j]=1;
            return;
        }
    }      /* In this func we update the last unoccupied value in the array to the number given and we also update the isempty array value at that position to 1 we do this by searching for unoccupied position from the last using for loop we return from loop at the instant we found it */
    return;
}

void BloomBrain::nonempty(){
    int i;
    isempty=new int[size];  /* here in this func we allocate size of the rooms to isempty array using new */
    for(i=0;i<size;i++)
        isempty[i]=1;      /* we initialise all the values to 1 */
} 
int x=0;   /* variable for first update func to use all values in the array */
long long int BloomBrain::update(){
    int* b;    /* array to store all the occupied positions in the array */
    int p;   /* to know no.of unoccupied positions */
    int i,j=0;  /* loop variables */
    if(x==0){
        int d[size];
        b=new int[size];
        for(i=0;i<size;i++)
            b[i]=arr[i];
        x=1;
        return inversion(b,d,0,size-1);
    }  /* for first time we take all values of array into the array b we define so we took the x value 0 and we assign the value of x to 1 after loop is completed to ensure that this works only for the first time.We allocate size to array b and we call the func inversion in which one of te arguments is d which is nothing but a temporary array to store the array after merging its sub arrays */
    p=0;
    for(i=0;i<size;i++){
        if(isempty[i]==0&&arr[i]==0)
            continue;
        else
            p++;
    }     /* calculating no.of unoccupied positions in the array */
    b=new int[p];  /* allocating size to b */
    i=0;
    while(i<=p-1&&j<=size-1){
        if(arr[j]!=0){
            b[i]=arr[j];
            i++;
            j++;
        }
        else if(arr[j]==0&&isempty[j]==1){
            b[i]=arr[j];
            i++;
            j++;
        }
        else
            j++;
    }  /* here in this while loop we are copying elements in the occupied position of array to new defined array b */
    int c[p]; /* here c array has same functonality as d */
    return inversion(b,c,0,p-1);  /* returning the value given by the inversion function */
}

long long int BloomBrain::inversion(int *b, int *c, int l, int h){
    int m;
    long long int count=0;   /* the variable to count no.of inversions initialised to zero */
    if(l<h){
        m=l+(h-l)/2;  /* middle elements index */
        count+=inversion(b,c,l,m)+inversion(b,c,m+1,h)+result(b,c,l,m,h);
    }  /* here in this func we are dividing the array into two sub arrays of equal size and we recursively call the func again and we also add inversions occur when we merge these two arrays together we find that as described in result func */
    return count;
}

long long int BloomBrain::result(int *b, int *c, int l, int m, int h){
    int i=l;   /* index for left element of the array b */
    int j=m+1;  /* index for element next to the middle element */
    int k=l;    /* index we use for array c temporary array */
    long long int count=0;  /* no.of inversions for this func */
    while(i<=m && j<=h){
        if(b[i]<=b[j]){
            c[k]=b[i];
            k++;
            i++;
        }  
        else{
            c[k]=b[j];
            k++;
            j++;
            count+=m+1-i;
        }   /* here in this we are copying elements of array b to array c as we do in merge sort but the only difference is in the case where the first element of the left subarray is greater than the first element of second subarray that means,all elements in the left subarray are greater than first element in the right sub array so there are middle-i+1 no.of inversions in total for that first element so as we increment count */
    }
    if(i<=m){
        while(i<=m){
            c[k]=b[i];
            k++;
            i++;
        }
    }   /* in the above while loop if the right subarray completes first we copy all elements of left to the array c */
    else{
        while(j<=h){
            c[k]=b[j];
            k++;
            j++;
        }
    }     /* in above while loop if the left subarray completes first we copy all elements of right to the array c */
    i=l;
    while(i<=h){
        b[i]=c[i];
        i++;
    }   /* changing all the values in the array b from l to h index */
    return count;  /* returning no.of inversions occur when merging happens */
}


void BloomBrain::create(int rooms){
    size=0;              /* initialising size to zero */
    arr=new int[rooms];  /* allocating space to array */ 
}

void BloomBrain::insert(int x){
    arr[size]=x;
    size++;  /* we add each element given at the end of array and increment size value by 1 */
}

long long int BloomBrain::play(){
    return Sum(0,size-1);  /* we are calling the func with respective arguments */
}

long long int BloomBrain::Sum(int l, int h){
    if(l==h)
        return arr[l];   /* if l==h means subarray or array has only one element we return that element */
    else{
        int m=l+(h-l)/2;
        long long int x=Sum(l,m);
        long long int y=Sum(m+1,h);
        long long int z=MiddleSum(l,h,m);
        if(x>=y&&x>=z)
            return x;
        if(y>=x&&y>=z)
            return y;
        else
            return z;
    }  /* here i this func we recursively call this Sum func by decrementing one of the arguments by half which means that we are divding array each time into two subarrays until it has one element then we are finding maximum of leftsubarray and maximum of rightsubarray and also we are finding maximum when meging  two subarrays using MiddleSum func as descied below then we return maximum of that three elements as maximum sum of sub array elments */
}

long long int BloomBrain::MiddleSum(int l, int h, int m){
    long long int sum=0;
    long long int count1=INT_MIN;  /* initialising count1 to -infinity */
    long long int count2=INT_MIN;  /* initialising count2 to -infinity */
    int i;
    i=m;
    while(i>=l){
        sum+=arr[i];
        if(sum>count1)
            count1=sum;
        i--;
    }   /* when we combine two subarrays the maximum subarray may be found as some elements to left of middle and some elements to right of middle so what we are doing here is we start from middle and we go to left index of the subarray or array such that we find partialsum at each step when partialsum is gretaer than count1 then we update count1 */
    sum=0;
    i=m+1;
    while(i<=h){
        sum+=arr[i];
        if(sum>count2)
            count2=sum;
        i++;
    }  /* we are doing same thing as above we start from middle and move to the right index of subarray or array such that we find partial sum at each stage and when partial sum is greater than count2 we update count 2 */
    sum=count1+count2;     /* now subarray sum when combined is leftsum i.e,count1 + rightsum i.e,count2 so total sum is                                                                                                  
                                                          count1+count 2 */
    if(count1>=count2&&count1>=sum)
        return count1;
    if(count2>=count1&&count2>=sum)
        return count2;
    else
        return sum;  /* we are returning maximum of leftsum right sum and combined sum as our result */
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int rooms;    /* variable for no.of rooms */
    int queries;  /* varable for no.of queries */
    string st;    /* variable to store query */
    int s,idx,z;  /* variables to store values after some of the queries */
    int i,j;      /* loop variables */
    int y=0;  
    BloomBrain B; /* class object B we perform operations on */
    cin>>rooms;
    cin>>queries;
    for(i=0;i<queries;i++){
        cin>>st;
        if(st=="update"){        /* if the query is update we first initialise the size of the array we use in the class BloomBrain and we insert each element after taking them using for loop as shown and after that only one time we call nonempty func to initialise all values in isemty array to 1 and after that we printing the value given by update func */
            B.create(rooms);
            for(j=0;j<rooms;j++){
                cin>>z;
                B.insert(z);
            }
            if(y==0){
                B.nonempty();
                y=1;
            }
            cout<<B.update()<<endl;
        }
        if(st=="join"){
            cin>>s;
            B.join(s);   /* if query is join we simply call func with argument taken as shown */
        }
        if(st=="leave"){
            cin>>idx;
            B.leave(idx); /* if query is leave we simply call func we used to delete element in array at index taken */ 
        }
        if(st=="occupied")
            cout<<B.occupied()<<endl;  /* if query is occupied we call occupy func and print the result */
        if(st=="play")
            cout<<B.play()<<endl;  /* if query is play func we call play func and print the result */
    }
    return 0;
}

