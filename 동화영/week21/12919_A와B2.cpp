// 12919 A�� B 2
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

// S���� T�� ����⿡�� ����� ���� (�־��� ���) 2^50�����̴�.
// ���� �ð� �ʰ� �߻�
// T���� S�� ������ ����
// 1. ���� T`���� �ڿ� A�� ������ A�� �� ���ڿ��� queue�� �ִ´�.
// 2. ���� T`���� �տ� B�� ������ B�� ���� ������ ���ڿ��� queue�� �ִ´�.
// �� ����̶�� ���ʿ��� ������ �� �ʿ䰡 ��� �ð� ����

int main() {
	// input
	string S, T;
	cin >> S >> T;

	int ans = 0;
	int sLen = S.size();
	queue<string> q;
	q.push(T);

	while (!q.empty()) {
		string now = q.front();
		q.pop();

		// ���� Ž�� ���� ���ڿ��� ������ S�� �����ϴٸ� ans ���� �� Ž�� ����
		if (now == S) {
			ans = 1;
			break;
		}

		// now�� S�� ���̰� ���ٸ� �̹� Ʋ�ȴٴ� ���̹Ƿ�
		// ���̻� Ž���� �ʿ� ����
		if (now.size() == sLen) continue;

		// 1. �� �ڰ� A��� A�� �� ���ڿ��� queue�� �߰�
		if (now[now.size() - 1] == 'A') {
			q.push(now.substr(0, now.size() - 1));
		}
		// 2. �� ���� B��� B�� ���� reverse�� ���ڿ��� queue�� �߰�
		if (now[0] == 'B') {
			string nxt = now.substr(1);
			reverse(nxt.begin(), nxt.end());
			q.push(nxt);
		}
	}

	// ���� ã�Ƽ� Ż���� ��� queue�� ���� ������ ����
	while (!q.empty()) q.pop();

	// output
	// 1:�� ã�� 0:�� ��ã��
	cout << ans << "\n";

	return 0;
}