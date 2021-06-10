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
    
public:
    ListNode *head;
    ListNode *bottom;
    int hit = 0;
    int miss = 0;
    map<int, bool> inCache;
    map<int, bool> coldMiss;
    circleLL(int n);
    void display();
    void insert(int entry);
    void replace(int entry);
    void find(int entry);
    void update(int entry);
    ~circleLL();
};

circleLL::circleLL(int n)
{
    head = new ListNode;
    bottom = new ListNode;
    ListNode *prev = bottom;
    ListNode *curr = head;
    for (int i = 0; i < n;i++){
        curr->prev = prev;
        if(i<n-2){
            curr->next = new ListNode;
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
    cout << curr->val<<endl;
    curr = curr->next;
    while(curr != head){
        cout << curr->val <<endl;
        curr = curr->next;
    }
}

void circleLL::insert(int entry){
    if(inCache[entry]){
        update(entry);
        return;
    }
    else if(bottom->val == 0){
        if(coldMiss[entry]){
            miss++;
        }
        else{
            coldMiss[entry] = true;
        }
        bottom->val = entry;
        head = bottom;
        bottom = bottom->prev;
        inCache[entry] = true;
    }
    else{
        if(coldMiss[entry]){
            miss++;
        }
        else{
            coldMiss[entry] = true;
        }
        replace(entry);
    }
}

void circleLL::replace(int entry){
    inCache[bottom->val] = false;
    inCache[entry] = true;
    ListNode *curr = new ListNode(entry);
    curr->next = head;
    head->prev = curr;
    head = curr;
    bottom = bottom->prev;
    bottom->next = head;
    head->prev = bottom;
}

void circleLL::update(int entry){
    ListNode *curr = head;
    while(curr->val != entry){
        curr = curr->next;
    }
    if(curr == head){
        return;
    }
    if(curr == bottom){
        head = bottom;
        bottom = bottom->prev;
        return;
    }
    curr->next->prev = curr->prev;
    curr->prev->next = curr->next;
    head->prev = curr;
    bottom->next = curr;
    curr->next = head;
    curr->prev = bottom;
    head = curr;
}

circleLL::~circleLL()
{
}

