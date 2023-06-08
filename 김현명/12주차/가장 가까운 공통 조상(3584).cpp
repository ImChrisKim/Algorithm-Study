#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int t;
int n;
int r_v;
int t_v1, t_v2;

vector<int> t_graph[10002];
vector<int> f_graph[10002];

struct node {
    int lev;
    bool v1_f;
    bool v2_f;
};

node dp[10002];

// �θ��忡�� �ڽĳ����� Ž���Ѵ�.
// ��ǥ��带 �����ٸ� �ش� ��ο� �̸� ����Ѵ�.
// lev���� ����Ѵ�.
node c_find(int v, int lev)
{
    if (v == t_v1)
    {
        dp[v].v1_f = true;
    }
    if (v == t_v2)
    {
        dp[v].v2_f = true;
    }

    if (dp[v].lev != -1)
    {
        return dp[v];
    }

    dp[v].lev = lev;

    // ������ ��尡 ��ǥ��带 ã�Ҵ����� ����.
    for (int s = 0; s < t_graph[v].size(); s++)
    {
        int to = t_graph[v][s];
        node now = c_find(to, lev+1);
        if (now.v1_f == true) {
            dp[v].v1_f = true;
        }
        if (now.v2_f == true) {
            dp[v].v2_f = true;
        }
    }

    return dp[v];
}

// ��Ʈ ��带 ã�´�.
// �θ� ��尡 ������������ ����.
void p_find(int v)
{
    bool em_p = false;

    for (int s = 0; s < f_graph[v].size(); s++)
    {
        int to = f_graph[v][s];
        em_p = true;
        p_find(to);
    }

    if (em_p == false) {
        r_v = v;
        return;
    }
}
int main() {
    cin >> t;
    for (int tc = 0; tc < t; tc++)
    {
        cin >> n;
        memset(t_graph, 0, sizeof(t_graph));
        memset(f_graph, 0, sizeof(f_graph));

        // �θ� -> �ڽ� �׷���: t_graph
        // �ڽ� -> �θ� �׷���: f_graph
        for (int i = 0; i < n-1; i++)
        {
            int p, c;
            cin >> p >> c;
            t_graph[p].push_back(c);
            f_graph[c].push_back(p);
        }

        // ��ǥ ���
        cin >> t_v1 >> t_v2;

        // ��Ʈ ��带 ã�´�.
        // ���� ���κ��� �θ� ������������ ����.
        p_find(n);

        // ����Ҹ� �ʱ�ȭ�Ѵ�.
        for (int i = 0; i < n + 1; i++)
        {
            dp[i].lev = -1;
            dp[i].v1_f = false;
            dp[i].v2_f = false;
        }

        // �θ���κ��� �����ؼ� ��ǥ�������� Ž���Ѵ�.
        // �� �� ��ǥ��忡 �����ߴٸ� �ش� ��ο� �̸� ����Ѵ�.
        // ���� �� ��忡�� lev�� ����Ѵ�.
        // �� ������� ���� ���� ���� ������ ���Ѵ�.
        c_find(r_v,1);
        
        // ���� ������ ���� ���� ã��
        int f_v = 0;
        int max_l = 0;

        for (int i = n; i > 0; i--)
        {
            if (dp[i].v1_f == true && dp[i].v2_f == true)
            {
                if (dp[i].lev > max_l)
                {
                    f_v = i;
                    max_l = dp[i].lev;
                }
            }
        }
        cout << f_v << endl;
    }
    return 0;
}