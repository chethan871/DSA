class Solution {
    public String stringHash(String s, int k) {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < s.length(); i += k) {
            String str = (s.substring(i, Math.min(i + k, s.length())));
            int sum = 0;
            for (int j = 0; j < str.length(); j++) {
                sum += str.charAt(j) - 'a';
            }
            int mod = sum % 26;
            sb.append((char) ('a' + mod));
        }

        return sb.toString();
    }
}