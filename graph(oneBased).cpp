#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <climits>

using namespace std;

class Graph {
private:
    vector<pair<int, int>> *adjList;
    vector<vector<int>> adj;
    vector<int> nodes;
    vector<bool> ves;
public:
    // Constructor to initialize vectors
    Graph(int size) {
        adjList = new vector<pair<int, int>>[size];
        adj.resize(size, vector<int>(size, 0));
        ves.resize(size); // Initialize ves with size (all elements set to false)
    }

    void insertNodes(int a, int b) {
        nodes.push_back(a);
        nodes.push_back(b);
    }

    void insert(int a, int b) {
        insertNodes(a, b);
        adj[a][b] = adj[b][a] = 1;
        adjList[a].push_back({b, 0});
        adjList[b].push_back({a, 0});
    }

    void insertWei(int a, int b, int weight) {
        insertNodes(a, b);
        adj[a][b] = adj[b][a] = weight;
        adjList[a].push_back({b, weight});
        adjList[b].push_back({a, weight});
    }

    void insertDirWei(int a, int b, int weight) {
        insertNodes(a, b);
        adj[a][b] = weight;
        adjList[a].push_back({b, weight});
    }

    void insertDir(int a, int b) {
        insertNodes(a, b);
        adj[a][b] = 1;
        adjList[a].push_back({b, 0});
    }

    void print(int size) {
    cout << "Matrix:\n";
        for (int i = 1; i < size; ++i) {
            for (int j = 1; j < size; ++j) {
                cout << adj[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "________________\n";
        cout << "Adjacency List:\n";
        for (int i = 1; i < size; ++i) {
            cout << i << "=> {";
            for (pair<int, int> p : adjList[i]) {
                cout << "(" << p.first << ", " << p.second << "), ";
            }
            cout << "}\n";
        }
    }

    void BFS(int root){
        queue<int> q;
        q.push(root);
        const int OO = 0x3f3f3f3f;
        vector<int> level(ves.size(), OO);
        level[root] = 0;

        cout << "BFS:\n";
        while(!q.empty()){
            int node = q.front();
            cout << node << " in level " << level[node] << '\n';
            q.pop();
            for (int i = 0; i < adjList[node].size(); ++i){
                int child = adjList[node][i].first;
                if (level[child] == OO){
                    level[child] = level[node] + 1;
                    q.push(child);
                }
            }
        }
    }

    void dfs(int node){
        ves[node] = true;
        cout << node << " ";
        for (int i = 0;i < adjList[node].size(); ++i){
            int nextNode = adjList[node][i].first;
            if (!ves[nextNode]){ 
                dfs(nextNode); 
            }
        }
    }

    void DFS(int node){
        int size = ves.size();
        ves.clear();
        this->ves.resize(size);
        dfs(node);
    }

    void DFS_Iter(int root){
        cout << "DFS_Iter:\n";
        stack<int> q;
        vector<int> vis(ves.size(), 0);

        q.push(root);
        vis[root] = 1;
        while(!q.empty()){
            int node = q.top();
            cout << node << " ";
            q.pop();
            for (int i = 0; i < adjList[node].size(); ++i){
                int child = adjList[node][i].first;
                if (!vis[child]){
                    vis[child] = 1;
                    q.push(child);
                }
            }
        }
    }
    // Define a custom comparator to compare pairs based on the second value
    class CompareSecond {
    public:
        bool operator()(const pair<int, int>& a, const pair<int, int>& b) const {
            return a.second > b.second;
        }
    };

    void MST(int start, int size){
        priority_queue<pair<int, int>, vector<pair<int, int>>, CompareSecond> pq;
        vector<pair<int, int>> *mst = new vector<pair<int, int>>[size];
        const int OO = 0x3f3f3f3f;
        vector<int> key(size, OO);
        vector<bool> vis(size);
        map<int, int> parent;
        key[start] = 0;
        
        pq.push({start, 0});

        // Pop elements from the priority queue
        while (!pq.empty()) {
            // Extract minimum
            int u = pq.top().first;
            pq.pop();
            vis[u] = true;
            for (int i = 0; i < adjList[u].size(); ++i){
                int child = adjList[u][i].first;
                int childWeight = adjList[u][i].second;
                if (!vis[child] && childWeight < key[child]){
                    // Update the weight of the child if better weight is found
                    pq.push({child, childWeight});
                    key[child] = childWeight;
                    parent[child] = u;
                }
            }
        }
        cout << "MST:\n";
        map<int, int>::iterator it = parent.begin();
        long long sum = 0;
        // Iterate through the map and print the elements
        while (it != parent.end()) {
            int child = it->first;
            int parent = it->second;
            int weight = key[child];
            sum += weight;
            mst[child].push_back({parent, weight});
            mst[parent].push_back({child, weight});
            ++it;
        }

        for (int i = 1; i < size; ++i) {
            cout << i << "=> {";
            for (pair<int, int> p : mst[i]) {
                cout << "(" << p.first << ", " << p.second << "), ";
            }
            cout << "}\n";       
        }
        cout << "\nTotal Cost OF MST = " << sum << '\n';
    }

    void DIalgo(int start, int size, int end){
        priority_queue<pair<int, int>, vector<pair<int, int>>, CompareSecond> pq;
        vector<pair<int, int>> *shPath = new vector<pair<int, int>>[size];
        const int OO = 0x3f3f3f3f;
        vector<bool> vis(size);
        vector<int> key(size, OO);

        map<int, int> parent;
        key[start] = 0;
        
        pq.push({start, 0});

        // Pop elements from the priority queue
        while (!pq.empty()) {
            // Extract minimum
            int u = pq.top().first;
            pq.pop();
            vis[u] = true;
            for (int i = 0; i < adjList[u].size(); ++i){
                int child = adjList[u][i].first;
                int childWeight = adjList[u][i].second;
                
                if (!vis[child] && key[u] + childWeight < key[child]){
                    // Update the weight of the child if better weight is found
                    key[child] = key[u] + childWeight;
                    pq.push({child, key[child]});
                    parent[child] = u;
                }
            }
        }
        cout << "Dijkstra:\n";
        map<int, int>::iterator it = parent.begin();
        // Iterate through the map and print the elements
        while (it != parent.end()) {
            int child = it->first;
            int parent = it->second;
            int weight = key[child];
            shPath[parent].push_back({child, weight});
            ++it;
        }

        for (int i = 1; i < size; ++i) {
            cout << i << "=> {";
            for (pair<int, int> p : shPath[i]) {
                cout << "(" << p.first << ", " << p.second << "), ";
            }
            cout << "}\n";       
        }
            
        cout << "\nShortest distances FROM VERTEX " << start << ":\n";
        for (int i = 1; i < size; ++i) {
            cout << "To Vertex " << i << ": ";
            if (key[i] == OO) {
                cout << "INFINITE\n";
            } else {
                cout << key[i] << "\n";
            }
        }

        vector<int> path;
        path.push_back(end);
        int p = parent[end];
        path.push_back(p);
        while(!(parent.find(p) == parent.end())){
            p = parent[p];
            path.push_back(p);
        }

        for(int i = path.size() - 1; i >= 0; --i){
            if (i == 0){
                cout << path[i] << '\n';
                cout << "Cost to End: " << key[end]; 
            }else {
                cout << path[i] << "->";
            }
        }

    }

    int ConnectedComponent(){
        int size = ves.size();
        ves.clear();
        this->ves.resize(size);
        int counter = 0;
        for (int i = 1;i < size; ++i){
            if (!ves[i]){
                cout << "\nDFS\n";
                dfs(i); 
                ++counter;
            }
        }
        cout << "\n Connected Component";
        return counter;
    }
    
    vector<int> BFSShortestPath(int root, int weight, int end){
        queue<int> q;
        q.push(root);
        const int OO = 0x3f3f3f3f;
        vector<int> des(ves.size(), -1);
        des[root] = 0;
        map<int, int> parent;

        while(!q.empty()){
            int node = q.front();
            q.pop();
            for (int i = 0; i < adjList[node].size(); ++i){
                int child = adjList[node][i].first;
                if (des[child] == -1){
                    des[child] = des[node] + weight;
                    parent[child] = node;
                    q.push(child);
                }
            }
        }
        cout << "\nShortest distances FROM VERTEX " << root << ":\n";
        for (int i = 1; i < des.size(); ++i) {
            cout << "To Vertex " << i << ": ";
            if (des[i] == -1) {
                cout << "INFINITE\n";
            } else {
                cout << des[i] << "\n";
            }
        }

        vector<int> path;
        path.push_back(end);
        int p = parent[end];
        path.push_back(p);
        while(!(parent.find(p) == parent.end())){
            p = parent[p];
            path.push_back(p);
        }

        for(int i = path.size() - 1; i >= 0; --i){
            if (i == 0){
                cout << path[i] << '\n';
                cout << "Cost to End: " << des[end]; 
            }else {
                cout << path[i] << "->";
            }
        }
        cout << '\n';
        return des;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    // one Based
    Graph g(n + 1);

    int u, v;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        g.insert(u, v);
    }

    // Weighted Graph
    // int w;
    // for (int i = 0; i < m; i++) {
    //     cin >> u >> v >> w;
    //     g.insertWei(u, v , w);
    // }
    g.print(n + 1);
    g.BFS(1);
    cout << "\nDFS:\n";
    g.DFS(1);
    cout << "\n-----------\n\n";
    g.DFS_Iter(1);
    cout << "\n-----------\n\n";
    g.DIalgo(1, n + 1, 2);
    cout << "\n-----------\n\n";
    g.BFSShortestPath(1, 6, 2);
    cout << "\n-----------\n\n";
    g.MST(1 , n+1);
    cout << "\n-----------\n\n";
    cout << g.ConnectedComponent();
    return 0;
}

/*
8 8
0 1
0 2
0 3
1 4
1 5
2 6
2 7
3 7
*/

/*
8 10
0 1 15
0 3 7
0 7 10
3 2 9
3 5 5
3 4 12
4 5 6
5 6 14
5 7 8
6 7 3
*/

/*
9 14
0 1 4
0 7 8
1 2 8
1 7 11
2 3 7
2 8 2
2 5 4
3 4 9
3 5 14
4 5 10
5 6 2
6 7 1
6 8 6
7 8 7
*/