#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n];
    int s[n];
    int dp[n][n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        dp[i][i] = 0;
    }
    s[0] = a[0];
    for (int i = 1; i < n; i++) {
        s[i] = s[i-1] + a[i];
    }
    for (int t = 1; t < n; t++) {
        for (int i = 0; i < n; i++) {
            if(i + t >= n)
                break;
            int mn = 1e9;
            for (int j = i; j <= i + t; j++) {
                mn = min(mn, (j - 1 >= i ? s[j-1] - (i - 1 < 0 ? 0 : s[i-1]) + dp[i][j-1] : 0) +
                         (j + 1 <= i + t ? s[i+t] - s[j] + dp[j+1][i+t] : 0));
            }
            dp[i][i+t] = mn;
        }
    }
    cout << dp[0][n-1] << '\n';
    return 0;
}


