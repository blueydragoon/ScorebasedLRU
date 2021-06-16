#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    double score;
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
    int hit = 0;
    int miss = 0;
    double fallFac;
    map<int, bool> inCache;
    map<int, bool> coldMiss;
    circleLL(int n,double w);
    void display();
    void insert(int entry);
    void replace(int entry);
    void find(int entry);
    void update(int entry);
    void geoFall(int entry);
    ~circleLL();
};

circleLL::circleLL(int n,double w)
{
    fallFac = w;
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
    geoFall(entry);
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

void circleLL::geoFall(int entry){
    ListNode *curr = head;
    while (curr->val != 0)
    {
        curr->score *= fallFac;
        if(curr->next == head){
            break;
        }
        else{
            curr = curr->next;
        }
    }
}

void circleLL::replace(int entry){
    ListNode *curr = head;
    ListNode *min = new ListNode();
    min->score = INT_MAX;
    while(1){
        if(curr->score <= min->score){
            min = curr;
        }
        if(curr->next == head){
            break;
        }
        else{
            curr = curr->next;
        }
    }
    if(min != head){
        if(min == bottom){
            head = bottom;
            bottom = bottom->prev;
        }
        else{
            min->next->prev = min->prev;
            min->prev->next = min->next;
            head->prev = min;
            bottom->next = min;
            min->next = head;
            min->prev = bottom;
            head = min;
        }
    }
    inCache[head->val] = false;
    inCache[entry] = true;
    head->val = entry;
    head->score = 1;
}

void circleLL::update(int entry){
    ListNode *curr = head;
    while(curr->val != entry){
        curr = curr->next;
    }
    curr->score += 1.00;
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

