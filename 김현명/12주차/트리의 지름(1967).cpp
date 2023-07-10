#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n;
int max_w;
int t_v;

struct node {
	int to;
	int weight;
};

vector<node> graph[10002];
int vi[10002];

// Ư�� ��忡�� ���� �� ������ ã�´�.
// Ʈ���� �׷����� ������ ����Ѵ�.
// ��, ���� ��θ� �� �ʿ䰡 ����.
void dfs(int v, int w)
{
	for (int i = 0; i < graph[v].size(); i++)
	{
		node now = graph[v][i];
		if (vi[now.to] == 1) continue;

		if (w + now.weight > max_w)
		{
			max_w = w + now.weight;
			t_v = now.to;
		}

		vi[now.to] = 1;
		dfs(now.to, w + now.weight);

	}

	return;
}

int main() {
	cin >> n;

	// Ʈ�� ������ ���� �׷����� �Է¹ޱ�
	// ������̴�.
	for (int i = 0; i < n - 1; i++)
	{
		int now, to, w;

		cin >> now >> to >> w;
		now -= 1;
		to -= 1;
		graph[now].push_back({ to, w });
		graph[to].push_back({ now, w });
	}

	// Ʈ���� ������ �̿��Ѵ�.
	// Ư�� ��忡�� ���� �հŸ��� �ִ� ��带 ã�´�.
	// �ش� ���� Ʈ���� ���� �ٱ� �����̴�.
	// �ش� �������κ��� ���� �հŸ��� ã�´�.
	vi[0] = 1;
	dfs(0, 0);
	memset(vi, 0, sizeof(vi));

	// ó�� ���� �������κ��� ���� �� ��� ã��
	max_w = 0;
	vi[t_v] = 1;
	dfs(t_v, 0);

	cout << max_w << endl;
	return 0;
}