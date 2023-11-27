#include <iostream>
#include <mysql/mysql.h> // Include the MySQL C API header

int main() {
    MYSQL *conn; // MySQL connection pointer
    MYSQL_RES *res; // Result set pointer
    MYSQL_ROW row; // Row data pointer

    // Step 1: Initialize MySQL connection
    conn = mysql_init(NULL);
    if (conn == NULL) {
        std::cerr << "mysql_init() failed" << std::endl;
        return 1;
    }

    // Step 2: Connect to MySQL database
    if (mysql_real_connect(conn, "localhost", "username", "password", "my_database", 0, NULL, 0) == NULL) {
        std::cerr << "mysql_real_connect() failed: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // Step 3: Create a table (CREATE operation)
    if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS Employees (ID INT PRIMARY KEY AUTO_INCREMENT, NAME VARCHAR(255), AGE INT)")) {
        std::cerr << "CREATE TABLE failed: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    } else {
        std::cout << "Table created successfully" << std::endl;
    }

    // Step 4: Insert data into the table (CREATE operation)
    if (mysql_query(conn, "INSERT INTO Employees (NAME, AGE) VALUES ('John Doe', 30)")) {
        std::cerr << "INSERT failed: " << mysql_error(conn) << std::endl;
    } else {
        std::cout << "Data inserted successfully" << std::endl;
    }

    // Step 5: Read data from the table (READ operation)
    if (mysql_query(conn, "SELECT * FROM Employees")) {
        std::cerr << "SELECT failed: " << mysql_error(conn) << std::endl;
    } else {
        std::cout << "Data selected successfully" << std::endl;
        res = mysql_store_result(conn);
        if (res) {
            while ((row = mysql_fetch_row(res))) {
                std::cout << "ID: " << row[0] << ", NAME: " << row[1] << ", AGE: " << row[2] << std::endl;
            }
            mysql_free_result(res);
        }
    }

    // Step 6: Update data in the table (UPDATE operation)
    if (mysql_query(conn, "UPDATE Employees SET AGE = 31 WHERE NAME = 'John Doe'")) {
        std::cerr << "UPDATE failed: " << mysql_error(conn) << std::endl;
    } else {
        std::cout << "Data updated successfully" << std::endl;
    }

    // Step 7: Delete data from the table (DELETE operation)
    if (mysql_query(conn, "DELETE FROM Employees WHERE NAME = 'John Doe'")) {
        std::cerr << "DELETE failed: " << mysql_error(conn) << std::endl;
    } else {
        std::cout << "Data deleted successfully" << std::endl;
    }

    // Step 8: Close MySQL connection
    mysql_close(conn);

    return 0;
}
