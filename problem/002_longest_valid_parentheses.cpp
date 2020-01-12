
/*
 * 002.最长有效匹配括号
 * 问题描述: https://leetcode.com/problems/longest-valid-parentheses
 * 提示:
 * 使用栈来存储和当前右括号匹配的左括号的位置
 * 当前位置匹配子串长度 cur_valid_len = i - 左括号位置 + 1
 * 与当前位置匹配子串连续的匹配子串长度 = valid_len[左括号位置 - 1]
 * 最大匹配子串长度 valid_len[i] = cur_valid_len + valid_len[左括号位置 - 1]
 */

class Solution {
public:
    int longestValidParentheses(string s)
    {
        if (s.empty()) return 0;
        
        int longest = 0;
        
        std::list<int> list_last_left_paren_pos;
        std::vector<int> vec_last_valid_len(s.length() + 1, 0);
        
        for (int i = 0; i < s.length(); ++i)
        {
            if (s[i] == '(')
            {
                list_last_left_paren_pos.push_back(i);
            }
            else
            {
                if (list_last_left_paren_pos.empty())
                    continue;
                
                int start_pos = list_last_left_paren_pos.back();
                list_last_left_paren_pos.pop_back();
                
                // 当前最大长度 = 当前括号长度 + 起始位置连接的上次最大长度
                int cur_valid_len = i - start_pos + 1 + vec_last_valid_len[start_pos];
                longest = longest > cur_valid_len ? longest : cur_valid_len;
                
                vec_last_valid_len[i + 1] = cur_valid_len;
            }
        }
        
        return longest;
    }
};
