#include <stdbool.h>

// Forward declaration of isBadVersion API.
bool isBadVersion(int version);

int firstBadVersion(int n) {
    int good = 0, bad = 0;
    while(bad - good != 1) {
        if(isBadVersion(n) == true) { bad = n; } 
        else { good = n; }
        n = ((long long)good + bad)/2;
    }
    return bad;
}
