// 13549 ���ٲ��� 3
#include <iostream>
#include <queue>
using namespace std;

// N�������� K�������� �ּ� �ð����� �����ϱ�
// �̵� ����� 3���� - +1ĭ �̵�, -1ĭ �̵�, *2ĭ���� �����̵�
// PQ�� Ȱ���ϱ�
// 1. ���� �������� 3���� ��� �� ������ ���̽��� PQ�� �ִ´�.
// 2. PQ���� �ð� ������ �������� ������ �Ͽ� ª�� �ð����� pop�Ͽ� Ž���Ѵ�.
// 3. pop�� �������� �ٽ� 1�� �ݺ��Ѵ�.

struct NODE {
	int time; // pnt�� �����ϴµ� �ɸ� �ð�
	int pnt; // pnt ����

	bool operator < (NODE nxt) const {
		if (time < nxt.time) return false;
		if (time > nxt.time) return true;
		if (pnt < nxt.pnt) return false;
		if (pnt > nxt.pnt) return true;
		return false;
	}
};

int visited[100001]; // 0~100000 ������ �����ϴµ� �ɸ� �ð�
int N, K; // N: ������ �ʱ� ��ġ, K: ������ ��ġ

int main() {
	// input
	cin >> N >> K;

	for (int i = 0; i <= 100000; i++) {
		visited[i] = 213456789; // �� ������ visited �� �ִ�� �ʱ�ȭ
	}

	priority_queue<NODE> pq;
	pq.push({ 0, N }); // N���� ����
 	visited[N] = 0;

	while (!pq.empty()) {
		NODE now = pq.top();
		pq.pop();

		// K������ �����ߴٸ� ����
		// PQ�� Ư���� �ð� ������ pop�ϱ� ������ ó������ K�� �����ߴٸ�
		// �̰� ���� ���� ���̴�
		if (now.pnt == K) {
			break;
		}

		// i == 0 : -1ĭ���� �̵� (1�� �ҿ�)
		// i == 1 : +1ĭ���� �̵� (1�� �ҿ�)
		// i == 2 : *2ĭ���� �̵� (0�� �ҿ�)
		for (int i = 0; i < 3; i++) {
			int nxtNum = i == 2 ? now.pnt * 2 : i == 1 ? now.pnt + 1 : now.pnt - 1;
			int nxtTime = i == 2 ? now.time : now.time + 1;

			if (nxtNum < 0 || nxtNum > 100000) continue; // 0~100000 ��ǥ �Ѿ�� ����
			if (visited[nxtNum] <= nxtTime) continue; // �̹� �� ���� �����ߴٸ� ����

			pq.push({ nxtTime, nxtNum }); // Ž�� ����
			visited[nxtNum] = nxtTime;
		}
	}

	// output
	if (visited[K] == 213456789) visited[K] = -1; // Kĭ�� ������ ���� ���ٸ� ���� �Ұ��� �Ǵ�
	cout << visited[K] << "\n";
	
	return 0;
}