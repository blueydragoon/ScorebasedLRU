#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;       // will contain the page number;
    double score;  // contains the score of a particular page;
    ListNode *next; // next node in the linked list;
    ListNode *prev; // prev node in the linked list;
    ListNode() : val(0), score(0), next(nullptr) {}
    ListNode(int x) : val(x), score(0), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), score(0), next(next) {}
};

class circleLL
{
private:

public:
    ListNode *head;  //head of the linked list;
    ListNode *bottom; //bottom of the linked list;
    int hit = 0;      //number of hits;
    int miss = 0;     // number of misses(excluding cold misses);
    double fallFac;   //a measure to decide how impactful geo fading will be;
    map<int, bool> inCache; //if a page is in cache the its entry will be true else false;
    map<int, bool> coldMiss; //if a page has been requested before then then its entry will be true;
    circleLL(int n, double w); //constructor;
    void display();            // will display the current contents of the cache;
    void insert(int entry);    //will check the cache for space/page already in cache;
    void replace(int entry);   //will replace the least recently used entry with the requested one;
    void update(int entry);    // will bring the requested entry to the top of the list;
    void geoFall(int entry);   // will decide the decrease score of an entry by a factor of fallFac;
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
    geoFall(entry);// updating the score
    if(inCache[entry]){//checking the cache for the requested page
        hit++;
        update(entry);
    }
    else if(bottom->val == 0){//will check if the cache is empty
        if(coldMiss[entry]){
            miss++;
        }
        else{
            coldMiss[entry] = true;
        }
        bottom->val = entry;
        bottom->score = 1; // setting a request score on 1;
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

