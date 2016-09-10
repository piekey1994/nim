#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;

inline int power(int n, int m)
{
	int num = 1;
	for (int i = 0; i<m; i++) num *= n;
	return num;
}

int main()
{
	srand((unsigned int)time(0));
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
	int n, m;
	int num[8000];
	for (n = 1000; n<8001; n += 1000)
	{
		int sum = 0;
		for (int i = 0; i<n; i++) sum += (num[i] = rand() % 100 + 1);
		int x = 0;
		int ln, cn;
		QueryPerformanceCounter(&t1);
		while (true)
		{
			int result = 0;
			for (int i = 0; i<n; i++) result ^= num[i];
			if (result == 0)
			{
				ln = -1;
				cn = -1;
			}
			else
			{
				int high = 0;
				int temp = result;
				while (temp)
				{
					temp /= 2;
					high++;
				}
				temp = power(2, high - 1);
				for (int i = 0; i<n; i++)
				{
					if (num[i]>=temp)
					{
						int temp2 = num[i];
						for (int j = 0; j < high-1; j++) temp2 /= 2;
						if (temp2 % 2 == 1)
						{
							ln = i;
							cn = num[i] - (num[i] ^ result);
							break;
						}
					}
				}
			}
			if (ln == -1)
			{
				for (int i = 0; i<n; i++)
				{
					if (num[i] != 0)
					{
						sum -= num[i];
						num[i] -= (rand() % num[i] + 1);
						sum += num[i];
						break;
					}
				}
			}
			else
			{
				num[ln] -= cn;
				sum -= cn;
			}
			x++;
			if (sum == 0) break;
			for (int i = 0; i<n; i++)
			{
				if (num[i] != 0)
				{
					sum -= num[i];
					num[i] -= (rand() % num[i] + 1);
					sum += num[i];
					break;
				}
			}
		}
		QueryPerformanceCounter(&t2);
		double tn = (t2.QuadPart - t1.QuadPart) * 1000.0 / tc.QuadPart;
		cout << "n=" << n << endl << "x=" << x << " time=" << tn << " ms" << endl << "平均时间=" << tn / x << "ms" << endl << endl;
	}
	return 0;
}
