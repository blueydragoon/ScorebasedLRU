#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;        // will contain the page number
    int score;      // score/freq of a page within the window
    ListNode *next; // next node in the linked list
    ListNode *prev; // prev node in the linked list
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
    vector<int> window;
    int hit = 0;
    int miss = 0;
    map<int, bool> inCache;
    map<int, bool> coldMiss;
    circleLL(int n,int w);
    void display();
    void insert(int entry);
    void replace(int entry);
    void update(int entry);
    void slide(int entry); // discard the last entry of the window and will do the needful for the next
    ~circleLL();
};

circleLL::circleLL(int n,int w)
{
    for (int i = 0; i < w;i++){
        window.push_back(-1);
    }
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
    cout << curr->val << " " << curr->score <<endl;
    curr = curr->next;
    while(curr != head){
        cout << curr->val << " " << curr->score <<endl;
        curr = curr->next;
    }
}

void circleLL::insert(int entry){
    slide(entry);
    if(inCache[entry]){
        hit++;
        update(entry);
    }
    else if(bottom->val == 0){
        if(coldMiss[entry]){
            miss++;
        }
        else{
            coldMiss[entry] = true;
        }
        bottom->val = entry;
        bottom->score = 1;
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

void circleLL::slide(int entry){
    int last;
    last = window[0];
    for (int i = 1; i < window.size();i++){
        window[i - 1] = window[i];
    }
    window[window.size() - 1] = entry;
    ListNode *curr = head;
    while(curr->val != last && curr->next != head){
        curr = curr->next;
    }
    if(curr == bottom){
        if(curr->val == last){
            curr->score--;
        }    
    }
    else{
        curr->score--;
    }
}

void circleLL::replace(int entry){
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

