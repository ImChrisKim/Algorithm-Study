#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>

using namespace std;

// ���� ť�� ����
char ori_cube[12][9] =
{
    {'0','0','0','w','w','w','0','0','0'},
    {'0','0','0','w','w','w','0','0','0'},
    {'0','0','0','w','w','w','0','0','0'},
    {'g','g','g','r','r','r','b','b','b'},
    {'g','g','g','r','r','r','b','b','b'},
    {'g','g','g','r','r','r','b','b','b'},
    {'0','0','0','y','y','y','0','0','0'},
    {'0','0','0','y','y','y','0','0','0'},
    {'0','0','0','y','y','y','0','0','0'},
    {'0','0','0','o','o','o','0','0','0'},
    {'0','0','0','o','o','o','0','0','0'},
    {'0','0','0','o','o','o','0','0','0'},

};

// test case���� ���� ť�� ���� �ҷ��´�.
char cube[12][9];

void front_cycle(int sr, int sc) {

    char tmp_square[3][3] = { {} };

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            tmp_square[r][c] = cube[sr + r][sc + c];
        }
    }

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            cube[sr + r][sc + c] = tmp_square[2-c][r];
        }
    }

};

// ť�� ������
// �� ����, ���� ����
void c_cycle(char com, char di) {
    // ����
    if (com == 'U') {
        if (di == '+') {
            // �ٶ󺸴� �� ȸ��
            front_cycle(0, 3);

            // ���� ȸ��
            // ť�� ���� ���� �����ϱ�
            char tmp[3];
            for (int m1 = 0; m1 < 3; m1++) {
                tmp[2-m1] = cube[3][2-m1];
            }

            // ť�� ȸ�� ����
            // ������� �ð���� ������ ������ �����Ѵ�.
            for (int m1 = 0; m1 < 3; m1++) {
                cube[3][2-m1] = cube[3][5-m1];
            }

            for (int m1 = 0; m1 < 3; m1++) {
                cube[3][5 - m1] = cube[3][8-m1];
            }
            for (int m1 = 0; m1 < 3; m1++) {
                cube[3][8 - m1] = cube[11][3+m1];
            }

            // ������ ���� ť��� ó�� ������ ������ �����Ѵ�.
            for (int m1 = 0; m1 < 3; m1++) {
                cube[11][3 + m1] = tmp[2-m1];
            }

        }
        else if (di == '-') {

            // �ݽð� ������ ��� �ð���� ȸ���� 3�����ش�.
            for (int i = 0; i < 3; i++) {
                // �ٶ󺸴� �� ȸ��
                front_cycle(0, 3);

                // ���� ȸ��
                // ť�� ���� ���� �����ϱ�
                char tmp[3];
                for (int m1 = 0; m1 < 3; m1++) {
                    tmp[2 - m1] = cube[3][2 - m1];
                }
                // ť�� ȸ�� ����
                // ������� �ð���� ������ ������ �����Ѵ�.
                for (int m1 = 0; m1 < 3; m1++) {
                    cube[3][2 - m1] = cube[3][5 - m1];
                }

                for (int m1 = 0; m1 < 3; m1++) {
                    cube[3][5 - m1] = cube[3][8 - m1];
                }
                for (int m1 = 0; m1 < 3; m1++) {
                    cube[3][8 - m1] = cube[11][3 + m1];
                }

                // ������ ���� ť��� ó�� ������ ������ �����Ѵ�.
                for (int m1 = 0; m1 < 3; m1++) {
                    cube[11][3 + m1] = tmp[2 - m1];
                }
            }
        }
    }
    // ������ ��
    else if (com == 'R') {
        if (di == '+') {
            // �ٶ󺸴� �� ȸ��
            front_cycle(3, 6);

            // ���� ȸ��
            // ť�� ���� ���� �����ϱ�
            char tmp[3];
            
            for (int m1 = 0; m1 < 3; m1++) {
                tmp[2 - m1] = cube[5-m1][5];
            }

            // ť�� ȸ�� ����
            // ������� �ð���� ������ ������ �����Ѵ�.
            for (int m1 = 0; m1 < 3; m1++) {
                cube[5 - m1][5] = cube[8-m1][5];
            }

            for (int m1 = 0; m1 < 3; m1++) {
                cube[8 - m1][5] = cube[11-m1][5];
            }
            for (int m1 = 0; m1 < 3; m1++) {
                cube[11-m1][5] = cube[2-m1][5];
            }

            // ������ ���� ť��� ó�� ������ ������ �����Ѵ�.
            for (int m1 = 0; m1 < 3; m1++) {
                cube[2 - m1][5] = tmp[2 - m1];
            }
        }
        else if (di == '-') {
            // �ݽð� ������ ��� �ð���� ȸ���� 3�����ش�.
            for (int i = 0; i < 3; i++) {
                // �ٶ󺸴� �� ȸ��
                front_cycle(3, 6);
                // ���� ȸ��
                // ť�� ���� ���� �����ϱ�
                char tmp[3];
                for (int m1 = 0; m1 < 3; m1++) {
                    tmp[2 - m1] = cube[5 - m1][5];
                }
                // ť�� ȸ�� ����
                // ������� �ð���� ������ ������ �����Ѵ�.
                for (int m1 = 0; m1 < 3; m1++) {
                    cube[5 - m1][5] = cube[8 - m1][5];
                }

                for (int m1 = 0; m1 < 3; m1++) {
                    cube[8 - m1][5] = cube[11 - m1][5];
                }
                for (int m1 = 0; m1 < 3; m1++) {
                    cube[11 - m1][5] = cube[2 - m1][5];
                }

                // ������ ���� ť��� ó�� ������ ������ �����Ѵ�.
                for (int m1 = 0; m1 < 3; m1++) {
                    cube[2 - m1][5] = tmp[2 - m1];
                }
            }
        }
    }
    // ����
    // ���� �������� �Ʒ������� �����ϴ�.
    // �ڼ��� �ּ� ����
    else if (com == 'F') {
        if (di == '+') {
            // �ٶ󺸴� �� ȸ��
            front_cycle(3, 3);

            char tmp[3];
            // store
            for (int m1 = 0; m1 < 3; m1++) {
                tmp[2 - m1] = cube[5 - m1][2];
            }

            // cycle
            for (int m1 = 0; m1 < 3; m1++) {
                cube[5 - m1][2] = cube[6][5-m1];
            }

            for (int m1 = 0; m1 < 3; m1++) {
                cube[6][5 - m1] = cube[3 + m1][6];
            }
            for (int m1 = 0; m1 < 3; m1++) {
                cube[3 + m1][6] = cube[2][3 + m1];
            }

            for (int m1 = 0; m1 < 3; m1++) {
                cube[2][3 + m1] = tmp[2 - m1];
            }
        }
        else if (di == '-') {
            for (int i = 0; i < 3; i++) {
                // �ٶ󺸴� �� ȸ��
                front_cycle(3, 3);

                char tmp[3];
                // store
                for (int m1 = 0; m1 < 3; m1++) {
                    tmp[2 - m1] = cube[5 - m1][2];
                }

                // cycle
                for (int m1 = 0; m1 < 3; m1++) {
                    cube[5 - m1][2] = cube[6][5 - m1];
                }

                for (int m1 = 0; m1 < 3; m1++) {
                    cube[6][5 - m1] = cube[3 + m1][6];
                }
                for (int m1 = 0; m1 < 3; m1++) {
                    cube[3 + m1][6] = cube[2][3 + m1];
                }

                for (int m1 = 0; m1 < 3; m1++) {
                    cube[2][3 + m1] = tmp[2 - m1];
                }
            }
        }
    }
    else if (com == 'L') {
        if (di == '+') {
            // �ٶ󺸴� �� ȸ��
            front_cycle(3, 0);

            char tmp[3];
            // store
            for (int m1 = 0; m1 < 3; m1++) {
                tmp[2 - m1] = cube[9 + m1][3];
            }

            // cycle
            for (int m1 = 0; m1 < 3; m1++) {
                cube[9 + m1][3] = cube[6+m1][3];
            }

            for (int m1 = 0; m1 < 3; m1++) {
                cube[6 + m1][3] = cube[3 + m1][3];
            }
            for (int m1 = 0; m1 < 3; m1++) {
                cube[3 + m1][3] = cube[m1][3];
            }

            for (int m1 = 0; m1 < 3; m1++) {
                cube[m1][3] = tmp[2 - m1];
            }
        }
        else if (di == '-') {
            for (int i = 0; i < 3; i++) {
                // �ٶ󺸴� �� ȸ��
                front_cycle(3, 0);

                char tmp[3];
                // store
                for (int m1 = 0; m1 < 3; m1++) {
                    tmp[2 - m1] = cube[9 + m1][3];
                }

                // cycle
                for (int m1 = 0; m1 < 3; m1++) {
                    cube[9 + m1][3] = cube[6 + m1][3];
                }

                for (int m1 = 0; m1 < 3; m1++) {
                    cube[6 + m1][3] = cube[3 + m1][3];
                }
                for (int m1 = 0; m1 < 3; m1++) {
                    cube[3 + m1][3] = cube[m1][3];
                }

                for (int m1 = 0; m1 < 3; m1++) {
                    cube[m1][3] = tmp[2 - m1];
                }
            }
        }
    }
    else if (com == 'D') {
        if (di == '+') {
            // �ٶ󺸴� �� ȸ��
            front_cycle(6, 3);

            char tmp[3];
            // store
            for (int m1 = 0; m1 < 3; m1++) {
                tmp[2 - m1] = cube[5][m1];
            }

            // cycle
            for (int m1 = 0; m1 < 3; m1++) {
                cube[5][m1] = cube[9][5-m1];
            }

            for (int m1 = 0; m1 < 3; m1++) {
                cube[9][5 - m1] = cube[5][6+m1];
            }
            for (int m1 = 0; m1 < 3; m1++) {
                cube[5][6 + m1] = cube[5][3+m1];
            }

            for (int m1 = 0; m1 < 3; m1++) {
                cube[5][3 + m1] = tmp[2 - m1];
            }
        }
        else if (di == '-') {
            for (int i = 0; i < 3; i++) {
                // �ٶ󺸴� �� ȸ��
                front_cycle(6, 3);

                char tmp[3];
                // store
                for (int m1 = 0; m1 < 3; m1++) {
                    tmp[2 - m1] = cube[5][m1];
                }

                // cycle
                for (int m1 = 0; m1 < 3; m1++) {
                    cube[5][m1] = cube[9][5 - m1];
                }

                for (int m1 = 0; m1 < 3; m1++) {
                    cube[9][5 - m1] = cube[5][6 + m1];
                }
                for (int m1 = 0; m1 < 3; m1++) {
                    cube[5][6 + m1] = cube[5][3 + m1];
                }

                for (int m1 = 0; m1 < 3; m1++) {
                    cube[5][3 + m1] = tmp[2 - m1];
                }

            }
        }
    }
    else if (com == 'B') {
        if (di == '+') {
            // �ٶ󺸴� �� ȸ��
            front_cycle(9, 3);

            char tmp[3];
            // store
            for (int m1 = 0; m1 < 3; m1++) {
                tmp[2 - m1] = cube[3+m1][0];
            }

            // cycle
            for (int m1 = 0; m1 < 3; m1++) {
                cube[3 + m1][0] = cube[0][5 - m1];
            }

            for (int m1 = 0; m1 < 3; m1++) {
                cube[0][5 - m1] = cube[5 - m1][8];
            }
            for (int m1 = 0; m1 < 3; m1++) {
                cube[5 - m1][8] = cube[8][3 + m1];
            }

            for (int m1 = 0; m1 < 3; m1++) {
                cube[8][3 + m1] = tmp[2 - m1];
            }

        }
        else if (di == '-') {
            for (int i = 0; i < 3; i++) {
                // �ٶ󺸴� �� ȸ��
                front_cycle(9, 3);

                char tmp[3];
                // store
                for (int m1 = 0; m1 < 3; m1++) {
                    tmp[2 - m1] = cube[3 + m1][0];
                }

                // cycle
                for (int m1 = 0; m1 < 3; m1++) {
                    cube[3 + m1][0] = cube[0][5 - m1];
                }

                for (int m1 = 0; m1 < 3; m1++) {
                    cube[0][5 - m1] = cube[5 - m1][8];
                }
                for (int m1 = 0; m1 < 3; m1++) {
                    cube[5 - m1][8] = cube[8][3 + m1];
                }

                for (int m1 = 0; m1 < 3; m1++) {
                    cube[8][3 + m1] = tmp[2 - m1];
                }

            }
        }
    }
};

int main() {
    // test ��
    int t;
    cin >> t;

    // ť�� ������ ����
    for (int tc = 0; tc < t; tc++) {
        int n;
        cin >> n;
        
        // ť�� ���� �ʱ�ȭ�ϱ�
        memcpy(cube, ori_cube, 12 * 9*sizeof(ori_cube[0][0]));

        // n���� ť�� ȸ�� ���� �Է�
        // ť�긦 ������.
        for (int i = 0; i < n; i++) {
            char orders[3] = "";
            cin >> orders[0];
            cin >> orders[1];

            c_cycle(orders[0], orders[1]);

        }

        // ���� ť�� ����
        for (int r = 0; r < 3; r++) {
            for (int c = 3; c < 6; c++) {
                cout << cube[r][c];
            }
            cout << endl;
        }

    }
    return 0;
}