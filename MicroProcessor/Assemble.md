# 명령어 정리
## LDI
## ADD & SUB
## INC & DEC
## STS & LDS
메모리 관련 명령어
- STS
    - 메모리 번지에 레지스터 데이터 저장
- LDS
    - 레지스터에 메모리 번지의 데이터를 저장
## IN & OUT
I/O장치 관련 명령어
- IN
    - I/O장치로 부터 데이터를 불러와 REGISTER에 저장한다.
- OUT
    - I/O장치로 데이터를 내보냄

## Assembler Directives
- 별칭 지어주기
    - .EQU
        - 선언하는 것
        - 코드 내에서 변경이 불가함
    - .SET
        - 선언함
        - 코드 내에서 변경이 가능함
- .INCLUDE
    - 파일 불러오기
- .ORG
    - 프로그램 시작하는 주소를 지정함

## RJMP
## BRCC & BRCS
- BRCC
    - Carry를 0이면 jmp
- BRCS
    - Carry를 1이면 jmp
## BRNE
## TST
- Test Register
    - Register값이 0이면 Zero flag가 1로 세팅됨

## SBI & CBI
- SBI
    - IO Register에서 특정 비트를 1로 세팅함
    - Example
        ```asm
        SBI	PORTD,0	;PORTD.0 = 1
        SBI	DDRC,5	;DDRC.5 = 1
        ```
- CBI
    - IO Register에서 특정 비트를 0로 세팅함
    - Example
        ```asm
        CBI	PORTD,0	;PORTD.0 = 0
        CBI	DDRC,5	;DDRC.5 = 0
        ```
        

## SBIC & SBIS
점프 명령어
- SBIC
    - i번째 비트가 0이면 다음 명령어는 수행하지 않는다.
    - Example
        ```asm
        SBIC  PORTD,0  ;skip next instruction if PORTD.0=0
        INC   R20
        LDI   R19,0x23
        ```
- SBIS
    - i번째 비트가 1이면 다음 명령어는 수행하지 않는다.
    - Example
        ```asm
        SBIS  PORTD,0  ;skip next instruction if PORTD.0=1
        INC   R20
        LDI   R19,0x23
        ```