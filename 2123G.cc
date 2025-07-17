/*
 * Problem: https://codeforces.com/contest/2123/problem/G
 * Author:  https://github.com/saltycookie
 * Date:    07/16/2025
 */
#include <cstring>
#include <iostream>
#include <vector>
 
using std::vector;

int gcd(int a, int b) {
  if (a < b) {
    int temp = a;
    a = b;
    b = temp;
  }
  while (a % b) {
    int temp = a % b;
    a = b;
    b = temp;
  }
  return b;
}
 
int num_descends(int a, int b, int c) {
  return (a > b) + (b > c);
}
 
int factor2idx[500000 + 1];

 
int main() {
  // Faster IO
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
 
  int num_cases;
  std::cin >> num_cases;
  while (num_cases --) {
    int n, m, q;
    std::cin >> n >> m >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      std::cin >> a[i];
    }
    memset(factor2idx, -1, m * sizeof(int));
    vector<vector<int>> remainders;
    vector<int> factors;
    vector<int> dips;
    for (int i = 0; i < q; ++i) {
      int cmd;
      std::cin >> cmd;
      if (cmd == 1) {
        int j, x;
        std::cin >> j >> x;
        --j;
        a[j] = x;
        for (int idx = 0; idx < factors.size(); ++idx) {
          int new_remainder = a[j] % factors[idx];
          int old_remainder = remainders[idx][j];
          int prev = (j == 0) ? -1 : remainders[idx][j - 1];
          int next = (j == n - 1) ? factors[idx] : remainders[idx][j + 1];
          dips[idx] += num_descends(prev, new_remainder, next) - num_descends(prev, old_remainder, next);
          remainders[idx][j] = new_remainder;
        }
      } else {
        int k;
        std::cin >> k;
        int factor = gcd(k, m);
        if (factor == 1) {
          std::cout << "YES" << std::endl;
        } else if (factor2idx[factor] >= 0) {
          int idx = factor2idx[factor];
          std::cout << ((dips[idx] < m / factor) ? "YES" : "NO") << std::endl;
        } else {
          int idx = factors.size();
          remainders.push_back(vector<int>(n));
          factors.push_back(factor);
          factor2idx[factor] = idx;
          dips.push_back(0);
          for (int j = 0; j < n; ++j) {
            remainders[idx][j] = a[j] % factor;
            if (j && remainders[idx][j] < remainders[idx][j - 1]) {
              ++dips[idx];
            }
          }
          std::cout << ((dips[idx] < m / factor) ? "YES" : "NO") << std::endl;
        }
      }
    }
  }
  return 0;
}
