#include<bits/stdc++.h>
using namespace std;

int main(){
    fstream fout;
    fout.open("trace05", ios::out | ios::app);
    int i = 0;
    int inst;
    char ch1 = '0';
    char ch2;
    while(i<10000){
        ch1 = '0';
        inst = rand() % 55 + 1;
        ch2 = inst%10 + '0';
        inst /= 10;
        if(inst > 0){
            ch1 = inst%10 + '0';
        }
        fout << ch1
             << ch2  
             << "\n";
        i++;
    }
    fout.close();
    return 0;
}