//Linked list header file
#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;                   // will contain the page number;
    long long timeCounter = 0; // time since last request;
    int lastAccess = 1;        //time between last two request;
    int freq = 1;              //frequency of the page;
    double weight = 0.00;      //timecounter/lastAccess*freq;
    ListNode *next;            // next node in the linked list;
    ListNode *prev;            // prev node in the linked list;
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
    int miss = 0;            // number of misses(excluding cold misses);
    map<int, bool> inCache;  //if a page is in cache the its entry will be true else false;
    map<int, bool> coldMiss; //if a page has been requested before then then its entry will be true;
    circleLL(int n);        //constructor;
    void display(); // will display the current contents of the cache;
    void insert(int entry);   //will check the cache for space/page already in cache;
    void replace(int entry);  //will replace the least recently used entry with the requested one;
    void entryHit(int entry); // will bring the requested entry to the top of the list;
    void updateScore();       //updates the score of every entry;
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
    while(1){
        cout << curr->val << " " << curr->weight << " " << curr->freq << " " << curr->timeCounter << " " << curr->lastAccess<<endl;
        if(curr->next == head){
            break;
        }
        else{
            curr = curr->next;
        }
    }
}

void circleLL::insert(int entry){
    updateScore();
    if(inCache[entry]){
        hit++;
        entryHit(entry);
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
    ListNode *curr = head;
    ListNode *max = new ListNode();
    while(1){
        if(curr->weight >= max->weight){
            max = curr;
        }
        if(curr->next == head){
            break;
        }
        else{
            curr = curr->next;
        }
    }
    if(max != head){
        if(max == bottom){
            head = bottom;
            bottom = bottom->prev;
        }
        else{
            max->next->prev = max->prev;
            max->prev->next = max->next;
            head->prev = max;
            bottom->next = max;
            max->next = head;
            max->prev = bottom;
            head = max;
        }
    }
    inCache[head->val] = false;
    inCache[entry] = true;
    head->val = entry;
    head->freq = 1;
    head->lastAccess = 1;
    head->timeCounter = 0;
}

void circleLL::entryHit(int entry){
    ListNode *curr = head;
    while(curr->val != entry){
        curr = curr->next;
    }
    //changes
    curr->lastAccess = curr->timeCounter;
    //curr->lastAccess = max(1,curr->timeCounter);
    curr->freq++;
    curr->timeCounter = 0;
    curr->weight = 0;
    //
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

void circleLL::updateScore(){
    ListNode *curr = head;
    while(curr->val != 0){
        curr->timeCounter++;
        curr->weight = (1.00 * curr->timeCounter) / (1.00 * curr->lastAccess * curr->freq);
        if(curr->next == head){
            break;
        }
        else{
            curr = curr->next;
        }
    }
}

circleLL::~circleLL()
{
}

