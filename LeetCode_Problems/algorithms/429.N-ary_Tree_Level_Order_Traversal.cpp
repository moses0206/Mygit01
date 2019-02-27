/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        if (root == NULL) return vector<vector<int>>();
        vector<vector<int>> rt;
        queue<Node*> que;
        que.push(root);
        while(!que.empty()) {
            int size = que.size();
            vector<int> curLevel;
            for(int i = 0; i < size; i++) {
                Node *tmp = que.front();
                que.pop();
                curLevel.push_back(tmp->val);
                for(auto n : tmp->children) {
                    que.push(n);
                }
            }
            rt.push_back(curLevel);
        }
        return rt;
    }
};
