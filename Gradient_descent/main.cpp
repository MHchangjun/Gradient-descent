#include<iostream>
#include <random>
#include <fstream>

#pragma warning(disable:4996)
using namespace std;
class linear_regression {
	public:
		static const int feature = 2, dataCount = 31;
		double data[dataCount+1][feature+1], y[dataCount], w[feature+1]; 
		void fileinput(string root)
		{
			ifstream in(root);
			if (in.is_open())
			{
				for (int i = 0; i < dataCount; i++)
				{
					data[i][0] = 1;
					for (int j = 1; j <= feature; j++)
					{
						in >> data[i][j];
					}
					in >> y[i];
				}
			}
		}
		void wSet()
		{
			for (int i = 0; i <= feature; i++)
			{
				w[i] = 0;
			}
		}
		void Test(string root)
		{
			double test1,test2, ans;
			ifstream in(root);
			if (in.is_open())
			{
				for (int i = 0; i < dataCount; i++)
				{
					in >> test1 >> test2>>ans;
					cout << "ERROR -> " << ans - (test1 * w[1] +test2 * w[2]+ w[0]) << endl;
				}
				in.close();
			}
		}
		void learning()
		{
			for (int i = 0; i < 400000; i++)
			{
				double learningRate = 0.00001;
				for (int j = 0; j <= feature; j++)
				{
					w[j] = w[j] - learningRate * error(j);
				}
			}
		}
	private:
		double ans = 0, sum = 0;
		int rnd(int min, int max)
		{
			random_device rn;
			mt19937_64 rnd(rn());
			uniform_int_distribution<int> range(min, max);
			return range(rnd);
		}
		double error(int form)
		{
			sum = 0;
			for (int i = 0; i < dataCount; i++)
			{
				sum += (H(i) - y[i]) * data[i][form]; //W(i) ERROR
			}
			sum = sum * (1.00 / (dataCount));
			//cout << "form = "<<form<<" sum = " << sum<<endl;
			return sum;
		}
		double H(int x) //
		{
			ans = 0;
			for (int i = 0; i <= feature; i++)
			{
				ans = ans + w[i] * data[x][i];
			}
			return ans;
		}
};
int main()
{
	freopen("output.txt", "w", stdout);

	linear_regression lr;
	lr.fileinput("dataset1.txt");
	lr.wSet();
	lr.learning();
	for (int i = -50; i < 50; i+=3)
	{
		for (int j = -300; j < 0; j+=3)
		{
			cout << lr.w[1] * i <<" " << lr.w[2] * j <<" "<< lr.w[1] * i + lr.w[2] * j + lr.w[0]<<endl;
		}
	}
	return 0;
}