#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h> // Based on SQLite3

#define INPUT_STR_LEN 50
#define STR_LEN 200
#define ID_LEN 11
#define DATE_LEN 11
#define ORD_LEN 5
#define MN 5
#define mem(a) (memset(a, 0, sizeof(a)))

// Help function declaration
void Show();
void Help();
int callback(void *data, int argc, char **argv, char **azColName);

// Database opration function declaration
void OpenDatabase();
void CreateTable();
int Insert(int state);
int View(int state);
int Select(int state);
int Update(int state);
int Delete(int state);

#endif