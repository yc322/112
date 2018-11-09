#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;
const int N = 1000005;
const int MOD = 100007;

int Hash[N], cnt[N];


unsigned int ELFhash(char *str)
{
    unsigned int h = 0;
    unsigned int x;
    while(*str)
    {
        h = (h << 4) + *str++;
        x = h & 0xF0000000L;
        if(x)
        {
            h ^= x>>24;
            h &= ~x;
        }
    }
    return h & 0x7FFFFFFF;
}

int HashHit(char *str)
{
    while(*str == '0') str++;
    int k = ELFhash(str);
    int t = k % MOD;
    while(Hash[t] != k && Hash[t] != -1)
        t = (t + 10) % MOD;
    if(Hash[t] == -1)
    {
        cnt[t] = 1;
        Hash[t] = k;
    }
    else cnt[t]++;
    return cnt[t];
}

int main()
{
    int n;
    char str[105];
    while(scanf("%d", &n)!=EOF)
    {
        int ans = 1;
        memset(Hash,-1,sizeof(Hash));//memset the hash table
        while(n--)
        {
            scanf("%s", str);
            ans = max(ans, HashHit(str));
        }
        printf("%d\n", ans);
    }
    return 0;
}
