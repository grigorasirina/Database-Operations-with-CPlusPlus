#include <iostream>
#include <libpq-fe.h> // Include the PostgreSQL C API header

int main() {
    // Step 1: Initialize a PostgreSQL connection
    PGconn *conn = PQconnectdb("dbname=mydb user=myuser password=mypassword host=localhost port=5432");
    
    // Check if the connection to the database is successful
    if (PQstatus(conn) == CONNECTION_BAD) {
        std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return 1;
    }

    // Step 2: Create a table (CREATE operation)
    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS Employees (ID SERIAL PRIMARY KEY, NAME VARCHAR(255), AGE INT);";
    PGresult *res = PQexec(conn, createTableSQL);
    
    // Check for errors during table creation
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "CREATE TABLE failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
        PQfinish(conn);
        return 1;
    } else {
        std::cout << "Table created successfully" << std::endl;
        PQclear(res);
    }

    // Step 3: Insert data into the table (CREATE operation)
    const char *insertDataSQL = "INSERT INTO Employees (NAME, AGE) VALUES ('John Doe', 30);";
    res = PQexec(conn, insertDataSQL);
    
    // Check for errors during data insertion
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "INSERT failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
    } else {
        std::cout << "Data inserted successfully" << std::endl;
        PQclear(res);
    }

    // Step 4: Read data from the table (READ operation)
    const char *selectDataSQL = "SELECT * FROM Employees;";
    res = PQexec(conn, selectDataSQL);
    
    // Check for errors during data retrieval
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "SELECT failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
    } else {
        std::cout << "Data selected successfully" << std::endl;
        
        // Process and display the result set
        int rows = PQntuples(res);
        for (int i = 0; i < rows; i++) {
            int id = std::stoi(PQgetvalue(res, i, 0));
            const char *name = PQgetvalue(res, i, 1);
            int age = std::stoi(PQgetvalue(res, i, 2));
            std::cout << "ID: " << id << ", NAME: " << name << ", AGE: " << age << std::endl;
        }
        PQclear(res);
    }

    // Step 5: Update data in the table (UPDATE operation)
    const char *updateDataSQL = "UPDATE Employees SET AGE = 31 WHERE NAME = 'John Doe';";
    res = PQexec(conn, updateDataSQL);
    
    // Check for errors during data update
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "UPDATE failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
    } else {
        std::cout << "Data updated successfully" << std::endl;
        PQclear(res);
    }

    // Step 6: Delete data from the table (DELETE operation)
    const char *deleteDataSQL = "DELETE FROM Employees WHERE NAME = 'John Doe';";
    res = PQexec(conn, deleteDataSQL);
    
    // Check for errors during data deletion
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "DELETE failed: " << PQerrorMessage(conn) << std::endl;
        PQclear(res);
    } else {
        std::cout << "Data deleted successfully" << std::endl;
        PQclear(res);
    }

    // Step 7: Close the PostgreSQL connection
    PQfinish(conn);

    return 0;
}
