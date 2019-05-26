#include <stdio.h>
#include <cstdlib>
using namespace std;
////////////////

  
void swap(int* a, int* b);

// To heapify a subtree rooted with node i which is 
// an index in arr[]. n is size of heap 
void heapify(int arr[], int n, int i) 
{ 
    int largest = i; // Initialize largest as root 
    int l = 2 * i + 1; // left = 2*i + 1 
    int r = 2 * i + 2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if (l < n && arr[l] > arr[largest]) 
        largest = l; 
  
    // If right child is larger than largest so far 
    if (r < n && arr[r] > arr[largest]) 
        largest = r; 
  
    // If largest is not root 
    if (largest != i) { 
        swap(&arr[i], &arr[largest]); 
  
        // Recursively heapify the affected sub-tree 
        heapify(arr, n, largest); 
    } 
} 
  
// main function to do heap sort 
void heapSort(int arr[], int n) 
{ 
    // Build heap (rearrange array) 
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 
  
    // One by one extract an element from heap 
    for (int i = n - 1; i >= 0; i--) { 
        // Move current root to end 
        swap(&arr[0], &arr[i]); 
  
        // call max heapify on the reduced heap 
        heapify(arr, i, 0); 
    } 
} 
  
  
 

//////////////////
void swap(int* a, int* b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}




void max_heapify(int A[],int n, int i){
	int max_idx = i;
	int l_idx = 2*i + 1;
	int r_idx = 2*i + 2;
	
	if(n > l_idx && A[i] < A[l_idx]) max_idx = l_idx;
	
	if(n > r_idx && A[max_idx] < A[r_idx]) max_idx = r_idx;

	if(max_idx != i) {
	swap(&A[i], &A[max_idx]);
	max_heapify(A, n, max_idx);
	}
}

void build_max_heap(int A[], int n){
	for(int i = n-1 ; i >= 0; i--) max_heapify(A, n, i);
}

void heapsort(int A[], int n){
	build_max_heap(A, n);
	for(int i = n-1; i>0; i--){
		swap(&A[0], &A[i]);

		max_heapify(A, i, 0);
	}
}

void printarray(int arr[], int n){
	for(int i = 0; i < n; i++) printf("%d, ", arr[i]);
	printf("\n");
}




int main(){
	int testarr[] = {4,6,1,8,2,9};
	int n = sizeof(testarr)/sizeof(testarr[0]);

	int testarr2[10];

	for(int i = 0; i<10; i++) testarr2[i] =rand()%100;	

	for(int i = 0; i < 10; i++) printf("%d ", testarr2[i]);
	printf("\n");
	heapsort(testarr2, 10);

//	printarray(testarr, n);
	
	printf("Original array: ");
	for(int i = 0; i < 10; i++) printf("%d ", testarr2[i]);
	
	return 0;
}
