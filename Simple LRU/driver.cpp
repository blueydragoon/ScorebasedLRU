#include <bits/stdc++.h>
#include "ll.h"
using namespace std;
int main(){
    int n = 5;
    //cin >> n;
    circleLL list(n);
    //list.display();
    list.insert(2);
    cout << " BEFORE STARTING ARRAY INSERTS "<< endl;
    for (int i = 0; i < 5;i++){
        list.insert(i+1);
    }
    list.display();
    int arr[5] = {8, 3, 6, 4, 5};
    for (int i = 0; i < 5;i++){
        cout << "AFTER INSERTING: " << arr[i] << endl;
        list.insert(arr[i]);
        list.display();
    }
}
