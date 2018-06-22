#include "header.h"

// Variables related to database
extern sqlite3 *db;
extern char *zErrMsg;
extern int rc;
extern char *sql;
extern const char* data;

// Show prompt
void Show(){
	printf("Please enter your command\n");
	printf("Enter 'h' for help\n");
}

// Help information
void Help(){
	printf("___Hint___\n");
	printf("INSERT:    i [id] [name] [num_of_keywords] [keyword1...]" \
		   " [num_of_author] [author1...] [publisher] [public_date(yyyy-mm-dd)]\n");
	printf("VIEW:      v\n");
	printf("SORT:      s [attribute] [order(ASC | DESC)]\n");
	printf("UPDATE:    u [id] [attribute] [new_value]\n");
	printf("DELETE:    d [id]\n");
	printf("QUIT:      q\n");
}

// Callback function
int callback(void *data, int argc, char **argv, char **azColName){
	int i;
	fprintf(stderr, "%s: ", (const char*)data);
	for(i = 0; i != argc; ++i)
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	printf("\n");
	return 0;
}