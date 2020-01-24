
/*
 * 007.分发糖果
 * 问题描述: https://leetcode.com/problems/candy
 * 提示:
 * a[i+1] > a[i]: 糖果 += 1
 * a[i+1] = a[i]: 糖果 = 1
 * a[i+1] < a[i]: 单调递减序列长度为k，则糖果按照k...1分配
 * 时间复杂度: time_complexity = O(n)
 * 空间复杂度: space_complexity = O(1)
 */

class Solution {
public:
    int candy(vector<int>& ratings)
    {
        if (ratings.empty()) { return 0; }
        
        int i = 0;
        int cur_candy = 1;
        int sum_candy = 1;
        while (i+1 < ratings.size())
        {
            if (ratings[i+1] > ratings[i])
            {
                cur_candy += 1;
                sum_candy += cur_candy;
                i += 1;
                continue;
            }
            
            if (ratings[i+1] == ratings[i])
            {
                cur_candy = 1;
                sum_candy += cur_candy;
                i += 1;
                continue;
            }
            
            // ratings[i+1] < ratings[i]
            int mono_decrease_seq_len = 2;
            i += 1;
            while (i+1 < ratings.size() && ratings[i+1] < ratings[i])
            {
                mono_decrease_seq_len += 1;
                i += 1;
            }
            
            sum_candy += (1 + mono_decrease_seq_len-1) * (mono_decrease_seq_len-1) / 2;
            sum_candy += mono_decrease_seq_len > cur_candy ? (mono_decrease_seq_len - cur_candy) : 0;
            cur_candy = 1;
        }
        
        return sum_candy;
    }
};
