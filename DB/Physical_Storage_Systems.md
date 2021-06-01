# Classification of Physical Storage Media
기억 장치의 결정 요소
- 속도
- 비용
- 신뢰성
## Storage Hierarchy
![Storage-structure](./img/Storage-structure.JPG)

구분
- primary storage
    - 휘발성 메모리
    - 매우 빠름
    - cache, main memory가 속함
- secondary storage
    - 비화발성 메모리
    - primary storage보다 느리지만 빠름
    - **on-line storage**라고도 한다.
    - flash memory(SSD), magnetic disk가 속함
- tertiary storage
    - 비휘발성 메모리
    - 가장 느림
    - 보관 공간, Backup용도로 사용
    - **off-line storage**라고도 한다.
    - magenetic tape, optical storage(CD)가 속함
        - magenetic tape
            - Sequential access(순차적 접근을 함)
                - 임의 접근 불가
            - 1부터 12 TB 공간을 가짐
            - 큰 용랑(petabytes) Juke box를 만들 수 있다.

## Storage Interface
- Disk Interface
    - Sata: 일반 disk interface
    - SAS: Server interface
    - NVMe(Non-Volatile Memory Express): SSD
- SAN
- NAS

## Tape Storage
- backup과 data 보관 용도로 사용
- 순차적 접근
- 큰 용량을 가짐
- tape 가격이 매우 쌈

## Optical Storage
- 광학 저장 공간
- 비휘발성 메모리
- Disk가 돌면서 laser를 통해 읽는다.
- 종류
    - CD-ROM (640 MB) and DVD (4.7 to 17 GB)
        - 초기에 만들어짐
    - Blu-ray disks: 27 GB to 54 GB
    - CD-R, DVD-R, DVD+R
        - Write-one, read-many (WORM)
        - 보관용으로 사용
    - CD-RW, DVD-RW, DVD+RW, and DVD-RAM
        - 여러번 쓰고 읽을 수 있음
- 일반 disk보다 느림
    - magnetic disk보다 느림
- Juke-box 시스템에서 자동으로 CD를 넣고 빼는 작업을 통해 큰 Data를 관리할 수 있다.

## Magnetic Hard Disk
![Magnetic-Hard-Disk-Mechanism](./img/Magnetic-Hard-Disk-Mechanism.png)

- platter
    - platter가 여러 개로 쌓여있는 형태로 구성
        - 일반적으로 1 ~ 5개로 존재
    - 하나의 platter는 양면으로 사용된다.
    - platter의 표면은 track으로 구성된다.
        - 각 platter는 5K~100K track으로 구성된다.
    - 각 platter 당 arm이 하나씩 존재함
        - 이는 같이 움직임
- read-write head 
    - read-write head에서 읽고 쓰기를 한다.
    - arm을 통해서 고정되며
    - 이 arm은 직선운동을 통해 W/R을 수행한다.
- track
    - sector의 집합이자 platter 표면에 위치
    - 각 track마다
        - Inner track: 500~1000 sector
        - Outer track: 1000~2000 sector
- sector
    - track의 최소 단위
    - 일반적으로 512 byte
    - To read/write a sector
        - disk arm이 track에 오도록 하고
        - platter는 계속 회전하며 sector가 head밑으로 오도록 한다. 
- cylinder
    - platter에 있는 track들이 read-write head를 통해 한 번에 읽고 연결한 단위
    - track이 모여서 cylinder가 됨
- Disk controller
    - CPU와 Disk 사이에 존재
    - CPU가 명령을 내리면 Controller가 arm을 움직이고 회전하며 W/R의 작업을 수행함
    - checksum
        - 어떤 data를 쓸 때, 그 Data를 검증하는 요소
        - Data + checksum = 0000의 값이 나오면 올바른 값임
    - writing 수행 후 제대로 써졌는지 확인 작업도 수행
    - remapping of bad sectors을 수행
        - 에러가 난 경우 다른 곳으로 remapping해주는 작업을 수행함

### Performance Measures of Disks
- Access time(접근 시간)
    - Seek time(트랙 탐색 시간)
        - 트랙을 찾는 시간이다.
        - 평균 탐색 시간은 최악 시간의 1/2이다.
            - sector의 수가 같을 때 arm의 평균 이동 거리는 전체 이동거리의 1/3이다.
        - 일반적으로 4 to 10 milliseconds
    - Rotational latency(회전 지연 시간)
        - 찾고자 하는 sector를 찾아 head가 sector로 움직이는 시간
        - 평균 지연시간은 한 바퀴 도는 시간의 1/2이다.
    - Access time =  Seek time + Rotational latency
        - 일반적으로 5 to 20 msec 이다.
- Data-transfer rate(전송 시간)
    - 데이터 양에 비례
    - Access time보다 훨씬 빠르다.
- Disk block
    - 제일 작은 단위는 sector이지만, 값이 너무 작은 관계로 Disk block이라는 logical unit을 사용
    - 일반적으로 4~16 kb
    - block이 작을수록
        - 더 많은 전송이 가능
    - block이 클수록
        - space가 낭비됨
- Access pattern
    - Sequential access pattern
        - data가 순차적으로 저장됨
        - access time이 일정함
    - Random access pattern
        - data가 불규칙적으로 저장됨
        - access time이 더 많이 소비됨
- I/O operations per second (IOPS)
    - Disk 성능을 나타내기 위한 성능 측정 단위
    - 일반적으로 50 ~ 200 IOPS 이다.
- Mean time to failure (MTTF)
    - 고장 평균 시간
    - 평균 기간이 3 ~ 5년
    - E.G. 
        - 하나의 디스크가 1,200,000 시간의 MTTF라고 할때
        - 1000개의 디스크가 있다면 고장날 확률을 계산해볼 때 1,200 시간 후 고장이 난다.
        - 디스크를 직렬로 처리하게 되면 1000개의 disk가 1개로 묶이며 1000개가 1,200,000 시간을 나누어 가지기 때문

## Flash Storage
- USB Memory, SSD
- NOR flash와 NAND flash가 존재
    - 일반적으로 NAND flash를 많이 사용
        - 더 가격이 쌈
- page 라는 단위를 사용
    - 512 byte ~ 4 KB
    - 하나의 page를 읽을 때 20 ~ 100 msec 걸린다.
- Access time이 없다.
    - sequential and random read 차이가 없다.
- 덮어 쓰기 기능이 없다.
    - 지운 후 rewrite를 수행
- Solid state disk(SSD)
    - Block 단위 interface를 제공
        - 내부 flash 저장장치와 OS의 File 시스템 사이의 interface
    - SATA interface일 경우 500MB/sec
    - NVMe PCIe interface일 경우 3GB/sec
- 지우는데 시간이 꽤 걸린다.
    - 2 ~ 5 msec
    - 지우는 단위는 256KB ~ 1MB로 크게 사용한다.
- Remapping
    - 지우는 것이 시간이 걸리다 보니 Remapping을 한다.
        - 다른 곳에 먼저 data를 쓰고 지우는 것을 나중에 수행함
    - Flash translation table
        - Mapping을 빠르게 수행하기 위한 table
- 약 100만번 정도 지우기를 수행하면 더 이상 Flash memory를 사용할 수 없다.
    - 따라서, wear leveling을 이용한다.
        - 즉 균등하게 사용해야 함
### SSD Performance Metrics
- Random reads/writes per second
    - 4KB 기준으로
        - Read: 초당 10,000번을 읽는다. (10,000 IOPS)
        - Write: 초당 40,000번을 쓴다. (40,000 IOPS)
- SSD는 병렬 Read를 지원한다.
    - 4KB 기준으로
        - Read
            - 최대 32번의 명령어를 입력받아 한번에 실행이 가능함
            - SATA의 경우 100,000 IOPS
            - NVMe의 경우 350,000 IOPS
        - Write
            - 100,000 IOPS 그 이상
- Data transfer
    - SATA의 경우 400MB/sec
    - NVMe의 경우 2~3GB/sec
- Hybrid disks
    - magnetic disk와 flash cache를 혼합해서 사용

## Storage Class Memory
- Memory를 비휘발성 Memory로 만든 것
- Intel에서 만든 3D-XPoint memory technology
- 속도 매우 빠름

## RAID
- RAID: Redundant Arrays of Independent Disks 
    - 독립적인 disk를 모아서 같이 사용함
    - 더 넓은 용량과 더 빠른 속도를 제공
    - 더 높은 신뢰성 제공
        - 병렬 처리라 하나가 고장나면 그 부분만 고치면 됨
