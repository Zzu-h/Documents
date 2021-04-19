# Database 개념
## Data absraction
3 levels of data abstraction
1. Physical level
    - 레코드가 어떻게 저장되는지를 기술
2. Logical level
    - 데이터에 대한 정보, 데이터들 사이의 관계를 기술
3. View level
    - 사용자가 보는 실질적인 DB부분

## Data Independence
DB 내의 데이터들과 이를 사용하는 응용프로그램이 서로 영향을 받지 않는 성질
- 일반적으로, 다양한 level과 component 사이의 인터페이스는 일부 부분의 변화가 다른 부분에 심각한 영향을 미치지 않도록 잘 정의되어야 한다.
- 응용 프로그램은 데이터 표현과 저장의 상세 내용이 노출되지 않아야 한다.

## DDL
Data Defintion Language의 약자로 데이터베이스를 정의하는 언어이다.    
데이터의 전체 골격을 결정하는 역할    
Data Dictionary는 metadata를 포함한다.

## DML
Data Manipulation Language의 약자로 데이터를 조작하는 언어다.    
질의어라고도 하며 데이터를 수정 및 접근하기 위한 언어

### Procedual DML
사용자에게 필요한 데이터와 그 데이터를 얻는 방법을 정의하게 함
### Declarative DML
비절차적 DML, 어떤 데이터가 필요한지만 사용자에게 물어봄

## SQL Query Language
- 비절차적 언어
- Turing machine equivalent language가 아니다.
    - 기능이 완벽하지 않다.
    - 따라서 고급언어가 필요하다.

## Transaciont Management
- 동시성 제어

## Database Users
[go to here](Intro.md#database-users)

# Algebra
- Select: σ
- project: ∏
- union: ∪
- set deifference: −
- Cartesian product: ⅹ
- rename: ρ
- Join: r ⨝_𝜃 s

---

<br>
<br>
<br>


# SQL
## Key
- Super key
    - 두 개 이상의 속성을 잡았을 때 Unique한 key
- Candidate key
    - 튜플을 식별가능한 key
    - PK ⊂ CK
- Primary key
    - 특정 튜플을 유일하게 구별할 수 있는 key
- Foreign key
    - 다른 테이블에 가서 key가 되는 경우
    - 외래키가 포함된 테이블을 자식 테이블이라고 하고 외래키 값을 제공하는 테이블을 부모 테이블이라한다.

## Table
### Table 생성과 Key 설정
```sql
create table instructor (
ID char(5),
name varchar(20) not null,
dept_name varchar(20),
salary numeric(8,2),
primary key (ID),
foreign key (dept_name) references department);
```
### Table 구조를 수정
- 속성 추가: `alter table r add A D`
- 속성 제거: `alter table r drop A`
- 테이블 제거
    - `drop table r`
    
## Data(tuple)
### 수정, 삽입과 제거
- 삽입
    - `insert R(a1, a2, ..., an) values(v1, v2 ..., vn)`
- 모든 튜플 제거
    - `delete from R where P`
- 수정
    - `update R set (update content)`
    - `update R set (A = case when P1 then C1 else C2 end)`
### 조회
```sql
select A1, A2, ..., An
from r1, r2, ..., rm
where P
```

## Subquery
### Group By
```sql
Select dept_name, avg (salary) as avg_salary
from instructor
group by dept_name
having avg (salary) > 42000;
```
### With 절
```sql
with max_budget (value) as 
    (select max(budget)
    from department)
select department.name
from department, max_budget
where department.budget = max_budget.value;
```