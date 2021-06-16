#include <bits/stdc++.h>
#include "ll.h"
using namespace std;

int main(){
    int n = 15;
    int w = 10;
    fstream my_file;
    fstream fout;
    fout.open("SW1.csv", ios::out | ios::trunc);
    fout << "size" << ", "
         << "window" << ","
         << "hits" << ", "
         << "misses" << ", "
         << "hitRatio" << ", "
         << "missRatio" << ", "
         << "\n";
    for (n = 3; n < 50; n++){
        w = 2;
        while (w < n/2 + 1)
        {
            circleLL list(n,w);
            my_file.open("./traces/trace01", ios::in);
            if (!my_file)
            {
                cout << "No such file";
            }
            else
            {
                char ch;
                char ch2;
                while (1)
                {
                    my_file >> ch;
                    my_file >> ch2;
                    if (my_file.eof())
                        break;
                    int out = 10 * (ch - '0') + ch2 - '0';
                    list.insert(out);
                }
            }
            my_file.close();
            double hitratio = (1.00 * list.hit) / 10000.00;
            double missratio = (1.00 * list.miss) / 10000.00;
            fout << n << ", "
                 << w << ","
                 << list.hit << ", "
                 << list.miss << ", "
                 << hitratio << ", "
                 << missratio << ", "
                 << "\n";
            w++;
        }
    }
    return 0;
}
