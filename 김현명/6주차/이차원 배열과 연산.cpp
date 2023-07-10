#define _CRT_SECURE_NO_WARNINGS

#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

// �迭 ���� ����
int n, m, k;
int board[100][100];

struct pq_node {
    int n;
    int freq;

    bool operator < (pq_node now) const {
        if (freq > now.freq) {
            return true;
        }
        if (freq < now.freq) {
            return false;
        }
        if (n > now.n) {
            return true;
        }
        if (n < now.n) {
            return false;
        }
        return false;

    }
};


int max_r;
int max_c;

// c �����ϱ�
// �� ������ �󵵼� ������ DAT�� Ȱ���Ѵ�.
// ���� �󵵼�, ���� ũ�� ���� �켱����ť�� ó���Ѵ�.
void c_method() {
    int new_board[100][100] = { {} };

    for (int c = 0; c < max_c; c++) {
        priority_queue<pq_node> res_pq = {};
        int DAT[101] = {};

        for (int r = 0; r < max_c; r++) {
            DAT[board[r][c]] += 1;
        }

        for (int i = 1; i < 101; i++) {
            if (DAT[i] == 0) continue;

            res_pq.push({ i,DAT[i] });
        }

        int nr = 0;

        // nr == 100 �� ��� return�ϰ� �ؼ� �ִ� 100������ �����Ѵ�.
        // ���ο� �迭 �ʿ� �����ϰ� �̸� ���߿� �����Ѵ�.
        while (!res_pq.empty()) {
            pq_node now = res_pq.top();
            res_pq.pop();
            new_board[nr][c] = now.n;
            new_board[nr+1][c] = now.freq;
            nr += 2;

            if (nr == 100) break;
        }

        if (nr > max_r) max_r = nr;

    }

    // �迭 ���� �����ϱ�
    for (int r = 0; r < max_r; r++) {
        for (int c = 0; c < max_c; c++) {
            board[r][c] = new_board[r][c];
        }
    }
}

// r �����ϱ�
// �� ������ �󵵼� ������ DAT�� Ȱ���Ѵ�.
// ���� �󵵼�, ���� ũ�� ���� �켱����ť�� ó���Ѵ�.
void r_method() {
    int new_board[100][100] = { {} };

    for (int r = 0; r < max_r; r++) {
        priority_queue<pq_node> res_pq = {};
        int DAT[101] = {};

        for (int c = 0; c < max_c; c++) {
            DAT[board[r][c]] += 1;
        }

        for (int i = 1; i < 101; i++) {
            if (DAT[i] == 0) continue;
            res_pq.push({i,DAT[i]});
        }
        
        int nc = 0;
        
        // nc == 100 �� ��� return�ϰ� �ؼ� �ִ� 100������ �����Ѵ�.
        // ���ο� �迭 �ʿ� �����ϰ� �̸� ���߿� �����Ѵ�.
        while(!res_pq.empty()){

            pq_node now = res_pq.top();
            res_pq.pop();

            new_board[r][nc] = now.n;
            new_board[r][nc + 1] = now.freq;
            nc += 2;
            if (nc == 100) break;
        }
        if (nc > max_c) max_c = nc;
    }

    // �迭 ���� �����ϱ�
    for (int r = 0; r < max_r; r++) {
        for (int c = 0; c < max_c; c++) {
            board[r][c] = new_board[r][c];
        }
    }
}

int main() {
    // ���� ���� ����
    int tr, tc;

    cin >> tr >> tc >> k;
    
    tr -= 1;
    tc -= 1;
    // �ʱ� �迭 ũ��, �ð� �����ϱ�
    max_r = 3;
    max_c = 3;
    int time = 0;

    // �迭 ���� �Է¹ޱ�
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            cin >> board[r][c];
        }
    }

    // 100�ʵ��� �����ϱ�
    // �����ϸ鼭 �� �迭�� ��� ��ũ��� ���Ѵ�.
    // �� �� ���� ū ���� ���� �����Ѵ�.
    // ���� ����� �ִ����� ������ ��,���� ó���Ѵ�.

    // 100 �ʰ� ���� ��� -1�̴�.
    while (time <= 100) {

        if (board[tr][tc] == k) break;

        if (max_r >= max_c) {
            r_method();
        }
        else {
            c_method();
        }

        time += 1;
    }

    if (time <= 100) {
        cout << time << endl;
    }
    else {
        cout << -1 << endl;
    }

    return 0;
}