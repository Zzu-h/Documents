# Web
- website
    -  인터넷 프로토콜 기반의 네트워크에서 도메인 이름이나 IP 주소, 루트 경로만으로 이루어진 일반 URL을 통하여 보이는 웹 페이지 (Web Page)들의 의미 있는 묶음이다
- web application
    - 인터넷이나 인트라넷을 통해 웹 브라우저에서 이용할 수 있는 응용 소프트웨어를 말한다.

## WebSite
- User
    - 웹 프레임워크와 상호작용하는 개체.
    - 사용자는 보안에 있어 취약점 덩어리이다.
        - 가장 많이 공격당하는 대상
- browser
    - 웹 서버에 정보를 제공하고 제공 받는다.
    - 제공 받은 정보를 사용자가 실제로 볼 수 있도록 처리

## Communication about Browser and Web server
통신은 HTTP 또는 HTTPS 프로토콜 규약을 지키며 일련의 요쳥들로 구성된다.    
> 요청: Request & Response
- HTTP는 브라우저와 웹 서버 사이의 통신을 정의하는데 사용
- HTTPS는 보안 계층인  SSL/TLS도 추가됨
    - 웹 서버가 브라우저에게 인증서를 제공함으로써 보안성 있는 통신을 하게 함
- 브라우저가 웹 서버로 요청하는 종류
    - GET: 데이터를 가져옴
    - POST: 데이터를 서버로 보냄
    - AJAX: 브라우저에서 실행 중인 자바스크립트에 의해 비동기적으로 수행되는 GET 또는 POST 요청
        - XML, JASON 또는 가공되지 않는 데이터를 수신할 수 있음
        - ex) 네이버 실시간 검색어

### Browswer View
- HTML, CSS, Media File, Data, HTTP Header 클라이언트 측 스크립트
- 받아와서 사용자에게 해석하여 보여줌

### Web Server
- Web Server
    - 아파치 / IIS / 기타 등
    - 데이터를 요청 받은 곳에 전송
- Web Application Server
    - DB나 그 외 서비스들을 정리하여 웹 서버에 올리는 역할

- Browser -> WS -> WAS -> DB

# Web Hacking Overview
- Injecting Malicious Data: 웹 어플리케이션에 조작된 데이터를 강제로 입력시켜 공격하는 것
    - Parameter Tampering
    - URL Tampering
    - Hidden Field Manipulation
    - HTTP Header Manipulation
    - Cookie Poisoning
    - Executable File Upload
- Exploiting Unchecked Input: 웹 서버가 정상 입력으로 간주하게 되어서, 백엔드 서비스 등에 2차 피해를 일으키는 공격
    - Cross-site Scripting (XSS)
    - SQL Injection
    - Path Traversal
    - Command Injection

## Injecting Malicious Data
### Parameter Tampering
웹 어플리케이션에서 사용하는 Parameter를 강제로 입력하여, 어플리케이션의 의도대로 동작하지 않게 하는 공격

## URL Tampering
URL로 중요한 데이터를 보내는 경우, 이를 조작하여 공격자의 의도대로 동작을 바꾸는 공격 방식