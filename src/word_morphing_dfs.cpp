#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int n = 456976; // 26^4

int cnt_neighborhood = 1;
vector<int> parent; 
vector<int> dist; 

int get_index(string s){
    return (s[0]-'A')*26*26*26 +
           (s[1]-'A')*26*26 +
           (s[2]-'A')*26 +
           (s[3]-'A');
}

string get_string(int x){
    string s(4,'A');
    s[3] = 'A' + x%26; x/=26;
    s[2] = 'A' + x%26; x/=26;
    s[1] = 'A' + x%26; x/=26;
    s[0] = 'A' + x%26;
    return s;
}

void dfs(string source, string target) {
    if (source == target) return;

    for (int i = 0; i <= n; i++) {
        parent[i] = i;
        dist[i] = -1; 
    }

    string v = source;
    stack<string> s;
    s.push(v);
    dist[get_index(v)] = 0;
    parent[get_index(v)] = get_index(v);

    while (!s.empty()) {
        v = s.top();
        s.pop();

        for (int i = 0; i < 4; i++) {
            for (char c = 'A'; c <= 'Z'; c++) {
                if (c == source[i]) continue;
        
                string u = v;
                u[i] = c;     

                if (dist[get_index(u)] == -1) {
                    cnt_neighborhood++;
                    dist[get_index(u)] = dist[get_index(v)] + 1;
                    s.push(u);
                    parent[get_index(u)] = get_index(v);
                    if (u == target) return;
                }
            }
        }
    }   
}

int main() {
    parent.resize(n);
    dist.resize(n);

    string source, target;
    cin >> source >> target;

    dfs(source, target);

    vector<string> path;
    string curr = target;

    while (curr != source) {
        path.push_back(curr);
        curr = get_string(parent[get_index(curr)]);
    }
    path.push_back(source);

    reverse(path.begin(), path.end());

    cout << "Total nodes processed: " << cnt_neighborhood << endl;
    cout << "Number of transformations: " << dist[get_index(target)] << endl;
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << (i == path.size() - 1 ? "\n" : " -> ");
    }
}