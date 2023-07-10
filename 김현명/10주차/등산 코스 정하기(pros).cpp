#include <algorithm>
#include <queue>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int n;

// �켱����ť(min heap) �����ϱ�
struct p_node {
    int cost;
    int to;

    bool operator < (p_node now) const
    {
        if (cost > now.cost)
        {
            return true;
        }
        if (cost < now.cost)
        {
            return false;
        }
        return false;
    }
};

// �׷����� �Ÿ� ����
priority_queue<p_node> pq;
vector<p_node> graph[50002];
int dists[50002];

int sum_vi[50002];

// �ּ� intensity, �������
int min_i = 21e8;
int min_v = 21e8;

// ������ ��� ��� ��θ� ����Ѵ�.
// ��� ��� �� ���� �� intensity�� ����Ѵ�.
// �� ��� ��δ� �ּ� intensity�� ��ǥ�� �Ѵ�.
void dikstra(vector<int>& gates)
{
    // �Ÿ� ���� �ʱ�ȭ
    for (int i = 0; i < n + 1; i++)
    {
        dists[i] = 21e8;
    }

    // ���� ���� ����
    for (int g : gates)
    {
        dists[g] = 0;
    }

    // ��� ��θ� ����.
    while (!pq.empty())
    {
        p_node now = pq.top();
        pq.pop();
        int now_v = now.to;
        int cost = now.cost;

        if (dists[now_v] < cost) continue;

        // ��� ������ ������ ����̴�.
        // ���� �ּ� intensity, ��������� ����Ѵ�.
        // ��� ������ �����ϰ� ������ �� ������� �ʴ´�.
        if (sum_vi[now_v] == 1)
        {
            if (min_i >= dists[now_v]) {

                if (min_v > now_v) {
                    min_i = dists[now_v];
                    min_v = now_v;
                }
            }
            continue;
        }

        // ��� ��ο��� intensity�� ����Ѵ�.
        // �� ��, intensity�� ���� �� �ð��̴�.
        for (int s = 0; s < graph[now_v].size(); s++)
        {
            p_node next = graph[now_v][s];
            int n_cost = max(cost, next.cost);

            if (dists[next.to] <= n_cost) continue;
            dists[next.to] = n_cost;
            pq.push({ n_cost, next.to });
        }
    }
    return;
}

vector<int> solution(int n_size, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<int> answer;

    n = n_size;

    // ��� ���� ���� �Է� �ޱ�
    // ���δ� ������̴�.
    for (vector<int> v : paths)
    {
        graph[v[0]].push_back({ v[2],v[1] });
        graph[v[1]].push_back({ v[2],v[0] });
    }

    // ���� ��������� ������ ��� ��θ� ����.
    // �켱���� ť�� ���� �־��ش�.
    for (int g : gates)
    {
        pq.push({ 0,g });
    }

    // ��� �������� �����ϱ�
    for (int s : summits)
    {
        sum_vi[s] = 1;
    }

    // ��� ��� ��ο��� �ּ� intensity���� ����Ѵ�.
    dikstra(gates);
    answer = { min_v, min_i };
    return answer;
}