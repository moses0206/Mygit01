public class Solution {
    public boolean detectCapitalUse(String word) { 
        char c = word.charAt(0);
        int flag1, flag2 = 0;
        if(Character.isUpperCase(c)) {
            flag1 = 1;
        }
        else {
            flag1 = 0;
        }
        int i = 1;
        while(i < word.length()){
            char chr = word.charAt(i);
            if((flag1 == 0)){
                if(Character.isUpperCase(chr)){
                    return false;
                }
            }else if( i==1 ) {
                if(Character.isUpperCase(chr)) flag2 = 1;
                else flag2 = 0;
            }else if(flag2 == 0 && Character.isUpperCase(chr)) return false;
            else if(flag2 == 1 && Character.isLowerCase(chr)) return false;
            i++;
        }
        return true;
    }
}
