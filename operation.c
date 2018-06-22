#include "header.h"

// Variables related to database
extern sqlite3 *db;
extern char *zErrMsg;
extern int rc;
extern char *sql;
extern const char* data;

// Open database
void OpenDatabase(){
	rc = sqlite3_open("library.db", &db);
	if(rc){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}else
		fprintf(stdout, "Opened database successfully\n");
}

// Create SQL table
void CreateTable(){
	// Create SQL statement
	sql = "CREATE TABLE LIBRARY(\n" \
	      "  ID INT PRIMARY KEY     NOT NULL,\n" \
	      "  NAME           TEXT    NOT NULL,\n" \
	      "  KEYWORD1       TEXT    NOT NULL,\n" \
	      "  KEYWORD2       TEXT,\n" \
	      "  KEYWORD3       TEXT,\n" \
	      "  KEYWORD4       TEXT,\n" \
	      "  KEYWORD5       TEXT,\n" \
	      "  AUTHOR1        TEXT    NOT NULL,\n" \
	      "  AUTHOR2        TEXT,\n" \
	      "  AUTHOR3        TEXT,\n" \
	      "  AUTHOR4        TEXT,\n" \
	      "  AUTHOR5        TEXT,\n" \
	      "  PUBLISHER      TEXT    NOT NULL,\n" \
	      "  PUBLIC_DATE    TEXT    NOT NULL\n);";

	// Feedback information
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if(rc != SQLITE_OK){
		fprintf(stderr, "%s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
		fprintf(stdout, "Table created successfully\n");
}

int Insert(int state){
	// Variable declaration
	int key_num, author_num;
	char id[ID_LEN], name[INPUT_STR_LEN], publisher[INPUT_STR_LEN], public_date[DATE_LEN];
	char key[MN][INPUT_STR_LEN], author[MN][INPUT_STR_LEN];

	// Read information
	int i;
	mem(key);
	mem(author);
	scanf("%s%s", id, name);
	scanf("%d", &key_num);
	if(key_num <= 0 || key_num > MN){
		fprintf(stderr, "Invalid input: numbers should be in the range of [1, 5]\n");
		return 0;
	}	
	for(i = 0; i < key_num; ++i)
		scanf("%s", key[i]);
	scanf("%d", &author_num);
	if(author_num <= 0 || author_num > MN){
		fprintf(stderr, "Invalid input: numbers should be in the range of [1, 5]\n");
		return 0;
	}
	for(i = 0; i < author_num; ++i)
		scanf("%s", author[i]);
	scanf("%s%s", publisher, public_date);

	// Construct a string of command
	char str[STR_LEN] = "INSERT INTO LIBRARY VALUES";
	strcat(str, "(");
	strcat(str, id);
	strcat(str, ",\'");
	strcat(str, name);
	strcat(str, "\',");
	for(i = 0; i != MN; ++i){
		strcat(str, "\'");
		strcat(str, key[i]);
		strcat(str, "\',");
	}
	for(i = 0; i != MN; ++i){
		strcat(str, "\'");
		strcat(str, author[i]);
		strcat(str, "\',");
	}
	strcat(str, "\'");
	strcat(str, publisher);
	strcat(str, "\',\'");
	strcat(str, public_date);
	strcat(str, "\');");
	
	// Use sqlite3 API
	sql = str;
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if(rc != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else{
		state = 1;
		fprintf(stdout, "Records created successfully\n");
	}

	return state;
}

int View(int state){
	sql = "SELECT * FROM LIBRARY;";

	// Use sqlite3 API
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	if(rc != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else{
		state = 1;
		fprintf(stdout, "Operation done successfully\n");
	}

	return state;
}

int Select(int state){
	// Read informatin
	char ord[ORD_LEN], attribute[INPUT_STR_LEN];
	scanf("%s", attribute);
	scanf("%s", ord);

	// Construct a string of command
	char str[STR_LEN] = "SELECT * FROM LIBRARY ORDER BY ";
	strcat(str, attribute);
	strcat(str, " ");
	strcat(str, ord);
	strcat(str, ";");

	// Use sqlite3 API
	sql = str;
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	if(rc != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else{
		state = 1;
		fprintf(stdout, "Operation done successfully\n");
	}

	return state;
}

int Update(int state){
	// Read information
	char id[ID_LEN], attribute[INPUT_STR_LEN], new_value[INPUT_STR_LEN];
	scanf("%s", id);
	scanf("%s", attribute);
	scanf("%s", new_value);

	// Construct a string of command
	char str[STR_LEN] = "UPDATE LIBRARY SET ";
	strcat(str, attribute);
	strcat(str, "=\'");
	strcat(str, new_value);
	strcat(str, "\' WHERE ID = ");
	strcat(str, id);
	strcat(str, ";");

	// Use sqlite3 API
	sql = str;
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	if(rc != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else{
		state = 1;
		fprintf(stdout, "Update done successfully\n");
	}

	return state;
}

int Delete(int state){
	// Read information
	char id[ID_LEN];
	scanf("%s", id);

	// Construct a string of command
	char str[STR_LEN] = "DELETE FROM LIBRARY WHERE ID = ";
	strcat(str, id);
	strcat(str, ";");

	// Use sqlite3 API
	sql = str;
	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
	if(rc != SQLITE_OK){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else{
		state = 1;
		fprintf(stdout, "Deletion done successfully\n");
	}

	return state;
}