#include <string>
#include <vector>
#include "SuffixArray.h"
#include <bits/stdc++.h>
using namespace std;

/**
 * Implement suffix_array() correctly
 */
vector<unsigned int> suffix_array(const string & s) {
    /* YOUR CODE HERE */
    vector<unsigned int> SA;
    for (int i = s.size() - 1; i >= 0; --i) SA.push_back(i);
    stable_sort(SA.begin(), SA.end(), [&](int a, int b) { return s[a] < s[b]; });
    vector<unsigned int> classes(s.size());
    for (long unsigned int i = 0; i < s.size(); ++i) classes[i] = s[i];
    for (long unsigned int len = 1; len < s.size(); len *= 2) {
        vector<unsigned int> c = classes;
        for (long unsigned int i = 0; i < s.size(); i++) {
            classes[SA[i]] =
                i > 0 && c[SA[i - 1]] == c[SA[i]] && SA[i - 1] + len < s.size() && c[SA[i - 1] + len / 2] == c[SA[i] + len / 2]
                    ? classes[SA[i - 1]]
                    : i;
        }
        vector<int> cnt(s.size());
        iota (cnt.begin(), cnt.end(), 0);
        vector<unsigned int> s = SA;
        for (long unsigned int i = 0; i < s.size(); i++) {
            int s1 = s[i] - len;
            if (s1 >= 0) SA[cnt[classes[s1]]++] = s1;
        }
    }
    return SA;
}
