// Сортировка пузырьком (Bubble Sort)
// Сортировка выбором (Selection Sort)
// Сортировка вставками (Insertion Sort)
// Сортировка слиянием (Merge Sort)
// Быстрая сортировка (Quick Sort)
// Сортировка кучей (Heap Sort)
// Сортировка Шелла (Shell Sort)
// Сортировка подсчетом (Counting Sort)
// Поразрядная сортировка (Radix Sort)
// Сортировка бочонком (Bucket Sort)

#include <iostream>

using namespace std;

void bubbleSort(int arr[], int n);
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void heapify(int arr[], int n, int i);
void heapSort(int arr[], int n);
void shellSort(int arr[], int n);
void countingSort(int arr[], int n);
void countingSortForRadix(int arr[], int n, int exp);
void radixsort(int arr[], int n);
void bucketSort(float arr[], int n);


int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    bubbleSort(arr, n);
    for(int i=0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    
    selectionSort(arr, n);
    for(int i=0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    
    insertionSort(arr, n);
    for(int i=0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    
    return 0;
}

// Сортировка пузырьком
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {     
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// Сортировка выбором
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[min_idx], arr[i]);
    }
}

// Сортировка вставками
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

////////////////

// Сортировка слиянием
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Быстрая сортировка
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Сортировка кучей
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

/////////////////

// Сортировка Шелла
void shellSort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

// Сортировка подсчетом
void countingSort(int arr[], int n) {
    int max = *max_element(arr, arr+n);
    int min = *min_element(arr, arr+n);
    int range = max - min + 1;
    int count[range], output[n];
    memset(count, 0, sizeof(count));
    for(int i = 0; i < n; i++)
        count[arr[i]-min]++;
    for(int i = 1; i < range; i++)
        count[i] += count[i-1];
    for(int i = n-1; i >= 0; i--) {
        output[count[arr[i]-min]-1] = arr[i];
        count[arr[i]-min]--;
    }
    for(int i = 0; i < n; i++)
        arr[i] = output[i];
}

// Поразрядная сортировка
void countingSortForRadix(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};
    for (int i = 0; i < n; i++)
        count[(arr[i]/exp)%10]++;
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i]/exp)%10] - 1] = arr[i];
        count[(arr[i]/exp)%10]--;
    }
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixsort(int arr[], int n) {
    int max = *max_element(arr, arr+n);
    for (int exp = 1; max/exp > 0; exp *= 10)
        countingSortForRadix(arr, n, exp);
}

// Сортировка бочонком
void bucketSort(float arr[], int n) {
    vector<float> b[n];
    for (int i=0; i<n; i++) {
       int bi = n*arr[i];
       b[bi].push_back(arr[i]);
    }
    for (int i=0; i<n; i++)
       sort(b[i].begin(), b[i].end());
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++)
          arr[index++] = b[i][j];
}
