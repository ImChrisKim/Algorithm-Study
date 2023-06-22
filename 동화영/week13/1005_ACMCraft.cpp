#include <iostream>
#include <cstring>
using namespace std;

int schedule[1001][1001]; // �ǹ� �Ǽ��� �켱���� schedule[a][b] => a->b
int time[1001]; // �� �ǹ� �Ǽ��� �ҿ� �ð�

int cache[1001]; // �� �ǹ� �Ǽ� �Ϸ� ������ ����

int N, K; // N:�ǹ��� �� K:�ǹ� �켱���� ������ ��
int target; // Ÿ�� �ǹ��� ��ȣ

// tar�� �ǹ��� ���µ� �ҿ�Ǵ� �ð� ���ϱ�
int build(int tar) {
	// tar�ǹ��� ���� ������ �̸� ������ϴ� �ǹ����� �ִ�
	// �� �ǹ����� ��� ���� ���� �ð��� timer
	// �� tar ������ �Ϸ��ؾ� �ϴ� �ǹ��� �� �ִ� �ҿ�ð��� timer�� �����Ѵ�
	int timer = 0;
	for (int i = 1; i <= N; i++) {
		if (schedule[i][tar] != 0) { // tar�ǹ� ���� ������ i�� �ǹ��� �Ϸ��ؾ� �Ѵ�
			if (cache[i] == -1) build(i); // i�� �ǹ��� ���µ� �ҿ�� �ð� ���� ���ٸ� -> ���Ϸ� ����

			if (cache[i] > timer) timer = cache[i]; // tar ������ �Ϸ��ؾ� �ϴ� �ǹ��� �� �ִ� �ҿ�ð� ����
		}
	}

	return cache[tar] = (timer + time[tar]); // tar�ǹ� �Ǽ� �ҿ�ð��� ���� �� ��ȯ -> (���� �ҿ�ð� + tar �Ǽ� �ҿ�ð�)
}

int main() {
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		// init
		memset(schedule, 0, sizeof(schedule));
		memset(cache, -1, sizeof(cache));

		// input
		cin >> N >> K;
		for (int i = 1; i <= N; i++) cin >> time[i];
		int a, b;
		for (int i = 0; i < K; i++) {
			cin >> a >> b;
			schedule[a][b] = 1;
		}
		cin >> target;

		// solve & output
		cout << build(target) << "\n";
	}

	return 0;
}

/*
5
3 2
1 2 3
3 2
2 1
1
4 3
5 5 5 5
1 2
1 3
2 3
4
5 10
100000 99999 99997 99994 99990
4 5
3 5
3 4
2 5
2 4
2 3
1 5
1 4
1 3
1 2
4
4 3
1 1 1 1
1 2
3 2
1 4
4
7 8
0 0 0 0 0 0 0
1 2
1 3
2 4
3 4
4 5
4 6
5 7
6 7
7
*/

/*
6
5
399990
2
0
*/