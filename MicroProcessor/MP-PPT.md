# Internal Organization of computers
- CPU
    - Register
- Memory
- I/O

## Von Neumann vs. Harvard architecture
Von Neumann 
![Von-Neumann](./img/Von-Neumann.png)
- 데이터와 코드 부분이 공유하는 bus를 사용

Harvard architecture
![Harvard-architecture](./img/Harvard-architecture.png)
- 데이터와 코드 부분이 분리되어 bus가 나누어져 있음
- AVR이 사용하고 있는 Architecture

# CPU
Task
- 명령어 수행
    - 명령어는 메모리에 존재
    - 메모리에서 명령어를 읽고 디코더에서 디코드 수행 후 명령어 수행
## Memory pin out
![Memory-pin-out](./img/Memory-pin-out.png)

메모리 중 가장 간단한 것     
구성 요소
- D0~D7: Data bus
    - / : bus임을 표시함
- A0~An-1: Address bus
- Vcc
    - 전원
- GND
- WE
    - 쓰는 것에 대한 것
- OE
    - 읽은 것에 대한 것
- CS: chip select
    - 메모리를 선택

## Connecting I/Os to CPU
만일 CPU가 모든 장치에 대해 직접 연결을 한다고 하면 상당히 많은 핀이 필요할 것이다.    
따라서, 전체 장치들이 bus를 공유하는 방식으로 사용한다.

### 첫 번째 방법: Peripheral I/O
모든 주소 공간을 공유하되 IO/MEM, CS를 통해 메모리주소와 IO주소를 구분해서 받는다.


![Connecting-Peripheral-IO-Memory-CPU](./img/Connecting-Peripheral-IO-Memory-CPU.png)

구성 요소
- Address bus
- Data bus
- Control bus
    - Write
    - Read
    - IO/-(MEM)
        - 이 회선이 high 일 때 IO장치 데이터를 받아온다.
        - 이 회선이 low 일 때 Memory의 CS가 Active가 되어 Memory의 데이터를 받는다.

### 두 번째 방법: Memory Mapped I/O
메모리와 분리된 주소 체계를 사용한다.    
예를 들어 메모리를 0~15번의 주소를 사용하게 하고 나머지 16번부터 IO장치에게 할당을 한다.

![Connecting-Memory-Mapped-IO-Memory-CPU](./img/Connecting-Memory-Mapped-IO-Memory-CPU.png)

구성 요소
- Address bus
- Data bus
- Control bus
    - Write
    - Read

이 방식을 사용하기 위해서는 0 ~ 15번지의 주소를 사용하면서 메모리를 사용함을 알리기 위해 CS에 Active Low를 흘려보내 주어야 한다.    
이를 위해 Logic Circuit을 처리해 줄 필요가 있다.    
<br>

solution
1. 사용할 주소의 범위 binary를 쓴다.
2. 사용할 주소의 범위에서 항상 같은 값 위치만 찾는다.
    - 위의 경우 00 ~ 0F까지 이므로 항상 같은 값 위치는 앞에서 4자리 이다.
3. 항상 같은 값 위치들만 NAND Gate로 연결한다.
    - 위의 경우 0만 존재하므로 a7~a4를 nand로 Bubble을 끼워 Active Low로 연결한다.

## Inside the CPU
구성 요소
- PC: Program Counter
    - 읽어와야 할 메모리 주소를 가지고 있음
- [Instruction decoder](#instruction-decoder)
- ALU: Arithmetic Logic Unit
- Register

과정
- 명령어를 수행하기 위해 명령어를 가지고 있는 주소를 저장하고 있는 PC가 준비됨
0. PC의 메모리 주소가 Address bus를 통해 메모리 주소로 접근
    - 그 후 일반적인 경우 PC가 다음의 주소를 가리키기 위해 1 증가
    - branch가 존재할 경우 그 이상 증가도 가능함
1. CPU는 Read신호를 보냄
2. 메모리의 CS가 Active가 되어 Data인 명령어를 보냄
3. 명령어가 Instruction decoder에 안착됨
    - 그 명령어를 해석함
4. 명령어를 수행함

## Instruction Decoder
명령어를 해석해준다.

![Instruction-Decoder](./img/Instruction-Decoder.png)

Instruction
- Opcode
    - 명령어를 의미함
- Operand
    - 데이터들을 담고 있음
- Example: ADD
    - 16bit Opcode
        - 0000 11rd dddd rrrr
    - D의 값과 R의 값을 더해서 D에다 저장


---

# General Purpose Microprocessors vs. Microcontrollers
- General Purpose Microprocessors
![General-Purpose-Microprocessors](./img/General-Purpose-Microprocessors.png)
- 이는 bus를 통해 ram rom 등이 연결되어있다.
- 따로 Component들을 연결할 필요가 있다.
- 장점
    - 확장성/이식성이 좋다.


- Microcontrollers
![Microcontrollers](./img/Microcontrollers.png)
- 이는 하나의 칩에 CPU RAM ROM 등 필요한 내용이 집적되어 있다.
- 따로 연결할 필요없이 바로 사용이 가능하다.
- Microcontrollers를 선정하는 방법은 자신이 하고자 하는 Application이 무엇인가에 달려있다.

- 장점
    - 하나에 집적되어 있으므로 작게 만들 수 있다.
- 단점
    - 이식성이 좋지 않다.

## Microcontrollers 종류
- 8-bit microcontrollers
    - AVR
    - PIC
    - HCS12
    - 8051
- 32-bit microcontrollers
    - ARM
    - PIC32

## AVR 이름에 따른 의미
![AVR-Name-Meaning](./img/AVR-Name-Meaning.png)

---

# AVR CPU
구성 요소
- ALU
- 32 General Purpose registers (R0 to R31)
- PC register
- Instruction decoder
![AVR-CPU-Component](./img/AVR-CPU-Component.png)

- SREG: Status Register
    - CPU상태를 가지는 레지스터
    - ITHSVNZC
        - I: Interrupt
        - T: Temporary
        - H: Half Carry
        - S: Sign
        - V: oVerflow
        - N: Negative
        - Z: Zero
        - C: Carry

# Assembler Project
![Assembler-Project](./img/Assembler-Project.png)
1. Editor Program
    - myfile.asm
    - 여기선 atmel
2. Assembler Program
    1. myfile.eep
    2. myfile.hex
        - Flash 메모리 영역에 다운할 수 있는 프로그램
    3. myfile.map
        - 메모리 주소를 저장함
    4. myfile.lst
    5. myfile.ojb

# How to speed up the CPU
- Clock 빈도수 향상
    - Clock이 빠르다?
        - 같은 시간에 처리하는 속도를 증가시킬 수 있음
    - 하지만 전류와 열이 많이 소모됨
- Architecture 바꾸기
    - Pipelining
        - fetch와 execute를 동시에 실행한다.
            - fetch에 들어온 일을 execute로 올리면서 밀린 일들을 fetch에 동시에 올림
    - RISC(Reduced Instruction Set Computer)
        - 제한된 명령어들을 가지고 있는 구조로 만드는 것
        - 장점
            - 명령어가 작고 구조가 단순하기에 일을 처리하는데 시간이 매우 짧다.

## RISC VS. CISC
HW를 제작할 때 RISC, CISC 둘 중 하나로 사용함   
하지만 Embedded system 에서는 RISC를 사용함

## RISC Architecture
- fixed instruction size
    - 명령어 크기가 고정되어 있다.
    - 따라서, 디코딩이 쉽고 HW설계도 쉬움
- 명령어 수가 적다.
    - 제한된 명령어로 원하는 명령어를 제작해서 사용해야 하는 단점이 존재
    - 어쩔 수 없이 메모리를 많이 사용하게 된다.
- 주소 지정에 제한이 있음
    - HW가 단순해지다 보니 주소도 제한적임
- Load/Store기능
- Harvard architecture
    - Opcode와 Operand의 bus를 분리시킨 구조이다.
    - 이를 통해 속도를 향상시킴
- 명령어 처리 될 때 대부분 1 machine cycle을 기준으로 처리된다.
- 32개의 Register 존재
    - Stack과 Memory사용을 줄일 수 있음

---

# Jump
## jump 주소 지정 방식
PC에 다음 위치로 움직이기 위한 방식
- PC = operand
    - non conditional jmp
        - JMP
- PC = PC + operand
    - Relative jump
        - RJMP
    - 현재 PC내용과 Operand값을 더해서 다음 주소지로 이동
- PC = Z register
    - Indirect jump
        - IJMP

# Stack & Call

## Stack
stack 예제
```asm
.INCLUDE "M128DEF.INC"
	.ORG	0
	;initialize the SP to point to the last location of RAM (RAMEND)
	LDI	R16, HIGH(RAMEND)	;load SPH
	OUT	SPH, R16
	LDI	R16, LOW(RAMEND)	;load SPL
	OUT	SPL, R16

	LDI	R31, 0
	LDI	R20, 0x21
	LDI	R22, 0x66
	PUSH	R20
	PUSH	R22

	LDI	R20, 0
	LDI	R22, 0

	POP	R22
	POP	R31
```

- 스택을 사용하기 위해서, 스택 포인터는 SRAM에 주소로 초기화 되어야 한다.
- 스택 포인터가 I/O 메모리에 있기 때문에 값들은 OUT 지시로 통해 로드될 수 있다.
- RAMEND는 SRAM의 마지막 주소를 가리키는 상수이다. 하지만 RAMEND는 16비트 주소이므로 8비트, HIGH and LOW 함수로 쪼개서 레지스터에 저장할 수 있다.

## Call
1. Call을 하게 되면 다음 실행할 주소를 Stack에 저장하고 함수로 이동하게 된다.
2. 다음 실행할 주소는 하위 8bit 먼저 Stack에 저장되고, 그 후 상위 8bit가 Stack에 저장된다.
3. 함수에서의 작업이 끝나고 (RET) Stack에서 다음 실행할 주소를 PC에 다시 올리면서 다음 작업을 수행한다.

Call 예제
```asm
    LDI R16,HIGH(RAMEND)
    OUT SPH,R16
    LDI R16,LOW(RAMEND)
    OUT SPL,R16        
    LDI R20,15
    LDI R21,5
    CALL FUNC_NAME
    INC  R20
L1:     
    RJMP  L1

FUNC_NAME:
    ADD  R20,R21
    SUBI  R20,3
    RET

```

# Time delay
명령어를 수행할 때 걸리는 delay 시간이다.     
- 단위는 1 machine cycle로 계산한다.
- 각 기계마다 시간이 주어지고 그 시간과 machine cycle의 곱을 통해 시간을 구할 수 있다.

---

# ATmega
- DDRx
    - 입력 또는 출력을 결정함
    - 0xff, 즉 1일 경우 출력 기능을 수행
    - 0x00, 즉 0일 경우 입력 기능을 수행
- PORTx
    - 출력을 수행함
- PINx
    - 입력을 수행함