- Table이 정상인지 비정상인지 확인하는 방법
- 비정상일 때 고치는 방법
# Normalization
- 잘못된 Table
    - ![Normalization-Incorrect-Table](./img/Normalization-Incorrect-Table.JPG)
    - 위 테이블은 instructor와 department table을 natural join한 것이다.
        - 만일 위 테이블이 하나의 테이블이라고 가정해보자.
    - 위에서 department table의 데이터들이 중복해서 출력되는 것을 확인할 수 있다.
        - Ex) Comp. Sci. Taylor 100000 이 중복해서 보임
    - 단점
        - disk, memory 낭비
        - 정보 Inconsistent
        - null value가 들어갈 수 있음
            - department에 새로운 부서가 추가되면 교수가 없으므로 null값 들어감
    - 따라서, instructor와 department로 나눌 필요성이 있다.
- 괜찮은 Table
    - student(ID, name, dept_name, tot_cred)
    - advisor(s_ID, i_ID) 
    - 위 두 개의 Table을 하나로 합쳐도 중복없이 정상적인 Table을 만들 수 있다.
        - student(ID, name, dept_name, tot_cred, advisor)

## Decomposition
- Table에 중복되는 Data가 존재하게 될 경우 분리를 시킨다. 
- 나누는 기준은 여러가지 존재
- 나눌 때는 공통되는 속성이 있어야 한다.
- Lossy Decomposition
    - 기존 테이블에서 나누고 그 테이블들을 하나로 다시 묶었을 때
    - 원본을 유지하지 않을 때를 Lossy Decomposition라 한다.
    - ![Table-Lossy-Decomposition](./img/Table-Lossy-Decomposition.JPG)
        - 위 테이블에서 Kim이라는 이름으로 2개의 정보가 나와야 하지만 4개가 나오게 됨
    - Form
        - `r ⊂ ∏_R1 (r) ⨝ ∏_R2 (r)`
    - Natural join결과가 원래 테이블보다 더 작을 순 없다.
        - `r ⊅ ∏_R1 (r) ⨝ ∏_R2 (r)`

- Lossless Decomposition
    - 기존 테이블을 나누고 다시 묶었을 때 원형 그대로일 때 Lossless Decomposition라 한다.
    - R을 R1과 R2로 나눈다고 하자.
        - `R = R1 U R2`
    - Form
        - `∏_R1 (r) ⨝ ∏_R2 (r) = r`

## Normalization Theory
- R이 좋은 형태인지 판별한다.
- 만일 좋은 형태가 아니라면 Decompose를 수행한다.
    - n개의 Table로 나누는데 각 Table은 좋은 형태를 유지해야 한다.
    - Lossless Decomposition로 만들어야 한다.
- 다음 두 가지의 개념을 기반하여 정규화한다.
    - [Functional dependencies](#functional-dependencies)
    - Multivalued dependencies


# Functional dependencies
- 실제로 data에 규칙 도는 제약조건이 존재한다.
    - 예를 들어 각 학생과 교수는 오직 하나의 이름만을 가진다.
    - etc..
- legal instance
    - 그러한 실제의 데이터 제약조건들을 만족하는 Table을 **legal instance**라 한다.
    - DB에 있는 모든 Table이 legal instance이면 그 DB는 legal instance이다.
- 어떤 속성이 다른 속성값을 결정할 수 있다.
    - Ex) 어떤 학생의 ID가 주어지면, 그 학생의 학과와 이름 등을 알 수 있다.
        - ID → Department, name, etc..
- functional dependency는 key와 비슷한 개념을 지닌다.
    - key는 어떤 table에서 특정 tuple을 찾는 역할을 한다.
        - 바로 위 내용과 유사한 개념
    - key값은 유일하다.

## Functional Dependencies Definition 
- 다음을 만족하는 α, β가 존재할 때
    - α ⊆ R and β ⊆ R
- `α → β`: determine
    - α가 β를 결정한다.
- `t1[α] = t2[α] ⇒ t1[β] = t2[β]`: determine
    - 분리된 tale에서 각각의 tuple t1과 t2에 대해
        - 같은 속성 α의 값이 같다면 같은 속성 β의 값도 같다.
    - 위를 만족하면 Functional Dependencies를 만족한다고 볼 수 있다.

## Closure of a Set of Functional Dependencies
- closure
    - 모든 functional depedency가 있을 때 이를 통해서 도출될 수 있는 모든  functional depedency들을 closure라고 한다.
    - F^+
        - functional depedency F로 부터 도출된 것

## Keys and Functional Dependencies
- K: superkey
    - K → R 일 때, K는 superkey라 한다.
- K: candidate key
    - K → R를 만족하고,
    - α ⊂ K, α → R을 만족하는 α가 존재하지 않을 때 K를 candidate key가 된다.
        - α: subset
- functional dependency는 superkey를 사용해서 표현할 수 없는 제약조건을 표현할 수 있다.
    - in_dep (<u>ID</u>, name, salary, dept_name, building, budget).
    - 여기서, ID는 모든 값들을 결정할 수 있다.
        - ID → building
    - 또한 dept_name을 통해서 , building을 결정할 수 있다.
        - dept_name → building
    - 하지만 dept_name → salary는 불가능함

## Use of Functional Dependencies
- 어떤 Table을 test해서 funtional dependency를 만족하면 `r satisfies F`라 할 수 있다.
- 반대로 legal relation을 통해서 제약조건을 정의할 수 있다.
    - `F holds on R`
- 우연히 성립하는 경우 Functional Dependencies를 만족한다고 볼 수 없다!
    - 모든 경우에서 만족해야 함

## Trivial Functional Dependencies
- trivial
    - β ⊆ α이면 α → β 이는 당연한 것이다.
    - 위 명제와 같이 당연한 내용을 일컫음
    - Example
        - ID, name → ID
        - name → name

## Lossless Decomposition