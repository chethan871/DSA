#include <stdio.h>

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

int isValid(long long x, long long divisor1, long long divisor2, long long cnt1, long long cnt2) {
    long long l = lcm(divisor1, divisor2);
    long long count1 = x - x / divisor1;
    long long count2 = x - x / divisor2;
    long long count_both = x - x / divisor1 - x / divisor2 + x / l;

    long long arr1_only = count1 - count_both;
    long long arr2_only = count2 - count_both;
    long long common = count_both;

    return (arr1_only + common >= cnt1) &&
           (arr2_only + common >= cnt2) &&
           (arr1_only + arr2_only + common >= cnt1 + cnt2);
}

long long minimizeSet(long long divisor1, long long divisor2, long long uniqueCnt1, long long uniqueCnt2) {
    long long left = 1, right = 2e18;
    while (left < right) {
        long long mid = left + (right - left) / 2;
        if (isValid(mid, divisor1, divisor2, uniqueCnt1, uniqueCnt2))
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}
