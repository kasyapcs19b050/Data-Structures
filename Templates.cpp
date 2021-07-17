/**********************
*
* FILE: Vectorops.cpp
*
*Purpose: can be used to calculate the operations of an array using template of the given conditions 
*
*Author: G Hithendra Kasyap
*
*Created: Mon 01-March-2021
*
********************/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

template<class T>   /* template used to define a data type */
class Vector{           /* class vector used to store variables */
    private:
        size_t capacity;
        size_t size=0;
        T*  vec;       /* private varables to store the size and capacity and the elements of array */
    protected:
        int partition(int l,int h);  /* func which returns the partiotioning element in the quick sort we use */
    public:
        Vector(){
            capacity=1;
            vec = new T[1];
        }         /* constructor with no arguments so we allocate one datatype memory to the array and capacity equlas to 1 */ 
        Vector(size_t c){
            capacity=c;
            vec = new T[c];
        }        /* constructor with one arguments so we allocate the given argument datatype memory to the array and capacity equlas to the argument value */
        Vector(size_t c,T x){
            capacity = c;
            size = c;
            vec = new T[c];
            size_t i;
            for(i=0;i<capacity;i++)
                *(vec+i)=x;
        }        /* constructor with two arguments so we allocate first argument datatype memory to the array and capacity equlas to the first argument and we initialise all elements of array to the second argument */
        ~Vector(){
            delete [] vec;
        }                  /* Destructor which deallocates or erases all the memory allocated to the array */
        void push(T x);   /* func to add element to array at first un assigned positon */
        void pop();       /* func to remove the last element of the array */
        T  front();       /* func for returning the first element */
        T  back();        /* func for returning the last element */
        size_t Capacity();  /* func to return capacity of the array */
        size_t Size();      /* func to return size of the array */
        T&  operator[](size_t i){
             T* p;
             p=new T[1];   /* creating a single element array to store the value of the ith element */
             if(size<=i){
                 p[0]=-1;
                 return p[0];
             }                  /* if given index is larger than or equal to size we return -1 */
             return vec[i];
        }   /* operator overloading func to return the ith element of array if don't present we return -1 */
        void Resize(T c);       /* func to reallocate double memory without deleting any elements */
        void sort(int l,int h); /* quick sort to sort the elements */
        void print();           /* print the elements of the array */
};

template<class T>
void Vector<T>::push(T x){
    if(size==capacity)
        Resize(2*capacity);
    vec[size]=x;
    size+=1;            /* if the array is full we resize the array such that now array is of double the capacity and after that we push another element in the array because initially there is no space for this after resizing there is enough space and we increment sze by 1 indicating that we add one more element */
}

template<class T>
size_t Vector<T>::Capacity(){
    return capacity;    /* returning capacity of the array */
}

template<class T>
size_t Vector<T>::Size(){
    return size;    /* returning no.of elements in the array */
}
    
template<class T>
void Vector<T>::pop(){
    if(size!=0)
        size-=1;      /* deleting the last elemet of the array by decreasing the no.of elements by 1 */
}

template<class T>
T Vector<T>::front(){
    if(size==0)
        return -1;
    return vec[0];     /* returning first element if exists else we return -1 */
}

template<class T>
T Vector<T>::back(){
    if(size==0)
        return -1;
    return vec[size-1];   /* returning last element if exists else we return -1 */
}

template<class T>
void Vector<T>::Resize(T c){
    T* vec1;
    size_t i,oldcapacity; /* loop variable and variable old capacity to store the initial capacity */
    oldcapacity=capacity;  /* initialising the value of oldcapacity as present capacity */
    capacity=c;      /* changing the capacity value to double */
    vec1 = new T[capacity];  /* creating a temporary array of size double the initial capacity */
    for(i=0;i<oldcapacity;i++)
        vec1[i]=vec[i];  /* copying all the array elements to the temp array */
    delete [] vec;    /* deleting the old array */
    vec=new T[capacity]; /* allocating and creating an array of size as new capacity */
    for(i=0;i<capacity;i++)
        vec[i]=vec1[i]; /* copying all the elements of the temp array to present  array */
    delete [] vec1;  /* deleting the temp array */
}

template<class T>
int Vector<T>::partition(int l,int h){  /* partition func to find the partitioning element */
    T pivot=vec[l];       /* making first element as pivot */
    int p1=l+1;           /* initialising the l+1 index to variable p1 */
    int i;
    T temp;   /* variable to swap */
    i=l+1;    /* starting element of the loop */
    while(i<=h){
        if(vec[i]<pivot){
            if(i!=p1){  
                temp=vec[p1];
                vec[p1]=vec[i];
                vec[i]=temp;
             }    
            p1++;
        }
        i++;
    }  /* through out the loop we find for the smaller elements than pivot from the l+1 index and we swap them first elements so that all the elements left to i are smmaler than i and right are greater tha i at a stage */ 
    vec[l]=vec[p1-1];
    vec[p1-1]=pivot; /* we swap the positons of the pivot with the last smallest element position */
    return p1-1;      /* we return p1-1 as the partitioning index such that all elements to the left of that index are lesser than the pivotal element assumed and all the elements greater than that index are greater than that pivotal element,we can say that the pivotal element assumed is now sorted in the array */ 
}

template<class T>
void Vector<T>::sort(int l,int h){  /* quick sort func */
    if(l<h){
        int p=partition(l,h);
        sort(l,p-1);
        sort(p+1,h);
    } /* we perform the partitions if the low value less than high value only and we recursively call the two sub arrays we divided at the partition */
}
   
template<class T>
void Vector<T>::print(){
    size_t i;
    for(i=0;i<size;i++)
        cout<<vec[i]<<" ";
    cout<<endl;  /* printing all the elements in the array */
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    string st;
    getline(cin,st);     /* getting all the elements in the first line into a string */
    int len=st.size();   /* storing length of string */
    int p=0,q=0;       /* variables to store the values coming after vector if exists */
    int i;          /* loop variable */
    int queries;    /* variable to store no.of queries */
    string s;       /* variable to store the query */
    int x,y;        /* variables to store the values after each query if they exists */
    int count=0;    /* variable to store no.of spaces */
    int arr[]={0,0,0};    /* array to store indices of the spaces */
    for(i=0;i<len;i++){
        if(st[i]==' '){
            arr[count]=i;
            count++;
        }
    }      /* storing the indices of spaces into array defined usng a for loop */
    if(len==7||len==6){     /* if the length of string is 6 then we know that string must be vector so we are calling the first constructor while definng vector object */
        Vector<int> V;
        cin>>queries;  
        for(i=0;i<queries;i++){
            cin>>s;     /* taking a query */
            if(s=="capacity")
                cout<<V.Capacity()<<endl;   /* calling and printing capapcity by calling the func required  */
            if(s=="size")
                cout<<V.Size()<<endl;       /* calling and printing size by calling the func required  */
            if(s=="pop")
                V.pop(); /* delete func */
            if(s=="push"){
                cin>>x;
                V.push(x);  /* adding element to the array */
             }
            if(s=="sort"){
                V.sort(0,V.Size()-1);
                V.print();  /* sorting the array using quick sort */
             }
            if(s=="element"){
                cin>>y;
                cout<<V[y]<<endl;  /* calling the overloaded func */
             }
            if(s=="front")
                cout<<V.front()<<endl; /* func for the first element if exists */
            if(s=="back")
                cout<<V.back()<<endl;  /* func for the last element if exists */
        }
    }
    else if((count==1&&len!=7)||(count==2&&arr[1]==len-1)){ /* if no.of spaces is 1 then we know there are two element one is a vector string and the other is the capacity  so we define the object   vector using second constructor */
        if((count==1&&len!=7)){
        for(i=arr[0]+1;i<len;i++){
            p*=10;
            p+=st[i]-48;
        }        
        }        /* converting the str elements to an integer */
        if((count==2&&arr[1]==len-1)){
            for(i=arr[0]+1;i<arr[1];i++){
            p*=10;
            p+=st[i]-48;
        }   
        }       /* converting the str elements to an integer */
        Vector<int> V(p);
        cin>>queries;
        for(i=0;i<queries;i++){  /* func descriptions are same as above */
            cin>>s;
            if(s=="capacity")
                cout<<V.Capacity()<<endl;
            if(s=="size")
                cout<<V.Size()<<endl;
            if(s=="pop")
                V.pop();
            if(s=="push"){
                cin>>x;
                V.push(x);
             }
            if(s=="sort"){
                V.sort(0,V.Size()-1);
                V.print();
             }
            if(s=="element"){
                cin>>y;
                cout<<V[y]<<endl;
             }
            if(s=="front")
                cout<<V.front()<<endl;
            if(s=="back")
                cout<<V.back()<<endl;
        }
    }
    else{    /* if no.of spaces are 2 we convert the two elemnts coming after vector string to capacity and intialisng the array elements using the third constructor */
        if(count==2){
        for(i=arr[0]+1;i<arr[1];i++){
            p*=10;
            p+=int(st[i])-48;
        }
        for(i=arr[1]+1;i<len;i++){
            q*=10;
            q+=int(st[i])-48;
        }  /* converting the values of two elements coming after vector string to integers */ 
        }
        else{
            for(i=arr[0]+1;i<arr[1];i++){
            p*=10;
            p+=int(st[i])-48;
        }
        for(i=arr[1]+1;i<arr[2];i++){
            q*=10;
            q+=int(st[i])-48;
        }
        }
        Vector<int> V(p,q);
        cin>>queries;
        for(i=0;i<queries;i++){    /* func descriptions are same as above */
            cin>>s;
            if(s=="capacity")
                cout<<V.Capacity()<<endl;
            if(s=="size")
                cout<<V.Size()<<endl;
            if(s=="pop")
                V.pop();
            if(s=="push"){
                cin>>x;
                V.push(x);
             }
            if(s=="sort"){
                V.sort(0,V.Size()-1);
                V.print();
             }
            if(s=="element"){
                cin>>y;
                cout<<V[y]<<endl;
             }
            if(s=="front")
                cout<<V.front()<<endl;
            if(s=="back")
                cout<<V.back()<<endl;
        }
    }
    return 0;
}

