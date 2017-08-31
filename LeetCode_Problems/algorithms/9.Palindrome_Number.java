class Solution {
    public boolean isPalindrome(int x) {
        if(x < 0) return false;
        int[] a = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
        int i = 0, j;
        while(x/10 != 0) {
            a[i++] = x%10;
            x/=10;
        }
        a[i] = x%10;
        for(j = 0; j < i; j++, i--) {
        if(a[j] != a[i])
            break;
        }
        if(j < i) return false;
        else return true;
    }
}
