#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    int score;
    ListNode *next;
    ListNode *prev;
    ListNode() : val(0), score(0), next(nullptr) {}
    ListNode(int x) : val(x), score(0), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), score(0), next(next) {}
};

class circleLL
{
private:

public:
    ListNode *head;
    ListNode *bottom;
    map<int, bool> inCache;
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
    cout << curr->val << " " << curr->score <<endl;
    curr = curr->next;
    while(curr != head){
        cout << curr->val << " " << curr->score <<endl;
        curr = curr->next;
    }
    //cout << curr->prev->val << " " << curr->val << " " << curr->next->val<<endl;
}

void circleLL::insert(int entry){
    if(inCache[entry]){
        update(entry);
        return;
    }
    else if(bottom->val == 0){
        bottom->val = entry;
        bottom->score = 1;
        head = bottom;
        bottom = bottom->prev;
        inCache[entry] = true;
    }
    else{
        replace(entry);
    }
}

void circleLL::replace(int entry){
    while(bottom->score > 1){
        bottom->score--;
        head = bottom;
        bottom = bottom->prev;
    }
    inCache[bottom->val] = false;
    inCache[entry] = true;
    ListNode *curr = new ListNode(entry);
    curr->score = 1;
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
    curr->score++;
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

