//
// Created by Alan Ta on 4/25/21.
//

#ifndef CARRENTALSYSTEMV2_SQLITEDB_H
#define CARRENTALSYSTEMV2_SQLITEDB_H
#define BOOST_TEST_DYN_LINK
#include "main.h"
#include <iostream>
#include <string>
#include <sqlite3.h>
#include <iomanip>

using namespace std;

class DBLite {

private:
    // Pointer to SQLite connection
    sqlite3 *db;

    // Save any error messages
    char *zErrMsg;

    // Save the result of opening the file
    int rc;

    // Saved SQL
    char* sql;

    // Compiled SQLite Statement
    sqlite3_stmt *stmt;

    // Create a callback function
    static int callbackTransact(void *data, int argc, char **argv, char **azColName){
        int i;

        printf("####################################\n");
        for(i = 0; i<argc; i++){
            printf("-------------------------------------\n");
            std::cout << std::left << std::setw(15) << azColName[i] << ": " << std::right;
            //printf("%s : ", azColName[i]);
            printf("%s ", argv[i] ? argv[i] : "NULL");
            printf("\n");


        }
        printf("-------------------------------------\n");
        printf("####################################\n");

        printf("\n");

        return 0;
    }
    static int callback(void *data, int argc, char **argv, char **azColName){
        static int shown = 0;
        int i;

        if(shown == 0) {
            for(i = 0; i<argc; i++){
                printf("%s ", azColName[i]);

            }
            printf("\n-------------------------------------\n");
            shown++;
        }

        for(i = 0; i<argc; i++){
            printf("%s ", argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
    }

    void checkDBErrors() {

        if( rc ){
            // Show an error message
            cout << "DB Error: " << sqlite3_errmsg(db) << endl;

            closeDB();

        }

    }


public:

    DBLite() {
        // Save the result of opening the file
        rc = sqlite3_open("CarRentalDatabase.db", &db);

        checkDBErrors();


    }

    void createTable(int whichTable) {

        if(whichTable == 0){
            sql = "CREATE TABLE CustomerInfo ("  \
      "Customer_ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "Name TEXT NOT NULL," \
      "DL TEXT NOT NULL," \
      "Phone INTEGER NOT NULL);";
        }
        if(whichTable == 1){
            // Save SQL to create a table
            sql = "CREATE TABLE CarInfo ("  \
            "Car_ID INTEGER PRIMARY KEY AUTOINCREMENT," \
            "Car_Regis TEXT NOT NULL," \
      "Year INTEGER NOT NULL," \
      "Make TEXT NOT NULL," \
      "Model TEXT NOT NULL," \
      "Type TEXT NOT NULL," \
      "Color TEXT NOT NULL," \
      "Avail TEXT NOT NULL);";
        }
        if(whichTable == 2){
            sql = "CREATE TABLE RentalData ("\
            "Invoice_ID INTEGER PRIMARY KEY AUTOINCREMENT," \
            "Days INTEGER NOT NULL," \
            "RentDue TEXT NOT NULL," \
            "CustName TEXT NOT NULL," \
            "DLNum TEXT NOT NULL," \
            "CarVin TEXT NOT NULL," \
            "CarName TEXT NOT NULL," \
            "CONSTRAINT Rentalfk1 FOREIGN KEY(DLNum) REFERENCES CustomerInfo(DL) ON UPDATE CASCADE ON DELETE CASCADE," \
            "CONSTRAINT Rentalfk2 FOREIGN KEY(CustName) REFERENCES CustomerInfo(Name) ON UPDATE CASCADE ON DELETE CASCADE," \
            "CONSTRAINT Rentalfk3 FOREIGN KEY(CarVin) REFERENCES CarInfo(Car_Regis) ON UPDATE CASCADE ON DELETE CASCADE);";

        }
        if(whichTable == 3){
            sql = "CREATE TABLE HistoryInfo ("\
            "Hist_ID INTEGER PRIMARY KEY AUTOINCREMENT,"  \
            "CurrTime TEXT NOT NULL," \
            "CurrDate TEXT NOT NULL," \
            "Noun TEXT," \
            "Subject TEXT," \
            "OtherNoun TEXT);";
        }
        if(whichTable == 4){
            sql = "CREATE TABLE InvoiceBill ("\
            "InvoiceBill_ID INTEGER PRIMARY KEY AUTOINCREMENT," \
            "InvoiceNum INTEGER NOT NULL," \
            "BillName TEXT NOT NULL," \
            "BillDL TEXT NOT NULL," \
            "BillCarReg TEXT NOT NULL," \
            "BillCarName TEXT NOT NULL," \
            "DueDate TEXT NOT NULL," \
            "DaysRent INTEGER NOT NULL," \
            "Total TEXT NOT NULL," \
            "CONSTRAINT Billfk1 FOREIGN KEY(BillDL) REFERENCES CustomerInfo(DL) ON UPDATE CASCADE ON DELETE CASCADE," \
            "CONSTRAINT Billfk2 FOREIGN KEY(BillName) REFERENCES CustomerInfo(Name) ON UPDATE CASCADE ON DELETE CASCADE," \
            "CONSTRAINT Billfk3 FOREIGN KEY(DueDate) REFERENCES RentalData(RentDue) ON UPDATE CASCADE ON DELETE CASCADE," \
            "CONSTRAINT Billfk4 FOREIGN KEY(DaysRent) REFERENCES RentalData(Days) ON UPDATE CASCADE ON DELETE CASCADE," \
            "CONSTRAINT Billfk5 FOREIGN KEY(BillCarReg) REFERENCES CarInfo(Car_Regis) ON UPDATE CASCADE ON DELETE CASCADE);";
        }
        if(whichTable == 5){
            sql = "PRAGMA foreign_keys = ON;";
        }

        // Run the SQL
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    }

    void insertData(int table, const std::string& val1, const std::string& val2, const std::string& val3, const std::string& val4 , const std::string& val5, const std::string& val6 , const std::string& val7, const std::string& val8){

        char *query = NULL;

        if(table == 0){
            asprintf(&query, "INSERT INTO CustomerInfo('Name', 'DL', 'Phone') VALUES  ('%s', '%s', '%s');", val1.c_str(), val2.c_str(), val3.c_str());
        }
        if(table == 1){
            asprintf(&query, "INSERT INTO CarInfo('Car_Regis', 'Year', 'Make', 'Model', 'Type', "
                             "'Color', 'Avail') VALUES  ('%s', '%s', '%s', '%s', '%s', '%s', 'Available');", val1.c_str(), val2.c_str(), val3.c_str(), val4.c_str(), val5.c_str(), val6.c_str());
        }
        if(table == 2){
            asprintf(&query, "INSERT INTO RentalData('Invoice_ID', 'Days', 'RentDue', 'CustName', 'DLNum', 'CarVin', 'CarName') VALUES  ('%s', '%s', '%s', '%s', '%s', '%s', '%s');", val1.c_str(), val2.c_str(), val3.c_str(), val4.c_str(), val5.c_str(), val6.c_str(), val7.c_str());
        }
        if(table == 3){
            asprintf(&query, "INSERT INTO HistoryInfo('CurrTime', 'CurrDate', 'Noun', 'Subject', 'OtherNoun') VALUES  ('%s', '%s', '%s', '%s', '%s');", val1.c_str(), val2.c_str(), val3.c_str(), val4.c_str(), val5.c_str());
        }
        if(table == 4){
            asprintf(&query, "INSERT INTO InvoiceBill('InvoiceNum', 'BillName', 'BillDL', 'BillCarReg', 'BillCarName', "
                             "'DueDate', 'DaysRent', 'Total') VALUES  ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s');", val1.c_str(), val2.c_str(), val3.c_str(), val4.c_str(), val5.c_str(), val6.c_str(), val7.c_str(), val8.c_str());
        }
        // Prepare the query
        sqlite3_prepare(db, query, strlen(query), &stmt, NULL);

        // Test it
        rc = sqlite3_step(stmt);

        // Finialize the usage
        sqlite3_finalize(stmt);

        // Free up the query space
        free(query);
    }

    void showTable(int whichTable) {

        // Save SQL insert data
        if(whichTable == 0){
            sql = ("SELECT * FROM 'CustomerInfo';");

            // Run the SQL
            rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
        }
        if(whichTable == 1){
            sql = ("SELECT * FROM 'CarInfo';");

            // Run the SQL
            rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
        }
        if(whichTable == 2){
            sql = ("SELECT * FROM 'RentalData';");

            // Run the SQL
            rc = sqlite3_exec(db, sql, callbackTransact, 0, &zErrMsg);
        }
        if(whichTable == 3){
            sql = ("SELECT * FROM 'HistoryInfo';");

            // Run the SQL
            rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
        }
        if(whichTable == 4){
            sql = ("SELECT * FROM 'InvoiceBill';");

            // Run the SQL
            rc = sqlite3_exec(db, sql, callbackTransact, 0, &zErrMsg);
        }

    }

    void deleteData(int whichTable, const std::string& val1, const std::string& val2) {

        char *query = NULL;

        if(whichTable == 0){
            // Build a string using asprintf()
            asprintf(&query, "DELETE FROM 'CustomerInfo' WHERE DL = '%s';", val1.c_str());
        }
        if(whichTable == 1){
            asprintf(&query, "DELETE FROM 'CarInfo' WHERE Car_Regis = '%s' AND Avail = 'Available';", val1.c_str());
        }


        // Prepare the query
        sqlite3_prepare(db, query, strlen(query), &stmt, NULL);

        // Test it
        rc = sqlite3_step(stmt);

        // Finialize the usage
        sqlite3_finalize(stmt);

        // Free up the query space
        free(query);

    }

    void updateData(int whichTable, const std::string& val1, const std::string& val2, const std::string& val3){

        char *query = NULL;

        if(whichTable == 0){
            // Build a string using asprintf()
            asprintf(&query, "UPDATE CustomerInfo SET '%s' = '%s' WHERE Customer_ID = '%s';", val1.c_str(), val2.c_str(), val3.c_str());
        }
        if(whichTable == 1){
            asprintf(&query, "UPDATE CarInfo SET '%s' = '%s' WHERE Car_ID = '%s';", val1.c_str(), val2.c_str(), val3.c_str());
        }
        if(whichTable == 2){
            asprintf(&query, "UPDATE CarInfo SET '%s' = '%s' WHERE Car_Regis = '%s';", val1.c_str(), val2.c_str(), val3.c_str());
        }
        if(whichTable == 3){
            asprintf(&query, "UPDATE RentalData SET '%s' = '%s' WHERE Invoice_ID = '%s';", val1.c_str(), val2.c_str(), val3.c_str());
        }
        if(whichTable == 4){
            asprintf(&query, "UPDATE InvoiceBill SET '%s' = '%s' WHERE InvoiceBill_ID = '%s';", val1.c_str(), val2.c_str(), val3.c_str());
        }




        // Prepare the query
        sqlite3_prepare(db, query, strlen(query), &stmt, NULL);

        // Test it
        rc = sqlite3_step(stmt);

        // Finialize the usage
        sqlite3_finalize(stmt);

        // Free up the query space
        free(query);

    }

    void closeDB() {

        // Close the SQL connection
        sqlite3_close(db);

    }



};
#endif //CARRENTALSYSTEMV2_SQLITEDB_H
