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