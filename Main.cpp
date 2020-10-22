#include <iostream>
#include <fstream>

using namespace std;



double p1(double x) {
	if (x <= 0.1 || x >= 0.4)
		return 0;
	else if (x <= 0.2)
		return 10*x - 1;
	else if (x <= 0.3)
		return 1;
	else
		return -10*x + 4;
}


int main() {

	const int n = 100;
	const double t_max = 4.2;

	double h = 1.0 / n;
	double const c = 0.11;
	double r = 0.5;
	double dt = (h*r) / c;

	ofstream file1, file2;
	file1.open("explicit1.txt", ios::out);
	file2.open("explicit2.txt", ios::out);


	double * u_past = new double[n + 1];
	double * u_present = new double[n + 1];

	// Начальные условия 
	for (int i = 0; i < n+1 ; i++)
	{
		u_past[i] = p1(i * h);
		u_present[i] = 0;
	}

	// Граничные условия
	u_past[0] = 0;
	u_past[n] = 0;
	

	for (int j = 0; j < n + 1; j++)
	{
		file1 << u_past[j] << endl;
	}

	cout << "r = " << r << endl;

	cout <<"c * dt / h = " << c * dt / h << endl;

	cout << "dt = " << dt << endl;

	cout << "h = " << h << endl;


	for (int i = 1; i*dt <= t_max; i++)
	{
		for (int j = 1; j < n; j++)
		{
			u_present[j] = u_past[j] + (u_past[j-1] - u_past[j]) * r;
		}

		// Граничные условия
		u_present[0] = 0;
		u_present[n] = 0;


		for (int j = 0; j < n+1; j++)
		{

			u_past[j] = u_present[j];
		}

	}

	for (int j = 0; j < n + 1; j++)
	{
		file2 << u_present[j] << endl;
	}


	file1.close();
	file2.close();
	return 0;
}