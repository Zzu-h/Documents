# Joined Relations
Three types of joins
- Natural join
- Inner join
- Outer join

# Natural Join
- 튜플을 모든 공통 속성에 매치시키고, 각 공통열의 복사본 하나만 유지한다.
    - EQUI JOIN같은 경우 같은 속성을 두 번 출력하지만
    - Natural Join은 중복된 속성을 제거하고 출력해 준다.
- 기본적으로 Inner join이다.
    - `inner join`으로 명시해도 되고, join만 써도 무관
- ex) 교수들이 교육했던 과목의 과목 ID와 함께 교수들의 이름들을 리스트화.
    - natural join
        ```sql
        select name, course_id
        from student natural join takes;
        ```
    - 이를 풀어쓰면,
        ```sql
        select name, course_id
        from students, takes
        where student.ID = takes.ID;
        ```
- Form
    ```sql
    select A1, A2, … An
    from r1 natural join r2 natural join .. natural join rn
    where P ;
    ```

### Dangerous in Natural Join
학생들이 수강하는 과목명과 함께 학생 이름을 리스트화.
- Natural join을 남발할 경우(incrrect version)
    ```sql
    select name, title
    from student natural join takes natural join course;
    ```
    - student의 dept_name과 course의 dept_name의 Attribute명이 같다.
        - 따라서, student.dept_name = course_dept_name 인 리스트만 출력할 것이다.
        - 타과의 수업을 들은 학생들은 출력하지 않게 된다.
- 위의 내용을 정상 출력(Correct version)
    ```sql
    select name, title
    from (student natural join takes), course
    where takes.course_id = course.course_id;
    ```

### Natural Join with Using Clause
using(Attribute)를 이용해서 정확하게 명시를 할 수 있다.    
```sql
select name, title
from (student natural join takes) join course using (course_id)
```

### Join Condition
- `on`을 이용해서 조건을 부여할 수 있다.
- `where`절과 비슷함
- Example
    ```sql
    Query example
    select *
    from student join takes on student_ID = takes_ID
    ```
## Outer Join
외부 조인
- 임의의 테이블을 기준으로 다른 테이블과 join할 때
    - 다른 테이블에서는 선택한 테이블의 데이터가 없을 경우
    - 선택한 테이블의 데이터를 강제로 리스트화 시킨다.
- 즉, 조건에 맞지 않는 데이터를 선택한 데이터들을 기준으로 해당하는 행을 모두 출력하고 싶을 때 사용
- Three Forms
    - left outer join
    - right outer join
    - full outer join
- Table Example
    - Relation course
        - ![Relation-course](./img/Relation-course.jpg)
    - Relation prereq
        - ![Relation-prereq](./img/Relation-prereq.jpg)

### Left Outer Join
```sql
FROM R1 LEFT OUTER JOIN R2 ON P;
```
- P에 따라 R1을 기준으로 R2에 데이터와 일치하지 않더라도 R1의 행은 모두 가져온다.
- 이때, R2의 데이터가 없는 경우 NULL값을 준다.
- In relational algebra
    - course ⟕ prereq
- Example
    - ![Relation-Left-Outer-Join](./img/Relation-Left-Outer-Join.jpg)

### Right Outer Join
```sql
FROM R1 RIGHT OUTER JOIN R2 ON P;
```
- P에 따라 R2을 기준으로 R1에 데이터와 일치하지 않더라도 R2의 행은 모두 가져온다.
- 이때, R1의 데이터가 없는 경우 NULL값을 준다.
- In relational algebra
    - course ⟖ prereq
- Example
    - ![Relation-Right-Outer-Join](./img/Relation-Right-Outer-Join.jpg)
### Full Outer Join
```sql
FROM R1 FULL OUTER JOIN R2 ON P;
```
- P에 따라 모든 테이블의 행을 가져온다.
- 이때, 데이터가 없는 경우 NULL값을 준다.
- In relational algebra
    - course ⟗ prereq
- Example
    - ![Relation-Full-Outer-Join](./img/Relation-Full-Outer-Join.jpg)

# View
- 기존 테이블의 필요한 데이터만 추출하여 가상의 테이블을 만드는 것
- view로 만들어진 테이블은 실제 테이블이 아닌 가상의 테이블이므로 실질적인 데이터는 존재하지 않는다.
- 약간 변수와 비슷함
    - view를 통해 해당 쿼리식을 저장함
    - 이 view를 사용할 때마다 쿼리식으로 기존 테이블에서 데이터를 추출함
- With 절과 유사하다
    - With절은 그 순간에만 사용하고 사라짐
    - 하지만 View는 삭제할 때 까지 남아 있다.
- Form
    - `create view v as < query expression >`
- Example
    - View 생성
        ```sql
        create view faculty as
        select ID, name, dept_name
        from instructor
        ```
    - View 사용
        ```sql
        select name
        from faculty
        where dept_name = 'Biology'
        ```
        - ![Use-View](./img/Use-View.JPG)

## Views Defined Using Other Views
- 다른 View를 이용해서 새로운 View를 생성할 수 있다.
- `Table -> V1 -> V2 -> V3 -> ... -> Vn`
    - V1은 V2에 대해 직접 종속이다.
    - V1은 V3에 대해 종속되어있다.
    - `Vn -> V1`로 갈 경우 Recursive하다고 한다.
        - 하지만 테이블이 생성이 안되고 무한루프를 돈다.
        - **따라서, 사용불가!**
- Example
    - V1 만들기
        ```sql
        create view physics_fall_2017 as
            select course.course_id, sec_id, building, room_number
            from course, section
            where course.course_id = section.course_id
                and course.dept_name = 'Physics'
                and section.semester = 'Fall'
                and section.year = '2017’;
        ```
    - V2 만들기
        ```sql
        create view physics_fall_2017_watson as
            select course_id, room_number
            from physics_fall_2017
            where building= 'Watson';
        ```
    