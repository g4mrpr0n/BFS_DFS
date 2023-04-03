#include <iostream>
#include <queue>
#include <fstream>
#include <chrono>
#define N 11
using namespace std;
using namespace std::chrono;
ifstream in("input.txt");
fstream out("results.txt", std::fstream::in | std::fstream::out | std::fstream::app);
bool graphU[N][N], graphB[N][N], visited[N];

bool BFS(bool adjMatrix[][N], int start, int end)
{
    bool visited[N] = { false };
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        if (curr == end) {
            return true;
        }

        for (int i = 0; i < N; i++) {
            if (adjMatrix[curr][i] && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    return false;
}
bool DFS(bool adjMatrix[][N], bool visited[], int start, int end)
{
    visited[start] = true;

    if (start == end) {
        return true;
    }

    for (int i = 0; i < N; i++) {
        if (adjMatrix[start][i] && !visited[i]) {
            if (DFS(adjMatrix, visited, i, end)) {
                return true;
            }
        }
    }

    return false;
}
void resetArray(bool v[])
{
    for (int i = 0; i < N; i++)
    {
        v[i] = 0;
    }
}
void input(bool graph[][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            in >> graph[i][j];
        }
    }
}
void outputMetrics(char f, char x, int a, int b)
{
    resetArray(visited);
    string s;
    auto search_start = high_resolution_clock::now();
    switch (f)
    {
    case '1':
        if (x == 'b')
             DFS(graphB, visited, a, b);
        else DFS(graphU, visited, a, b);
        s = "DFS: ";
        break;
    case '2':
        if (x == 'b')
             BFS(graphB, a, b);
        else BFS(graphU, a, b);
        s = "BFS: ";
        break;
    }
    auto search_stop = high_resolution_clock::now();
    auto duration_search = duration_cast<nanoseconds>(search_stop - search_start);
    cout  << a << "-" << b << "\t" << duration_search.count() / 1e3f << endl;
}

int main()
{
    input(graphB);
    input(graphU);
    outputMetrics('1', 'b', 0, 1);
    outputMetrics('1', 'b', 0, 2);
    outputMetrics('1', 'b', 0, 3);
    outputMetrics('1', 'b', 0, 6);
    outputMetrics('1', 'b', 0, 8);

    outputMetrics('2', 'b', 0, 1);
    outputMetrics('2', 'b', 0, 2);
    outputMetrics('2', 'b', 0, 3);
    outputMetrics('2', 'b', 0, 6);
    outputMetrics('2', 'b', 0, 8);

    outputMetrics('1', 'u', 0, 1);
    outputMetrics('1', 'u', 0, 3);
    outputMetrics('1', 'u', 0, 6);
    outputMetrics('1', 'u', 0, 9);
    outputMetrics('1', 'u', 0, 10);

    outputMetrics('2', 'u', 0, 1);
    outputMetrics('2', 'u', 0, 3);
    outputMetrics('2', 'u', 0, 6);
    outputMetrics('2', 'u', 0, 9);
    outputMetrics('2', 'u', 0, 10);
}
