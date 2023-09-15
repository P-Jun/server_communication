# environ
Canonical, Ubuntu, 22.04 LTS, amd64 jammy image build on 2023-03-25

[docker env](https://github.com/P-Jun/server_mysql/tree/main)
# usage
## server

* Makefile
```
make
```
* run
```
./server_con
```
## client
run client.c
# implement
client의 추가적인 헤더와 설치를 막기위해 일단 microsft에 내장되어있는 winsock2.h를 사용하여 소켓 통신으로 서버와 통신하도록 구현하였습니다.

서버의 경우 server_con.c에서 소켓 생성과 클라이언트와 연결, trans.c에서 클라이언트의 입력을 받아 해당 정보를 db에 검색하는 역할을 수행합니다.

라이센스가 존재하는지 확인하고, 존재한다면 하드웨어 아이디가 일치하는지 확인합니다.
# etc
* client의 코드에 서버의 ip와 port를 변경해야 합니다.
* server의 trans.c에 db정보를 입력해야 합니다.
* mysql 헤더의 위치가 다르다면 해당 include 부분도 변경해 주세요.
