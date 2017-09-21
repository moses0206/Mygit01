class Solution {
    public boolean judgeCircle(String moves) {
        int len = moves.length();
        int ll = (len - (moves.replace("L", "").length()));
        len =  moves.length();
        int rl = (len - (moves.replace("R", "").length()));
        len =  moves.length();
        int ul = (len - (moves.replace("U", "").length()));
        len =  moves.length();
        int dl = (len - (moves.replace("D", "").length()));
        len =  moves.length();
        if (ll == rl && ul == dl) {
            return true;
        } else {
            return false;
        }
    }
}
