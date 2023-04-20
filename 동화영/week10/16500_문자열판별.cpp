/* ���ڿ� �Ǻ� */
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int dp[101];
string result;
string words[100];
int N;

// DP
// ���ڿ� ��ü�� �κй��ڿ��� ������ �����Ѱ��� �Ǻ�
// i��° ���ڱ��� ���������ϴٸ� dp[i+1]�� 1�� ǥ��
// ���ڿ� ���̰� len�̶�� dp[len] �� ���� ���� �����̴�

int main() {
	// input
	cin >> result;

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> words[i];
	}

	int len = result.length();

	// ���ڿ� ��ü�� ���鼭
	for (int i = 0; i < len; i++) {
		// ���������̰ų� (i-1)���ڱ��� ������ �����ϴٸ� i��°���� Ž�� ����
		if (i == 0 || dp[i]) { 
			for (int j = 0; j < N; j++) { // �κй��ڿ����� Ž��
				int tlen = words[j].length();

				if (i + tlen > len) continue; // ���ڿ��� �� ���̸� ������ ����

				// j��° �κй��ڿ��� i�� ���ں��� �����Ǿ� �ִ°��� Ž��
				bool flag = true;
				for (int k = 0; k < tlen; k++) {
					if (result[i + k] != words[j][k]) {
						flag = false;
						break;
					}
				}

				// ���ԵǾ� �ִٸ� j�� �κй��ڿ��� ���� ���� �� �ε����� 1�� ǥ��
				if (flag) {
					dp[i + tlen] = 1;
				}
			}
		}
	}

	// output
	cout << dp[len]; // ���ڿ� ���������� ������ �Ͽ��°��� ���

	return 0;
}

/*
softwarecontest
3
software
cont
ntest
*/