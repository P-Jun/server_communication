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

우선 부차적인 부분은 제외하고 소켓 생성, 서버에 문자열 전송, 수신, 기초적인 에러 핸들링 부분만 남겨 두었습니다.

서버의 경우 server_con.c에서 소켓 생성과 클라이언트와 연결, trans.c에서 클라이언트의 입력을 받아 해당 정보를 db에 검색하는 역할을 수행합니다.

서버 측에서 db에 검색, 추가가 모두 가능한 것을 확인하였으나, 일단 검색하는 기능만 동작하게 고정하여 구현하였습니다.
# etc
* client의 코드에 서버의 ip와 port를 변경해야 합니다.
* server의 trans.c에 db정보를 입력해야 합니다.
* mysql 헤더의 위치가 다르다면 해당 include 부분도 변경해 주세요.
