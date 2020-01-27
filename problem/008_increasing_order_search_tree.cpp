
/*
 * 008.递增序列二叉查找树
 * 问题描述: https://leetcode.com/problems/increasing-order-search-tree
 * 提示: 本题属于二叉树中序遍历的衍生问题
 * 访问左子获取prev -> 连接prev.right和node -> prev=node & node.left=null -> 访问右子
 * 时间复杂度: time_complexity = O(n)
 * 空间复杂度: space_complexity = O(1)
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* res;
    TreeNode* prev;
    Solution() : res(NULL), prev(NULL) {}
    
    void inorder(TreeNode* node)
    {
        if (node->left != NULL)
        {
            inorder(node->left);
        }
        
        if (res == NULL) // find the new root
        {
            res = node;
        }
        
        if (prev != NULL) // connect 'prev' and 'node'
        {
            prev->left = NULL;
            prev->right = node;
        }
        
        prev = node;
        node->left = NULL;
        
        if (node->right != NULL)
        {
            inorder(node->right);
        }
    }
    
    TreeNode* increasingBST(TreeNode* root)
    {
        if (root == NULL) { return NULL; }
        
        inorder(root);
        return res;
    }
};
