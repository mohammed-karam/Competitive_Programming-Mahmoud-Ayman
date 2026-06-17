#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <set>
#include <iomanip>

using namespace std;

// Struct to hold point data, including original index
struct Point {
    double x, y;
    int id; // Original index in the input array
};

// 1. Sort primarily by X-coordinate for the sweep line
bool compareX(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y; // Tie-breaker
}

// 2. Custom comparator for our 'active window' set to sort by Y-coordinate
struct compareY {
    bool operator()(const Point& a, const Point& b) const {
        if (a.y != b.y) return a.y < b.y;
        return a.x < b.x; // Tie-breaker to ensure points with same Y aren't treated as identical
    }
};

// Standard Euclidean distance
double get_dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void solve() {
    int n;
    if (!(cin >> n)) return;
    
    vector<Point> pts(n);
    for (int i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].id = i; // Save original index (0-based)
    }

    // Sort all points from left to right
    sort(pts.begin(), pts.end(), compareX);

    // Our active window stored in a balanced BST
    set<Point, compareY> active_set;
    
    double min_d = 1e18; // Start with a massive distance
    int best_i = -1, best_j = -1;
    
    int left = 0; // The left boundary pointer of our sweeping window
    
    for (int i = 0; i < n; i++) {
        // Step A: Shrink the window
        // Remove points from the set that are too far to the left to possibly form a closer pair
        while (left < i && pts[i].x - pts[left].x >= min_d) {
            active_set.erase(pts[left]);
            left++;
        }
        
        // Step B: Check Y-bounds
        // We only care about points in the set whose Y is between [pts[i].y - min_d, pts[i].y + min_d]
        Point search_point = {pts[i].x, pts[i].y - min_d, -1};
        auto it = active_set.lower_bound(search_point); // Find lowest valid Y
        
        while (it != active_set.end() && it->y - pts[i].y < min_d) {
            double current_d = get_dist(pts[i], *it);
            
            // Step C: Update if we found a strictly closer pair
            if (current_d < min_d) {
                min_d = current_d;
                best_i = pts[i].id;
                best_j = it->id;
            }
            it++;
        }
        
        // Step D: Add the current point into the active window
        active_set.insert(pts[i]);
    }
    
    // The problem requires outputting indices in order (a < b)
    if (best_i > best_j) swap(best_i, best_j);
    
    // Output formatted to 6 decimal places as requested
    cout << best_i << " " << best_j << " " << fixed << setprecision(6) << min_d << "\n";
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
    
    return 0;
}
