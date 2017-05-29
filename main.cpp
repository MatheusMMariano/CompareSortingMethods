#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;
using namespace std::chrono;

//Generate random vector
void random_vector(vector<int> &container){
	iota(container.begin(), container.end(), 0);
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	std::shuffle(container.begin(), container.end(), generator);
}

//Generate a sequencial vector
void sequencial_vector(vector<int> &container){
	iota(container.begin(), container.end(), 0);
}

//Generate a reverse vector
void reverse_vector(vector<int> &container){
	sequencial_vector(container);
	reverse(container.begin(), container.end());
}

void half_order_vector(vector<int> &container){
    sequencial_vector(container);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	std::shuffle(container.begin()+(container.size()/2), container.end(), generator);
}

//Insert sort
void insertionsort(int vet[], int n){
	for (int i = 1; i < n; i++){
		if(vet[i-1] > vet[i]){
			int t = vet[i], j = i;

			while((j > 0) && (vet[j-1] > t)){
        		vet[j] = vet[j-1];
        		j--;
      		}
      		vet[j] = t;
    	}
  	}
}

void insertion_sort(vector<int> &vec, int n){
	insertionsort(&vec[0], n);
}

//Selection Sort
void selection_sort(vector<int> &vet, int n){
  int i, k, m, j, t;
    j = n;
    for(i = 0; i < (n-1); i++){
        j = j - 1;
        m = 0;
        for (k = 0; k <= j; k++){
            if (vet[k] > vet[m]){
                m = k;
            }
        }
        t = vet[m];
        vet[m] = vet[j];
        vet[j] = t;
    }
}

//Shell Sort
void shell(int array[], int count){
	int interval = 1;
	while (interval < count) interval = 3 * interval + 1;

	for (NULL; interval > 0; interval = interval/3) {
		for (int i = interval; i < count; i++){
			int temp = array[i];
			int j;
			for (j = i; j >= interval && array[j - interval] > temp; j -= interval) {
				array[j] = array[j - interval];
			}
			array[j] = temp;
		}
	}
}

void shellsort(vector<int> &vec, int n){
	shell(&vec[0], n);
}

//Heapsort
void heapify(vector<int> &arr, int n, int i){
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i){
        swap(arr[i], arr[largest]); //método da biblioteca algorithm
        heapify(arr, n, largest);
    }
}

void heapsort(vector<int> &arr, int n){
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);

    for (int i=n-1; i>=0; i--){
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

//Merge Sort
void merg(int *arr, int size1, int size2) {
    int temp[size1+size2];
    int ptr1=0, ptr2=0;

    while ((ptr1+ptr2) < (size1+size2)) {
        if (ptr1 < size1 && arr[ptr1] <= arr[size1+ptr2] || ptr1 < size1 && ptr2 >= size2)
            temp[ptr1+ptr2] = arr[ptr1++];

        if (ptr2 < size2 && arr[size1+ptr2] < arr[ptr1] || ptr2 < size2 && ptr1 >= size1)
            temp[ptr1+ptr2] = arr[size1+ptr2++];
    }

    for (int i=0; i < (size1+size2); i++)
        arr[i] = temp[i];
}

void mergeSort(int *arr, int size) {
    if (size == 1) return;

	int size1 = size/2, size2 = size-size1;
	mergeSort(arr, size1);
	mergeSort(arr+size1, size2);
	merg(arr, size1, size2);
}

void mergesort(vector<int> &v, int n){
	mergeSort(&v[0], n);
}

//Quick Sort
void quickSort(int arr[], int left, int right) {
      int i = left, j = right;
      int tmp;
      int pivot = arr[(left + right) / 2];

      //partition
      while (i <= j) {
            while (arr[i] < pivot)
                  i++;
            while (arr[j] > pivot)
                  j--;
            if (i <= j) {
                  tmp = arr[i];
                  arr[i] = arr[j];
                  arr[j] = tmp;
                  i++;
                  j--;
            }
      };

      //recursion
      if (left < j) quickSort(arr, left, j);
      if (i < right) quickSort(arr, i, right);
}

void quick(vector<int> &arr, int n){
    quickSort(&arr[0], 0, n-1);
}

//std::sort
void std_sort(vector<int> &vec, int n){
	std::sort(vec.begin(), vec.end());
}

//std::stable_sort
void std_stable_sort(vector<int> &vec, int n){
	std::stable_sort(vec.begin(), vec.end());
}

//std::sort_heap
void std_sort_heap(vector<int> &vec, int n){
	std::make_heap(vec.begin(), vec.end());
	std::sort_heap(vec.begin(), vec.end());
}

void show(vector<int> v){
    cout << "\n";
    for(int i = 0; i < v.size(); i++) cout << v[i] << " ";
    cout << "\n";
}

template<class Functor>
void time_sort(Functor f, int n){
	double total_r = 0, total_s = 0, total_rv = 0, total_h = 0;

	for(int i = 0; i < 100; i++){
	    vector<int> vec_r(n), vec_s(n), vec_rv(n), vec_h(n);

	    random_vector(vec_r);
	    sequencial_vector(vec_s);
	    reverse_vector(vec_rv);
	    half_order_vector(vec_h);

	    //Random vector
		auto start_r = chrono::steady_clock::now();
		f(vec_r, n);
		auto stop_r  = chrono::steady_clock::now();

	    //Sequencial vector
		auto start_s = chrono::steady_clock::now();
		f(vec_s, n);
		auto stop_s  = chrono::steady_clock::now();

	    //Reverse vector
		auto start_rv = chrono::steady_clock::now();
		f(vec_rv, n);
		auto stop_rv  = chrono::steady_clock::now();

		//A half order vector
		auto start_h = chrono::steady_clock::now();
		f(vec_h, n);
		auto stop_h  = chrono::steady_clock::now();

    	//Final time
		total_r = total_r   + chrono::duration<double, milli> (stop_r-start_r).count();
	    total_s = total_s   + chrono::duration<double, milli> (stop_s-start_s).count();
	    total_rv= total_rv  + chrono::duration<double, milli> (stop_rv-start_rv).count();
	    total_h = total_h   + chrono::duration<double, milli> (stop_h-start_h).count();
  	}

  	cout << "\n\n[Time]" << endl;
  	cout << "\t|- Random vector time: "     << (total_r/100)   << " milliseconds."   << endl;
  	cout << "\t|- Sequential vector time: " << (total_s/100)   << " milliseconds."   << endl;
  	cout << "\t|- Reverse vector time: "    << (total_rv/100)  << " milliseconds."   << endl;
  	cout << "\t|- A half order vector time: " << (total_h/100)  << " milliseconds.\n"   << endl;
}

void test_case(int n){
	cout << "================= " << n << " =================" << endl;
  	cout << "--> Insertion Sort:";
  	time_sort(insertion_sort, n);

	cout << "--> Selection Sort:";
  	time_sort(selection_sort, n);

  	cout << "--> Shellsort:";
  	time_sort(shellsort, n);

	cout << "--> Heapsort:";
  	time_sort(heapsort, n);

  	cout << "--> Mergesort:";
  	time_sort(mergesort, n);

    cout << "--> Quicksort:";
  	time_sort(quick, n);

	cout << "--> std::sort:";
	time_sort(std_sort, n);

	cout << "--> std::stable_sort:";
	time_sort(std_stable_sort, n);

	cout << "--> std::sort_heap:";
	time_sort(std_sort_heap, n);
}

void test(vector<int> &container){
    cout << "\nTamanho: " << container.size() << endl;
    for(int i = 0; i < container.size(); i++) cout << container[i] << " ";
}

int main(){
	for(int i = 10; i <= 100000; i=i*10) test_case(i);
	return 0;
}
