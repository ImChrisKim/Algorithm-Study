// 1715 ī�� �����ϱ�
#include <iostream>
#include <queue>
using namespace std;

// �� ���ؿ��� ���� ���� ī�� ���� 2���� ���
// ���ϴ� Ƚ���� ���Ѵ�
// �ܼ��� �ʱ⿡ 1ȸ�� �������� �ʰ� PQ�� ����ϴ� ������
// �� Ƚ���� ���ϸ鼭�� ������ ī�� ���� ���ŵǰ� �� �ȿ��� �� ������ �ʿ��ϱ� ������
// ���� �������� ���� ���� ���� 2���� ���°� �´� (�׸��� �˰���)

int main() {
	int N, num; // N: ī�� ������ ��, num: �Է°�
	priority_queue<int, vector<int>, greater<int>> pq; // �������� ������ PQ

	// input
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num;
		pq.push(num);
	}

	int sum = 0; // �� ��Ƚ��

	// pq�� �ּ� 2���� �־�� �� ����
	// 1���� �����͸� �ִٸ� ���� �� �� ������ �� ī���� ���̴�
	while (pq.size() > 1) {
		// 2���� �ּ� ������ �����´�
		int one = pq.top(); pq.pop();
		int two = pq.top(); pq.pop();
		sum += (one + two); // �� Ƚ���� ���Ѵ�
		pq.push(one + two); // pq�� �����͸� ���� �־��ش�
	}

	// output
	cout << sum << "\n";

	return 0;
}