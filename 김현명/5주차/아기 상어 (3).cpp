#define _CRT_SECURE_NO_WARNINGS

#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;

// �⺻ ���� ����
int n;
int sea[20][20];
int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

// �켱���� ť ����ϱ�
struct node {
    int r;
    int c;
};

struct pq_node {
    int r;
    int c;
    int dist;

    bool operator < (pq_node now) const {
        if (dist > now.dist) {
            return true;
        }
        if (dist < now.dist) {
            return false;
        }
        return false;
    }
};


// ��� ����
// ��� ��ġ, ���� ũ��, ���� ����
int shark_r, shark_c;
int s_size;
int s_eat;

// ���� �����, ���� ���������� �Ÿ�, ���� �ð�
int fish_num;
int fish_dist;
int w_time;


// ����� Ž��
// ���� ������� �۰ų� ���ٸ� �̵� �����ϴ�.
// ���� ������� ������ target���� ���� �����ϴ�.
pq_node detect_path(int sr, int sc, int tr, int tc) {
    queue<node>q = {};
    q.push({ sr,sc });
    int visited[20][20] = { {} };

    visited[sr][sc] = 1;

    while (!q.empty()) {
        node now = q.front();
        q.pop();

        // �������� �� �� �ִ� ��� �Ÿ��� �Բ� return�Ѵ�.
        if (now.r == tr && now.c == tc) {
            int now_dist = visited[now.r][now.c] - 1;
            return {tr,tc,now_dist};
        }

        int nr, nc;
        for (int i = 0; i < 4; i++) {
            nr = now.r + dr[i];
            nc = now.c + dc[i];

            if (0 > nr || n <= nr || 0 > nc || n <= nc) continue;
            if (visited[nr][nc] != 0) continue;
            if (s_size < sea[nr][nc]) continue;

            visited[nr][nc] = visited[now.r][now.c] + 1;
            q.push({ nr,nc });
        }
    }

    return { -1,-1,-1 };
}

// ��� ����ϱ�
void go_shark() {
    // ���� �� �ִ� ����� Ž��
    // �ش� ����⸦ ���� �� �ִٸ� �켱���� ť�� dist�� �Բ� �����Ѵ�.
    priority_queue<pq_node>pq = {};

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (0 < sea[r][c] && s_size > sea[r][c]) {
                pq_node tmp;
                tmp = detect_path(shark_r, shark_c, r, c);

                if (tmp.dist == -1) continue;
                
                pq.push(tmp);
            }
        }
    }

    // �Ÿ��� ���� ����� ������ ���� ����
    // ��� ��ǥ, ��ü�ð�, ���size, ��� �������� ����
    // ����⸦ �ٸԾ��ٸ� return�Ѵ�.
    if (!pq.empty()) {
        pq_node now = pq.top();
        shark_r = now.r;
        shark_c = now.c;

        w_time += now.dist;
        fish_num -= 1;
        s_eat += 1;

        if (s_eat >= s_size) {
            s_size += 1;
            s_eat = 0;
        }

        if (fish_num == 0) {
            return;
        }

        sea[shark_r][shark_c] = 0;
        
        go_shark();
    }
}

int main() {
    // ��� size �ʱ�ȭ
    cin >> n;
    s_size = 2;

    // �����, ��� ���� �Է�
    // fish_num�� ����⸦ �� ������ �ٷ� return�Ҷ� ����Ѵ�.
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin >> sea[r][c];

            if (0 < sea[r][c] && 9 != sea[r][c]) {
                fish_num += 1;
            }
            // �����ġ ���� ����, ��ǥ�� Ȱ��
            else if (9 == sea[r][c]) {
                shark_r = r;
                shark_c = c;
                sea[r][c] = 0;
            }
        }
    }

    // Ž��
    go_shark();

    // ���
    cout << w_time << endl;

    return 0;
}