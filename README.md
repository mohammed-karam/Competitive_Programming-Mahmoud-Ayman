# SegmentTree-Codeforces-EDU

- sparse table 
![image](https://github.com/user-attachments/assets/1b0670c8-b2f2-4b5b-afb9-52bfaff374ee)

![image](https://github.com/user-attachments/assets/cdeb0a53-7a6a-4774-9186-7543bbeb0690)

# Ordered Set and Multiset
```
✅ Purpose of the Template
This template is used to efficiently compute things like:

Number of elements less than a given value (order_of_key)

K-th smallest/largest element (find_by_order)

Support for multisets (with duplicates allowed)

🔍 Key Components:
- PBDS headers: 
  #include <ext/pb_ds/assoc_container.hpp>
  #include <ext/pb_ds/tree_policy.hpp>
  using namespace __gnu_pbds;

- ordered_set:
  #define ordered_set tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update>
  This behaves like std::set but supports order statistics (no duplicates).

- ordered_multiset:
  typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
  This version allows duplicates and supports the same operations.

🎯 Why Is It Used in Your Code?
To compute how many elements before a value are strictly less than it:
    sum += st.order_of_key(x);
This is done in O(log n), unlike std::multiset which would need linear time or extra effort.

💡 Summary of Advantages:
- Insertion: O(log n)
- Deletion: O(log n)
- find_by_order(k): O(log n)
- order_of_key(x): O(log n)
- Duplicates support: ✅ (only with less_equal)
- STL Equivalent: ❌ Not available in STL

⚠️ Notes:
- Only works with GCC/G++ (libstdc++).
- Not supported in MSVC or Clang by default.
- May be slow or unstable with very large input sizes in some online judges.
```



