#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/*
perform depth first search {
 visited[source node]=true
    for all unvisited neighbours:
        stack.push(neighbor)
}
*/
void DFS(int node, stack<int> &nodeStack, vector<int> &visited, vector<vector<int>> adj)
{
    visited[node] = 1;
    for (auto neighbor : adj[node])
    {
        if (!visited[neighbor])
        {
            DFS(neighbor, nodeStack, visited, adj);
        }
    }
    nodeStack.push(node);
}

// traverse the adjacency list
// transpose edges
void getTranspose(vector<int> &visited, vector<vector<int>> adj, vector<int> transpose[], int n)
{
    for (int i = 1; i <= n; i++)
    {
        visited[i] = 0;
        for (auto neighbor : adj[i])
        {
            transpose[neighbor].push_back(i);
        }
    }
}

// print source (from stack)
// mark it as visited[source]
// for all unvisited source neighbours of transposed graph:
// DFSrev(node)

void DFSRev(int node, vector<int> &visited, vector<int> transpose[])
{
    cout << char(node + 'a' - 1) << " ";
    visited[node] = 1;
    for (auto neighbor : transpose[node])
    {
        if (!visited[neighbor])
        {
            DFSRev(neighbor, visited, transpose);
        }
    }
}

/*

perform DFS on unvisted nodes
    transpose get transposed graph
while stack is not empty:
   source = stack.top()
    stack.pop()
if not visisted:
  DFSrev(source)

  */

void getGroups(stack<int> &nodeStack, vector<int> &visited, vector<vector<int>> adj, vector<int> transpose[], int n)
{
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            DFS(i, nodeStack, visited, adj);
        }
    }
    getTranspose(visited, adj, transpose, n);
    while (!nodeStack.empty())
    {
        int node = nodeStack.top();
        nodeStack.pop();
        if (!visited[node])
        {
            cout << "Group: ";
            DFSRev(node, visited, transpose);
            cout << "\n";
        }
    }
}

int main()
{
    int n = 5;
    vector<int> visited(n + 1, 0);
    vector<int> transpose[n + 1];
    stack<int> nodeStack;
    vector<vector<int>> adj(n + 1);

    adj[1] = {2};
    adj[2] = {4, 3};
    adj[3] = {5};
    adj[4] = {1};

    cout << "Test case 1:\n";
    getGroups(nodeStack, visited, adj, transpose, n);

    cout << "\nExample 2:\n";
    int i = 11;

    vector<int> visited2(i + 1, 0);
    vector<int> transpose2[i + 1];
    stack<int> nodeStack2;
    vector<vector<int>> adj2(i + 1);

    adj2[1] = {3};
    adj2[2] = {1};
    adj2[3] = {2};
    adj2[4] = {2, 6};
    adj2[5] = {4};
    adj2[6] = {5, 7};
    adj2[7] = {10};
    adj2[8] = {7};
    adj2[9] = {8};
    adj2[10] = {9};
    adj2[11] = {10};

    getGroups(nodeStack2, visited2, adj2, transpose2, i);

    return 0;
}
