#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int alpha[26]; // A ~ Z �� ���ĺ��� �ڸ��� �ش��ϴ� ���ڵ��� ��
vector<pair<int, int>> ans; // �� ���ĺ� �� �����ϴ� ������ �� ��

int main() {
	int N; // �ܾ��� ��
	char words[10][10]; // �Է¹��� �ܾ�

	// input
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> words[i];

		// �ܾ��� ���� ���ϱ�
		int len = 0;
		for (int j = 0; j < 10; j++) {
			if (words[i][j] == '\0') break;
			len++;
		}

		// �� ���ĺ��� ��ġ�� ���� ���� ���ϱ�
		for (int j = 1; j <= len; j++) {
			int ind = (int)(words[i][j - 1] - 'A');
			alpha[ind] += pow(10, len - j);
		}
	}
	
	// �� ���ĺ� �� �����ϴ� ������ �� ���� vector�� ����
	for (int i = 0; i < 26; i++) {
		if (alpha[i] == 0) continue;
		ans.push_back({ alpha[i], i });
	}
	
	sort(ans.begin(), ans.end(), greater<>()); // �������� ����

	// ���� ū ���� �����ϴ� ���ĺ����� 9 �����Ͽ� �� ���ϱ�
	int res = 0;
	for (int i = 0; i < ans.size(); i++) {
		res += (9 - i) * ans[i].first;
	}

	// output
	cout << res << "\n";

	return 0;
}