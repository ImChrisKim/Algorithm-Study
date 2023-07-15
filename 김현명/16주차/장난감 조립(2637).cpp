#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// �ʿ��� ����
// ���� ��ǰ ��ȣ, ���ϴ� ��

int n, m;
int pros_t[102];

struct p_no {
    int to;
    int cnt;
};

vector <p_no> p_gp[102];
vector <int> base_ts;
queue <int> ts_com;

int base_ca[102][102];
int base_num[102];
int base_vi[102];

int main() {
    // ��ǰ��ȣ, ���� ��
    cin >> n;
    cin >> m;

    // ��ǰ x�� y�� k�� ����.
    // �� �� y�� x���� ���� �׷���, x��ǰ�� �߿䵵 ���� ����Ѵ�.

    for (int i = 0; i < m; i++)
    {
        int x, y, k;
        cin >> x >> y >> k;
        p_gp[y].push_back({ x,k });
        pros_t[x] += 1;
    }

    // base_ts: �⺻ ��ǰ�� �����Ѵ�.
    for (int i = 1; i < n + 1; i++)
    {
        if (pros_t[i] == 0) {
            base_ts.push_back(i);
        }
    }

    // �� ��ǰ���� �⺻ ��ǰ ������ ����� ����Ѵ�.
    // �⺻ ��ǰ �� �����ϱ�
    for (int j = 0; j < base_ts.size(); j++)
    {
        base_ca[base_ts[j]][base_ts[j]] = 1;
    }

    // ���� ����
    // �⺻ ��ǰ���� �ش� ��ǰ���� ä�� �� �ִ� ��ǰ���� ã�ư���.
    // �ش� ��ǰ�� �⺻ ��ǰ���� ����ϰ� �߿䵵���� ���ҽ�Ų��.
    // �߿䵵���� 0�� �Ǹ� �ش� ��ǰ�� ����Ѵ�.

    while (!ts_com.empty())
    {
        int n_t = ts_com.front();
        ts_com.pop();

        int to_t = 0;
        int to_cnt = 0;

        for (int i = 0; i < p_gp[n_t].size(); i++)
        {
            to_t = p_gp[n_t][i].to;
            to_cnt = p_gp[n_t][i].cnt;

            for (int j = 0; j < base_ts.size(); j++)
            {
                if (base_ca[n_t][base_ts[j]] == 0) continue;
                base_ca[to_t][base_ts[j]] += base_ca[n_t][base_ts[j]] * to_cnt;
                
            }
            pros_t[to_t] -= 1;

            if (pros_t[to_t] == 0) {
                ts_com.push(to_t);
            }
        }

    }

    // ����ǰ�� �⺻ ǰ��� �����ϱ�
    for (int i = 0; i < base_ts.size(); i++)
    {
        base_num[base_ts[i]] = base_ca[n][base_ts[i]];
    }

    // ��ǰ��ȣ �����ͺ��� �� ����ϱ�
    for (int i = 1; i < 102; i++)
    {
        if (base_num[i] == 0) continue;
        cout << i << " " << base_num[i] << "\n";
    }

    return 0;
};