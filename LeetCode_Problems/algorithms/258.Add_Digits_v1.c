int addDigits1(int num) {
    int sum = 0;
    goto START;
    while(sum > 9) {
        num = sum;
        sum = 0;
START:
        while(num) {
            sum += (num%10);
            num /= 10;
        }
    }
    return sum;
}

int addDigits2(int num) {
    int sum = -1;
    while(sum == -1 || sum > 9) {
        if(sum != -1) {
            num = sum;
        }
        sum = 0;
        while(num) {
            sum += (num%10);
            num /= 10;
        }
    }
    return sum;
}
