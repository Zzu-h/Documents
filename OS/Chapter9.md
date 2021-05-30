# Memory Management Strategies
- Virtual Address Space
    - 프로그램이 실행에 필요한 메모리 공간
    - Disk 공간에 일부를 Virtual Address Space를 잡아둔다.
- Physical Address Space
    - 실제 CPU가 읽을 수 있는 메모리
    - Virtual Sapace보다 공간이 더 작다.
- Swapping
    - VA 데이터와 PA 데이터를 교환 과정
    - 하지만 실제로 메모리 주소값이 다르기 때문에 OS가 그것을 관리해주어야 함
        - 해당 작업이 Address Translation이다.
- Address Translation
    - CPU가 만들어낸 가상 주소를 Physical Address로 바꾸는 작업
    - OS가 만든 Table을 통해서 바꾸는 작업을 함
- Memory Mapping Table
    - 가상 주소와 실제 주소의 연관관계를 저장해놓은 테이블
    - Page의 단위로 저장되어 있다.
- Page
    - Physical Memory와 Disk의 Virtual Memory를 교환하는 단위

# Background

## Memory Protection
- Memory Protection
    - 자신의 할당된 공간을 제외하고 나머지 공간에 접근하려고 할 때 막는 것
- base와 limit register의 쌍이 logical address(virtual address) 공간에 정의되어 있다.    
    - user mode에서 memory access할 때마다 base와 limit의 값과 비교를 한다.
    - 벗어나려고 한다면 segmentation fault를 발생시킨다.
- Kernel에 의해 base와 limit register가 갱신된다.

## Address binding
- Program은 binary 형태의 실행 가능한 형식으로 disk에 저장되어 있다.
- Address binding
    - 프로그램을 실행시켜 메모리에 올릴 때 실제 Physical memory 주소를 결정하는 것
- binding 과정
    -  Symbolic address -> relocatable address -> absolute address 
        - Symbolic address
            - code 상태
            - 변수를 선언할 경우 해당 변수가 코드로 남아있음
        - relocatable address
            - 실행 가능한 상태
            - Compiler가 만들어 준다.
            - 변수가 메모리의 시작주소로부터 얼마나 떨어져있는가를 정해준다.
        - absolute address 
            - 실제 Physical memory의 절대주소
            - 변수가 메모리 상의 실제 주소를 정해준다.
- binding 시기
    - Compile time
        - relocatable address가 만들어짐
        - Physical 주소가 정해진 상태로 나옴
        - 시작 주소가 바뀐다면 Compile를 다시 해야한다.
        - Compile time에 Physical 주소가 결정되는 경우가 있다.
            - OS의 boot loader의 경우 시작주소를 0번지로 확정지어야 한다.
            - 컴퓨터 시작할 때 0번지를 찍고 boot loader를 시작함
            - 이런 경우에 메모리 주소가 달라질 경우 compile을 다시 해야한다.
    - Load time
        - Main memory에 실제로 올리는 과정
        - relocatable code가 실제 메모리에 올라갈 때 상대주소가 결정됨
        - 이때 절대주소와 상대주소 모두 결정됨
    - Execution time
        - 프로그램 실행 중 해당 코드가 맞닿았을 때 메모리 주소가 결정됨
        - e.g.) dynamic memory allocation
        - Memmory Management Unit(MMU)
            - Hardware이다.
            - Address Table 관리하는 기능을 수행함
## Logical address
- virtual address
    - System 혹은 OS 입장에서 가상 메모리 공간
- logical address
    - 각 User Applicaion의 가상 메모리 공간
- physical address
    - 실제 메모리 주소
- compile-time and load-time address-binding이 다 끝나게 된다면
    - Logical and physical addresses이 같다고 볼 수 있다.
    - 현재 시스템에서는 사용하지 않음
### Memory mapping table
- CPU가 생성하는 Virtual Address를 Physical Address로 변환시켜주는 Table
1. 만일 VA가 0일 때 PA가 500을 가리킨다고 하자.
2. 프로세스가 죽거나 쫓겨난 후 다시 올라갈 때 Address가 바뀔 수 있다.
3. 바뀐 Address가 600일 경우 Table의 PA 부분에 500값을 600으로 바꿔준다.
4. CPU는 굳이 Address를 재설정할 필요없이 그대로 0번지를 사용하여 가리킬 수 있다.
### Memory Management Unit (MMU)
- Memory mapping table을 통한 Address Translation은 자주 일어나며 이 작업은 매우 빠른속도로 진행되어야 한다.
- 따라서, MMU는 Address Translation를 위한 HW Unit이다.
    - CPU 내에 존재
    - virtual 주소를 physical주소로 변환시킨다.
- 가장 간단한 방법
    - relocation register를 삽입한다.
    - CPU에서 Memory로 보내기 전에 한번에 변환이 가능함
    - 기본값을 register에 넣어두고 CPU에서 Memory로 보낼 때 logical address를 기본 값을 더해서 변환시킨다.


## Dynamic loading, linking, shared library
- 해당 루틴이 실제로 호출될 때 메모리에 적재하는 경우도 있다.
- 메모리의 효율성 때문에 사용함
- main memory에 똑같은 데이터가 다 올라가는 것을 막음
    - 예로 cout과 같이 자주 쓰는 명령어는 라이브러리에 넣고 한번만 메모리에 올림
- 자주 사용하지 않고 사이즈도 매우 큰 루틴을 관리하는데 매우 유용함

- Dynamic loading
    - 호출했을 때 Dynamic하게 메모리에 적재
- Dynamic linking
    - 프로그램이 실행될 때 링크됨
    - stub를 이용해서 linking 시점을 표시함
        - stub: dll 파일이 어디에 있는가를 저장한 code
    - 다음에 유용함
        - Shared libraries
            - e.g. cout
        - library가 update될 때

# Contiguous Allocation
- Main Memory는 일반적으로 두 부분으로 나눌 수 있다.
    - OS가 쓰는 영역
        - interrupt vector가 가장 아래에 들어가며 그 다음에 코드가 적재됨
    - User Process가 쓰는 영역
        - OS 위에 적재됨
        - 다른 process 영역에 접근하지 못하도록 mapping과 protection이 필요
            - Relocation registers과 Limit register를 사용함
                - 이때 Relocation registers가 base register가 된다.
- 여러 프로세스를 할당하다보면 Hole이 생김
- Hole
    - 사용 가능한 memory block
    - 사이즈가 다양하고 흩어져 있다.

## Dynamic storage allocation
- First-fit
    - 첫번째 hole이 프로세스가 들어갈 만큼 넉넉한 공간임
    - OS 기준으로 Overhead가 가장 적음
- Best-fit
    - 프로세스를 할당할 수 있는 hole 중 가장 작은 hole에 할당
- Worst-fit
    - 프로세스를 할당할 수 있는 hole 중 가장 큰 hole에 할당
- First-fit와 Best-fit가 Worst-fit보다 공간 활용에 대해서 더 낫다.

## Fragmentation
- Fragmentation
    - 메모리를 계속 할당해줌에 따라서 여러 Hole들이 생성된다.
    - 그 조각난 것들을 Fragmentation라 한다.
- 분류
    - External Fragmentation
        - total memory space에는 남아있으나 연속되게 남아있지 않음
    - Internal Fragmentation
        - Hole에 공간이 되어 프로세스를 할당을 했는데 Hole이 더 커서 그만큼의 남는 공간
        - 사용하기 어려운 공간
- Internel Fragmentation는 어쩔 수 없으나 External Fragmentation은 관리가 안된 것이다.
    - 이를 해결하기 위해 "compaction"를 이용해서 줄인다.
    - compaction: Hole들을 한쪽으로 모으는 작업
        - 제약조건
            - 프로세스가 running 하는 중간에 메모리 주소를 바꿀 수 있어야 한다.
        - 비용이 매우 많이 드는 작업이다.
## Paging
- compaction이 오버헤드가 매우 커서 탄생한 기법
- 비연속적이어도 된다.
- physical memory를 **frame**이라 불리는 고정된 사이즈의 블럭으로 나눈다.
- logical memory를 **page**라 불리는 같은 사이즈의 블럭으로 나눈다.
- 이젠 hole이 아니라 n개의 page을 관리한다.
- 하지만 이 기법은 하나의 프로세스가 연속된 공간에 할당되는 것이 아니다.
    - 하나의 프로세스가 나누어져서 메모리에 분산되어 있다.
    - 이를 위해 page table을 만들어서 메모리 주소를 관리한다.
- no external fragmentation
- page table
    - logical address를 Physical address로 translate 수행
    - ![page-table](./img/page-table.JPG)
