
/*
 * 003.从上往下打印二叉树
 * 问题描述: 从上往下，从左往右，依次访问二叉树节点
 * 提示: 使用队列，按照当前节点、左子节点、右子节点依次入队
 */

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        vector<int> res;
        if (root == NULL) { return res; }
        
        std::list<TreeNode*> q;
        q.push_back(root);
        
        while (!q.empty())
        {
            TreeNode* pCurNode = q.front();
            res.push_back(pCurNode->val);
            
            if (pCurNode->left)
            {
                q.push_back(pCurNode->left);
            }
            
            if (pCurNode->right)
            {
                q.push_back(pCurNode->right);
            }
            
            q.pop_front();
        }
        
        return res;
    }
};
