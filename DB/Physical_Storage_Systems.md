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