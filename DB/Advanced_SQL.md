# Accessing SQL From a Programming Language
SQL + Programming Language    
SQL만 단독으로 사용하기 어렵다.      
- SQL만으로 모든 표현을 할 수 없다.
- 출력이나 사용자 입력 등 action들을 수행할 수 없다.

따라서, 프로그래밍 언어와 합쳐서 SQL를 사용한다.     

<br>

프로그래밍 언어와 SQL을 합치는데 두 가지 방식이 있다.
- A general-purpose program
    - API 함수를 사용하여 데이터베이스 서버와 통신을 한다.
    - Example
        - JDBC
            - 자바에서 데이터베이스에 접속할 수 있도록 하는 자바 API이다.
        - ODBC
            - C에서 사용하는 API
- Embedded SQL
    - SQL이 내장됨


# JDBC
- JDBC는 JAVA API 이다.
- metadata도 가져올 수 있다.
- Database 연동 model
    1. connection open
    2. statement 객체 생성
    3. 쿼리 실행하고 결과를 fetch한다.
    4. 에러 처리
## JDBC code
```java
public static void JDBCexample(String dbid, String userid, String passwd) { 
    try (Connection conn = DriverManager.getConnection( 
        "jdbc:oracle:thin:@db.yale.edu:2000:univdb", userid, passwd); 
        Statement stmt = conn.createStatement();
        ){ 
        stmt.executeUpdate("insert into instructor values('77987', 'Kim',  'Physics', 98000)");
        ResultSet rset = stmt.executeQuery("select dept_name, avg (salary) from instructor group by dept_name");
    }
    catch (SQLException sqle) { 
        System.out.println("SQLException : " + sqle);
    }
}
```
- try(~)
    - ~: connection open처리이다.
- catch(~)
    - ~: 에러처리
- stmt.executeUpdate
    - 질의 처리
- stmt.executeQuery
    - 질의 결과 fetch
- ResultSet rset
    - 질의 결과가 가져왔을 때 cursor의 역할을 한다.
    - rset으로 getString은 속성의 순서를 써도 가능하고 속성의 이름을 써도 가능하다.

## Prepared Statement
- java String 연결 '+'을 이용해서 쿼리 문장을 만드는 것은 바람직하지 않다.
    - SQL Injection 때문
- 따라서, PreparedStatement 객체를 생성해서 이 객체를 통해 쿼리문을 완성시킨다.
    - `PreparedStatement pStmt = conn.prepareStatement("insert into instructor values(?,?,?,?)");`
    - 이것이 기본적인 문장인데 ?에 값을 넣는다.
    - 이 때 첫번째부터 마지막까지 1~4의 숫자가 할당된다.
        - 즉 첫번째 value는 1번으로 지정해서 데이터를 삽입
        - `pStmt.setString(1, "88877");`
    - 그 후 excuteUpdate를 통해 쿼리를 처리한다.
        - `pStmt.executeUpdate();`

## Metadata Features
테이블에 대한 질의를 처리할 때 테이블의 정보를 모를 수 있다.     
이때 Metadata를 받아오는 함수를 이용하여 정보를 받아온다.
- getMetaData()
    - `ResultSetMetaData rsmd = rs.getMetaData();`
- Table의 속성을 모를 때
    - `rsmd.getColumnName(i)`
    - `rsmd.getColumnTypeName(i)`
- Table의 PrimarKey를 모를 때
    ```java
    DatabaseMetaData dmd = connection.getMetaData();
    ResultSet rs = dmd.getPrimaryKeys(“”, “”, tableName);
    (rs.getString(“KEY_SEQ”)
    ```
- Table의 이름을 모를 때
    - `ResultSet rs = dmd.getTables (“”, "", “%", new String[] {“TABLES”});`
    - `rs.getString(“TABLE_NAME“)`

## Transaction Control in JDBC
기본적으로 SQL 문은 자동적으로 commit이 된다.    
- tuple들을 insert문을 execute를 하면 자동적으로 실행이 된다.
- update 중에 잘못된 값이 있다면 이는 수정이 불가하다.

이를 수동으로 바꿀 수 있다.
- `conn.setAutoCommit(false);`
- 이를 통해 전체를 다 입력받은 후 commit하여 질의를 처리할 수 있다.
- `conn.commit();`
    - 처리를 완료하는 것
- `conn.rollback();`
    - 질의 처리 중 잘못된 값이 들어갔을 경우 이전에 데이터로 되돌아 갈 수 있다.

## SQL function call
function call도 가능
```java
CallableStatement cStmt1 = conn.prepareCall("{? = call some 
function(?)}");
CallableStatement cStmt2 = conn.prepareCall("{call some 
procedure(?,?)}");
```

## Large object in JDBC
Photo, video 등과 같은 큰 객체들에 대한 함수이다.
- getBlob()/getClob()
    - 데이터들을 받아온다.
- setBlob()/setClob()
    - blob.setBlob(int parameterIndex, InputStream inputStream)
    - clob.setClob(int parameterIndex, InputStream inputStream)

## SQLJ
java 내장 SQL이며, PL/SQL과 유사하다.    
`#sql iterator deptInfoIter(String dept_name, int avgSal);`    
- 이는 PL/SQL에서 Cursor의 역할을 한다.
- 나머지 PL/SQL참고

# Embedded SQL
- 호스트 프로그램이 SQL문을 직접 포함하고 있는 프로그램
- C, C++, Java Fortran, PL/1과 같은 프로그래밍 언어로 작성 가능
    - 책에서는 PL/1으로 소개가 되었다.
        - PL/1은 IBM에서 많이 사용함
    - PL/SQL를 학습 예정
        - ORACLE에서 만든 언어

## Running the Embedded SQL
- 호스트 언어에서 SQL문을 사용하기 위해 SQL문을 사용하겠음을 알려야 한다.
    - `EXEC SQL <embedded SQL statement >;`
    - 언어마다 다름
-  **데이터베이스 서버에 연동**
    - `EXEC-SQL connect to server user user-name using password;`
    - Oracle에서는 이미 로그인이 되어 있으므로 연동할 필요가 없다.
- 호스트 언어에서 선언된 변수를 사용하고 싶을 때
    - `:`을 사용해서 호스트 언어의 변수임을 밝힌다.
    - PL/SQL에서는 필요 없음
    - Example
        ```sql
        EXEC-SQL BEGIN DECLARE SECTION}
            int credit-amount ;
        EXEC-SQL END DECLARE SECTION

        EXEC SQL
            declare c cursor for 
            select ID, name
            from student
            where tot_cred = :credit_amount
        END EXEC
        ```
- Cursor
    - 각 튜플들을 저장하는 Buffer
    - 해당 튜플로 오면 그 튜플의 데이터들을 Buffer에 저장한다.
        - Iterator와 유사하나, 해당 데이터들을 Buffer에 저장하는 것이 다름
    - Form
        - `declare c cursor for <SQL query>`
    - Example
        ```sql
        EXEC SQL
            declare c cursor for 
            select ID, name
            from student
            where tot_cred = :credit_amount
        END EXEC
        ```
    - Cursor는 open 되어야 실행한다.
        - Form
            - `EXEC SQL open c;`
    - Cursor로 데이터 가져오기
        - Form
            - `EXEC SQL fetch c into :si, :sn END_EXEC`
            - si, sn에 데이터를 하나씩 저장한다.
        - for나 while로 연속해서 데이터를 가져온다.
            - 그리고 Cursor는 자동으로 다음 값을 지정한다.
            - 데이터가 존재하는지 꼭 체크하고 없다면 loop를 종료한다.
    - Cursor를 다 사용했다면 close한다.
        - Form
            - `EXEC SQL close c;`
### Updates Through Embedded SQL
Embedded SQL를 통해 (수정, 삽입, 삭제)의 기능을 수행할 수 있다.     
Cursor를 이용하여 수정, 삽입, 삭제의 기능도 가능하다.
- Cursor를 이용하여 update를 하기 위해 Cursor를 생성할 때 `for update`를 꼭 붙여준다.
    ```sql
    EXEC SQL 
        declare c cursor for
            select *
            from instructor
            where dept_name = 'Music'
            for update
    ```
- 수정할 때 `where current of c`의 조건을 주어 수정함
    ```sql
    update instructor
    set salary = salary + 1000
    where current of c
    ```

### Example of PL/SQL
![Example-of-PLSQL](./img/Example-of-PLSQL.JPG)

---

<br>

# 기말고사 범위


<br>

# Functions and Procedures
Functions and Procedures를 구분을 잘 하지 않음
- Functions
    - 일반적으로 return값이 있음
- Procedures
    - 일반적으로 Argument에 값을 반환함
- Functions와 Procedures는 "business logic"을 따른다.
    - business logic
        - 휴가날짜를 계산, 평점에 F학점을 넣을 것인가 뺄것인가 등과 같은 규정을 말함
    - 이를 따로 저장해서 사용하면 편리함
- SQL, C, Java, 등에서 포함할 수 있음

## Functions 선언
- Example Code: Declare Function
    ```sql
    create function dept_count (dept_name varchar(20))
        returns integer
        begin
        declare d_count  integer;
            select count (* ) into d_count
            from instructor
            where instructor.dept_name = dept_name
        return d_count;
    end
    ```
    - `create function dept_count (dept_name varchar(20))`
        - 함수 생성코드
        - 함수 명: dept_count
        - 함수 매개변수: (dept_name varchar(20))
            - 매개변수 명과 타입을 씀
    - `returns integer`
        - Return type
        - Return's'를 조심
- Example Code: Use Function
    ```sql
    select dept_name, budget
    from department
    where dept_count (dept_name ) > 12
    ```

### Table Functions
- Table을 return하는 함수
- Example Code
    ```sql
    create function instructor_of (dept_name char(20))
        returns table  (  
                ID varchar(5),
                name varchar(20),
                dept_name varchar(20),
                salary numeric(8,2))
            return table
                (select ID, name, dept_name, salary
                from instructor
                where instructor.dept_name = instructor_of.dept_name)

    ```

## SQL Procedures
- Example Code: Declare Procedures
    ```sql
    create procedure dept_count_proc (in dept_name varchar(20),
                                        out d_count integer)
        begin
            select count(*) into d_count
            from instructor
            where instructor.dept_name = dept_count_proc.dept_name
        end
    ```
    - ` create procedure dept_count_proc (in dept_name varchar(20),out d_count integer)`
        - in: 입력 argument
        - out: 출력 argument
- Example Code: Use Procedures
    ```sql
    declare d_count integer;
    call dept_count_proc( 'Physics', d_count);
    ```
    - 'Physics'를 입력으로 받고 d_count를 통해서 결과값을 읽어 온다.
- SQL Procedures은 dynamic SQL으로 프로그램 실행 중(runtime)에 생성된다.
- 오버로딩이 가능하다.
    - 같은 이름의 Procedures를 선언하더라도, 매개변수 수가 다르면 다르게 동작하는 Procedures를 만들 수 있다.

## Language Constructs for Procedures & Functions
- 기본적으로 **begin과 end를** 통해서 내용을 실행한다.
- 반복문
    - while
        ```sql
        while boolean expression  do
            sequence of statements ;
        end while
        ```
        - 일반 whilte문과 비슷함 while
        - 다음에 비교문이 들어감
    - repeat
        ```sql
        repeat
                sequence of statements ;
            until boolean expression 
            end repeat
        ```
        - `until boolean expression`
            - 여기서 비교문을 수행함
            - do~while문 실행방식
    - for
        ```sql
        declare n  integer default 0;
        for r  as
            select budget from department
            where dept_name = 'Music'
        do
            set n = n + r.budget
        end for
        ```
        - 이는 테이블의 모든 튜플을 돌고 종료한다.
- 조건절
    - if-then-else
        ```sql
        if boolean  expression
            then statement or compound statement
        elseif boolean  expression
            then statement or compound statement
        else statement or compound statement
        end if
        ```
- 예외
    ```sql
    declare out_of_classroom_seats  condition
    declare exit handler for out_of_classroom_seats
    begin
    …
    end
    ```
    - out_of_classroom_seats에서 에러가 발생했을 때
        - begin ~ end절을 실행한다.

## External Language Routines
- 다른 언어로 함수 또는 프로시저를 만들어서 사용이 가능하다.
    ```sql
    create procedure dept_count_proc(in dept_name varchar(20),
                                    out count integer)
    language C
    external name   '/usr/avi/bin/dept_count_proc'

    create function dept_count(dept_name varchar(20))
    returns integer
    language C
    external name '/usr/avi/bin/dept_count'
    ```
    - 위 프로시저는 /usr/avi/bin/dept_count_proc 경로에 있는 dept_count_proc파일을 실행한다.
    - 위 함수는 /usr/avi/bin/dept_count 경로에 있는 dept_count파일을 실행한다.
- 장점
    - operation이 더 효율적이다.
    - SQL만으로 표현이 안되는 것을 가능하게 함
        - ex) 출력 등
- 단점
    - DB에서 데이터를 가져올 때 데이터 손상이 발생할 수 있다.
    - 보안상에서 위험을 가지고 있다.
        - ex) 데이터 유출사고
- 따라서, 보안보다 효율성을 중시할 때 DB 내에서 수행한다.

## Security with External Language Routines
- 안전성 향상을 위한 두 가지 방법
    - Sandbox
        - 외부 언어로 function / procedure을 쓸 때,
        - 별도의 메모리 공간을 만들어주고 그 공간에서 작업을 수행하며 결과만 돌려준다.
    - Java와 같이 안전한 언어를 사용함
        - C같은 경우 Pointer 등을 이용하면서 메모리 접근 자유도가 높다.
        - 이는 안전성에 문제를 던질 수 있음
- 위 방법 모두 성능상 Overhead가 존재함


# Triggers
- Trigger: DB에서 수정되었을 때 자동적으로 실행되는 문장
- Trigger를 설계하기 위해서는 조건과 조건에 따른 동작을 정의해야 한다.

## Triggering Events and Actions in SQL
- Trigger를 발생시키는 조건은 3가지 이다.
    - insert
    - delete
    - update
    - 즉, DB가 수정되었을 때
- data가 수정되기 전/후 둘 다 참조가 가능하다.
    - 수정 전 data 참조
        - `referencing old row as`
    - 수정 후 data 참조
        - `referencing new row as`
- Trigger를 수정 전에 발생시킬 수 있고 수정 후에도 발생시킬 수 있다.
    - `before update of takes`
        - 수정 전에 발생
    - `after update of takes`  
        - 수정 후 발생

## Statement Level Triggers
- row Level Triggers와 대치된다.
    - row level은 각 행마다 Trigger가 실행됨
- Statement Level Triggers은 하나의 SQL문 마다 Trigger가 실행됨
- for each row대신 for each statement을 사용하면 됨
- 수정 전 Table과 수정 후 Table 둘 다 참조 가능

## Trigger 사용 자제
- Trigger를 자주 사용하면 여러 문제점이 있을 수 있음
    - 따라서, 남발하지 말고 자제하는 것이 좋음
- Trigger의 문제점
    - Trigger가 의도치 않게 사용될 수 있다.
        - 새로 insert 될 때만 Trigger를 설정해 두었을 때
            - 문제가 발생해서 이전 backup 데이터를 로드하면 중복 Trigger가 발생
        - 복사본이 실행될 때도 Trigger가 발생한다.
            - 원본에 대한 Trigger이기 때문에 복사본에서는 발생해서는 안된다.
    - 위 경우 Trigger를 중지시키고 실행해야 한다.
    - Trigger가 잘못된 경우 중요한 transactions이 실패할 수 있다.
- 다음의 경우에서 사용을 한다.
    - data를 요약할 때
        - 하지만 오늘날 materialized view를 제공함으로써 더 효율적인 관리가 가능
    - 복사본을 생성할 때
        - 이 또한 오늘날 DB가 제공하는 기능이 존재함
- Trigger를 사용하는 대신 function 또는 procedure로 Encapsulation해서 사용하는 것이 좋음

# Recursive Queries
```sql
with recursive rec_prereq(course_id, prereq_id) as (
        select course_id, prereq_id
        from prereq
    union
        select rec_prereq.course_id, prereq.prereq_id,
        from rec_rereq, prereq
        where rec_prereq.prereq_id = prereq.course_id
    )
select ∗
from rec_prereq;
```

## The Power of Recursion
- iteration
    - findAllPrereqs 예제는 iteration을 통해 만든 것 참고
    - iteration을 사용해서 연속적으로 rec_prereq를 추가함
    - 더이상 추가하지 않는 시점을 fixed point라고 한다.
- Recursive views들은 단순 증가(monotonic)하는 성격을 가져야 한다.

# Advanced Aggregation Features

## Ranking
- order by를 통해 순위를 메김
- Example
    ```sql
    select ID, rank() over (order by GPA desc) as s_rank
    from student_grades
    order by s_rank
    ```
- 일반적으로 순위 메기는 기준에서 같은 값을 가지면 같은 등수를 부여한다.
- dense_rank를 이용하면 같은 등수를 부여하는 것이 아닌 세밀하게 부여를 한다.
- subquery를 통해서도 가능은하나 비효율적이다.
- Ranking을 할 때 data를 분할할 수 있다.
    - Example
        ```sql
        select ID, dept_name,
            rank () over (partition by dept_name order by GPA desc) 
                    as dept_rank
        from dept_grades
        order by dept_name, dept_rank;
        ```
        - 과별로 나눈 다음 성적순으로 정렬 후 각 과마다 ranking을 메긴다.
- Rank절은 단일 select 절에서 발생할 수 있다.
- 또한 gruop by를 통해서도 가능하다.
- limit을 사용해서 tuple 갯수를 제한할 수 있다.
    ```sql
    select ID, GPA
    from student_grades
    order by GPA desc
    limit 10;
    ```
- null을 처음에 넣을지 나중에 넣을지 선택할 수 있음
- ntile()함수를 이용해서 등분할 수 있음
    ```sql
    select ID, ntile(4) over (order by GPA desc) as quartile
        from student_grades;
    ```
    - 위는 총 4등분을 하여 출력

## Windowing
- random한 변수들을 부드럽게 만들기 위함
- Example
    ```sql
    select date, sum(value) over 
        (order by date between rows 1 preceding and 1 following)
    from sales
    ```
    - 평균을 내면서 불규칙한 값들을 부드럽게 만듦
- partition이 가능함
    - Exmaple
        ```sql
        select account_number, date_time,
        sum (value) over
                (partition by account_number 
                order by date_time
                rows unbounded preceding)
            as balance
        from transaction
        order by account_number, date_time
        ```
        - 