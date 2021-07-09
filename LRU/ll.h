//header file for the driver function
#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;        // will contain the page number
    ListNode *next; // next node in the linked list
    ListNode *prev; // prev node in the linked list
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class circleLL
{
private:
    
public:
    ListNode *head;   //head of the linked list;
    ListNode *bottom; //bottom of the linked list;
    int hit = 0;      //number of hits;
    int miss = 0;     // number of misses(excluding cold misses);
    map<int, bool> inCache; //if a page is in cache the its entry will be true else false;
    map<int, bool> coldMiss; //if a page has been requested before then then its entry will be true;
    circleLL(int n);         //constructor;
    void display();          // will display the current contents of the cache;
    void insert(int entry);  //will check the cache for space/page already in cache;
    void replace(int entry); //will replace the least recently used entry with the requested one;
    void update(int entry);  // will bring the requested entry to the top of the list;
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
    if(inCache[entry]){//checking the cache for the requested page
        hit++;
        update(entry);
        return;
    }
    else if(bottom->val == 0){//will check if the cache is empty
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

