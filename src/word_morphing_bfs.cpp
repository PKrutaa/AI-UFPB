#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>

using namespace std;

int n = 456976; // 26^4

int cnt_neighborhood = 1;
vector<int> parent;
vector<int> dist;

// convertendo string para número
int get_index(string s){
    return (s[0]-'A')*26*26*26 +
           (s[1]-'A')*26*26 +
           (s[2]-'A')*26 +
           (s[3]-'A');
}

// converte número -> string
string get_string(int x){
    string s(4,'A');
    s[3] = 'A' + x%26; x/=26;
    s[2] = 'A' + x%26; x/=26;
    s[1] = 'A' + x%26; x/=26;
    s[0] = 'A' + x%26;
    return s;
}

void bfs(string source, string target) {
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
        dist[i] = -1;
    }

    string v = source;
    queue<string> q;
    q.push(v);
    dist[get_index(v)] = 0;
    parent[get_index(v)] = get_index(v);

    if (source == target) return;

    while (!q.empty()) {
        v = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            for (char c = 'A'; c <= 'Z'; c++) {
                if (c == v[i]) continue;

                string u = v;
                u[i] = c;

                if (dist[get_index(u)] == -1) {
                    cnt_neighborhood++;
                    dist[get_index(u)] = dist[get_index(v)] + 1;
                    q.push(u);
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

    auto start = chrono::high_resolution_clock::now();
    bfs(source, target);
    auto end = chrono::high_resolution_clock::now();
    // tempo em ms (float)
    double elapsed_ms = chrono::duration<double, milli>(end - start).count();


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
    cout << "Time (ms): " << elapsed_ms << endl;

    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << (i == path.size() - 1 ? "\n" : " -> ");
    }
}
