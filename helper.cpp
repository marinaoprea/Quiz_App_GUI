#include <iostream>
#include <algorithm>
#include "helper.h"

using namespace std;

bool equal_strings(const string &x, const string &y)
{
    string auxx, auxy;

    auto it1 = back_inserter(auxx);
    auto it2 = back_inserter(auxy);

    transform(x.cbegin(), x.cend(), it1, [](auto c){return tolower(c);});
    transform(y.cbegin(), y.cend(), it2, [](auto c){return tolower(c);});
    
    return auxx == auxy;
}

short int levenstein(const string &a, const string &b)
{
    short int dp[LGMAX][LGMAX];

    for (int i = 0; i <= a.length(); i++)
        dp[i][0] = i;
    for (int i = 0; i <= b.length(); i++)
        dp[0][i] = i;

    for (int i = 1; i <= a.length(); i++)
        for (int j = 1; j <= b.length(); j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
                continue;
            }

            dp[i][j] = 1 + min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1]));
        }

    return dp[a.length()][b.length()];
}