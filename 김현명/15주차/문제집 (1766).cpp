#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n, m;
int p_pros[32002];
vector<int> p_gp[32002];
vector<int> p_pa;

struct p_no {
    int pn;

    bool operator < (p_no now) const {
        if (pn > now.pn) {
            return true;
        }
        if (pn < now.pn) {
            return false;
        }
        return true;
    }
};

int main() {
    cin >> n >> m;
    int a, b;

    // ������ �������踦 �����Ѵ�.
    // ������ �̸� Ǯ��ߵǴ� ���� ���� �����Ѵ�.

    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        p_gp[a].push_back(b);
        p_pros[b] += 1;
    }

    // ���� ���� ���� ���� ���, ���̵��� ����ͺ��� �������� �켱����ť�� ����Ѵ�.
    priority_queue<p_no> pq = {};
    for (int i = 1; i < n + 1; i++)
    {
        if (p_pros[i] == 0)
        {
            pq.push({ i });
        }
    }

    // ���� ���̵� �������� Ǯ�� ����Ѵ�.
    // �ش� ������ Ǭ ���, �� ������ ������ ������ �߿䵵�� ���ҽ�Ų��.
    // 0�� �Ǹ� ��ť�� �����Ѵ�.
    int n_p;
    while (!pq.empty())
    {
        n_p = pq.top().pn;
        pq.pop();

        p_pa.push_back(n_p);
        int to_p;
        for (int i = 0; i < p_gp[n_p].size(); i++)
        {
            to_p = p_gp[n_p][i];
            p_pros[to_p] -= 1;
            if (p_pros[to_p] == 0) {
                pq.push({ to_p });
            }
        }
    }

    for (int i = 0; i < p_pa.size(); i++)
    {
        cout << p_pa[i] << " ";
    }

    return 0;
};