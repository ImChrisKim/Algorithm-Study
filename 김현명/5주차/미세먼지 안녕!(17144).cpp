#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>

using namespace std;

// �ʱ� ���� ����
int n, m, time;
int board[50][50];
int tmp_board[50][50];

int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

// ����û���� ��ġ ����
struct node {
    int r;
    int c;
};

node cleaner[2];

int main() {
    cin >> n >> m >> time;

    // ����û���� ��ġ, ��ü ���� ��
    int node_i = 0;
    int m1_r, m1_c, m2_r, m2_c;
    int total_dust = 0;

    // �̼����� ���� �Է�
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            cin >> board[r][c];
            
            if (board[r][c] == -1) {
                cleaner[node_i] = { r,c };
                board[r][c] = 0;
                node_i += 1;
            }
        }
    }

    // ���� û���� ��ġ ����
    m1_r = cleaner[0].r;
    m1_c = cleaner[0].c;
    m2_r = cleaner[1].r;
    m2_c = cleaner[1].c;

    // �ð� �帣��
    for (int sec = 0; sec < time; sec++) {
        // �ӽ� Board �ʱ�ȭ
        memset(tmp_board, 0, sizeof(tmp_board));

        // �̼� ���� Ȯ��
        // ���� Ȯ��Ǵ� ������ ���� û���Ⱑ �ִ°��̸� �����Ѵ�.
        // �̼� ������ ���뿵���� ���� �� �ִ�.
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                int dust = 0;
                int nr, nc;

                if (board[r][c] > 0) {
                    tmp_board[r][c] += board[r][c];
                    for (int di = 0; di < 4; di++) {
                        nr = r + dr[di];
                        nc = c + dc[di];

                        if (0 > nr || n <= nr || 0 > nc || m <= nc) continue;
                        if((nr == m1_r && nc == m1_c) || (nr == m2_r && nc == m2_c)) continue;
                        tmp_board[nr][nc] += (board[r][c] / 5);
                        dust += (board[r][c] / 5);
                    }
                    tmp_board[r][c] -= dust;
                }
            }
        }

        // ���� ���� ����
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                board[r][c] = tmp_board[r][c];
            }
        }


        // ���� û���� �۵�
        
        // ��, �ݽð����
        // ó�� ���������� �̼������� �����Ѵ�.
        // ���� û���⿡ ���� �̼������� ��ȭ ��Ű�� ������ ������ �̰��� ������� �ʰ� ���۽�Ų��.
        for (int r = m1_r; r > 0; r--) {
            board[r][0] = board[r - 1][0];
        }

        board[m1_r][m1_c] = 0;

        for (int c = 0; c < m - 1; c++) {
            board[0][c] = board[0][c + 1];
        }

        for (int r = 0; r < m1_r; r++) {
            board[r][m - 1] = board[r + 1][m - 1];
        }

        for (int c = m - 1; c > 0; c--) {
            board[m1_r][c] = board[m1_r][c - 1];
        }

        // �Ʒ�, �ð����
        // ó�� �Ʒ��������� �̼������� �����Ѵ�.
        // ���� û���⿡ ���� �̼������� ��ȭ ��Ű�� ������ ������ �̰��� ������� �ʰ� ���۽�Ų��.
        for (int r = m2_r; r < n-1; r++) {
            board[r][0] = board[r + 1][0];
        }

        board[m2_r][m2_c] = 0;

        for (int c = 0; c < m - 1; c++) {
            board[n-1][c] = board[n-1][c + 1];
        }

        for (int r = n-1; r > m2_r; r--) {
            board[r][m - 1] = board[r - 1][m-1];
        }

        for (int c = m - 1; c > 0; c--) {
            board[m2_r][c] = board[m2_r][c - 1];
        }
    }

    // �� �̼����� �Է�
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            total_dust += board[r][c];
        }
    }

    cout << total_dust << endl;

    return 0;
}