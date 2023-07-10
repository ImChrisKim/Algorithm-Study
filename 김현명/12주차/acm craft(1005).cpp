#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
int n;
int t;
int k;

struct node {
    int id;
    int cost;
};

struct g_v {
    int to;
};

node build[1002];
vector<int> b_graph[1002];
int dp[1002];

// ��ǥ��� w�κ��� �������� ����.
// �� ��带 �������� ���� ����� �ð������ �ִ븦 ����Ѵ�.
// �ش� �ð���ŭ ��ٷ��ߵǱ� �����̴�.
// �ڱ� �ǹ��� ���� �ð��� �� �ð��� ���ϰ� �ּ� �ð�������� �����Ѵ�. 
int dfs(int now)
{
    if (dp[now] != 21e8)
    {
        return dp[now];
    }

    int max_t = 0;

    for (int s = 0; s < b_graph[now].size(); s++)
    {
        int to = b_graph[now][s];
        max_t = max(max_t, dfs(to));
    }

    dp[now] = min(dp[now], build[now].cost + max_t);
    return dp[now];
}

int main() {
    cin >> t;
    // ���� ���
    int w;

    for (int tc = 0; tc < t; tc++)
    {
        cin >> n >> k;
        memset(b_graph, 0, sizeof(b_graph));

        // �� �ǹ� ����� ����� �����ϱ�
        for (int i = 0; i < n; i++)
        {
            build[i+1].id = i+1;
            cin >> build[i+1].cost;
        }

        // �ǹ� ��庰 ���� ������ϴ� ��带 �����Ѵ�.
        // ��ǥ���� w�̴�.
        // ��� �ش� ���κ��� Ǯ����ϴ� �͵��� ����
        // �Ǳ� ������ �ܹ������� �����Ѵ�.
        for (int i = 0; i < k; i++)
        {
            int a, b;
            cin >> a >> b;
            b_graph[b].push_back(a);
        }

        cin >> w;

        // �� ������ ���� ���� �ǹ��� ���� �ִ� �ð��� ����ȴ�.
        // �� ���� ���� �ǹ������� ���ǹǷ� ����ؼ� ����Ѵ�.
        for (int i = 0; i < n+1; i++)
        {
            dp[i] = 21e8;
        }

        // �ǹ�w�� ���� �ּ� �ð�
        int min_time = dfs(w);
        cout << min_time << endl;
    }

    return 0;
}