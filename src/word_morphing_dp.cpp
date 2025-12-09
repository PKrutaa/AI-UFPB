/**
* @file word_morphing_dp.cpp
* @author GabrielCampelo
* Created on 2025-12-01 at 18:15:35
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

string a, b;

vector<string> reconstruct(vector<vector<int>> &dp) {
    int i = a.size();
    int j = b.size();

    vector<string> path;
    string cur = b; 
    path.push_back(cur);

    while (i > 0 || j > 0) {
        // Match/Substitution
        if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + (a[i - 1] != b[j - 1])) {
            if (a[i - 1] != b[j - 1]) {
                // Substitution b[j-1] -> a[i-1]
                cur[j - 1] = a[i - 1];
                path.push_back(cur);
            }
            i--, j--;
        }

        // Delete
        else if (j > 0 && dp[i][j] == dp[i][j - 1] + 1) {
            cur.erase(cur.begin() + (j - 1));
            j--;
            path.push_back(cur);
        }

        // Insert
        else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            cur.insert(cur.begin() + j, a[i - 1]);
            i--;
            path.push_back(cur);
        }
    }

    reverse(path.begin(), path.end());
    return path;
}

void print(vector<vector<int>> &dp) {
    cout << "   ";
    for (int j = 0; j <= b.size(); j++) {
        cout << b[j - 1] << " ";
    }
    cout << endl;
    for (int i = 0; i <= a.size(); i++) {
        if (i == 0) cout << "  ";
        else cout << a[i - 1] << " ";
        for (int j = 0; j <= b.size(); j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() { 
    cout << "Enter source: ";
    cin >> a;
    cout << "Enter target: ";
    cin >> b;

    vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1, INF));

    dp[0][0] = 0;

    for (int i = 0; i <= a.size(); i++) {
        for (int j = 0; j <= b.size(); j++) {
            if (i != 0) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
            }

            if (j != 0) {
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
            }

            if (i != 0 && j != 0) {
                int tmp = dp[i - 1][j - 1] + (a[i - 1] != b[j - 1]);
				dp[i][j] = min(dp[i][j], tmp);
            }
        }
    }

    print(dp);

    cout << "Edit Distance: ";
    cout << dp[a.size()][b.size()] << endl;
    
    vector<string> path = reconstruct(dp);
    
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << (i == path.size() - 1 ? "\n" : " -> ");
    } 

    return 0;
}