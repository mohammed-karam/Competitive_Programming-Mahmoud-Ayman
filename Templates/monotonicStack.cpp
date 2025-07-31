#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'

vector<int> nextGreaterElements(const vector<ll> &nums) {
    int n = nums.size();
    vector<int> result(n, -1); // initialize result with -1
    stack<int> st; // stack to store **indices**

    for (int i = 0; i < n; ++i) {
        // While current element is greater than the top element's value
        while (!st.empty() && nums[i] > nums[st.top()]) {
            result[st.top()] = nums[i]; // current element is next greater
            st.pop();
        }
        st.push(i); // push current index
    }

    return result;
}

vector<int> nextSmallerElements(const vector<int> &nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st; // Stack stores indices

    for (int i = 0; i < n; ++i) {
        // While current is smaller than stack top
        while (!st.empty() && nums[i] < nums[st.top()]) {
            result[st.top()] = nums[i];
            st.pop();
        }
        st.push(i); // Push current index
    }

    return result;
}

vector<int> previousSmallerElements(const vector<int> &nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st;

    for (int i = 0; i < n; ++i) {
        // Pop all elements greater than or equal to current
        while (!st.empty() && st.top() >= nums[i]) {
            st.pop();
        }

        // If stack is not empty, top is the previous smaller
        if (!st.empty()) {
            result[i] = st.top();
        }

        // Push current element to be a candidate for next values
        st.push(nums[i]);
    }

    return result;
}

vector<int> previousGreaterElements(const vector<ll> &nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st;

    for (int i = 0; i < n; ++i) {
        // Pop elements smaller than or equal to current
        while (!st.empty() && st.top() <= nums[i]) {
            st.pop();
        }

        // If stack is not empty, top is previous greater
        if (!st.empty()) {
            result[i] = st.top();
        }

        // Push current element for future elements to use
        st.push(nums[i]);
    }

    return result;
}


