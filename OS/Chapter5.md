# Process scheduling

## Motivation of Scheduling
컴퓨터 시스템 내에서 프로세스가 여러 개 존재할지라도 실제로 실행되기 위해서는 CPU를 활용해야 실행이 된다.    
하지만 실행하고자 하는 프로세스에 비해 CPU의 수는 너무나도 제한적이다.

Solution: CPU가 1개, 프로세스가 여러 개 일때
- CPU Schedule
    - 시간을 적절히 나누어서 모든 프로세스가 CPU를 사용할 수 있도록 함

### 목표
CPU를 누가 언제 어떻게 쓸것인지 정해야 함    
어떤 알고리즘을 통해 우선순위를 정하고 CPU를 사용하게 함    
이때 사용하는 알고리즘이 Scheduling algorithm이다


# Concepts of Scheduling
Process의 성질
- 일반적으로 Process는 CPU를 사용해야 실행이 된다.
    - Program 안에 들어가 있는 SW들이 실제로 실행되는 순간이 CPU가 실질적인 일을 함
        - 이 순간을 CPU burst라 한다.
- CPU를 사용하다 특정 시점에 주변 장치의 자료를 받는다.
    - 파일의 형태로 읽거나 쓰거나 한다.
    - 파일은 TEXT일 수도 있으나 Network Interface, Device 등을 의미
        - Network Interface, Device 등을 File의 형태로 관리한다.
    - 이 동안에는 CPU에서 할 일이 없다.
        - 이 순간을 **I/O burst**라고 한다.
- 즉, CPU burst와 I/O burst를 번갈아가며 수행함
    - Process에 따라 CPU burst가 더 길거나 짧을 수 있다.
        - CPU-intensive
            - CPU burst가 더 길 경우
            - 이 Process가 많을 경우 CPU Scheduling을 더 길게 잡는 것이 더 효율적
        - I/O-intensive
            - CPU burst가 더 짧을 경우
            - 이 Process가 많을 경우 CPU Scheduling을 자주 바꾸는 것이 효율적

#### Histogram of CPU-burst Times
![Histogram-CPU-burst-Times](./img/Histogram-CPU-burst-Times.JPG)

위 Histogram을 보면, 일반적으로 burst duration이 짧은 경우가 매우 많고, 반대로 긴 경우가 훨씬 드물다.

## CPU scheduler
- 어떤 프로세스가 CPU를 사용할 것인가를 골라주는 `Kernel의 프로그램 코드`
    - ready상태의 process들이 있을 때 그 중 하나만 골라 CPU 할당
- 언제 Process를 CPU에 올릴 것인가?(중요함)
    1. 현재 실행하고 있는 Process가 waiting 상태로 갈 때 
    2. 현재 실행하고 있는 Process가 ready 상태로 갈 때 
    3. waiting에서 ready 상태로 넘어갈 때
    4. 특정 Task가 끝났을 때

## Type of Scheduling
scheduler는 Kernel call이다.
- Nonpreemptive scheduling
    - 우선순위가 높은 프로스세가 들어올 때 이전 프로세스가 끝날 때까지 기다림
    - 할당된 CPU 시간을 기다려 줌
        - Time Slice로 시간이 할당됨
    - 프로세스가 특정 event가 발생하면 CPU를 놓아줌
        - e.g. I/O or Synchronization
    - Overhead가 줄어듦
        - 이전의 프로세스가 정상 종료가 되었기 때문
- Preemptive scheduling
    - 우선순위가 높은 프로스세가 들어올 때 이전 프로세스를 내쫓고 CPU를 차지함
    - block 상태에서 ready 상태로 되면 바꾼다.
        - block -> e.g. waiting
    - 또는 shared data access가 존재할 경우
    - Timer interrupt가 발생할 경우
    - 이 경우 Overhead가 존재함
        - 이전 프로세스가 하던 일을 중단해야하고 나중에 다시 이어서 해야 함

> 대부분의 UNIX 시스템은 context switch가 발생하기 전에 system call이 호출이 되서 실행하게 된다.: Non-preemptive kernel     
> Non-preemptive kernel은 real-time computing에 맞지 않다.

## Interrupt
Interrupt: HW의 외부 event를 알려주는 mechanism이다.   
CPU는 Interrupt가 발생하면 하던 일을 중단하고 즉시 Interrupt routine을 처리하게 된다.
- Example
    - Linux 2.6에서 Interrupt가 발생했을 때
        - Kernel은 하던 일을 중단하고 exception handler를 수행한다.
        - 하지만 Interrupt를 처리하고 있는 중에는 Interrupt가 또 들어오더라도 처리는 불가하다.

## Dispatcher
Dispatcher: 실제 다음 실행할 프로세스를 CPU에 할당시키고 여러가지 실행 준비를 함
- 실행 알고리즘을 Scheduler 실제 구현된 module을 Dispatcher라 한다.

- 하는 일은 Short-term Scheduler에 의해 선정된 프로세스에게 CPU의 control을 넘겨준다.
    - context switching
    - User mode로 전환
    - User program에 시작주소를 Program Counter를 통해 jump한다.
- Dispatch latency
    - 한 프로세스를 중단하고 다른 프로세스를 시작하는데 걸리는 시간
    - dispatch를 하는 것 자체도 overhead가 크다.

# Scheduling Criteria

다음의 기준으로 Scheduling이 좋은지 안좋은지 판단
- CPU utilization 
    - CPU를 가능한 한 바쁘게 일을 계속 시키는 것
    - 좋으면 좋을수록 좋음
- Throughput 
    - 주어진 시간 동안 프로세스들이 많이 끝나게 하는 것
    - 좋으면 좋을수록 좋음
- Turnaround time 
    - 실행 시작부터 프로세스가 된 후 그 프로세스가 종료될 때 까지의 시간
    - 짧을 수록 User 입장에서 좋아 보임
- Waiting time 
    - ready상태에서 기다리는 시간
- Response time
    - User에게 빠르게 결과물을 보여주는 시간

## Optimization Scheduling Criteria
- Maximize CPU utilization
- Maximize throughput
- Minimize turnaround time 
- Minimize waiting time 
- Minimize response time
- Average ? 
- Variance ?

# Scheduling Algorithms

## First-Come, First-Served (FCFS) Scheduling
- Ready queue에 먼저 들어온 프로세스에게 CPU를 할당함
- 장점
    - Ready queue를 관리하기가 쉬움
    - 비교적 공평함

### 비교
![FCFS-EX-1](./img/FCFS-EX-1.JPG)

이 존재할 때 순서대로 P1, P2, P3을 실행할 경우와 최적의 조건을 사용해서 비교해보자.

- 그냥
    - ![FCFS-EX-2](./img/FCFS-EX-2.JPG)
    - 각 Wating time: P1 = 0; P2 = 24; P3 = 27
    - 평균 Wating time : (0 + 24 + 27)/3 = 17
- 최적화
    - ![FCFS-EX-3](./img/FCFS-EX-3.JPG)
    - 각 Wating time: P1 = 6; P2 = 0; P3 = 3
    - 평균 Wating time : (6 + 0 + 3)/3 = 3

훨씬 효율적임     
그냥 했을 경우를 **Convoy effect**라 한다.
- 긴 process 뒤에 짧은 process가 오는 경우
- 1개의 CPU-bound process가 있고, 많은 I/O-bound process가 있을 경우

## Shortest-Job-First (SJF) Scheduling
Convoy effect를 막기 위한 Scheduling 기법
- CPU burst가 짧은 process부터 먼저 처리하는 기법
- Two Schema
    - nonpreemptive
        - 일단 CPU 가 어떤 process에 할당이 되어 있으면 CPU burst가 끝날 때까지 기다려줌
    - preempiive
        - CPU burst가 진행 중에 더 짧은 프로세스가 들어온다면 선점을 허용한다.
        - 이는 Shortest-Remaining-Time-First (SRTF)
        - nonpreemptive보다 Average waiting time은 짧지만 Overhead가 더 크다.
            - Context switching이 더 많이 발생
- SJF는 최적이다.
    - 모든 Task에 대해 minimum average waiting time

### SJF의 CPU burst의 길이 계산
- 다음 CPU burst의 길이를 알아야 사용 가능함
    - 하지만 구체적인 길이는 알 수 없다.
- 일반적으로 같은 프로세스들은 같은 style 대로 프로그램을 실행 함
- 반복적으로 실행되는 경우 loop를 함
- 즉, 과거의 정보를 통해 미래를 예상할 수 있음
    - 이를 통해 CPU burst를 예상하고 계산을 함
- 과거의 History를 통해 어느정도 평균을 낸다.

이전 CPU burst의 길이를 바탕으로 지수 평균을 사용
- t_n
    - n번째 CPU burst의 실제 길이
- τ_(n+1)
    - 다음 발생할 CPU burst의 예상 값
- α, 0 ≤ α ≤ 1
    - 가중치
- Difne: `τ_(n+1) = αt_n + (1-α)τ_n`
- 극단값
    - α = 1
        - τ_(n+1) = t_n
        - 무조건 직전의 CPU burst만 보겠음을 의미
    - α = 0
        - τ_(n+1) = τ_n
        - 이전 History가 무엇이든지 상관안하고 초기 예상값 그대로 사용하겠음을 의미

## Priority scheduling
- 프로세스마다 차별을 두는 scheduling 방식
    - 어떤 프로세스는 더 자주 CPU에 할당
- 각 프로세스에다가 Priority Number을 할당해 준다.
    - Priority Number가 더 높은 프로세스에게 CPU를 더 자주 할당한다.
    - 일반적으로 숫자가 작을수록 우선순위 높음
- Preemptive와 Nonpreemptive로 구분하여 볼 수있음
- SJF는 Priority scheduling의 일종이다.
    - Priority scheduling에서 CPU burst time을 기준으로 삼음
- 문제점: Starvation(indefinite blocking)
    - Priority가 낮은 프로세스는 끝없이 ready상태로 대기하며 양보할 수 있다.
    - 그 프로세스는 시간이 지나도 CPU를 할당받을 확률이 낮아짐
    - waiting time이 무한정 길어질 수 있음
- Sol: Aging
    - 오랫동안 CPU를 못 받은 Process에게 우선순위를 점진적으로 높여준다.
- 대부분의 시스템이 Priority scheduling를 사용
- Priority 할당 방법
    - Static priority
        - 한번 번호를 할당하면 바뀌지 않는다.
    - Dynamic priority
        - 번호를 할당하더라도 추후 바뀔 수 있다.
        - ex_ Aging

## Round-robin scheduling
- 각각의 Process에게 CPU time의 작은 단위(time quantum)를 정해두고 그 할당된 시간만큼만 우선적으로 할당해 줌
- 그 할당된 시간이 끝나면 ready queue의 맨 뒤로 들어간다.
- n개의 process가 있는 ready queue에서 마지막 process의 최대 waiting time은 (n-1)q time이다.
    - q는 quantum time
    - 무한한 waiting time을 만들지 않는다.
- 만일 q가 길다면 FIFO(queue의 작동방식)을 따라 수행한다.
- 하지만 q가 짧다면 context switching이 자주 발생하여 overhead가 커진다.
- 일반적인 rule
    - 대부분의 CPU burst time보다는 time quantum을 조금 작게(80%) 한다.

SJF와 비교
- ![Round-robin-EX1](./img/Round-robin-EX1.JPG)
    - 다음과 같이 프로세스가 있고, q = 20일 때
    - ![Round-robin-EX2](./img/Round-robin-EX2.JPG)
    - 이와 같이 수행을한다.
- SJF보다 평균 turnaround time이 더 높다.
    - 하지만 response time이나 waiting time은 더 효율적일 수 있다.

## Multilevel Queue
Multilevel Queue: Ready queue를 여러 queue로 나누어서 관리하는 queue    
- queue마다 다른 알고리즘을 적용하기 위해서 만들어짐
- Example: foreground processes와 background processes를 따로 둠
    - foreground processes – RR
        - 당장 화면에 나오는 것, User가 반응하는 시간이 필요한 것
    - background processes – FCFS
        - CPU를 최대한 효과적으로 사용하는 것이 좋음
- 하지만 프로세스가 해당 알고리즘에 맞지 않고 다른 알고리즘에 적용할 필요가 있을 수 있다.
    - 이때, queue들 사이에서 교환이 필요함 즉 Scheduling이 필요
    - Example: Time slice
        - CPU의 시간을 일정분량 나누어서 각 queue에게 할당을 한다.
        - 위의 경우 background가 CPU 점유율이 낮으므로 20%를 보장해준다.
        - 나머지 80%를 foreground가 가져감


## Multilevel Feedback Queue
- Multilevel Queue를 만들어두고 프로세스들이 여러 Queue를 돌아다닐 수 있도록 한 것
- Multilevel Queue를 더 잘 관리하기 위해 만들어진 방법
- 다음의 파라미터들이 필요하다.
    - queue의 수
    - 각 queue의 scheduling algorithms
    - 어떤 경우에 process priority가 올라가는지, 내려가는지 결정하는 기준 방식
    - 실제로 queue를 옮겨갈 수 있는 mechanism

# Multiple-Processor Scheduling
기본적으로 CPU가 여러 개이다.     
이를 분류하면
- Symmetric Multiprocessing (SMP)
    - 똑같은 CPU가 여러개이다.
    - 모든 CPU가 우선순위 없이 스케줄링할 때 자체적으로 CPU사용을 결정함
    - 조금 더 복잡
- Asymmetric multiprocessing
    - CPU가 여러개 존재하지만 자격이 같지가 않음
    - Master가 존재하며 이것이 CPU를 관리한다.
## Issue
- Load balancing
    - 일을 골고루 나누어서 모든 CPU가 최대한 바쁘게 만드는 것
    - Push migration
        - 놀고 있는 CPU가 존재하면 그 CPU에 할당
        1. 주기적으로 노는 CPU가 있는지 확인한다.
        2. Load balance가 깨지면 재할당
    - Pull migration
        - 놀고 있는 CPU가 자기가 직접 일을 가져옴
- Process affinity
    - 프로세스에 따라 선호하는 CPU가 달라지게 된다.
        - 그에 따라 CPU를 할당하는 것이 다르게 됨
    - 각각의 프로세스별로 자기한테 유리한 CPU가 할당 되도록 하는 것
    - Cloud Computing에서도 중요하게 보임

## Affinity를 고려하여 Scheduling
- Soft affinity
    - OS가 affinity를 가지고 스케줄링을 할 때 되도록 affinity를 고려하지만,
    - 100% 보장을 하지 못한다.
- Hard Affinity
    - System call을 이용해서 다른 CPU로 넘어가지 않도록
    - 무조건 특정 Process는 특정 CPU에만 할당되도록 하는 것

## Thread Scheduling
Kernel이 인식하는 것은 Process이지 Thread가 아니다.    
따라서, Thread Scheduling은 다음과 같이 나뉜다.
- Global Scheduling
    - Kernel Level에서 Scheduling을 수행해준다.
    - Kernel이 알아서 프로세스와 동일한 수준으로 쓰레드를 관리해준다.
    - System-contention scope
- Local Scheduling
    - User Level에서 User Thread들 간에 Kernel Thread 하나에 Mapping 되어 있는 쓰레드가 여러 개 있을 경우
        - 그 쓰레드들 중에서 누가 먼저 Scheduling이 될지를 결정함
        - LWP 내부에서 결정됨
    - Process-contention scope
![Global-Local-Thread-Scheduling](./img/Global-Local-Thread-Scheduling.JPG)

# OS Example (Linux 2.6)     
- Linux Scheduling은 기본적으로 scheduling classes 따라서 Scheduling을 한다.
    - 각각의 Priority 별로 그룹을 나누어져 있다.
    - 그룹별로 다른 Scheduling Mechanism을 적용시킨다.
    - active & expired
        - 위 두 개의 array를 가지고 ready queue를 구현한다.
    - active array 중에서 highest-priority task가 들어있는 array를 CPU 할당함
- 각 Process는 3개의 Class로 나누어진다.
    - SCHED_FIFO
        - first-in first-out **real-time process**
        - 우선순위가 높은 process 할당
        - 다른 Process가 Runnable하지 않다면, 무조건 이 CPU를 독점함
        - CPU를 한 번 잡으면 끝날 때까지 사용하게 함
        - Kernel
    - SCHED_RR
        - round robin **real-time process**
        - 일정시간 지나면 CPU를 다른 Process에게 할당해 줌
        - Kernel
    - SCHED_NORMAL
        - conventional time-shared process
        - **Conventional processes**
        - 우선순위 낮은 process 할당
        - User

## Scheduling of Conventional processes
- 모든 Conventional processes는 자기 고유의 static priority를 가진다.
    - 그 priority의 범위는 100(우선순위 높음)~139(우선순위 낮음)이다.
        - nice value를 통해 process의 우선순위를 바꿀 수 있음
            - nice는 -20 ~ +19를 가짐
            - nice value (ranging from -20 to +19) + 120
    - 모든 새로운 프로세스는 부모의 static priority를 상속받는다.
- static priority를 정해놓고 Round-Robin 방식으로 수행한다.
    - static priority에 따라 time quantum을 다르게 한다.
        - static priority가 낮은 process는 time quantum을 낮게 할당
        - static priority가 높은 process는 time quantum을 높게 할당
        - base time quantum
            - = (140 - static priority) X 20 if static priority < 120
            - = (140 - static priority) X 5 if static priority >=120
- base priority에 따라서 Scheduling이 되어 있으면
    - Starvation과 유사한 단점이 발생하게 된다.
    - 이를 위해 Dynamic priority를 추가한다.
        - Dynamic priority = max (100, min(static priority-bonus+5, 139))
    - Bonus time은 
        - waiting time이 길어질수록 Bonus time은 더 커진다.
        - 그 범위는 0~10이다.

### Ready queue 구현하기
Linux에서는 Ready queue를 2개의 Array로 구현한다.
- Active array
    - CPU에 올라갈 예정인 Process들 대기
    - 위 Base time quantum만큼 사용하고 Expired array로 Running이 끝난 Process를 옮긴다.
- Expired array
    - Active array에서 running이 끝난 Process들을 적재한다.
    - Active array의 모든 Process들이 time quantum만큼 실행 하고 비워진다면,
        - Expired array와 Active array를 Swap한다.
        - 그리고 다시 time quantum만큼 실행한다.
- 이렇게 함으로써 Round-Robin 방식과 유사한 형태로
    - Starvation이 생기는 것을 줄여준다.

## Scheduling of Real-time processes
Conventional Process보다 우선순위가 높은 Process들을 별도로 이 스케쥴링 함
- 스케줄러는 항상 더 높은 우선순위의 Process를 우선시 한다.
- Conventional Process와는 달리 Real-time Process는 항상 active하다고 생각한다.
- 위와 같은 이유로 Ready queue는 Actvie array만 있다.
- Scheduling 방식
    - 기본적으로 우선순위대로 Process들을 실행한다.
        - <u>같은 우선순위의 Process들에 대해</u>
            - 다음의 두 가지 방식으로 처리를 한다.
    - Scheduling of real-time FIFO processes
        - FIFO 형식으로 Real-time Scheduling을 한다.
    - Scheduling of real-time RR processes
        - RR 형식으로 Real-time Scheduling을 한다.

## New scheduling method(Linux 2.6.13)
- Linux 2.6.13에서 Conventional classes에 대해 새로운 Scheduling 기법이 추가됨(CFS)
- [Completely Fair Sharing (CFS)](#cfs) scheduler
    - CONFIG_FAIR_GROUP_SCHED

### CFS
- 각각의 Process들이 CPU time에 1/n 만큼 사용하는 것이 공평하고 이상적이다.
    - 하지만 실제로는 이렇게 구현이 힘듦
- CFS는 최대한 위처럼 공평하게끔 할당해주도록 하는 것을 목표로 함
- Virtual time
    - CFS를 구현하기 위해 도입된 개념
        - 시간은 정수이므로 1/n처럼 유리수를 표현할 수 없다.
        - 이를 위해 Virtual time을 넣어서 생각을 하게 되었다.
    - 이 Vruntime이 가장 적다는 것은 현재 가장 불공평한 상태에 놓여있음을 의미한다.
        - 따라서, 이 가장 적은 Vruntime의 Process에게 CPU를 할당해 줌
- Example
    - 6의 CPU를 A가 2/3 B가 1/3을 할당하기 위해
        - A가 1~4, B가 5~6을 할당받는 것은 불공평하다 생각이 듦
        - A-B-A-A-B-A로 할당 받는 것이 위 사례보다 더 공평함
    - 이를 구현하기 위한 CFS이다.

#### Vruntime
Virtual time이다.    
각 Vruntime은 처음은 항상 0임.
- `vruntime += (NICE_0_LOAD / se->load.weight) * delta_exec`
    - NICE_0_LOAD
        - CPU가 어떻게 나누어지는지에 따라 달라지는 상수값
    - se->load.weight
        - 자신의 Process의 비중
        - 위 예제의 경우 A는 2 B는 1이 된다.
- Vruntime이 작을 경우
    - CPU에 먼저 할당된다.
- Vruntime이 같을 경우
    - weight을 비교하여 더 비중이 높은 것이 CPU에 할당된다.

# Algorithm Evaluation
알고리즘이 잘 작동하는 것인지 확인

1. Deterministic modeling
    - 가장 간단한 방식
        - 모델링을 하는 방법이다.
    - 단점
        - Process가 매우 많을 때 도착시간, Priority 등을 일일이 그리기에는 너무 벅차다.
        - Deterministic하게 Arrival time이 나오지 않는다.
2. Queueing models
    - 실제적인 workload를 흉내내서 실제와 비슷한 환경을 만들어낸 상태
        - 수치적인 모델을 만들어낼 수 있는 형태
    - 컴퓨터 시스템을 Server를 네트워크으로 이해함
    - CPU는 Ready queue가 있는 server로 이해함
    - 이를 이용해서 어떤 역할을 하는가?
        - Utilization, Arrival 빈도수, 어떤 Rate로 Service가 실행되는가를 통해
        - 평균 queue 길이와, 평균 waiting time 등을 가지고 수치적인 모델링을 함
    - 간단한 Formula
        - `Average queue length = average arrival rate * average waiting time`
3. Simulations
- 실제로 가장 시스템 만드는 사람들이 많이 쓰는 방식
- 어떤 Process가 언제 생겨서 CPU를 얼마나 썼는지, I/O가 언제 발생했는지를 모두 Log로 남겨둔다.
    - 이를 이용하여
        - FCFS Simulation
        - SJ Simulation
        - RR Simulation
4. Implementation
- 실제로 구현해봄
    - 가장 일이 많지만 가장 정확함
- 실제로 구현하는 만큼 많은 비용이 든다.