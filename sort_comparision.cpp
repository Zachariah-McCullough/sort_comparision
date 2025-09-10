#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <queue>

using namespace std;
using namespace std::chrono;

// ------------------- Utility Function: Random Vector Generation -------------------
// Generates a vector of 'n' random integers in the range [min_val, max_val]
// Uses Mersenne Twister for efficient random number generation
vector<int> generate_random_vector(int n, int min_val = 1, int max_val = 100000) {
    random_device rd;
    mt19937 gen(rd()); // Mersenne Twister random number generator
    uniform_int_distribution<> dis(min_val, max_val);
    vector<int> vec(n);
    for (int& x : vec) {
        x = dis(gen);
    }
    return vec;
}

// ------------------- Selection Sort -------------------
// Sorts a vector using the Selection Sort algorithm.
// Time Complexity: O(n^2). Not stable. In-place.
// Repeatedly finds the minimum element from the unsorted part and moves it to the front.
vector<int> selection_sort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        swap(arr[i], arr[min_idx]);
    }
    return arr;
}

// ------------------- Merge Sort -------------------
// Sorts a vector using the Merge Sort algorithm.
// Time Complexity: O(n log n). Stable. Not in-place due to auxiliary storage.
// Divide-and-conquer strategy: recursively splits the array and merges sorted halves.

// Forward declarations
vector<int> merge_sort(vector<int> arr);
vector<int> merge_sort_helper(vector<int>& arr, int left, int right);

// Entry point for Merge Sort
vector<int> merge_sort(vector<int> arr) {
    return merge_sort_helper(arr, 0, arr.size() - 1);
}

// Recursive helper function for Merge Sort
vector<int> merge_sort_helper(vector<int>& arr, int left, int right) {
    if (left >= right) 
        return {arr.begin() + left, arr.begin() + right + 1}; // Single element

    int mid = (left + right) / 2;

    // Recursively sort left and right halves
    vector<int> left_part = merge_sort_helper(arr, left, mid);
    vector<int> right_part = merge_sort_helper(arr, mid + 1, right);

    // Merge sorted halves
    vector<int> result;
    int i = 0, j = 0;
    while (i < left_part.size() && j < right_part.size()) {
        if (left_part[i] <= right_part[j]) result.push_back(left_part[i++]);
        else result.push_back(right_part[j++]);
    }
    while (i < left_part.size()) result.push_back(left_part[i++]);
    while (j < right_part.size()) result.push_back(right_part[j++]);

    return result;
}

// ------------------- Heapsort -------------------
// Sorts a vector using Heapsort (via min-heap).
// Time Complexity: O(n log n). Not stable. 
// Not in-place (in this implementation).
// Uses STL priority_queue to repeatedly extract the minimum element.
vector<int> heapsort(vector<int> arr) {
    priority_queue<int, vector<int>, greater<int>> 
    min_heap(arr.begin(), arr.end());

    vector<int> sorted;
    while (!min_heap.empty()) {
        sorted.push_back(min_heap.top());
        min_heap.pop();
    }
    return sorted;
}

// ------------------- Quicksort -------------------
// Sorts a vector using the Quicksort algorithm.
// Average Time Complexity: O(n log n), Worst-case: O(n^2). 
// Not stable. Not in-place (in this version).
// Pivot is selected from the middle; partitions array into <, =, > pivot.
vector<int> quicksort(vector<int> arr) {
    if (arr.size() <= 1) return arr;

    int pivot = arr[arr.size() / 2];
    vector<int> left, mid, right;

    for (int x : arr) {
        if (x < pivot) left.push_back(x);
        else if (x == pivot) mid.push_back(x);
        else right.push_back(x);
    }

    vector<int> sorted = quicksort(left);
    sorted.insert(sorted.end(), mid.begin(), mid.end());
    vector<int> right_sorted = quicksort(right);
    sorted.insert(sorted.end(), right_sorted.begin(), right_sorted.end());

    return sorted;
}

// ------------------- Performance & Correctness Utilities -------------------

// Measures the execution time of a sorting function in milliseconds.
// Parameters:
// - name: name of the sorting algorithm (for display)
// - data: unsorted input vector
// - sort_func: function pointer to the sorting algorithm
// Returns: a pair containing the sorted vector and the runtime in milliseconds.
pair<vector<int>, long long> measure_sort(const string& name, vector<int> data, vector<int> (*sort_func)(vector<int>)) {
    auto start = high_resolution_clock::now(); // Start timer
    vector<int> result = sort_func(data);      // Execute sorting
    auto end = high_resolution_clock::now();   // End timer

    long long duration = duration_cast<milliseconds>(end - start).count();
    cout << name << ": " << duration << " ms" << endl;

    return {result, duration};
}

// Compares all vectors in the results list to determine if they are identical.
// Returns true if all sorting outputs are the same; false otherwise.
bool all_equal(const vector<vector<int>>& results) {
    for (size_t i = 1; i < results.size(); i++) {
        if (results[i] != results[0]) return false;
    }
    return true;
}

// ------------------- Main Function -------------------
// Entry point of the program.
// - Generates a random vector of integers
// - Sorts the vector using four algorithms
// - Measures and displays execution time for each
// - Verifies correctness by comparing all outputs
int main() {
    const int n = 10000; // Input size; adjust as needed for performance testing
    vector<int> original = generate_random_vector(n); // Generate unsorted input

    vector<vector<int>> results; // Store sorted outputs for comparison

    // Run each sorting algorithm, measure time, and store the result
    results.push_back(measure_sort("Selection Sort", original, selection_sort).first);
    results.push_back(measure_sort("Merge Sort", original, merge_sort).first);
    results.push_back(measure_sort("Heapsort", original, heapsort).first);
    results.push_back(measure_sort("Quicksort", original, quicksort).first);

    // Verify whether all sorted outputs match
    if (all_equal(results)) {
        cout << "All algorithms produced identical sorted results." << endl;
    } else {
        cout << "Mismatch detected in sorting results." << endl;
    }

    return 0;
}