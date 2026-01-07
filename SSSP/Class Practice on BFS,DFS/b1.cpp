#include <bits/stdc++.h>
using namespace std;

// Direction arrays (Up, Down, Left, Right)
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Global grid to avoid passing it in recursion (common in CP)
vector<vector<int>> grid;
int m, n;

void dfs(int r, int c) {
    // Mark current cell as visited (set to 1)
    grid[r][c] = 1;

    // Check all 4 directions
    for (int i = 0; i < 4; i++) {
        int nr = r + dx[i];
        int nc = c + dy[i];

        // NO boundary check needed here!
        // The padding guarantees 'nr' and 'nc' are always valid indices.
        // We only check if the neighbor is a valid path (0).
        if (grid[nr][nc] == 0) {
            dfs(nr, nc);
        }
    }
}

void solve() {
    cin >> m >> n;

    // 1. Create grid of size (M+2) x (N+2)
    // Initialize EVERYTHING to 1 (blocked/visited)
    grid.assign(m + 2, vector<int>(n + 2, 1));

    // 2. Read input into the center of the grid (1-based indexing)
    // This leaves row 0, row m+1, col 0, and col n+1 as "1"
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int val;
            cin >> val;
            // Only update if it's a 0 (path). 
            // If input is 1, it matches our initialization anyway.
            if (val == 0) {
                grid[i][j] = 0;
            }
        }
    }

    int components = 0;

    // 3. Iterate only through the valid inner area
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            // If we find an unvisited path (0)
            if (grid[i][j] == 0) {
                components++;
                dfs(i, j);
            }
        }
    }

    cout << components << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}