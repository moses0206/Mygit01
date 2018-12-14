int maxProfit(int* prices, int pricesSize) {
    int i = 0;
    int total = 0;
    for(i = 1; i < pricesSize; i++) {
        if(prices[i] > prices[i-1])
            total += (prices[i] - prices[i-1]);
    }
    return total;
}
