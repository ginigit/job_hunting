
/*
 * 010.在D天内送达包裹的运载能力
 * 问题描述: https://leetcode.com/problems/capacity-to-ship-packages-within-d-days
 * 提示: 本题属于二分查找的衍生问题
 * 运载能力下限 = max(单个包裹最大重量，D天内运送完毕所需的最小运载能力) = max(max(a[i]), sum(a[i])/D)
 * 运载能力上限 = 所有包裹1天内运送完毕 = sum(a[i])
 * 根据运载能力的下限和上限，对运载能力进行二分查找
 * 和经典二分查找的区别：
 * 经典二分查找的查找条件：mid是否等于target
 * 本题的查找条件：midCapacity是否能够实现D天内运送完毕
 */

class Solution {
public:
    inline int maxOf2(int a, int b)
    {
        return a > b ? a : b;
    }
    
    void calcMaxAndSum(vector<int>& weights, int& max, int& sum)
    {
        max = 0;
        sum = 0;
        
        for (int i = 0; i < weights.size(); ++i)
        {
            if (weights[i] > max)
            {
                max = weights[i];
            }
            
            sum += weights[i];
        }
    }
    
    int calcDays(vector<int>& weights, int capacity)
    {
        int i = 0;
        int curSum = 0;
        int days = 1;
        while (i < weights.size())
        {
            if (curSum + weights[i] <= capacity)
            {
                curSum += weights[i];
                ++i;
            }
            else
            {
                curSum = 0;
                days += 1;
            }
        }
        
        return days;
    }
    
    int shipWithinDays(vector<int>& weights, int D)
    {
        int max = 0;
        int sum = 0;
        
        calcMaxAndSum(weights, max, sum);
        
        int minCapacity = maxOf2(max, sum/D);
        int maxCapacity = sum;
        
        while (minCapacity < maxCapacity)
        {
            if (calcDays(weights, minCapacity) <= D)
            {
                return minCapacity;
            }
            
            int midCapacity = (minCapacity + maxCapacity) / 2;
            
            if (calcDays(weights, midCapacity) <= D)
            {
                maxCapacity = midCapacity;
                minCapacity += 1;
            }
            else
            {
                minCapacity = midCapacity + 1;
            }
        }
        
        return minCapacity;
    }
};
