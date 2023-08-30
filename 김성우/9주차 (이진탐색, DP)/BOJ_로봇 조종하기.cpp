#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int Min = -9999999;

int n, m;
int map[1005][1005];
int dr[] = {1, 0, 0};
int dc[] = {0, -1, 1};
int dp[1005][1005][3]; // dp[i] : 가치, i : 이동 횟수
int visited[1005][1005];
int ans;

int recursive(int row, int col, int dir)
{

    // 기저 조건
    if (row == n - 1 && col == m - 1)
    {
        return map[row][col];
    }

    if (dp[row][col][dir] != -1)
        return dp[row][col][dir];
    dp[row][col][dir] = Min;
    visited[row][col] = 1;

    // 재귀 조건
    for (int i = 0; i < 3; i++)
    {
        int nr = row + dr[i];
        int nc = col + dc[i];

        if (nr < 0 || nc < 0 || nr >= n || nc >= m)
            continue;

        if (visited[nr][nc] == 1)
            continue;

        dp[row][col][dir] = max(dp[row][col][dir], recursive(nr, nc, i) + map[row][col]);
    }
    visited[row][col] = 0;

    return dp[row][col][dir];
}

void sol()
{

    visited[0][0] = 1;

    memset(dp, -1, sizeof(dp));

    ans = recursive(0, 0, 0);
}

void input()
{

    cin >> n >> m;
    // n - 1, m - 1이 목적지
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
        }
    }
}

int main()
{

    input();

    sol();

    cout << ans;
}