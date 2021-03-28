# Divisibility
- 나누기의 정의
    - 정수 a, b, m에 대하여 a = mb를 만족할 때, 0이 아닌 b는 a를 나눈다.
    - 나눴을 때, 나머지가 없을 경우 b는 a를 나눈다고 한다.
- Notation: b | a
- b | a라면, b는 a의 약수이다.

## Properties of Divisibility
- a|1
    - a = ±1
- a|b and b|a
    - a = ±b
- 0이 아닌 b는 항상 0을 나눈다.
- a|b and b|c
    - a|c
- a|g and b|h
    - b|(mg + nh)

## Division Algorithm
- a = qn + r(양의 정수 n, 음이 아닌 정수 a) 0 ≤ r < n
- q = [a / n]


# Euclidean Algorithm (유클리드 알고리즘)
두 정수의 최대 공약수 구하는 알고리즘     
- notation: gcd(a, b)

## Modular Arithmetic
- a mod n
    - n을 모듈러라고 한다.
- 어떤 정수 a에 대해
    - a = qn + r(양의 정수 n, 음이 아닌 정수 a) 0 ≤ r < n
    - q = [a / n]
    - a = [a / n]*n + (a mod n)
- 합동 모듈러 n
    - (a mod n) = (b mod n)
        - 두 정수 a, b는 모듈러 n에 대하여 합동이다.
    - notation: a ≡ b (mod n)
    - a ≡ 0 (mod n)
        - n | a이다.
- 모듈러 연산
    - [(a mod n) + (b mod n)] mod n = (a + b) mod n
    - [(a mod n) - (b mod n)] mod n = (a - b) mod n
    - [(a mod n) * (b mod n)] mod n = (a * b) mod n

![Modular Arithmetic](./img/Modular-Arithmetic.png)

## Properties of Congruences
1. `a ≡ b (mod n)` 는 `n | (a - b)` 와 필요 충분 조건이다.
2. `a ≡ b (mod n)`와 `b ≡ a (mod n)`는 같다.
3. `a ≡ b (mod n)`와 `b ≡ c (mod n)`는 `a ≡ c (mod n)`이다.

---

## Extended Euclidean Algorithm
- 항등원
    - 어떤 원소에다가 항등원이라는 요소를 더하더라도 어떤 원소가 다시 돌아옴.
- 역원
    - 항등원을 구하기
    - ex1) 0은 모든 덧셈의 항등원이다.
        - 모듈러 8에 대하여 6과 2로 역원 0을 구한다.
    - ex2) 1은 모든 곱셈의 항등원이다.
        - 모듈러 8에 대하여 3과 3으로 역원 1을 구한다.

**두 수가 서로소인 경우만! 역원이 존재한다.**

![Extand Euclidean Ex](./img/Extand-Euclidean-Ex.jpg)

두 페어를 찾고, 음수일 경우 양수로 변환해줌(앞의 값을 더해줌.)

### 시험 문제 유의
-> 곱셈의 역원을 계산하시오.

