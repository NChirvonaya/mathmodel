#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <sstream>

using namespace std;

void ch_screen(short y, short x, string c, int len)
{
  HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(hndl, &csbi);
  DWORD written;
  //DWORD n = csbi.dwSize.X * csbi.dwCursorPosition.Y + csbi.dwCursorPosition.X + 1;
  COORD curhome = { x,y };
  for (int i(0); i < len; ++i) {
    curhome.X++;
    FillConsoleOutputCharacter(hndl, c[i], 1, curhome, &written);
  }
  /*csbi.srWindow.Bottom -= csbi.srWindow.Top;
  csbi.srWindow.Top = 0;
  SetConsoleWindowInfo(hndl, TRUE, &csbi.srWindow);
  SetConsoleCursorPosition(hndl, curhome);*/
}

void clear_screen()
{
  HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(hndl, &csbi);
  DWORD written;
  DWORD n = csbi.dwSize.X * csbi.dwCursorPosition.Y + csbi.dwCursorPosition.X + 1;
  COORD curhome = { 0,0 };
  FillConsoleOutputCharacter(hndl, ' ', n, curhome, &written);
  csbi.srWindow.Bottom -= csbi.srWindow.Top;
  csbi.srWindow.Top = 0;
  SetConsoleWindowInfo(hndl, TRUE, &csbi.srWindow);
  SetConsoleCursorPosition(hndl, curhome);
}

int main()
{

  freopen("cup.txt", "r", stdin);
  vector<string> cup;
  string s;
  while (cin >> s) {
    cup.push_back(s);
  }

  double t0(27.0);
  double tt(97.0);
  double speed(1.0);
  double time(10.0);
  double eps(1e-3);

  double t(t0);

  int n(time / eps);
  int p(0), prevp(0);
  string prevc("_"), c("@");

  HWND console = GetConsoleWindow();
  RECT r;
  GetWindowRect(console, &r); 

  MoveWindow(console, r.left, r.top, 800, 700, TRUE);

  cout << "Time: " << fixed << setprecision(5) << 0 << "\n";
  cout << "Temperature: " << fixed << setprecision(5) << t0 << "\n";
  for (size_t j(0); j < cup.size(); ++j) {
    for (size_t k(0); k < cup[j].size(); ++k) {
      if (j == p && k == 27) {
        cout << "@";
      }
      else {
        cout << cup[j][k];
      }
    }
    cout << "\n";
  }
  
  for (int i(0); i < n; ++i) {
    t += eps*speed*(tt - t);
    std::stringstream ss1, ss2;
    ss1 << fixed << setprecision(5) << eps*(i + 1);
    ss2 << fixed << setprecision(5) << t;
    std::string str = ss1.str();
    ch_screen(0, 6, str, 8);
    str = ss2.str();
    ch_screen(1, 12, str, 8);
    p = (i + 1) * 29 / n;
    if (p > prevp) {
      ch_screen(prevp + 2, 26, prevc, 1);
      prevc = cup[p][26];
      ch_screen(p + 2, 26, c, 1);
      prevp = p;
    }
    
  }



  return 0;
}