#include "../include/DataBaseWork.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <crypt.h>
int ConnectDataBase(MYSQL **conn, const char *server, const char *user, const char *password, const char *databse) {
    *conn = mysql_init(NULL);
    if(!mysql_real_connect(*conn, server, user,password, databse, 0, NULL,0)) {
        printf("Error connect to database:%s\n", mysql_error(*conn));
        return -1;
    } else {
        printf("connect success\n");
        return 0;
    }
}
char *GenRandomString(int length) {
    int flag, i;
    char *string;
    srand((unsigned)time(NULL));
    if((string = (char *)malloc(length)) == NULL) {
        printf("malloc failed! flag:14\n");
        return NULL;
    }
    for(i= 0; i < length+1; i++) {
        flag = rand()%3;
        switch(flag) {
        case 0:
            string[i] = 'A' + rand() %26;
            break;
        case 1:
            string[i] = 'a' + rand() % 26;
            break;
        case 2:
            string[i] = '0' + rand() % 10;
            break;
        default:
            string[i] = 'x';
            break;
        }
    }
    string[length] = 0;
    return string;
}
int RegisteredAccount(MYSQL *conn, const char *account, const char *passwd) {
    char *salt = GenRandomString(10);
    char cryptpwd[256];
    memset(cryptpwd, 0, sizeof(cryptpwd));
    strcpy(cryptpwd, crypt(passwd, salt));
    char query[256];
    memset(query, 0, sizeof(query));
    sprintf(query, "insert into account_table(account, salt, cryptpwd) values('%s', '%s','%s')", account, salt, cryptpwd);
    int t = mysql_query(conn, query);
    if(t) {
        printf("insert failure, error: %s\n", mysql_error(conn));
        return -1;
    }
    else {
        printf("insert success\n");
        return 0;
    }
}
int InsertRecordToLogTable(MYSQL *conn, const char *account, const char *operator_name, const char *content) {
  char query[256];
  memset(query, 0, sizeof(query));

  sprintf(query, "insert into log_table(account, operator, content) values('%s','%s', '%s')", account, operator_name, content);
  int t = mysql_query(conn, query);
  if(t) {
      printf("insert failure, error: %s\n", mysql_error(conn));
      return -1;
  }
  else {
      printf("insert success\n");
      return 0;
  }
}
int GetSaltFromDataBase(MYSQL *conn, const char *account,char *salt) {
    char query[256];
    memset(query, 0, sizeof(query));
    sprintf(query,"select salt from account_table where account = '%s'", account);
    


#ifdef DEBUG
    printf("query sen : %s\n", query);
#endif
    int t  = mysql_query(conn, query);
    if(t) {
        printf("Error making query:%s\n", mysql_error(conn));
        return -1;
    } else {
        MYSQL_RES *res = mysql_store_result(conn);
        printf("mysql_num_rows=%ld\n", mysql_num_rows(res));
        
        MYSQL_ROW row = mysql_fetch_row(res);
        if(row == NULL) {
            printf("not find data\n");
            return -1;
        } else {
#ifdef DEBUG
            printf("salt: %s \n", row[0]);
#endif
            strcpy(salt, row[0]);
        }
        mysql_free_result(res);
    }
    return 0;
}
int GetCryptFromDataBase(MYSQL *conn, const char *account,char *crypt) {
      char query[256];
    memset(query, 0 ,sizeof(query));
    sprintf(query, "select cryptpwd from account_table where account = %s", account);
    int t  = mysql_query(conn, query);
    if(t) {
        printf("Error making query:%s\n", mysql_error(conn));
        return -1;
    } else {
        MYSQL_RES *res = mysql_store_result(conn);
        printf("mysql_num_rows=%ld\n", mysql_num_rows(res));
        
        MYSQL_ROW row = mysql_fetch_row(res);
        if(row == NULL) {
            printf("not find data\n");
            return -1;
        } else {
#ifdef DEBUG
            printf("crypt: %s \n", row[0]);
#endif
            strcpy(crypt, row[0]);
        }
        mysql_free_result(res);
    }
    return 0;
 
}
