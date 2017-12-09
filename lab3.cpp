#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const long long N = 4294967295;
const double a[] = {1.0000886, 0.4713941, 0.0001348028, -0.008553069, 0.00312558, -0.0008426812, 0.00009780499};
const double b[] = {-0.2237368, 0.02607083, 0.01128186, -0.01153761, 0.005169654, 0.00253001, -0.001450117};
const double c[] = {-0.01513904, -0.008986007, 0.02277679, -0.01323293, -0.006950356, 0.001060438, 0.001565326};

vector<int> vA;
vector<vector<int> > vB;
vector<long long> vC;
vector<long long> vD(5);
vector<vector<long long> > StirlingNumb;
vector<double> pr;

double chiSquared(double alpha, double frdegr)
{
  double res(0);
  double d;
  if (alpha < 0.5) {
    d = -2.0637 * pow(log(1.0 / alpha) - 0.16, 0.4274) + 1.5774;
  }
  else {
    d = 2.0637 * pow(log(1.0 / (1.0 - alpha)) - 0.16, 0.4274) - 1.5774;
  }

  for (int j(0); j < 7; ++j) {
    res += pow(frdegr, (-j * 1.0) / 2.0) * pow(d, 1.0 * j) * (a[j] + b[j] / (1.0 * frdegr) + c[j] / (1.0 * frdegr * frdegr));
  }

  res = frdegr * pow(res, 3.0);
  return res;
}

int checkType(const vector<long long> &vals)
{
  map<long long, int> tp;
  for (int i(0); i < vals.size(); ++i) {
    tp[vals[i]]++;
  }

  return tp.size() - 1;
}

void countStirling(int d)
{
  StirlingNumb.resize(d + 1);
  for (int i(0); i <= d; ++i) {
    StirlingNumb[i].resize(d + 1);
    StirlingNumb[i][0] = 0;
    StirlingNumb[i][i] = 1;
  }

  for (int i(1); i < StirlingNumb.size(); ++i) {
    for (int j(1); j < StirlingNumb[i].size(); ++j) {
      StirlingNumb[i][j] = j * StirlingNumb[i - 1][j] + StirlingNumb[i - 1][j - 1];
    }
  }
}

int main()
{
  long long m(4294967296);
  long long a(69069);
  long long c(0);
  long long x0(1);

  int d(10);
  vA.resize(d);

  long long n;
  cout << "Would you be so kind to enter the amount of numbers <3\n";
  cin >> n;
  int eps;
  double p(1.0 / d);

  cout << "\nChechking frequency criterion...\n";

  long long x(x0);
  for (int i(0); i < n; ++i) {
    eps = (1ll * d * x) / m;
    vA[eps]++;
    x = (a * x + c) % m;
  }
  
  double V(0);
  for (int i(0); i < d; ++i) {
    V += pow(vA[i] - n * p, 2.0) / (1.0 * n * p);
  }

  double chi(chiSquared(0.95, d - 1));

  if (V < chi) {
    cout << "Satisfy criterion A\n";
  }
  else {
    cout << "Don't satisfy criterion A\n";
  }
  cout << "V = " << V << "\n";
  cout << "chi-squared(0.95, " << d - 1 << ") = " << chi << "\n";
  //-----------------------------------------------------
  cout << "\nChechking pair criterion...\n";
  vB.resize(d);
  for (int i(0); i < d; ++i) {
    vB[i].resize(d);
  }

  x = x0;
  long long aa, bb;
  for (int i(0); i < n / 2; ++i) {
    aa = (d * x) / m;
    x = (a * x + c) % m;
    bb = (d * x) / m;
    vB[aa][bb]++;
  }

  p = 1.0 / (d * d);
  V = 0;
  for (int i(0); i < d; ++i) {
    for (int j(0); j < d; ++j) {
      V += pow(vB[i][j] - n / 2 * p, 2.0) / (1.0 * n / 2 * p);
    }
  }

  chi = chiSquared(0.95, d * d - 1);

  if (V < chi) {
    cout << "Satisfy criterion B\n";
  }
  else {
    cout << "Don't satisfy criterion B\n";
  }
  cout << "V = " << V << "\n";
  cout << "chi-squared(0.95, " << d * d - 1 << ") = " << chi << "\n";
  //------------------------------------------------------------
  cout << "\nChechking series criterion...\n";
  int h = 5;
  vC.resize(h + 1);
  int sercount(0);

  x = x0;
  int l(1);
  for (int i(0); i < n; i += 2) {
    aa = 1ll * d * x / m;
    x = (a * x + c) % m;
    bb = 1ll * d * x / m;
    x = (a * x + c) % m;
    if (aa != bb) {
      vC[l - 1]++;
      l = 1;
    }
    else {
      l = min(l + 1, h + 1);
    }
  }
  if (l > 1) {
    vC[l - 1]++;
  }

  for (int i(0); i < vC.size(); ++i) {
    sercount += vC[i];
  }

  pr.resize(h + 1);
  for (int i(0); i < h; ++i) {
    pr[i] = 9.0 / pow(10.0, 1.0 * (i + 1));
  }
  pr[h] = 1.0 / pow(10.0, 1.0 * h);

  V = 0;
  for (int i(0); i <= h; ++i) {
    V += pow(vC[i] - pr[i] * sercount, 2.0) / (1.0 * pr[i] * sercount);
  }

  chi = chiSquared(0.95, h);
  if (V < chi) {
    cout << "Satisfy criterion C\n";
  }
  else {
    cout << "Don't satisfy criterion C\n";
  }
  cout << "V = " << V << "\n";
  cout << "chi-squared(0.95, " << h << ") = " << chi << "\n";
  //------------------------------------------------------------
  cout << "\nChechking poker criterion...\n";
  x = x0;
  vector<long long> vals(5);
  int type;
  for (int i(0); i < n; i += 5) {
    int j(0);
    while(j < 5) {
      vals[j] = (d * x) / m;
      x = (a * x + c) % m;
      j++;
    }
    type = checkType(vals);
    vD[type]++;
  }

  countStirling(5);
  pr.resize(5);
  for (int k(0); k < 5; ++k) {
    pr[k] = 1;
    int r(k + 1);
    for (int j(1); j <= r; ++j) {
      pr[k] *= (d + 1 - j);
    }
    pr[k] /= pow(d, 5);
    pr[k] *= StirlingNumb[5][r];
  }

  V = 0;
  for (int i(0); i < 5; ++i) {
    V += pow(vD[i] - pr[i] * n / 5.0, 2.0) / (1.0 * pr[i] * n / 5.0);
  }

  chi = chiSquared(0.95, 4);

  if (V < chi) {
    cout << "Satisfy criterion D\n";
  }
  else {
    cout << "Don't satisfy criterion D\n";
  }
  cout << "V = " << V << "\n";
  cout << "chi-squared(0.95, " << 4 << ") = " << chi << "\n";

  return 0;
}