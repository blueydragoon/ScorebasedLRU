#include<bits/stdc++.h>
using namespace std;

int main(){
    fstream fout;
    fout.open("trace02", ios::out | ios::app);
    int i = 0;
    while(i<5000){
        fout << rand() % 42 + 1  
             << "\n";
        i++;
    }
    fout.close();
    return 0;
}