# Internal Organization of computers
- CPU
    - Register
- Memory
- I/O

# CPU
Task
- 명령어 수행
    - 명령어는 메모리에 존재
    - 메모리에서 명령어를 읽고 디코더에서 디코드 수행 후 명령어 수행
## Memory pin out
![Memory-pin-out](./img/Memory-pin-out.PNG)

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


![Connecting-Peripheral-IO-Memory-CPU](./img/Connecting-Peripheral-IO-Memory-CPU.PNG)

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

![Connecting-Memory-Mapped-IO-Memory-CPU](./img/Connecting-Memory-Mapped-IO-Memory-CPU.PNG)

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

![Instruction-Decoder](./img/Instruction-Decoder.PNG)

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
![General-Purpose-Microprocessors](./img/General-Purpose-Microprocessors.PNG)
- 이는 bus를 통해 ram rom 등이 연결되어있다.
- 따로 Component들을 연결할 필요가 있다.
- 장점
    - 확장성/이식성이 좋다.


- Microcontrollers
![Microcontrollers](./img/Microcontrollers.PNG)
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
![AVR-Name-Meaning](./img/AVR-Name-Meaning.PNG)

---

# AVR CPU
구성 요소
- ALU
- 32 General Purpose registers (R0 to R31)
- PC register
- Instruction decoder
![AVR-CPU-Component](./img/AVR-CPU-Component.PNG)

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

        