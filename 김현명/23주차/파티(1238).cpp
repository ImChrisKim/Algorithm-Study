#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// x -> ���� ���

int n, m;
int t_v;

struct r_no {
    int to_v;
    int ct;

    bool operator < (r_no n_v) const {
        if (ct > n_v.ct)
        {
            return true;
        }
        if (ct < n_v.ct)
        {
            return false;
        }
        return false;
    }
};

vector<r_no> for_gp[1002];
vector<r_no> back_gp[1002];

int s_dists[1002];

// �л����� ��Ƽ��ҿ� ���� ���� ���
void for_count() {
    int dists[1002] = {};

    for (int i = 0; i < n + 1; i++)
    {
        dists[i] = 10e8;
    }
    dists[t_v] = 0;

    priority_queue<r_no> pq = {};
    pq.push({ t_v,0 });

    while (!pq.empty())
    {
        r_no n_no = pq.top();
        pq.pop();

        if (dists[n_no.to_v] < n_no.ct) { continue; }
        
        int to_v = 0;
        int to_ct = 0;
        for (int s = 0; s < for_gp[n_no.to_v].size(); s++)
        {
            to_v = for_gp[n_no.to_v][s].to_v;
            to_ct = dists[n_no.to_v] + for_gp[n_no.to_v][s].ct;
            if (dists[to_v] < to_ct) { continue; }
            dists[to_v] = to_ct;

            pq.push({ to_v, to_ct });
        }
    }

    // ��� �����ϱ�
    for (int i = 1; i < n + 1; i++)
    {
        s_dists[i] += dists[i];
    }

    return;
}

// �л����� ��Ƽ ��ҷ� ���� ���
void back_count()
{
    int dists[1002] = {};

    for (int i = 0; i < n + 1; i++)
    {
        dists[i] = 10e8;
    }
    dists[t_v] = 0;

    priority_queue<r_no> pq = {};
    pq.push({ t_v,0 });

    while (!pq.empty())
    {
        r_no n_no = pq.top();
        pq.pop();

        if (dists[n_no.to_v] < n_no.ct) { continue; }

        int to_v = 0;
        int to_ct = 0;
        for (int s = 0; s < back_gp[n_no.to_v].size(); s++)
        {
            to_v = back_gp[n_no.to_v][s].to_v;
            to_ct = dists[n_no.to_v] + back_gp[n_no.to_v][s].ct;
            if (dists[to_v] < to_ct) { continue; }
            dists[to_v] = to_ct;

            pq.push({ to_v, to_ct });
        }
    }

    // ��� �����ϱ�
    for (int i = 1; i < n + 1; i++)
    {
        s_dists[i] += dists[i];
    }

    return;
}

int main() {
    cin >> n >> m >> t_v;

    // ������ �׷������� t_v������ ��θ� �� �� �ִ�.
    // �����⿡���� �л����� ��Ƽ��ҿ��� ���ƿ��� ����� ���� �� �ִ�.
    // �л���� t_v������ �ּ� ���, t_v���� �л�������� �ּ� ��θ� ���Ѵ�.
    // ���� �� ��쿡���� �ּҺ���� ���ϰ� dists�� �����Ѵ�.
    int a, b, ct;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> ct;
        for_gp[a].push_back({ b,ct });
        back_gp[b].push_back({ a,ct });
    }

    // �� ����� �ּ� ����� ���Ѵ�.
    for_count();
    back_count();

    // �л����� �պ� ��� �� �ִ� ���� ���Ѵ�.
    int max_dist = 0;
    for (int i = 1; i < n + 1; i++)
    {
        if (max_dist < s_dists[i])
        {
            max_dist = s_dists[i];
        }
    }

    cout << max_dist << endl;

    return 0;
};