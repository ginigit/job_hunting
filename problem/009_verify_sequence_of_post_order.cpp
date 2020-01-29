
/*
 * 009.二叉查找树的后序遍历序列
 * 问题描述: 输入一个数组，任意元素互不相同，判断该数组是不是二叉查找树的后序遍历序列。
 * 提示: 后序遍历序列的特点:
 * a[end]是根节点
 * a[start...partition-1]是左子树，左子树任意元素必须小于根节点
 * a[partition...end-1]是右子树，右子树任意元素必须大于根节点
 */

class Solution {
public:
    
    bool VerifySequenceOfBST(vector<int>& seq, int start, int end)
    {
        int partition = -1;
        for (int i = start; i < end; ++i)
        {
            if (partition == -1 && seq[i] > seq[end])
            {
                partition = i;
                continue;
            }
            
            if (partition != -1 && seq[i] < seq[end])
            {
                return false;
            }
        }
        
        if (partition == -1) // only left subtree exists
        {
            partition = end;
        }
        
        bool isLeftValid = true;
        bool isRightValid = true;
        
        if (start < partition - 1)
        {
            isLeftValid = VerifySequenceOfBST(seq, start, partition-1);
        }
        
        if (partition < end - 1)
        {
            isRightValid = VerifySequenceOfBST(seq, partition, end-1);
        }
        
        return isLeftValid && isRightValid;
    }
    
    bool VerifySequenceOfBST(vector<int>& seq)
    {
        if (seq.empty()) { return false; }
        
        return VerifySequenceOfBST(seq, 0, seq.size()-1);
    }
};
