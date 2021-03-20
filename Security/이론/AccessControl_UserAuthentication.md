# Access Control and User Authentication

# Access Control
공격을 막는 가장 최적의 방법이다.
- 처음 위치에서 공격을 막는다.
- 기밀성을 제공해야 한다.

허가되지 않은 공개, 허가되지않은 변조로부터 data나 resouces들을 보호하는 작업

## Access Control Policies
추상적인 개념    
무엇을 어떻게 하는지를 원하는가?

- DAC(Discretionary access control: 임의적 접근 제어)
    - 파일 생성한 주인이 누가 읽을 수 있고, 쓸 수 있고, 실행할 수 있는지 결정함
    - 데이터의 주인이 그것에 누가 접근할 수 있는지 결정할 수 있다.
    - 방법
        - Access Control List(ACL)
            - Linux같이 그룹, 유저 등이 어떤 권한이 있는가 명시됨
        - ID, GROUP 기반
    - 장점
        - 세분화된 컨트롤이 가능
    - 단점
        - 관리측에서 사용자를 신뢰하지 못함
- MAC(Mandatory access control: 강제적 접근 제어)
    - 데이터 주인이 아니라 시스템이 권한을 부여함
    - 관리자나 전체를 관장하는 기관이 누가 접근할 수 있는지 미리 지정함
    - Rule-based access control 이라고도 한다.
        - RBAC과는 다르다!
    - EX
        - 군대 기밀정보 접근 레벨
    - 두 가지 규칙
        - No reed-up
            - 기밀 레벨이 주어진 주체가 더 높은 레벨을 읽을 수 없다.
        - No write-dwon
            - 기밀 레벨이 주어진 주체가 자기가 볼 수 있는 데이터들을(더 낮은 기밀 레벨의 데이터를) 덮어쓰면 안된다.
## Access Control Mechanisms(Models)
정책을 구현하는 수단    
그래서 그것을 어떻게 구현하겠는가?

- Access Control Matrices
    - 권한이 정의된 테이블이다.
    - 각 행은 주체(사용자, 그룹, 또는 시스템)에 대응
    - 각 열은 객체(파일, 폴더, 문서, 등)에 대응
    - 각 셀은 그 주체가 그 객체에 대해 어떤 권한을 가지는지 명시
        - 비어있는 셀은 아무런 권한이 없음
    - 단점
        - 비효율적이다.
            - 행렬이 매우 커지므로 스페이스가 매우 커진다.
    - 주체 위주로 압축하는 경우
        - Capabilities
    - 객체 위주로 압축하는 경우 
        - ACL
- Access Control Lists(ACL)
    - DAC의 방식 중 하나
    - 파일이나 디렉토리에 각 사용자의 권한을 명시
    - UNIX에서는 더 단축된 ACL을 사용
        - 소유주, 소유주 그룹, 다른 사용자들을 나누어서 권한을 표시
        - 세밀함을 잃음
        - permission이 3가지만 있음
        - windows도 비슷함
- Capabilities(CL: Capabilities List)
    - 주체 별로(ID별로) 각 객체에 대해서 권한을 명시
    - EX
        - 조작이 불가능한 티켓
            - 놀이공원 티켓에 탈 수 있는 기구 명시
        - Android app permision
            - 앱들 주체에 대해서 어떤 리소스들에 접근할 수 있는가 명시
            - manifest
- Role-based Access Contorl(RBAC)
    - Role을 정의함
    - 사용자가 작업 포지션이 바뀌면 특정 기능에 대한 동작 권한이 바뀐다.
    - MAC과 DAC을 섞어 놓은 모양
        - GROUP을 가진 DAC는 RBAC 기능을 수행할 수 있다.
- User Authentication: 사용자 인증
    - !! identification과 다르다.
        - identification: 누구인가를 찾아내는 것
        - Authentication: 누군가가 자기 자신을 인증하는 것
    - Authentication Mechanisms
        - 사용자가 기억하는 Something
            - Password, PIN etc..
            - 두 가지 방식
                - 직접 입력
                - 질문에 대한 답
            - 문제
                - 어깨 넘어 엿보기
                - 키로깅
        - 사용자가 가지고 있는 Something
            - ID card, SIM, RFID, OTP etc..
            - 문제
                - 도둑맞음
                - 손실
        - 사용자 자체 또는 행동의 Something
            - 지문, 얼굴, 목소리, 시그니쳐 etc..
            - 개인 정보 염려, 노출 되었을 경우 바꾸기 어려움
        - 두가지 요소를 섞어서 인증