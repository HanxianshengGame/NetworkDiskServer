#ifndef DATABASEWORK_H_
#define DATABASEWORK_H_
#include <mysql/mysql.h>
int RegisteredAccount(MYSQL *conn, const char *account, const char *passwd);
int ConnectDataBase(MYSQL **conn, const char *server, const char *user, const char *password, const char *databse);
int GetSaltFromDataBase(MYSQL *conn, const char *account,char *salt);
int GetCryptFromDataBase(MYSQL *conn, const char *account,char *crypt);
int InsertRecordToLogTable(MYSQL *conn, const char *account, const char *operator_name, const char *content);
#endif
