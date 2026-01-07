#include <bits/stdc++.h>
using namespace std;
int inf = 1e9;
vector<vector<int>> grid;
vector<vector<int>> total_dis;
vector<vector<int>> k_count;
int n, m;

pair<int, int> moves[] = {
    {1, 2}, {1, -2}, {2, 1}, {2, -1}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}};

void bfs(int x, int y)
{
    queue<pair<int, int>> q;
    q.push({x, y});
    vector<vector<int>> dis(n, vector<int>(n, -1));
    dis[x][y] = 0;

    while (!q.empty())
    {
        auto u = q.front();
        q.pop();
        int r = u.first, c = u.second;
        total_dis[r][c] += dis[r][c];
        k_count[r][c] += 1;

        for (auto m : moves)
        {
            int f = r + m.first, s = c + m.second;

            if (f >= 0 && f < n && s >= 0 && s < n && dis[f][s] == -1)
            {
                q.push({f, s});
                dis[f][s] = dis[r][c] + 1;
            }
        }
    }
}

void solve()
{
    cin >> n >> m;
    grid.assign(n, vector<int>(n, 0));
    total_dis.assign(n, vector<int>(n, 0));
    k_count.assign(n, vector<int>(n, 0));

    vector<pair<int, int>> knights;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> grid[i][j];
            // FIX: Only add to vector if it is a knight
            if (grid[i][j] == 1)
            {
                knights.push_back({i, j});
            }
        }
    }

    for (auto p : knights)
        bfs(p.first, p.second);

    int min_moves = inf;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (k_count[i][j] == m)
                min_moves = min(min_moves, total_dis[i][j]);
        }
    }

    if (min_moves == inf)
        cout << -1;
    else
        cout << min_moves;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin>>t;
    for (int i = 0; i < t; i++)
    {
        solve();
    }
}