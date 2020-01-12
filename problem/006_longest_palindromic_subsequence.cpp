
/*
 * 004.最长回文子序列
 * 问题描述: https://leetcode.com/problems/longest-palindromic-subsequence
 * 提示:
 * i从左到右, j从右到左, 则lps问题可以转化成lcs问题
 * 注意下标相差1的问题: s[0...n-1] lps[1...n]
 * 时间复杂度: time_complexity = O(n^2)
 * 空间复杂度: space_complexity = O(n^2)
 */

class Solution {
public:
    inline int max_of_2(int a, int b)
    {
        return a > b ? a : b;
    }
    
    int longestPalindromeSubseq(string s)
    {
        if (s.empty()) { return 0; }
        
        int n = s.size();
        vector< vector<int> > dp_lps(n+2, vector<int>(n+2, 0));
        
        for (int i = 1; i <= n; ++i)
        {
            for (int j = n; j >= 1; --j)
            {
                if (s[i-1] == s[j-1])
                {
                    dp_lps[i][j] = dp_lps[i - 1][j + 1] + 1;
                }
                else
                {
                    dp_lps[i][j] = max_of_2(dp_lps[i - 1][j], dp_lps[i][j + 1]);
                }
            }
        }
        
        return dp_lps[n][1];
    }
};
