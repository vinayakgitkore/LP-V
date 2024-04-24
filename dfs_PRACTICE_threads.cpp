#include <iostream>
#include <queue>
#include <chrono>
#include <iomanip>
#include <omp.h>
using namespace std;
using namespace std::chrono;

class Node {
public:
    int key;
    Node* left;
    Node* right;

    Node(int k) {
        key = k;
        left = right = NULL;
    }
};

// Parallel BFS on a binary tree
void parallelBFS(Node* root) {
    if (root == nullptr)
        return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();

        // Traverse all nodes at the current level
        #pragma omp parallel for num_threads(omp_get_num_threads())
        for (int i = 0; i < levelSize; ++i) {
            Node* curr;
            #pragma omp critical
            {
                curr = q.front();
                q.pop();
            }
            cout << curr->key << " ";

            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
        }
    }
}

int main() {
    Node* root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30);
    root->left->left = new Node(40);
    root->left->right = new Node(50);

    cout << "Parallel BFS traversal: ";
    auto start = high_resolution_clock::now();
    int numThreads;
    #pragma omp parallel
    {
        #pragma omp master
        numThreads = omp_get_num_threads();
    }
    parallelBFS(root);
    cout << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start).count() / 1e9;
    cout << "Parallel BFS Execution Time: " << fixed << setprecision(10) << duration << " seconds" << endl;
    cout << "Number of Threads Used: " << numThreads << endl;

    return 0;
}
