#include "header.h"

// Define and initialize variables related to database
sqlite3 *db;
char *zErrMsg = 0;
int rc;
char *sql;
const char* data = "Book Information";

int main(int argc, char* argv[]){
	// Operation control variable
	char mode;
	
	// Open database
	OpenDatabase();

	// Create SQL table
	CreateTable();

	// Operations
	Show();
	mode = getchar();
	while(mode != 'q'){
		// State
		int state = 0;

		// Exeption
		if(mode == '\n'){
			mode = getchar();
			continue;
		}

		// Help
		if(mode == 'h')
			Help();

		// Insert
		else if(mode == 'i')
			// Update state
			state = Insert(state);

		// Select
		else if(mode == 'v')
			state = View(state);

		// Advanced Select
		else if(mode == 's')
			state = Select(state);

		// Update
		else if(mode == 'u')
			state = Update(state);

		// Delete
		else if(mode == 'd')
			state = Delete(state);
		
		// Show prompt
		if(state)
			Show();
		mode = getchar();
	}

	// Close database
	sqlite3_close(db);
	return 0;
}