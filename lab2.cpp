#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

double alpha(double t)
{
  return -3.0 * t + 7.0;
}

double betha(double x)
{
  return 3.0 * x + 7.0;
}

double fcheck(double t, double x)
{
  return 3.0 * (x - t) + 7.0;
}

int main()
{
  double X(2.0);
  double T(2.0);
  double dt(0.2);
  double dx(0.2);

  int n(T / dt);
  int m(X / dx);

  vector<vector<double> > f(n + 1, vector<double>(m + 1, 0));
  for (size_t i(0); i < f.size(); ++i) {
    f[i][0] = alpha(i * dt);
  }
  for (size_t j(0); j < f[0].size(); ++j) {
    f[0][j] = betha(j * dx);
  }

  for (int i(1); i < f.size(); ++i) {
    for (int j(1); j < f[i].size(); ++j) {
      f[i][j] = f[max(i - 2, 0)][j] + f[i - 1][j - 1] * (i == 1 ? 1.0 : 2.0) * dt / (dx*(j == m ? 1.0 : 2.0)) - f[i - 1][min(j + 1, m)] * (i == 1 ? 1.0 : 2.0) * dt / (dx*(j == m ? 1.0 : 2.0));
    }
  }

  cout << "Approximate solution: \n";

  for (int i(f.size() - 1); i >= 0; --i) {
    for (int j(0); j < f[i].size(); ++j) {
      printf("%7.3lf", f[i][j]);
    }
    cout << "\n";
  }

  cout << "\n";
  cout << "Analytical solution: \n";

  for (int i(f.size() - 1); i >= 0; --i) {
    for (int j(0); j < f[i].size(); ++j) {
      printf("%7.3lf", fcheck(i*dx, j*dt));
    }
    cout << "\n";
  }

  cout << "\n";
  cout << "Difference: \n";

  for (int i(f.size() - 1); i >= 0; --i) {
    for (int j(0); j < f[i].size(); ++j) {
      printf("%7.3lf", fabs(fcheck(i*dx, j*dt)- f[i][j]));
    }
    cout << "\n";
  }

  return 0;
}