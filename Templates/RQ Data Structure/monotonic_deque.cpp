


// to get the max element in each segment of size k 


#include <iostream>
#include <vector>
#include <deque>

using namespace std;

// The reusable Monotonic Deque template
template <typename T>
struct MonotonicDeque {
    deque<int> dq;
    const vector<T>& arr; // Reference to the original array

    // Constructor requires the array we are processing
    MonotonicDeque(const vector<T>& a) : arr(a) {}

    // 1. Add a new index to the window
    void push(int idx) {
        // Pop from the back if the current value is greater than or equal to the back value
        while (!dq.empty() && arr[dq.back()] <= arr[idx]) {
            dq.pop_back();
        }
        dq.push_back(idx);
    }

    // 2. Remove indices that have fallen out of the left side of the window
    void remove_out_of_bounds(int left_bound) {
        while (!dq.empty() && dq.front() < left_bound) {
            dq.pop_front();
        }
    }

    // 3. Get the maximum value in the current window
    T get_max() {
        // The maximum is always at the front
        return arr[dq.front()];
    }
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 1. Define your array and window size
    vector<int> nums = {4, 1, 3, 5, 2, 7, 6};
    int k = 3;

    cout << "Array: ";
    for (int num : nums) cout << num << " ";
    cout << "\nWindow size: " << k << "\n\n";

    cout << "Sliding Window Maximums: ";

    // 2. Initialize the struct with your array
    int n = nums.size();
    MonotonicDeque<int> window(nums);

    // 3. Slide the window across the array
    for (int i = 0; i < n; i++) {
        // Add the current element's index
        window.push(i);

        // Remove any index that is no longer in the window of size k
        window.remove_out_of_bounds(i - k + 1);

        // Once our window has reached at least size k, print the maximum
        if (i >= k - 1) {
            cout << window.get_max() << " ";
        }
    }
    
    cout << "\n";

    return 0;
}
