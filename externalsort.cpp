// C++ program to implement 
// external sorting using 
// merge sort 
#include <bits/stdc++.h> 
using namespace std; 
typedef long long ll;
  
struct MinHeapNode { 
    // The element to be stored 
    ll element; 
  
    // index of the array from which 
    // the element is taken 
    ll i; 
}; 
  
// Prototype of a utility function 
// to swap two min heap nodes 
void swap(MinHeapNode* x, MinHeapNode* y); 
  
// A class for Min Heap 
class MinHeap { 
    // pointer to array of elements in heap 
    MinHeapNode* harr; 
  
    // size of min heap 
    ll heap_size; 
  
public: 
    // Constructor: creates a min 
    // heap of given size 
    MinHeap(MinHeapNode a[], ll size); 
  
    // to heapify a subtree with 
    // root at given index 
    void MinHeapify(ll); 
  
    // to get index of left child 
    // of node at index i 
    ll left(ll i) { return (2 * i + 1); } 
  
    // to get index of right child 
    // of node at index i 
    ll right(ll i) { return (2 * i + 2); } 
  
    // to get the root 
    MinHeapNode getMin() { return harr[0]; } 
  
    // to replace root with new node 
    // x and heapify() new root 
    void replaceMin(MinHeapNode x) 
    { 
        harr[0] = x; 
        MinHeapify(0); 
    } 
}; 
  
// Constructor: Builds a heap from 
// a given array a[] of given size 
MinHeap::MinHeap(MinHeapNode a[], ll size) 
{ 
    heap_size = size; 
    harr = a; // store address of array 
    ll i = (heap_size - 1) / 2; 
    while (i >= 0) { 
        MinHeapify(i); 
        i--; 
    } 
} 
  
// A recursive method to heapify 
// a subtree with root 
// at given index. This method 
// assumes that the 
// subtrees are already heapified 
void MinHeap::MinHeapify(ll i) 
{ 
    ll l = left(i); 
    ll r = right(i); 
    ll smallest = i; 
    if (l < heap_size && harr[l].element < harr[i].element) 
        smallest = l; 
    if (r < heap_size && harr[r].element < harr[smallest].element) 
        smallest = r; 
    if (smallest != i) { 
        swap(&harr[i], &harr[smallest]); 
        MinHeapify(smallest); 
    } 
} 
  
// A utility function to swap two elements 
void swap(MinHeapNode* x, MinHeapNode* y) 
{ 
    MinHeapNode temp = *x; 
    *x = *y; 
    *y = temp; 
} 

void swap(ll* a, ll* b)  
{  
    ll t = *a;  
    *a = *b;  
    *b = t;  
}  
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
int partition (ll arr[], ll low, ll high)  
{  
    ll pivot = arr[high]; // pivot  
    ll i = (low - 1); // Index of smaller element  
  
    for (ll j = low; j <= high - 1; j++)  
    {  
        // If current element is smaller than the pivot  
        if (arr[j] < pivot)  
        {  
            i++; // increment index of smaller element  
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  
/*
void quickSort(vector<ll>& arr, ll low, ll high)  
{  
    if (low < high)  
    {  
        / pi is partitioning index, arr[p] is now  
        at right place /
        ll pi = partition(arr, low, high);  
  
        // Separately sort elements before  
        // partition and after partition  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
}  */
void quickSort(ll arr[], ll low, ll high)  
{  
    if (low < high)  
    {  
        /* pi is partitioning index, arr[p] is now  
        at right place */
        ll pi = partition(arr, low, high);  
  
        // Separately sort elements before  
        // partition and after partition  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
}  

  
FILE* openFile(char* fileName, char* mode) 
{ 
    FILE* fp = fopen(fileName, mode); 
    if (fp == NULL) { 
        perror("Error while opening the file.\n"); 
        exit(EXIT_FAILURE); 
    } 
    return fp; 
} 
  
// Merges k sorted files. Names of files are assumed 
// to be 1, 2, 3, ... k 
void mergeFiles(char* output_file, ll n, ll k) 
{ 
    FILE* in[k]; 
    for (ll i = 0; i < k; i++) { 
        char fileName[2]; 
  
        // convert i to string 
        snprintf(fileName, sizeof(fileName), 
                 "%lld", i); 
  
        // Open output files in read mode. 
        in[i] = openFile(fileName, "r"); 
    } 
  
    // FINAL OUTPUT FILE 
    FILE* out = openFile(output_file, "w"); 
  
    // Create a min heap with k heap 
    // nodes. Every heap node 
    // has first element of scratch 
    // output file 
    MinHeapNode* harr = new MinHeapNode[k]; 
    ll i; 
    for (i = 0; i < k; i++) { 
        // break if no output file is empty and 
        // index i will be no. of input files 
        if (fscanf(in[i], "%lld", &harr[i].element) != 1) 
            break; 
  
        // Index of scratch output file 
        harr[i].i = i; 
    } 
    // Create the heap 
    MinHeap hp(harr, i); 
  
    ll count = 0; 
  
    // Now one by one get the 
    // minimum element from min 
    // heap and replace it with 
    // next element. 
    // run till all filled input 
    // files reach EOF 
    while (count != i) { 
        // Get the minimum element 
        // and store it in output file 
        MinHeapNode root = hp.getMin(); 
        fprintf(out, "%lld,", root.element); 
        
  
        // Find the next element that 
        // will replace current 
        // root of heap. The next element 
        // belongs to same 
        // input file as the current min element. 
        if (fscanf(in[root.i], "%lld ",&root.element)!= 1) 
        { 
            root.element = LLONG_MAX; 
            count++; 
        } 
  
        // Replace root with next 
        // element of input file 
        hp.replaceMin(root); 
    } 
  
    // close input and output files 
    for (ll i = 0; i < k; i++) 
        fclose(in[i]); 
  
    fclose(out); 
} 
  
// Using a merge-sort algorithm, 
// create the initial runs 
// and divide them evenly among 
// the output files 
void createInitialRuns(char* input_file, ll run_size,ll num_ways) 
{ 
    // For big input file 
    FILE* in = openFile(input_file, "r"); 
  
    // output scratch files 
    FILE* out[num_ways]; 
    char fileName[2]; 
    for (ll i = 0; i < num_ways; i++) { 
        // convert i to string 
        snprintf(fileName, sizeof(fileName), "%lld", i); 
  
        // Open output files in write mode. 
        out[i] = openFile(fileName, "w"); 
    } 
  
    // allocate a dynamic array large enough 
    // to accommodate runs of size run_size 
    ll* arr = (ll*)malloc(run_size * sizeof(ll)); 
    //vector<ll> arr(run_size);
  
    bool more_input = true; 
    ll next_output_file = 0; 
  
    ll i; 
    while (more_input) { 
        // write run_size elements 
        // into arr from input file 
        for (i = 0; i < run_size; i++) { 
            if (fscanf(in, "%lld,", &arr[i]) != 1) { 
                more_input = false; 
                break; 
            } 
        } 
  
        
        quickSort(arr, 0, i - 1); 
  
        // write the records to the 
        // appropriate scratch output file 
        // can't assume that the loop 
        // runs to run_size 
        // since the last run's length 
        // may be less than run_size 
        for (ll j = 0; j < i; j++) 
            fprintf(out[next_output_file],"%lld ", arr[j]); 
  
        next_output_file++; 
    } 
  
    // close input and output files 
    for (ll i = 0; i < num_ways; i++) 
        fclose(out[i]); 
  
    fclose(in); 
} 
  
// For sorting data stored on disk 
void externalSort( 
    char* input_file, char* output_file, 
    ll num_ways, ll run_size) 
{ 
    // read the input file, 
    // create the initial runs, 
    // and assign the runs to 
    // the scratch output files 
    createInitialRuns(input_file,run_size, num_ways); 
  
    // Merge the runs using 
    // the K-way merging 
    mergeFiles(output_file, run_size, num_ways); 
} 
  
// Driver program to test above 
int main() 
{ 
    
  
    char input_file[] = "input.txt"; 
    char output_file[] = "output.txt"; 
    FILE *p_file = NULL;
    string filename = "input.txt";
    p_file = fopen(filename.c_str(),"rb");
    fseek(p_file,0,SEEK_END);
    ll filesize = ftell(p_file);
    fclose(p_file);
   

    cout<<"The size is "<<filesize<<endl;
  
    // The size of each partition 
    ll num_ways = 10; 
    // No. of Partitions of input file. 
    ll int_file_size = ceil(filesize/100);
  
    externalSort(input_file, output_file, num_ways,int_file_size); 

                
  
    return 0; 
}