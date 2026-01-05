class Solution {
public:
    string removeOccurrences(string s, string part) {
        string ans = "";
        for(int i = 0; i < s.size(); i++){
            ans.push_back(s[i]);  // Always add current character first
            
            // Check if the end of ans matches part
            if(ans.size() >= part.size()){
                int startPos = ans.size() - part.size();
                string sub = ans.substr(startPos, part.size());
                if(sub == part){
                    ans = ans.substr(0, startPos);  // Remove the match
                }
            }
        }
        return ans;
    }
};