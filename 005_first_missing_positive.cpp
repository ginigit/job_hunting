
/*
 * 005.第一个缺失的正整数
 * 问题描述: https://leetcode.com/problems/first-missing-positive
 * 提示:
 * 若k = a[i] == i+1, 则数值k已经位于合适的位置
 * 若k = a[i] != i+1, 则需要将数值k调整到合适的位置
 * 数值k合适的位置应当是: a[k-1]
 * 迭代执行以下操作将数值调整到合适的位置: tmp = a[k-1]; a[k-1] = k; k = tmp;
 * 时间复杂度: time_complexity = O(n)
 * 空间复杂度: space_complexity = O(1)
 */

class Solution {
public:
    int firstMissingPositive(vector<int>& nums)
    {
        for (int i = 0; i < nums.size(); ++i)
        {
            if (nums[i] <= 0 || nums[i] > nums.size() || nums[i] == i+1)
            {
                continue;
            }
            
            // 0 < nums[i] <= nums.size() && nums[i] != i+1, find suitable place for k
            int k = nums[i];
            while (nums[k - 1] != k)
            {
                int tmp = nums[k - 1];
                nums[k - 1] = k;
                
                if (tmp <= 0 || tmp > nums.size())
                {
                    break;
                }
                
                k = tmp;
            }
        }
        
        for (int i = 0; i < nums.size(); ++i)
        {
            if (nums[i] != i + 1) { return i + 1; }
        }
        
        return nums.size() + 1;
    }
};
