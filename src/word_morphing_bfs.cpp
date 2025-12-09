#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n = 456976; //26^4

int cnt_neighborhood = 1;
vector<int> parent; 
vector<int> dist; 

//convertendo string para numero unico, pq eu to usando vetor 
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
    int s = get_index(source);
    int t = get_index(target);

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
        
        // os dois fors aninhados geram todas as palavras possíveis a partir de "v"
        // eh basicamento um for each como esse
        // for (string u : adj[v]) 
        for (int i = 0; i < 4; i++) {
            for (char c = 'A'; c <= 'Z'; c++) {
                if (c == v[i]) continue;
                
                string u = v; // v = GATO
                u[i] = c;     // u = TATO ex:
                
                if (dist[get_index(u)] == -1) {
                    cnt_neighborhood++;
                    dist[get_index(u)] = dist[get_index(v)] + 1;
                    q.push(u);
                    parent[get_index(u)] = get_index(v);
                    if (u == target) return; // encontrou o alvo
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

    bfs(source, target);

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