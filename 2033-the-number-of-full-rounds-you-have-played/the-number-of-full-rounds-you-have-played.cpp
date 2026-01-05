class Solution {
public:
    int numberOfRounds(string loginTime, string logoutTime) {
        auto toMinutes = [](const string &t) {
            return stoi(t.substr(0, 2)) * 60 + stoi(t.substr(3));
        };
        int start = toMinutes(loginTime);
        int end = toMinutes(logoutTime);
        if (end < start) end += 24 * 60;
        int startRound = (start + 14) / 15;
        int endRound   = end / 15;
        return max(0, endRound - startRound);
    }
};