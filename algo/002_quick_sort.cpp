
/*
 * 002.快速排序
 * partition: 以vec[end]作为pivot
 * 经过一次partition，可以保证pivot之前的元素<=pivot，pivot之后的元素>=pivot
 * quick_sort: 执行一次partition之后，分别对[start, pivot-1]和[pivot+1, end]递归执行quick_sort
 * 时间复杂度:
 * T.partition = O(end - start + 1)
 * T.quick_sort.worst = 每次将数组划分成[1,n-1] = n-1 + n-2 + ... + 1 = O(n^2)
 * T.quick_sort.best = 每次将数组划分成[n/2,n/2] = n/2 * 2 + n/4 * 4 + ... + n/2^k * 2^k (k=logn) = O(nlogn)
 * T.quick_sort.avg = T.quick_sort.best
 * 空间复杂度:
 * S.quick_sort.ignore_recursion_cost = O(1)
 * S.quick_sort.recursion_cost = 根据递归的深度 = O(logn) ~ O(n)
 * 优化思路:
 * a. pivot元素选取: 三值取中法(median-of-three)
 * b. std::sort(intro_sort): (1)优先使用快速排序 (2)递归层数达到2logn时使用堆排序 (3)子数组元素<=16时使用插入排序
 */

#include <vector>
#include <algorithm>

using namespace std;

int partition(vector<int>& vec, int start, int end)
{
    int last_smaller_pos = start - 1;
    for (int i = start; i < end; ++i)
    {
        if (vec[i] < vec[end]) // vec[end] as pivot element
        {
            last_smaller_pos += 1;
            std::swap(vec[last_smaller_pos], vec[i]);
        }
    }
    
    int partition_pos = last_smaller_pos + 1;
    std::swap(vec[partition_pos], vec[end]);
    return partition_pos;
}

void quick_sort(vector<int>& vec, int start, int end)
{
    if (start < end)
    {
        int partition_pos = partition(vec, start, end);
        quick_sort(vec, start, partition_pos - 1);
        quick_sort(vec, partition_pos + 1, end);
    }
}
