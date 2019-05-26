#include <stdio.h>
#include <cstdlib>
using namespace std;
 
//swap function 
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
	for(int i = n/2 - 1 ; i >= 0; i--) max_heapify(A, n, i);
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
