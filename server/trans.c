#include "/usr/include/mysql/mysql.h" //set your own path
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

char DB_HOST[] = #;
char DB_USER[] = #;
char DB_PWD[] = #;
char schema[] = #;

MYSQL* conn, connection;
MYSQL_RES* result;
MYSQL_ROW row;

char sel_sql[] = "SELECT * FROM test WHERE id = "; 
char INS_sql[] = "INSERT INTO test(id) VALUES (?)";

void trans(int connfd) 
{
    int n; 
    char buf[1024], sql[1024];

    mysql_init(&connection);
    conn = mysql_real_connect(&connection, DB_HOST, DB_USER, DB_PWD, schema, 3306, (char*)NULL, 0);

    printf("mysql connected!\n");
    while((n = read(connfd, buf, sizeof(buf) - 1)) != 0) {
	printf("server get %d byte : %s\n",n , buf);

	for(int i = 0; buf[i] != 0; i++)
	    if(buf[i]=='\n'){
	    	buf[i] = 0;
		break;
	    }

	strcpy(sql, sel_sql);
	strcat(sql, buf);
	
	printf("querry : %s\n",sql);
	if(mysql_query(conn, sql)){ 
		printf("querry error\n");
		continue;
	}	
	result = mysql_store_result(conn);

	if((row = mysql_fetch_row(result)) != NULL){
	    write(connfd, "id in", 6);
	}
	else write(connfd, "no in", 6);

    }
    

    mysql_close(conn);
}
