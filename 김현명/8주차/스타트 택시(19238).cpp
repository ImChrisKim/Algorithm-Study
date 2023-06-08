#define _CRT_SECURE_NO_WARNINGS

#include <queue>
#include <iostream>

using namespace std;

// ���� ���� ����
// �ý� ��ġ ����
int n, m;
int road[20][20];
int tr, tc;

// ���� ��, �ӹ� ���� ���� ���� ����
int f_num;
bool possible = true;

// �°� �̵� ����
struct m_node {
    int sr;
    int sc;
    int er;
    int ec;
    bool done;
};

// � �°����� ������ ���Ҷ� ����Ѵ�.
struct p_node {
    int sr;
    int sc;
    int er;
    int ec;
    int id;

    bool operator < (p_node now) const {
        if (sr > now.sr) {
            return true;
        }
        if (sr < now.sr) {
            return false;
        }
        if (sc > now.sc) {
            return true;
        }
        if (sc < now.sr) {
            return false;
        }
        return false;
    }
};

// ��, �� ������ ���� ����ϴ� �ڷᱸ��
priority_queue<p_node> s_m_info;

// ���� �°� �̵� ���� ����
m_node ori_m_info[400];

int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

struct node {
    int r;
    int c;
};

int move_to(int er, int ec) {
    queue<node> q;
    q.push({ tr,tc });

    int vi[20][20] = { {} };
    vi[tr][tc] = 1;

    if (tr == er && tc == ec) {
        return 0;
    }

    while (!q.empty()) {
        node now = q.front();
        q.pop();

        int nr, nc;

        for (int i = 0; i < 4; i++) {
            nr = now.r + dr[i];
            nc = now.c + dc[i];

            if (0 > nr || n <= nr || 0 > nc || n <= nc) continue;
            if (road[nr][nc] == 1) continue;
            if (vi[nr][nc] != 0) continue;

            vi[nr][nc] = vi[now.r][now.c] + 1;

            if (nr == er && nc == ec) {
                return vi[nr][nc] - 1;
            }

            q.push({ nr,nc });
        }
    }
    return -1;
};

// �ý���ġ���� ���� ����� �°����� ã�´�.
// ����� �Ÿ� ���� ����ϰ� �̵��Ѵ�.
// �°���ġ�� �̵� ��, �ش� ���� ��ǥ�������� �̵��Ѵ�. 
// ���� ������ �����Ѵ�.
void t_move() {
    // �� �� ���ǿ� �°� �켱����ť�� �����Ѵ�.
    priority_queue<p_node> q_m_info = {};

    for (int i = 0; i < m; i++) {
        q_m_info.push({ ori_m_info[i].sr ,ori_m_info[i].sc ,ori_m_info[i].er ,ori_m_info[i].ec ,i });
    }

    // �Ÿ����� ����
    int min_dist = 21e8;

    // �°���ġ: nr,nc
    // ��ǥ��ġ: nr2,nc2
    int nr = -1;
    int nc = -1;
    int nr2 = -1;
    int nc2 = -1;

    int id = 0;

    // ���� ������ ���� ���ǿ� �´� �°��� ã�´�.
    while (!q_m_info.empty()) {
        p_node now = q_m_info.top();
        q_m_info.pop();

        // �ӹ� ���� �ȵ� �°��� ����Ѵ�.
        if (ori_m_info[now.id].done == true) continue;
        int er, ec;
        er = now.sr;
        ec = now.sc;

        // �Ÿ� ���
        int dist = move_to(er, ec);

        // ���� ����� �°� ���� �����ϱ�
        if (dist != -1 && dist < min_dist) {
            nr = er;
            nc = ec;
            min_dist = dist;
            id = now.id;

            nr2 = now.er;
            nc2 = now.ec;
        }
    }

    // �� ��ġ�� �̵� ���������� ����.
    if (nr == -1 && nc == -1)
    {
        possible = false;
        return;
    }

    // ������� ����Ѵ�.
    if (f_num <= min_dist) {
        possible = false;
        return;
    }

    // ������ �°� ���� ����
    ori_m_info[id].done = true;
    f_num -= min_dist;
    
    // ��ǥ�� �̵��ϱ�
    tr = nr;
    tc = nc;

    int dist2 = move_to(nr2, nc2);

    // ���� ���� ��� �� �����ϱ�
    if (dist2 == -1 || f_num - dist2 < 0)
    {
        possible = false;
        return;
    }

    f_num += dist2;
    tr = nr2;
    tc = nc2;

};

int main() {
    cin >> n >> m >> f_num;

    // ���� ���� �Է�
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin >> road[r][c];
        }
    }

    // m�� �ӹ� ����
    // �ý� ��ġ �Է�
    int m_num = m;
    cin >> tr >> tc;
    tr -= 1;
    tc -= 1;

    // �°� �̵� ���� ����
    for (int i = 0; i < m; i++) {
        int sr, sc, er, ec;
        cin >> sr >> sc >> er >> ec;

        sr -= 1;
        sc -= 1;
        er -= 1;
        ec -= 1;

        ori_m_info[i] = { sr, sc, er, ec,false };
    }

    // m�� �ӹ��� �����Ѵ�.
    // �ӹ� ������ �����ϴٸ� ��� �����Ѵ�.
    while (m_num > 0) {
        t_move();
        m_num -= 1;
        if (possible == false) {
            break;
        }
    }

    if (possible == false) {
        cout << -1 << endl;
    }
    else if (possible == true) {
        cout << f_num << endl;
    }
   return 0;
}