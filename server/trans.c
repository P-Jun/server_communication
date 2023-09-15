#include "/usr/include/mysql/mysql.h" //set your own path
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

char DB_HOST[] = "#";
char DB_USER[] = "root";
char DB_PWD[] = "example";
char schema[] = "test";

MYSQL* conn, connection;
MYSQL_RES* result;
MYSQL_ROW row;

char sel_sql[] = "SELECT * FROM test WHERE license = '";
char id_is_null[] = " AND id is null";
char sel_plus[] = " AND id = '";
char UPD_sql[] = "UPDATE test SET id = '";
char UPD_plus[] = "WHERE license = '";

void trans(int connfd) 
{
    int n; 
    char buf[1024], sql[1024];
    char sql_tmp[1024];
    mysql_init(&connection);
    conn = mysql_real_connect(&connection, DB_HOST, DB_USER, DB_PWD, schema, 3306, (char*)NULL, 0);

    printf("mysql connected!\n");

    read(connfd, buf, sizeof(buf) - 1);

    for(int i = 0; buf[i] != 0; i++)
        if(buf[i+1]==0){
        buf[i+1] = 39;//'
        buf[i+2] = 0;
        break;
    }

    strcpy(sql, sel_sql);
    strcat(sql, buf);

    mysql_query(conn, sql);
    result = mysql_store_result(conn);
    if((row = mysql_fetch_row(result)) == NULL){
    	write(connfd, "3", 2);
	return;
    }

    strcat(sql, id_is_null);
    strcpy(sql_tmp, UPD_plus);
    strcat(sql_tmp, buf);


    printf("q1 : %s\n", sql);
    mysql_query(conn, sql);
    result = mysql_store_result(conn);

    if((row = mysql_fetch_row(result)) != NULL){
        write(connfd, "0", 2);
	read(connfd, buf, sizeof(buf) - 1);
	for(int i = 0; buf[i] != 0; i++)
            if(buf[i+1]==0){
            buf[i+1] = 39;//'
            buf[i+2] = 0;
            break;
        }

	strcpy(sql, UPD_sql);
	strcat(sql, buf);
	strcat(sql, sql_tmp);
	printf("q2 : %s\n",sql);
	mysql_query(conn, sql);

    }
    else{
	write(connfd, "1", 2);
        strcpy(sql, sel_sql);
        strcat(sql, buf);
        read(connfd, buf, sizeof(buf) - 1);
        for(int i = 0; buf[i] != 0; i++)
            if(buf[i+1]==0){
            buf[i+1] = 39;//'
            buf[i+2] = 0;
            break;
        }
	
	strcat(sql, sel_plus);
	strcat(sql, buf);
	printf("q2 : %s\n", sql);
	mysql_query(conn, sql);
        result = mysql_store_result(conn);
        if((row = mysql_fetch_row(result)) ==  NULL)
            write(connfd, "0", 2);
        else
            write(connfd, "1", 2);

    }
    mysql_close(conn);
}
