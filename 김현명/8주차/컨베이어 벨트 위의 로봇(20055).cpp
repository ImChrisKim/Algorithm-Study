#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

int n, k;

// ��Ʈ ����: ������, �κ� ����
struct node {
    int life;
    bool robot;
};

node belt[2][100];

// �ܰ� ��, operate ���� ����
int step;
bool done = false;

// �κ� �����̱�
// ���ϸ��� ��Ʈ�� ȸ���Ѵ�.
// ������ ��ġ���� �κ����� ��� ������ ������ robot : true, false�� �����ϴ�. 
void r_move() {
    // ������ ��ġ �κ� ����ϱ�
    if (belt[0][n - 1].robot == true) {
        belt[0][n - 1].robot = false;
    }

    if (belt[0][n - 2].robot == true && belt[0][n - 1].life > 0) {
        belt[0][n - 1].life -= 1;
        belt[0][n - 2].robot = false;
    }

    for (int c = n - 3; c > -1; c--) {
        if (belt[0][c].robot == true && belt[0][c+1].robot == false
            && belt[0][c+1].life > 0) {

            belt[0][c + 1].robot = true;
            belt[0][c + 1].life -= 1;
            belt[0][c].robot = false;
        }
    }

    // �κ� �ø���
    if (belt[0][0].life > 0) {
        belt[0][0].robot = true;
        belt[0][0].life -= 1;
    }
    
    // operate ���� ���� ����ϱ�
    int d_num = 0;

    for (int r = 0; r < 2; r++) {
        for (int c = 0; c < n; c++) {
            if (belt[r][c].life <= 0)
            {
                d_num += 1;
            }
        }
    }

    if (d_num >= k) {
        done = true;
    }
};

// ��Ʈ ������
void b_cycle() {
    node r_tmp, l_tmp;
    
    r_tmp = belt[0][n - 1];
    l_tmp = belt[1][0];

    for (int c = n - 1; c > 0; c--) {
        belt[0][c] = belt[0][c - 1];
    }

    for (int c = 0; c < n-1; c++) {
        belt[1][c] = belt[1][c + 1];
    }

    belt[0][0] = l_tmp;
    belt[1][n - 1] = r_tmp;

};

// ��Ʈ�� ������.
// �κ��� �����δ�.
void operate() {
    b_cycle();
    r_move();
};

int main() {
    cin >> n >> k;

    // ��Ʈ ���� �Է¹ޱ�
    // ���� ���ǿ� �°� �Է¹���.
    for (int c = 0; c < n; c++) {
        cin >> belt[0][c].life;
        belt[0][c].robot = false;
    }
    for (int c = n-1; c > -1; c--) {
        cin >> belt[1][c].life;
        belt[1][c].robot = false;
    }

    // ������ ������ �����Ҷ����� operate�Ѵ�.
    while (done == false) {
        operate();
        step += 1;
    }

    cout << step << endl;

    return 0;
}