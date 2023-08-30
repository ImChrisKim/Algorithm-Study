#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> v;
pair<int, int> ans;

void sol()
{

	int ids = 0;
	int left = 0; // left < right
	int right = v.size() - 1;
	int abs_sum = 21e8;

	while (left < right)
	{
		int sum = v[left] + v[right];
		if (abs_sum > abs(sum))
		{
			abs_sum = abs(sum);
			ans.first = v[left];
			ans.second = v[right];
		}
		if (sum < 0)
		{
			left++;
		}
		else if (sum > 0)
		{
			right--;
		}
		else if (sum == 0)
		{
			ans.first = v[left];
			ans.second = v[right];
			break;
		}
	}
}

void input()
{

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int temp;
		cin >> temp;
		v.push_back(temp);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	input();

	sol();

	cout << ans.first << " " << ans.second << endl;
}