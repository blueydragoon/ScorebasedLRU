//Linked list header file
#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode *prev;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class circleLL
{
private:
    /* data */
public:
    ListNode *head;
    ListNode *bottom;
    circleLL(int n);
    void display();
    ~circleLL();
};

circleLL::circleLL(int n)
{
    head = new ListNode;
    bottom = new ListNode;
    //bottom = newListNode(n-1);
    ListNode *prev = bottom;
    ListNode *curr = head;
    for (int i = 0; i < n;i++){
        curr->prev = prev;
        if(i<n-2){
            curr->next = new ListNode;
            //curr->next = new ListNode(i+1);
        }
        else if (i == n-2)
        {
            curr->next = bottom;
        }
        else if (i == n-1)
        {
            curr->next = head;
        }
        prev = curr;
        curr = curr->next;
    }
}

void circleLL::display()
{
    ListNode *curr = head;
    cout << curr->prev->val << " " << curr->val << " " << curr->next->val<<endl;
    curr = curr->next;
    while(curr != head){
        cout << curr->prev->val << " " << curr->val << " " << curr->next->val<<endl;
        curr = curr->next;
    }
    cout << curr->prev->val << " " << curr->val << " " << curr->next->val<<endl;
}

circleLL::~circleLL()
{
}

