#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <climits>

using namespace std;

void printArr(int arr[], int size){
	for(int i = 0; i < size; i++) cout << arr[i] << " ";
	cout << endl;
}


////////////////////////////////////////
//////////...INSERTION SORT...//////////
void insertionSort(int arr[], int len){
	for(int i = 0; i < len; i++){
		int cur = arr[i];
		int j = i-1;
		for(; j >= 0; j--){
			if(arr[j] > cur) arr[j+1] = arr[j];
			else break;
		}
		arr[j+1] = cur;
	}
}


////////////////////////////////////
//////////...MERGE SORT...//////////
void merge(int array[], int helper[], int low, int middle, int high){
    for(int i = low; i <= high; i++) helper[i] = array[i]; 

    int helperLeft = low;
    int helperRight = middle + 1; 
    int current = low; 

    while(helperLeft <= middle && helperRight <= high){
        if(helper[helperLeft] <= helper[helperRight]){
            array[current] = helper[helperLeft];
            helperLeft++;
        }else{
            array[current] = helper[helperRight];
            helperRight++;
        }
        current++;
    }

    int remaining = middle - helperLeft; 
    for(int i = 0; i <= remaining; i++) array[current+i] = helper[helperLeft + i];
}

void mergeSort(int array[], int helper[], int low, int high){
    if(low < high){
        int middle = (low+high)/2;
        mergeSort(array, helper, low, middle);         
		mergeSort(array, helper, middle+1, high); 
        merge(array, helper, low, middle, high); 
    }
}

void mergeSort(int array[], int length){
    int helper[length];
    mergeSort(array, helper, 0, length-1);
}


/////////////////////////////////////////
//////////...QUICK SORT LAST...//////////
void quickSortLast(int arr[], int left, int right){
	if(left >= right) return;

	int start = left;
	int end = right;
	int pivot = arr[right];
	right--;
	while(left <= right){
		if(arr[left] > pivot && arr[right] < pivot){
			swap(arr[left], arr[right]);
			left++; right--;
			continue;
		}

		if(arr[left] <= pivot) left++;
		if(arr[right] >= pivot) right--;

	}
	swap(arr[left], arr[end]);

	quickSortLast(arr, start, left-1);
	quickSortLast(arr, left+1, end);
}

void quickSortLast(int arr[], int len){
	quickSortLast(arr, 0, len-1);
}


////////////////////////////////////////
//////////...QUICK SORT MED...//////////
int partition(int arr[], int l, int r, int x){ 
    int i; 
    for (i=l; i<r; i++) 
        if (arr[i] == x) 
           break; 
    swap(arr[i], arr[r]); 
    i = l; 
    for (int j = l; j <= r - 1; j++){ 
        if (arr[j] <= x){ 
            swap(arr[i], arr[j]); 
            i++; 
        } 
    } 
    swap(arr[i], arr[r]); 
    return i; 
} 


int findMedian(int arr[], int n){
    sort(arr, arr+n); 
    return arr[n/2];  
}

int kthSmallest(int arr[], int l, int r, int k)
{
    if (k > 0 && k <= r - l + 1)
    {
        int n = r-l+1;
        int i, median[(n+4)/5]; 
        for (i=0; i<n/5; i++)
            median[i] = findMedian(arr+l+i*5, 5);
        if (i*5 < n) 
        {
            median[i] = findMedian(arr+l+i*5, n%5);
            i++;
        }

        int medOfMed = (i == 1)? median[i-1]:
                                 kthSmallest(median, 0, i-1, i/2);
        int pos = partition(arr, l, r, medOfMed);
        if (pos-l == k-1)
            return arr[pos];
        if (pos-l > k-1)  
            return kthSmallest(arr, l, pos-1, k);
        return kthSmallest(arr, pos+1, r, k-pos+l-1);
    }
    return INT_MAX;
}

void quickSortMed(int arr[], int left, int right){
	if(left >= right) return;

	int start = left; int end = right;
//	int pivot = findMed(arr, left, right);
	int pivot = kthSmallest(arr, left, right, (right-left+1)/2);
	int pivot_idx;
	for(int i = left; i <= right; i++){
		if(arr[i] == pivot) {
			pivot_idx = i;
			break;
		}
	}
	swap(arr[pivot_idx], arr[right]);
	right--;
	while(left <= right){
		if(arr[left] > pivot && arr[right] < pivot){
			swap(arr[left], arr[right]);
			left++; right--;
			continue;
		}

		if(arr[left] <= pivot) left++;
		if(arr[right] >= pivot) right--;
	}
	swap(arr[left], arr[end]);

	quickSortMed(arr, start, left-1);
	quickSortMed(arr, left+1, end);
}

void quickSortMed(int arr[], int len){
	quickSortMed(arr, 0, len-1);
}



///////////////////////////////////
//////////...HEAP SORT...//////////

void maxHeapify(int arr[], int i, int len){
	int left = 2*i + 1;
	int right = 2*i + 2;
	int largest = i;
	if(left < len && arr[left] > arr[largest]) largest = left;
	if(right < len && arr[right] > arr[largest]) largest = right;
	if(i != largest){
		swap(arr[i], arr[largest]);
		maxHeapify(arr, largest, len);
	}
}

void buildMaxHeap(int arr[], int len){
	for(int i = len/2; i >= 0; i--)
		maxHeapify(arr, i, len);
}

void heapSort(int arr[], int len){
	buildMaxHeap(arr, len);
	while(len > 1){
		swap(arr[len-1], arr[0]);
		len--;
		maxHeapify(arr, 0, len);
	}
}


/////////////////////////////////////
//////////...STOOGE SORT...//////////
void stoogeSort(int arr[], int l, int h) { 
    if (l >= h) return; 
  
    if (arr[l] > arr[h]) 
        swap(arr[l], arr[h]); 
    if (h - l + 1 > 2) { 
        int t = (h - l + 1) / 3; 
  
        stoogeSort(arr, l, h - t); 
        stoogeSort(arr, l + t, h); 
        stoogeSort(arr, l, h - t); 
    } 
} 

void stoogeSort(int arr[], int len){
	stoogeSort(arr, 0, len-1);
}


//////////////////////////////
//////////////////////////////
//////////...MAIN...//////////

int main(){
	int size;
	cout << "Input the size of array: ";
	cin >> size;

	int input[size];
	for(int i = 0; i < size; i++) input[i] = i+1;
	random_shuffle(input, input+size);

	//Choose an algorithm to use
	int sortType;
	cout << "\nChoose sorting algorithm\n1.Insertion Sort\n2.Merge Sort\n3.Quick Sort(pivot=last)\n4.Quick Sort(optimized)\n5.Heap Sort\n6.Stooge Sort" << endl;
	cin >> sortType;
	if(sortType<1 || sortType>6){
		cout << "Invaid input" << endl;
		return 0;
	}
	
	clock_t begin, end;

	//Execute the algorithm once
	cout << "\nExecuting once" << endl;
	switch(sortType){
		case 1:
			cout << "Insertion Sort" << endl;
			begin = clock();
			insertionSort(input ,size);
			end = clock();
			break;
		case 2:
			cout << "Merge Sort" << endl;
			begin = clock();
			mergeSort(input ,size);
			end = clock();
			break;
		case 3:
			cout << "Quick Sort Last" << endl;
			begin = clock();
			quickSortLast(input ,size);
			end = clock();
			break;
		case 4:
			cout << "Quick Sort Med" << endl;
			begin = clock();
			quickSortMed(input ,size);
			end = clock();
			break;
		case 5:
			cout << "Heap Sort" << endl;
			begin = clock();
			heapSort(input ,size);
			end = clock();
			break;
		case 6:
			cout << "Stooge Sort" << endl;
			begin = clock();
			stoogeSort(input ,size);
			end = clock();
			break;

	}
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Elapsed time: " << elapsed_secs << endl;


	cout <<"\nExecuting 10 times" << endl;
	double computeTime[10];
	double computeSum = 0;
	for(int i = 0; i < 10; i++){
		srand(i);
		random_shuffle(input, input+size);
		switch(sortType){
			case 1:
				begin = clock();
				insertionSort(input ,size);
				end = clock();
				break;
			case 2:
				begin = clock();
				mergeSort(input ,size);
				end = clock();
				break;
			case 3:
				begin = clock();
				quickSortLast(input ,size);
				end = clock();
				break;
			case 4:
				begin = clock();
				quickSortMed(input ,size);
				end = clock();
				break;
			case 5:
				begin = clock();
				heapSort(input ,size);
				end = clock();
				break;
			case 6:
				begin = clock();
				stoogeSort(input ,size);
				end = clock();
				break;


		}
		double elapsed = double(end - begin) / CLOCKS_PER_SEC;
		computeSum += elapsed;
		computeTime[i] = elapsed;
	}

	cout << "Computing time array" << endl;
	for(int i = 0; i < 10; i++) cout << computeTime[i] << " ";
	cout << "\nAverage: " << computeSum/10.0 << endl;




}

