#include<iostream>
#define bit32 32
#define bit64 64
using namespace std;
unsigned long long int x, k;
bool bbit[bit64], kbit[bit64];


int main() {
    cin >> x >> k;

    unsigned long long int xnot = ~x;
    int count1 = 0, count2 = 0;

    // bbit持失
    while (xnot) {
        if (xnot % 2) {
            bbit[count2] = true;
        }
        else;
        count2++;
        xnot /= 2;
    }

    // kbit 持失
    while (k) {
        if (k % 2) {
            kbit[count1] = true;
        }
        else;
        count1++;
        k /= 2;
    }

    unsigned long long int sum = 0;
    for (int i = 0; i < bit64; i++) {
        if (kbit[i]) {
            int saveidx = 0;
            for (int k = 0; k < bit64; k++)
                if (bbit[k]) {
                    bbit[k] = false;
                    saveidx = k;
                    break;
                }
            unsigned long long square = 1;
            for (int k = 1; k <= saveidx; k++)
                square = (unsigned long long)square * 2;
            sum = (unsigned long long) sum + square;
        }
        else {
            for (int k = 0; k < bit64; k++)
                if (bbit[k]) {
                    bbit[k] = false;
                    break;
                }
        }
    }
    cout << sum;

    return 0;
}