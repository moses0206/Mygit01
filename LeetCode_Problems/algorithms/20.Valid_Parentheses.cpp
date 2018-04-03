#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        int size = s.length();
        int *a = (int *)calloc(size, sizeof(int));
        int i = 0, j;
        int flag = 1;
        for(j = 0; j < size; j++) {
            switch (s[j]){
                case '(': a[i++] = 1;
                    continue;
                case '[': a[i++] = 2;
                    continue;
                case '{': a[i++] = 3;
                    continue;
            }
            if(s[j] == ')') {
                if(i<1 || a[i-1] != 1) {flag = 0; break;}
                else {a[--i] = 0;}
            }
            if(s[j] == ']') {
                if(i<1 || a[i-1] != 2) {flag = 0; break;}
                else {a[--i] = 0;}
            }
            if(s[j] == '}') {
                if(i<1 || a[i-1] != 3) {flag = 0; break;}
                else {a[--i] = 0;}
            }
        }
        free(a);
        if(i != 0 || flag == 0) return false;
        else return true;
    }
};

int main(int argc, char *argv[]) {
    std::cout << "Hello World" << std::endl;
    return(0);
}
