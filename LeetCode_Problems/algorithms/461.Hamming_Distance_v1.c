
int hammingDistance(int x, int y) {
    int z = x ^ y;
    int num = 0;
    int a;
    for (a = 30; a >= 0 ; a--) {
        if ( z < (1<<a))continue;
        else {
            z-=(1<<a);
            num++;
        }
    }
    return num;
}

int main(void) {
}
