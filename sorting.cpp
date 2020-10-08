#include<iostream>
#include <vector>
#include <stdlib.h> 
#include<math.h>
#include <algorithm>
using namespace std;

void print_vector(vector<int> a){
    for (int i=0;i<a.size();i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}
void swap(int* a,int *b){
    auto i = *a;
    *a = *b;
    *b = i;
}

bool is_sorted(int* arr, int size){
    for (int i=1;i<size;i++){
        if (arr[i-1]>arr[i]){
            return false;
        }
    }
    return true;
}


//BOGOSORT
int randint(int max){
    return rand()%max;
}
void shuffle(int* arr, int size){
    for (int i=0;i<size;i++){
        swap(&(arr[i]),&(arr[randint(size)]));
    }
}
void bogosort(int* arr, int size){
    int i=1;
    while(!is_sorted(arr,size)){
        shuffle(arr,size);
        i++;
    }
    cout<<"BOGOSORT TOOK "<<i<<" TRIES"<<endl;
    cout<<"CONGRATULATIONS BOGOSORT"<<endl;
}


//BUBBLE SORT
void bubblesort(int* arr,int size){
    for (int i=0;i<size;i++){
        for (int j=0;j<size-1-i;j++){
            if (arr[j]>arr[j+1]){
                swap(&(arr[j]),&(arr[j+1]));
            }
        }
    }
}

//SELECTIONSORT
int selectionsort(int* arr,int size){
    for (int i=0;i<size;i++){
        int menor =i;
        for (int j=i;j<size;j++){
            if (arr[j]<arr[menor]){
                menor=j;
            }
        }
        swap(&(arr[menor]),&(arr[i]));
    }
}

//INSERTION SORT
void insertionsort(int* arr,int size){
    int j;
    for (int i=0;i<size;i++){
        int place = arr[i];
        for (j=i-1;j>=0;j--){
            if (arr[j]>place){
                arr[j+1]=arr[j];
            }
            else{
                break;
            }
        }
        arr[j+1]=place;
    }
}

//SHELLSORT
void shellsort(int* arr,int size){
    for (int gap=size/2;gap>0;gap/=2){
        for (int i=gap;i<size;i++){
            int k=1;
            while (i-k*gap>=0 && arr[i-k*gap]>arr[i-(k-1)*gap]){
                swap(&(arr[i-k*gap]),&(arr[i-(k-1)*gap]));
                k++;
            }
        }
    }
}


//QUICKSORT
void quicksort_rec(int* arr, int begin,int end){
    if (end-begin<2){
        return;
    }
    //PARTICIONA
    bool right=true;
    int pl=begin;
    int pr=end-1;
    int pivot=arr[begin];
    while(pl<pr){
        if (right){
            if (arr[pr]<pivot){
                arr[pl]=arr[pr];
                pl++;
                arr[pr]=pivot;
                right=!right;
            }
            else{
                pr--;
            }
        }
        else{
            if (arr[pl]>pivot){
                arr[pr]=arr[pl];
                pr--;
                arr[pl]=pivot;
                right=!right;
            }
            else{
                pl++;
            }
        }
    }
    //RECURSA
    quicksort_rec(arr,begin,pl);
    quicksort_rec(arr,pl+1,end);
}

void quicksort(int* arr, int size){
    quicksort_rec(arr,0,size);
}

//MERGESORT
void merge(int* a, int begin, int mid, int end){
    int pb = begin;
    int pm = mid;
    int arr[end-begin+1];
    int index=0;
    while (pb<mid && pm<end){
        if (a[pb]<a[pm]){
            arr[index]=a[pb];
            index++;
            pb++;
        }
        else{
            arr[index]=a[pm];
            index++;
            pm++;
        }
    }
    while (pb<mid){
        arr[index]=a[pb];
        index++;
        pb++;
    }
    while(pm<end){
        arr[index]=a[pm];
        index++;
        pm++;
    }
    index=0;
    for (int i=begin;i<end;i++){
        a[i]=arr[index];
        index++;
    }
}

void mergesort_rec(int* arr,int begin,int end){
    if (end-begin<2){
        return;
    }
    int mid = begin + (end-begin)/2;
    mergesort_rec(arr,begin,mid);
    mergesort_rec(arr,mid,end);
    merge(arr,begin,mid,end);
}

void mergesort(int*arr, int size){
    mergesort_rec(arr,0,size);
}

//HEAPSORT
void heapify(int* arr,int index,int size){
    int largest = index;
    int left=2*index+1;
    int right=2*index+2;
    if (left<size && arr[left]>arr[largest]){
        largest=left;
    }
    if (right<size && arr[right]>arr[largest]){
        largest=right;
    }
    if (largest!=index){
        swap(&(arr[index]),&(arr[largest]));
        heapify(arr,largest,size);
    }
    
}
void build_heap(int*arr, int size){
    for (int i=size-1;i>=0;i--){
        heapify(arr,i,size);
    }
}
void heapsort(int* arr,int size){
    build_heap(arr,size);
    for (int i=0;i<size;i++){
        swap(&(arr[0]),&(arr[size-1-i]));
        heapify(arr,0,size-1-i);
    }
}

// COUNTING SORT O(max(maior-menor,n))
void countingsort(int*arr,int size){
    if (size<2){
        return;
    }
    int min=arr[0];
    int max=arr[0];
    for (int i=1;i<size;i++){
        if (arr[i]<min){
            min=arr[i];
        }
        if (arr[i]>max){
            max=arr[i];
        }
    }
    vector<int> counter(max-min+1);
    for (int i=0;i<size;i++){
        counter[arr[i]-min]++;
    }
    int index=0;
    for (int i=0;i<counter.size();i++){
        while(counter[i]>0){
            arr[index]=min+i;
            index++;
            counter[i]--;
        }
    }
}


//LSD RADIX SORT
int intAtPos(int a, int pos){
    int k1 = pow(10,pos);
    int k2 = pow(10,pos+1);
    return (a%k2)/k1;
}
void radixsort(int* arr, int size){
    if (size<2){
        return;
    }
    int maior = arr[0];
    for (int i=1;i<size;i++){
        if (arr[i]>maior){
            maior = arr[i];
        }
    }
    int len_max=(to_string(maior)).size();
    for (int i=0;i<len_max;i++){
        vector<vector<int>> radix(10);
        for (int j=0;j<size;j++){
            radix[intAtPos(arr[j],i)].push_back(arr[j]);
        }
        int index=0;
        for (int j=0;j<10;j++){
            for (int k:radix[j]){
                arr[index]=k;
                index++;
            }
        }
    }
}
















int main(){
    srand(time(NULL));
    vector<int> arr0 = {10,9,8,7,6,5,13};//7 elementos
    vector<int> arr1 = {1,3,5,6,7,8,2,3,3,4,6,7};//12 elementos
    vector<int> arr2 = {5,4,3,9,89,294,215,12,21,82,24,5952,225,21,4921,5239,1,2,3,93529,3259};//21 elementos


}