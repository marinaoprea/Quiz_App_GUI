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