
/*
 * 004.最长公共子序列
 * 问题描述: https://leetcode.com/problems/longest-common-subsequence
 * 提示:
 * a[i] == b[j] => lcs[i][j] = lcs[i-1][j-1] + 1
 * a[i] != b[j] => lcs[i][j] = max(lcs[i-1][j], lcs[i][j-1])
 * 注意下标相差1的问题: a[0...m-1] b[0...n-1] lcs[1...m][1...n]
 * 时间复杂度: time_complexity = O(mn)
 * 空间复杂度: space_complexity = O(mn)
 */

class Solution {
public:
    inline int max_of_2(int a, int b)
    {
        return a > b ? a : b;
    }
    
    int longestCommonSubsequence(string text1, string text2)
    {
        int len1 = text1.length();
        int len2 = text2.length();
        if (len1 == 0 || len2 == 0) { return 0; }
        
        vector< vector<int> > dp_lcs(len1+1);
        for (int i = 0; i < len1+1; ++i)
        {
            dp_lcs[i] = vector<int>(len2+1, 0);
        }
        
        for (int i = 1; i < len1+1; ++i)
        {
            for (int j = 1; j < len2+1; ++j)
            {
                if (text1[i - 1] == text2[j - 1])
                {
                    dp_lcs[i][j] = dp_lcs[i-1][j-1] + 1;
                }
                else
                {
                    dp_lcs[i][j] = max_of_2(dp_lcs[i-1][j], dp_lcs[i][j-1]);
                }
            }
        }
        
        return dp_lcs[len1][len2];
    }
};
