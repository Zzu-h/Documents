# Database Systems
- **DBMS**(Database Management System)
    - DBMS은 다음과 같은 내용의 역할을 수행한다.
        - 상호 관련있는 데이터를 수집
        - 데이터 접근에 대한 프로그램의 집합
        - 사용하기 편리하고 효율적인 환경
- Database System은 다음과 같은 데이터 컬렉션을 관리하는데 사용된다.
    - 매우 가치있는 collections of data
    - 상대적으로 큰 collections of data
    - 여러 사용자와 애플리케이션이 동시에 접근하는 collections of data
- 정리하자면,
    - 복잡하고 큰 데이터 수집을 관리하는 복잡산 SW 시스템
- DB는 우리의 삶에 모든 방면에 영향을 끼친다.

# Purpose of Database Systems
초기에는 DB가 파일 시스템에 직접 구축되었으며, 이로인해 다음과 같은 내용을 야기했다.
- 데이터가 중복되고 일관성 없어짐
    - 데이터가 여러 파일 형식으로 저장되므로 다른 파일과 중복된다.
- 데이터 접근이 어려워짐
    - 각 새 작업을 수행하기 위해 새 프로그램을 만들어야 했다.
- 데이터 고립
    - 다중 파일과 포맷
- 무결성 문제
    - 무결성 제약 조건은 명시적으로 명시되지 않고, 프로그램 코드에 묻힌다.
    - 새 제약 조건을 추가하거나 기존 제약 조건을 변경하기가 어렵다.
- 수정의 원자성
    - 부분 업데이트가 수행하는 상태에서 오류가 발생하면 데이터베이스가 일관되지 않을 수 있다.
- 다중 사용자에 의한 동시성 제어
    - 성능을 위해 동시 접근이 필요함
    - 통제가 되지 않는 동시 접근은 데이터 불일치를 야기함
- 보안성 문제
    - 전체는 아니지만, 일부 데이터에 사용자 엑세스를 제공하기 어렵다.

Database Systems은 위 모든 문제에 대해 해결책 제시

## View of Data
DB System의 주 목적은 사용자에게 데이터에 대한 추상적인 관점을 제공하는 것
- Data models(데이터 설계 - modeling)
    - 데이터, 데이터 관계, 데이터 의미, 일관성 제약 조건을 설명하기 위한 개념 도구 모음
    - 다음을 기술하기 위한 도구의 집합
        - Data
        - Data Relationships
        - Data Semantics(의미론)
        - Data Constraints(제약)
    - Relational Model(관계형 모델)
    - Entity-Relationship data model(개체-관계 모델 - ERM)
    - Object-based data models
        - Object-oriented data models(객체 지향 데이터 모델)
        - Object-relational data models(객체 관계 데이터 모델)
    - Semi-structured data model (XML)
        - 데이터와 스키마 사이에 구분이 없는 DB 모델
        - 목적에 따른 구조의 양에 따라 사용된다.
    - 다른 오래된 모델
        - Network model
        - Hierarchical model

# Data abstraction(데이터 추상화)
- 데이터 추상화를 통해 사용자에게 데이터 구조의 복잡성을 숨길 수 있음
- 3 levels of data abstraction이 있다.
    1. Physical level
        - 레코드가 어떻게 저장되어 있는지 기술한다.
    2. Logical level
        - 데이터베이스에 저장되어 있는 데이터를 기술하고, 그 데이터들 사이의 관계를 기술한다.
    3. View level
        - 사용자가 보는 유일한 실질적인 DB의 부분
        - 데이터 유형의 세부 정보를 굳이 사용자에게 보여주지 않는다.
        - 필요한 정보만 보여준다.

# Instances and Schemas
- Schema: DB의 전반적인 설명
    - DB에 데이터가 어떻게 저장되는지에 관한 기본적인 구조를 Schema라고 한다.
    - Logical Schema: DB의 전반적인 논리 구조
    - Physical Schema: DB의 전반적인 물리 구조
- Instances: 특정 시간에 DB의 실질적인 내용이다.
    - Snap shot 같이 그 순간에 있는 데이터이다.

# Physical Data Independence
논리적 스키마를 변경하지 않고 물리적 스키마를 수정하는 기능
- 일반적으로, 다양한 level과 component 사이의 인터페이스는 일부 부분의 변화가 다른 부분에 심각한 영향을 미치지 않도록 잘 정의되어야 한다.
- 응용 프로그램은 데이터 표현과 저장의 상세 내용이 노출되지 않아야 한다.

# Data Definition Language(DDL)
데이터 정의어     
DDL 컴파일러는 **Data Dictionary**에 저장된 템플릿 테이블의 집합들을 생성한다.    

<br>

Data Dictionary는 metadata를 포함한다.
- DB 구조
    - Table의 이름
    - Table의 속성 이름과 타입
- 무결성 제약조건
    - Primary Key
        - 주키: 식별할 수 있는 키
- 권한
    - 누가 무엇에 접근할 수 있는지

# Data Manipulation Language(DML)
데이터 조작어    
DML은 질의어라고도 한다.      
적절한 데이터 모델에 의해 만들어진 데이터를 수정 및 접근하기 위한 언어    
- 기본적으로 DML의 두 가지 유형이 있다.
    - Procedual DML(절차적 DML)
        - 사용자에게 필요한 데이터와 그 데이터를 얻는 방법을 정의하게끔 함
    - Declarative DML(선언적 DML)
        - 데이터를 얻는 방법을 정의하는 것 없이 어떤 데이터가 필요한지만 사용자에게 요구함
        - 비절차적 DML이라고도 한다.

# SQL Query Language
- 비절차적언어이다.     
- Turing machine equivalent language가 아니다.
    - 기능이 완벽하지 않다.(모든 기능을 가지고 있지 않다.)
- 프로그래밍을 하려면 고급 언어(C++, JAVA 등)가 필요하다.
    - SQL이 내장된 언어
    - JAVA + SQL, etc..
    - Host Language: 위 JAVA나 C++같이 SQL이 내장된 언어를 일컫는다.
- API(Application Program Interface)를 통해서 DB에 접속이 가능하다.

# Database Design
DB 설계
- Logical Desgin(Program)
    - Business decision
        - 어떤 속성이 필요한가?
    - Compuer Science decision
        - 어떤 테이블을 어떻게 구성할 것인가?
- Physical Design(실제 데이터가 저장되는 구조)
    - DB의 물리적 layout을 결정
        - ex 옵션 같은 것들을 줌, 파티션을 함 etc

# Database Engine
DB 핵심프로그램
- The storage manager
- The query processor component
- The transaction management component
    - Atomic(원자성)
        - 데이터가 중간에 끊기면 안됨

## ~~Storage Manager~~
~~이번 학기에 안함~~

~~OS 파일을 사용, 데이터를 저장하는 기능    
Data fiels, Data dictionary, indices~~

# Query Processing
질의를 처리    

1. Parsing and translation
    - 구문 분석
2. Optimization
    - 최적화
3. Evaluation
    - 실행

# Transaciont Management
**Concurrency-control manager(동시성 제어)**

# Database Architecture
- Centralized databases(중앙 집중 DB)
    - DB가 1개
- Client-server
    - 하나의 서버와 다수의 클라이언트
- Parallel databases
    - 여러 DB가 병렬처리
- Distributed databases
    - 분산 DB

# Database Applications
- Two-tier architecture
    - Server
        - DB System
    - Client
        - user
        - application
- Three-tier architecture
    - Server
        - application server
        - DB System
    - Client
        - user
        - application client

# Database Users
- naive users - 일반 사용자
- application programmers - DB 개발자
- sophisticated users - 데이터 분석가
- database administrators(DBA) - 관리자
    - 스키마 정의 - 개발자 + 관리자
    - 저장 구조와 접근 방식 정의 - 개발자 + 관리자
    - 스키마와 물리적 조직 수정 - 개발자 + 관리자
    - 권한 부여
    - 유지 보수 루틴
    - 백업
    - 디스크 공간 체크
    - 현재 돌아가는 일을 모니터링
