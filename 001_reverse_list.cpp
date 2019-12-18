
/*
 * 001.反转链表
 * 问题描述: 输入一个链表，反转链表后，输出新链表的表头。
 * 提示: three pointers
 */

struct ListNode
{
    int val;
    struct ListNode *next;
    
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        if (pHead == NULL) { return NULL; }
        
        ListNode* p = pHead;
        ListNode* q = p->next;
        while (q != NULL)
        {
            ListNode* k = q->next;
            q->next = p;
            
            p = q;
            q = k;
        }
        
        pHead->next = NULL;
        return p;
    }
};
