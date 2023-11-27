#include <iostream>
#include <sqlite3.h>

// Define a callback function to handle the results of SELECT queries.
int callback(void *data, int argc, char **argv, char **azColName) {
    // Process each row of the result set here
    for (int i = 0; i < argc; i++) {
        // Print the column name and its value
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
    return 0; // Returning 0 indicates successful processing of the row
}

int main() {
    sqlite3 *db; // SQLite database pointer
    char *errMsg = 0; // Error message string

    // Step 1: Open a database or create a new one if it doesn't exist.
    int rc = sqlite3_open("my_database.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return(1);
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    // Step 2: Create a table (CREATE operation).
    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS Employees ("
                                 "ID INT PRIMARY KEY NOT NULL,"
                                 "NAME TEXT NOT NULL,"
                                 "AGE INT NOT NULL);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Table created successfully" << std::endl;
    }

    // Step 3: Insert data into the table (CREATE operation).
    const char *insertDataSQL = "INSERT INTO Employees (ID, NAME, AGE) VALUES (1, 'John Doe', 30);";
    rc = sqlite3_exec(db, insertDataSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Data inserted successfully" << std::endl;
    }

    // Step 4: Read data from the table (READ operation).
    const char *selectDataSQL = "SELECT * FROM Employees;";
    rc = sqlite3_exec(db, selectDataSQL, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Data selected successfully" << std::endl;
    }

    // Step 5: Update data in the table (UPDATE operation).
    const char *updateDataSQL = "UPDATE Employees SET AGE = 31 WHERE NAME = 'John Doe';";
    rc = sqlite3_exec(db, updateDataSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Data updated successfully" << std::endl;
    }

    // Step 6: Delete data from the table (DELETE operation).
    const char *deleteDataSQL = "DELETE FROM Employees WHERE NAME = 'John Doe';";
    rc = sqlite3_exec(db, deleteDataSQL, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Data deleted successfully" << std::endl;
    }

    // Step 7: Close the database connection.
    sqlite3_close(db);

    return 0;
}
