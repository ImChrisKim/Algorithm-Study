#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <queue>
#include <iostream>

using namespace std;

// �ʱ� ���� ���� set
int n;
int area[100][100] = { {} };
int dists[100][100];
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

struct pq_node {
    int r;
    int c;
    int cost;

    bool operator < (pq_node now) const {
        if (cost > now.cost) {
            return true;
        }
        if (cost < now.cost) {
            return false;
        }
        return false;
    }
};

// ���ͽ�Ʈ��
// s���� r���� ���� ��θ� Ž���Ѵ�.
void dikstra(int sr, int sc) {
    priority_queue<pq_node>pq = {};
    pq.push({ sr,sc,0 });

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            dists[r][c] = 21e8;
        }
    }

    dists[sr][sc] = 0;

    while (!pq.empty()) {
        pq_node now = pq.top();
        pq.pop();
        int nr, nc, n_cost;

        if (dists[now.r][now.c] < now.cost) continue;

        for (int i = 0; i < 4; i++) {
            nr = now.r + dr[i];
            nc = now.c + dc[i];

            if (0 > nr || n <= nr || 0 > nc || n <= nc) continue;

            n_cost = dists[now.r][now.c] + area[nr][nc];
            if (dists[nr][nc] <= n_cost) continue;

            dists[nr][nc] = n_cost;
            pq.push({ nr,nc,dists[nr][nc] });
        }
    }

    return;
}

int main() {
    int t = 0;
    cin >> t;

    // ���� ���� �Է�
    for (int tc = 0; tc < t; tc++) {
        cin >> n;

        for (int r = 0; r < n; r++) {
            string tmp;
            cin >> tmp;

            for (int c = 0; c < n; c++) {
                area[r][c] = (int)(tmp[c]-'0');
            }
        }

        // ���� ���� ������� ���������� �� �� �ֵ��� dikstra�� ����Ѵ�.
        dikstra(0, 0);

        cout << "#" << tc + 1 << " " << dists[n-1][n-1] << endl;
    }

    return 0;
}