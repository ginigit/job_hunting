
/*
 * 001.堆排序
 * max_heapify: 对a[i]建堆: 在a[i]、a[left]、a[right]，找出最大者，交换a[i]和a[largest]
 * 令i = largest，继续对a[i]建堆: 递归或非递归，直到a[i] >= a[left] 且 a[i] >= a[right]
 * build_max_heap: 从后往前，依次对a[i]建堆，使数组任意节点均满足最大堆的性质
 * heap_sort: 交换a[0]和a[len-1]，len=len-1，再对a[0]建堆
 * 基本思路: 首先调整元素位置使之满足最大堆的性质，然后将堆首元素(最大值)移动到堆尾
 * 时间复杂度粗略计算:
 * T.max_heapify = 完全二叉树，沿根至叶子的简单路径下溯 = O(logn)
 * T.build_max_heap = n/2 * T.max_heapify = O(nlogn)
 * T.heap_sort = T.build_max_heap + n * T.max_heapify = O(nlogn)
 * 时间复杂度精细计算:
 * T.max_heapify = O(logn)
 * T.build_max_heap = 1*(h-1) + 2*(h-2) + 4*(h-3) + ... + 2^(h-2)*1 + 2^(h-1)*0 = O(n)
 * T.heap_sort = 2^(h-1)*(h-1) + 2^(h-2)*(h-2) + ... + 2*1 + 1*0 = O(nlogn)
 * 空间复杂度:
 * S.heap_sort = O(1)
 */

#include <vector>

using namespace std;

void max_heapify(vector<int>& vec, int i, int end)
{
    int largest = i;
    
    int left = 2 * i + 1;
    if (left <= end && vec[largest] < vec[left])
    {
        largest = left;
    }
    
    int right = left + 1;
    if (right <= end && vec[largest] < vec[right])
    {
        largest = right;
    }
    
    if (largest != i)
    {
        std::swap(vec[i], vec[largest]);
        i = largest;
        max_heapify(vec, i, end);
    }
}

void max_heapify_non_recursive(vector<int>& vec, int i, int end)
{
    int left = 2 * i + 1;
    while (left <= end)
    {
        int largest = i;
        if (vec[largest] < vec[left])
        {
            largest = left;
        }
        
        int right = left + 1;
        if (right <= end && vec[largest] < vec[right])
        {
            largest = right;
        }
        
        if (largest == i)
        {
            break;
        }
        
        std::swap(vec[i], vec[largest]);
        i = largest;
        left = 2 * i + 1;
    }
}

void build_max_heap(vector<int>& vec, int len)
{
    for (int i = len / 2 - 1; i >= 0; --i)
    {
        max_heapify(vec, i, len - 1);
    }
}

void heap_sort(vector<int>& vec, int len)
{
    build_max_heap(vec, len);
    
    for (int i = len - 1; i > 0; --i)
    {
        std::swap(vec[0], vec[i]);
        max_heapify(vec, 0, i - 1);
    }
}
