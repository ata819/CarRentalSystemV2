#include <iostream>
#include "main.h"
#include "SQLiteDB.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN  // in only one cpp file

void databaseInitial(){
    DBLite sqldb;
    sqldb.createTable(5);
    sqldb.createTable(0);
    sqldb.createTable(1);
    sqldb.createTable(2);
    sqldb.createTable(3);
    sqldb.createTable(4);
    sqldb.closeDB();

}

void customerInformation(){
    std::string line;
    int custOption;
    std::cout << "\t\t\t\t\t------------------------------";
    std::cout << "\n\t\t\t\t\t       CUSTOMER INFO \n";
    std::cout << "\t\t\t\t\t------------------------------\n\n";
    DBLite sqldb;
    sqldb.showTable(0);
    sqldb.closeDB();

    std::cout << "\n1:ADD CUSTOMER | 2:REMOVE CUSTOMER | 3:EDIT CUSTOMER | 4:BACK" << std::endl ;
    std::cout << ":";
    std::cin >> custOption;
    switch (custOption) {
        case 1:
            loadingScreen();
            addCustomer();
            break;
        case 2:
            loadingScreen();
            removeCustomer();
            break;
        case 3:
            loadingScreen();
            updateCustomer();
            break;
        case 4:
            ClearScreen();
            std::cout << "\t\t\t\t\t\t\t\tGOING BACK...\n";
            sleep(4);
            break;
        default:
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            ClearScreen();
            customerInformation();
    }
}

void addCustomer(){
    std::string firstName;
    std::string lastName;
    std::string fullName;
    std::string driverLicense;
    std::string phoneNum;
    std::string line;
    char yesOrNo;
    std::cout << "\t\t\t\t\t------------------------------";
    std::cout << "\n\t\t\t\t\t    ADD CUSTOMER ACCOUNT   \n";
    std::cout << "\t\t\t\t\t------------------------------\n\n";
    DBLite sqldb;
    sqldb.showTable(0);

    std::cout << "Please enter the customer's FIRSTNAME LASTNAME" << std::endl;
    std::cout << ":";
    std::cin >> firstName >> lastName;
    std::cout << "Please enter the customer's DRIVER LICENSE NUMBER" << std::endl;
    std::cout << ":";
    std::cin >> driverLicense;
    std::cout << "Please enter the customer's PHONE NUMBER" << std::endl;
    std::cout << ":";
    std::cin >> phoneNum;

    std::cout << "The customer information entered was NAME:" << firstName << " " << lastName << " DL#:" << driverLicense << " PH#:" << phoneNum << std::endl;

    std::cout << "Is that the correct name? (y/n) " << std::endl;
    std::cout << ":";
    std::cin >> yesOrNo;
    switch(yesOrNo) {
        case 'y':{
            std::cout << "CUSTOMER ADDED" << std::endl;
            fullName = firstName + " " + lastName;
            sqldb.insertData(0,fullName, driverLicense, phoneNum, "", "", "", "", "");
            sqldb.closeDB();
            histCreate(fullName, 0, "CUSTOMER INFO");
            sleep(4);
            ClearScreen();
            break;
        }
        case 'n': {
            ClearScreen();
            addCustomer();
            break;
        }
        default:
            std::cout << "INVALID" << std::endl;
            ClearScreen();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }


}

void removeCustomer(){
    std::string firstName;
    std::string lastName;
    std::string driverLicense;
    std::string fullName;
    std::string line;
    char yesOrNo;
    DBLite sqldb;

    do{
        std::cout << "\t\t\t\t\t------------------------------";
        std::cout << "\n\t\t\t\t\t REMOVE CUSTOMER ACCOUNT   \n";
        std::cout << "\t\t\t\t\t------------------------------\n\n";
        sqldb.showTable(0);


        std::cout << "Please enter the customer's FIRSTNAME LASTNAME" << std::endl;
        std::cout << ":";
        std::cin >> firstName >> lastName;
        fullName = firstName + " " + lastName;
        std::cout << "Please enter the customer's DRIVER LICENSE NUMBER" << std::endl;
        std::cout << ":";
        std::cin >> driverLicense;
        std::cout << "The customer information entered was NAME:" << fullName << " DL#:" << driverLicense<< std::endl;
        std::cout << "Is that the correct name? (y/n) " << std::endl;
        std::cout << ":";
        std::cin >> yesOrNo;
    } while (yesOrNo != 'y');
    std::cout << "CUSTOMER REMOVED" << std::endl;
    sqldb.deleteData(0, driverLicense, "");
    sqldb.closeDB();
    histCreate(fullName, 1, "CUSTOMER INFO");
}

void updateCustomer(){
    std::string firstName;
    std::string lastName;
    std::string fullName;
    std::string driverLicense;
    std::string phoneNum;
    std::string custID;
    std::string columnName;
    std::string errName;
    char yesOrNo;
    std::cout << "\t\t\t\t\t------------------------------";
    std::cout << "\n\t\t\t\t\t    UPDATE CUSTOMER ACCOUNT   \n";
    std::cout << "\t\t\t\t\t------------------------------\n\n";
    DBLite sqldb;
    sqldb.showTable(0);

    std::cout << "Please enter the customer's ID" << std::endl;
    std::cout << ":";
    std::cin >> custID;
    std::cout << "Please enter the column of item name to change (i.e. Name, DL, or Phone)" << std::endl;
    std::cout << ":";
    std::cin >> columnName;
    if(columnName == "Name"){
        std::cout << "Please enter the correct item name" << std::endl;
        std::cout << ":";
        std::cin >> firstName >> lastName;
        errName = firstName + " " + lastName;
    }
    else{
        std::cout << "Please enter the correct item name" << std::endl;
        std::cout << ":";
        std::cin >> errName;
    }
    std::cout << "The UPDATED customer information entered was: " << errName << std::endl;
    std::cout << "Is that the correct name? (y/n) " << std::endl;
    std::cout << ":";
    std::cin >> yesOrNo;
    switch(yesOrNo) {
        case 'y':{
            std::cout << "CUSTOMER UPDATED " << std::endl;
            sqldb.updateData(0, columnName, errName, custID );
            sqldb.closeDB();
            histCreate(columnName, 3, errName);
            sleep(4);
            ClearScreen();
            break;
        }
        case 'n': {
            ClearScreen();
            sqldb.closeDB();
            addCustomer();
            break;
        }
        default:
            std::cout << "INVALID" << std::endl;
            sqldb.closeDB();
            ClearScreen();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }
}

void carListScreen(){
    int carListOption;
    std:: string line;
    std::cout << "\t\t\t\t\t------------------------------";
    std::cout << "\n\t\t\t\t\t       CUSTOMER INFO \n";
    std::cout << "\t\t\t\t\t------------------------------\n\n";
    DBLite sqldb;
    sqldb.showTable(1);
    sqldb.closeDB();


    std::cout << "\n1:ADD CAR | 2:REMOVE CAR | 3:EDIT CAR | 4:BACK" << std::endl ;
    std::cout << ":";
    std::cin >> carListOption;
    switch (carListOption) {
        case 1: {
            ClearScreen();
            addCar();
            break;
        }
        case 2:
            ClearScreen();
            removeCar();
            break;
        case 3:
            ClearScreen();
            editCar();
            break;
        case 4:
            ClearScreen();
            std::cout << "\t\t\t\t\t\t\t\tGOING BACK...\n";
            sleep(4);
            break;
        default:
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            ClearScreen();
            carListScreen();
    }

}

void addCar(){
    std::string carVin;
    std::string carYear;
    std::string carMake;
    std::string carName;
    std::string carType;
    std::string carColor;
    std::string fullCarName;
    std::string line;
    char yesOrNo;
    std::cout << "\t\t\t\t\t------------------------------";
    std::cout << "\n\t\t\t\t\t       ADD CAR \n";
    std::cout << "\t\t\t\t\t------------------------------\n\n";
    DBLite sqldb;
    sqldb.showTable(1);

    std::cout << "Please enter the new car's VIN number" << std::endl;
    std::cout << ":";
    std::cin >> carVin;
    std::cout << "Please enter the YEAR MAKE NAME TYPE COLOR of the new car" << std::endl;
    std::cout << ":";
    std::cin >> carYear >> carMake >> carName >> carType >> carColor;
    std::cout << "The new car's VIN number is " << carVin << std::endl;
    std::cout << "The car entered was " << carYear << " " << carMake << " " << carName << " " << carType << " "  << carColor << std::endl;
    std::cout << "Is that the correct VIN & name? (y/n) " << std::endl;
    std::cout << ":";
    std::cin >> yesOrNo;
    switch(yesOrNo) {
        case 'y':{
            std::cout << "CAR ADDED" << std::endl;
            fullCarName = carVin + " " + carYear + " " + carMake + " " + carName + " " + carType + " " + carColor;
            sqldb.insertData(1,carVin, carYear, carMake, carName, carType, carColor, "", "");
            sqldb.closeDB();
            histCreate(fullCarName,0, "CAR INVENTORY");
            break;
        }
        case 'n': {
            ClearScreen();
            addCar();
            break;
        }
        default:
            std::cout << "INVALID" << std::endl;
            ClearScreen();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }
}

void removeCar(){
    std::string carVin;
    char yesOrNo;
    DBLite sqldb;

    do{
        std::cout << "\t\t\t\t\t------------------------------";
        std::cout << "\n\t\t\t\t\t    CAR'S AVAILABLE \n";
        std::cout << "\t\t\t\t\t------------------------------\n\n";
        sqldb.showTable(1);
        std::cout << "Please enter the car's VIN number you would like to remove" << std::endl;
        std::cout << ":";
        std::cin >> carVin;
        std::cout << "The car VIN number entered was: " + carVin << std::endl;
        std::cout << "Is that the correct name? (y/n) " << std::endl;
        std::cout << ":";
        std::cin >> yesOrNo;
    }while(yesOrNo != 'y');
    sqldb.deleteData(1,carVin, "" );
    sqldb.closeDB();
    histCreate(carVin, 1, "CAR INVENTORY");

}
void editCar(){
    std::string carID;
    std::string columnName;
    std::string errName;
    char yesOrNo;
    std::cout << "\t\t\t\t\t------------------------------";
    std::cout << "\n\t\t\t\t\t  UPDATE CAR INFORMATION   \n";
    std::cout << "\t\t\t\t\t------------------------------\n\n";
    DBLite sqldb;
    sqldb.showTable(1);

    std::cout << "Please enter the car's ID (Car_ID)" << std::endl;
    std::cout << ":";
    std::cin >> carID;
    std::cout << "Please enter the column of item name to change (i.e. Car_Regis, Year, Make, or etc...)" << std::endl;
    std::cout << ":";
    std::cin >> columnName;
    std::cout << "Please enter the correct item name" << std::endl;
    std::cout << ":";
    std::cin >> errName;

    std::cout << "The UPDATED car information entered was: " << errName << std::endl;
    std::cout << "Is that the correct name? (y/n) " << std::endl;
    std::cout << ":";
    std::cin >> yesOrNo;
    switch(yesOrNo) {
        case 'y':{
            std::cout << "CAR UPDATED " << std::endl;
            sqldb.updateData(1, columnName, errName, carID );
            sqldb.closeDB();
            histCreate(columnName, 2, errName);
            sleep(4);
            ClearScreen();
            break;
        }
        case 'n': {
            sqldb.closeDB();
            ClearScreen();
            addCustomer();
            break;
        }
        default:
            std::cout << "INVALID" << std::endl;
            sqldb.closeDB();
            ClearScreen();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }
}

void rentOptions(){
    int custOption;
    std::cout << "\t\t\t\t\t------------------------------";
    std::cout << "\n\t\t\t\t\t       CUSTOMER INFO \n";
    std::cout << "\t\t\t\t\t------------------------------\n\n";
    DBLite sqldb;
    sqldb.showTable(0);
    sqldb.closeDB();
    std::cout << "\n1:ASSIGN CAR TO CUSTOMER | 2:CHECK RENT DUES | 3:UPDATE RENT INFO | 4:BACK" << std::endl ;
    std::cout << ":";
    std::cin >> custOption;
    switch (custOption) {
        case 1:
            ClearScreen();
            rentCar();
            break;
        case 2:
            ClearScreen();
            rentCheck();
            break;
        case 3:
            ClearScreen();
            rentUpdate();
            break;
        case 4:
            ClearScreen();
            std::cout << "\t\t\t\t\t\t\t\tGOING BACK...\n";
            sleep(4);
            break;
        default:
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            ClearScreen();
            rentOptions();
    }
}

void rentCar(){
    std::string customerFN;
    std::string customerLN;
    std::string customerFullName;
    std::string DLNumber;
    std::string customerInfo;
    std::string rentDays;
    std::string rentDueDate;
    std::string carInfo;
    std::string carYear;
    std::string carMake;
    std::string carName;
    std::string carType;
    std::string carColor;
    std::string carVin;
    char yesOrNo;
    DBLite sqldb;

    do{
        std::cout << "\t\t\t\t\t------------------------------";
        std::cout << "\n\t\t\t\t\t       CUSTOMER INFO \n";
        std::cout << "\t\t\t\t\t------------------------------\n\n";
        sqldb.showTable(0);
        std::cout << "Enter the customer FIRSTNAME LASTNAME that would like to rent a car" << std::endl;
        std::cout << ":";
        std::cin >> customerFN >> customerLN;
        customerFullName = customerFN + " " + customerLN;
        std::cout << "Enter the customer Driver License Number " << std::endl;
        std::cout << ":#";
        std::cin >> DLNumber;
        //ClearScreen();
        std::cout << "Are these correct? (y/n)" << std::endl;
        std::cout << "FN&LN: " << customerFullName << " | " << "DL#: " << DLNumber << std::endl;
        std::cout << ":";
        std::cin >> yesOrNo;
    } while(yesOrNo != 'y');

    yesOrNo = 'n';

    do{
        std::cout << "\t\t\t\t\t------------------------------";
        std::cout << "\n\t\t\t\t\t       CAR'S AVAILABLE \n";
        std::cout << "\t\t\t\t\t------------------------------\n\n";
        sqldb.showTable(1);
        std::cout << "Please enter the YEAR MAKE NAME TYPE COLOR of the car to be rented" << std::endl;
        std::cout << ":";
        std::cin >> carYear >> carMake >> carName >> carType >> carColor;
        carInfo = carYear + " " + carMake + " " + carName + " " + carType + " " + carColor;
        //ClearScreen();
        std::cout << "Please enter the VIN number of the car to be rented" << std::endl;
        std::cout << ":";
        std::cin >> carVin;
        std::cout << "The car entered was: " + carInfo << std::endl;
        std::cout << "Is that the correct name? (y/n) " << std::endl;
        std::cout << ":";
        std::cin >> yesOrNo;
    }while(yesOrNo != 'y');

    yesOrNo = 'n';
    do {
        std::cout << "How many days will this customer rent this vehicle? (DD)" << std::endl;
        std::cout << ":";
        std::cin >> rentDays;
        std::cout << "What date will the customer need to return the vehicle by? (MM/DD/YYYY)" << std::endl;
        std::cout << ":";
        std::cin >> rentDueDate;
        std::cout << "Total days to be rented: " << rentDays << " | Due date: " << rentDueDate << std::endl;
        std::cout << "Is this correct?" << std::endl;
        std::cin >> yesOrNo;
    }while(yesOrNo != 'y');
    std::string invoiceN = invoiceNum();
    std::string totalCost = rentalCost(carType, carMake, rentDays);
    sqldb.insertData(2, invoiceN, rentDays, rentDueDate, customerFullName, DLNumber, carVin, carInfo, "");
    sqldb.insertData(4, invoiceN, customerFullName, DLNumber, carVin, carInfo, rentDueDate, rentDays, totalCost);
    sqldb.updateData(2, "Avail", "Unavailable", carVin );
    sqldb.closeDB();
    histCreate(customerFullName, 3, carInfo);


}

void rentCheck(){
    DBLite sqldb;
    char yesOrNo;
    do{
        sqldb.showTable(2);
        std::cout << "Would like to exit? (y/n)" << std::endl;
        std::cout << ":";
        std::cin >> yesOrNo;
    }while(yesOrNo != 'y');
    sqldb.closeDB();

}

void rentUpdate(){
    std::string customerFN;
    std::string customerLN;
    std::string customerFullName;
    std::string customerInvoice;
    std::string rentDays;
    std::string rentDueDate;
    std::string carInfo;
    std::string carYear;
    std::string carMake;
    std::string carName;
    std::string carType;
    std::string carColor;
    std::string carVin;
    std::string InvoiceBill;
    char yesOrNo;
    std::cout << "\t\t\t\t\t------------------------------";
    std::cout << "\n\t\t\t\t\t       RENTAL INFO \n";
    std::cout << "\t\t\t\t\t------------------------------\n\n";
    std::cout << "For rental updates, you may only update the DAYS RENTED or DUE" << std::endl;
    std::cout << "Is that appropriate? " << std::endl;
    std::cout << ":";
    std::cin >> yesOrNo;
    if(yesOrNo == 'y'){
        DBLite sqldb;
        sqldb.showTable(2);
        std::cout << "Enter the customer Invoice_ID of the customer/car to be updated" << std::endl;
        std::cout << ":";
        std::cin >> customerInvoice;
        std::cout << "Enter the customer FIRSTNAME LASTNAME of the car to be updated" << std::endl;
        std::cout << ":";
        std::cin >> customerFN >> customerLN;
        customerFullName = customerFN + " " + customerLN;
        std::cout << "Please enter the YEAR MAKE NAME TYPE COLOR of the car to be rented" << std::endl;
        std::cout << ":";
        std::cin >> carYear >> carMake >> carName >> carType >> carColor;
        carInfo = carYear + " " + carMake + " " + carName + " " + carType + " " + carColor;
        std::cout << "Please enter the VIN number of the car to be rented" << std::endl;
        std::cout << ":";
        std::cin >> carVin;
        sqldb.showTable(4);
        std::cout << "Please enter the InvoiceBill_ID of the customer" << std::endl;
        std::cout << ":";
        std::cin >> InvoiceBill;
        std::cout << "How many days will this customer rent this vehicle? (DD)" << std::endl;
        std::cout << ":";
        std::cin >> rentDays;
        std::cout << "What date will the customer need to return the vehicle by? (MM/DD/YYYY)" << std::endl;
        std::cout << ":";
        std::cin >> rentDueDate;
        std::cout << "Total days to be rented: " << rentDays << " | Due date: " << rentDueDate << std::endl;
        sqldb.createTable(5);
        sqldb.updateData(3,"Days", rentDays, customerInvoice);
        sqldb.updateData(3,"RentDue", rentDueDate, customerInvoice);
        std::string totalCost = rentalCost(carType, carMake, rentDays);
        sqldb.updateData(4, "Total", totalCost, InvoiceBill);
        //sqldb.updateData(4,"DaysRent", rentDays, customerInvoice);
        //sqldb.updateData(4,"DueDate", rentDueDate, customerInvoice);
        sqldb.closeDB();
        histCreate(customerFullName, 4, InvoiceBill);
    }

}

void invoiceCheck(){
    DBLite sqldb;
    char yesOrNo;
    do{
        sqldb.showTable(4);
        std::cout << "Would like to exit? (y/n)" << std::endl;
        std::cout << ":";
        std::cin >> yesOrNo;
    }while(yesOrNo != 'y');
    sqldb.closeDB();
}

void histCreate(const std::string& noun1, int action, const std::string& noun2){
    std::string act;
    std::string time = timeNow();
    std::string date = dateNow();
    if(action == 0){
        act = "was inserted into";
    }
    if(action == 1){
        act = "was deleted from";
    }
    if(action == 2){
        act = " information was updated for";
    }
    if(action == 3){
        act = "was assign a rental car:";
    }
    if(action == 4){
        act = "had their rental days/car updated with an invoice:";
    }
    DBLite sqldb;
    sqldb.insertData(3, time, date, noun1, act, noun2, "", "", "");
    sqldb.closeDB();
}

void historyCheck(){
    DBLite sqldb;
    char yesOrNo;
    do{
        sqldb.showTable(3);
        std::cout << "Would like to exit? (y/n)" << std::endl;
        std::cout << ":";
        std::cin >> yesOrNo;
    }while(yesOrNo != 'y');
    sqldb.closeDB();
}

int options(){
    std::cin.clear();
    int option = 10;
    std::cout << "\t\t\t\t\t\tPlease Select An Option to continue: \n";
    std::cout << "\t\t\t\t\t\t      OPTIONS:";
    std::cout << "\n\t\t\t\t\t\t\t      1: Customer Information";
    std::cout << "\n\t\t\t\t\t\t\t      2: Available Car List";
    std::cout << "\n\t\t\t\t\t\t\t      3: Car Rent";
    std::cout << "\n\t\t\t\t\t\t\t      4: Customer Invoice";
    std::cout << "\n\t\t\t\t\t\t\t      5: History";
    std::cout << "\n\t\t\t\t\t\t\t      6: EXIT\n";
    std::cout << "\n\t\t\t\t\t\t\t       :";
    std::cin >> option;
    switch (option) {
        case 1: {
            loadingScreen();
            customerInformation();
            break;
        }
        case 2:
            loadingScreen();
            carListScreen();
            break;
        case 3:
            loadingScreen();
            rentOptions();
            break;
        case 4:
            loadingScreen();
            invoiceCheck();
            break;
        case 5:
            loadingScreen();
            historyCheck();
            break;
        case 6:
            ClearScreen();
            std::cout << "\t\t\t\t\t\t\t\tExiting...\n";
            sleep(5);
            exit(EXIT_SUCCESS);
        default:
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            ClearScreen();
            options();
            break;
    }
    options();
    return 0;

}

int loginSystem(){
    ClearScreen();
    std::string userPassword;
    std::string line;
    std::string realPassword;

    std::cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t       KAR'S RENTAL SYSTEM \n\n";
    std::cout << "\t\t\t\t\t------------------------------";
    std::cout << "\n\t\t\t\t\t\t     LOGIN \n";
    std::cout << "\t\t\t\t\t------------------------------\n\n";
    std::cout << "\t\t\t\t\tEnter Password: ";
    std::cin >> userPassword;

    std::ifstream loginPassword ("loginPW.txt");
    if(loginPassword.is_open()){
        while(getline(loginPassword, line)){
            int compReslt = strcmp(userPassword.c_str(),line.c_str());
            if(compReslt == 0){
                printf("\t\t\t\t\t\t\tSuccess\n");
                sleep(2);
                loadingScreen();
                return 0;
            }
            else
                printf("\t\t\t\t\t\t\tFailed\n");
        }

    }
    return 1;
}
int main() {
    int pwFailure = 0;
    introDisplay();
    while(loginSystem() == 1){
        pwFailure += 1;
        if(pwFailure == 3)
            exit(EXIT_SUCCESS);
    }
    databaseInitial();
    options();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
