string convertToNewString(const string &s) {
    string newString = "@";
 
    for (int i = 0; i < s.size(); i++) {
        newString += "#" + s.substr(i, 1);
    }
 
    newString += "#$";
    return newString;
}
 
vector<int> longestPalindromeSubstring(const string &s) {
    string Q = convertToNewString(s);
    int c = 0, r = 0;
    
    std::vector<int> P(Q.size());
 
    for (int i = 1; i < Q.size() - 1; i++) {
        int iMirror = c - (i - c);
 
        if(r > i) {
            P[i] = min(r - i, P[iMirror]);
        }
 
        while (Q[i + 1 + P[i]] == Q[i - 1 - P[i]]){
            P[i]++;
        }
 
        if (i + P[i] > r) {
            c = i;
            r = i + P[i];
        }
    }
 
    return P;
}
