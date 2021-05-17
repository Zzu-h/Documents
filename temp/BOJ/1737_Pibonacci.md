# Pibonacci
링크: [https://www.acmicpc.net/problem/1737](https://www.acmicpc.net/problem/1737)

<br>

dp top-down 방식으로 구현했다.    
Pibonacci는 다음의 규칙을 가진다.    
- P[n] = 1 (0 ≤ n ≤ π)
- P[n] = P[n-1] + P[n-π] (그 외)

그리고 문제에서 다음의 힌트를 주었다.    
- P[n-π] = P[n-π-1] + P[n-π-π]    

이를 정리하면, P[n-π] = P[(n-1)-π] + P[n-2π] 이다.    
배열로 n-π를 index로 사용하기에는 실수기 때문에 사용이 불가하다.     
하지만, 위 힌트를 통해 n과 π는 독립적인 개수를 가지게 됨을 알 수 있다.    
따라서, 이차원 배열 dp[a][b]를 통해 a는 n의 수 b는 π의 수로 정하고 위 식을 대입한다.    

dp[n][#π] = dp[n-1][#π] + dp[n][#(π+1)]로 정의할 수 있다.     
그리고, 문제에서 숫자가 커질 수 있으므로 10^18로 나누라고 되있으므로, 나눈 값을 출력한다. 

<br>

- 정답 코드
    ```c++
    #include<iostream>
    using namespace std;
    #define maxNum 1000000000000000000
    #define pi 3.141592
    long long unsigned int dp[1001][1001];
    int n;

    long long unsigned int pibo(int nidx, int pidx) {
        
        if (dp[nidx][pidx])
            return dp[nidx][pidx];

        double cal = (nidx - (pidx * pi));
        
        if (0 <= cal && cal <= pi)
            return dp[nidx][pidx] = 1;
        
        if (cal < 0)
            return 0;

        dp[nidx][pidx] = (pibo(nidx - 1, pidx) + pibo(nidx, pidx + 1)) % maxNum;

        return (dp[nidx][pidx] % maxNum);
    }

    int main() {
        cin >> n;
        dp[1][0] = dp[2][0] = dp[3][0] = 1;
        cout << pibo(n, 0);

        return 0;
    }
    ```