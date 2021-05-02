//
// Created by Alan Ta on 4/24/21.
//
#ifndef CARRENTALSYSTEMV2_MAIN_H
#define CARRENTALSYSTEMV2_MAIN_H
#define BOOST_TEST_DYN_LINK
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <zconf.h>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <ctime>
#include <time.h>
#include <sqlite3.h>

//std::string invoiceNum();

void printFileToScreen(const std::string& fileName);

std::string dateNow();

std::string timeNow();

std::string invoiceNum();

std::string rentalCost(const std::string& carType, const std::string& carMake, const std::string& daysRented);

void loadingScreen();

void ClearScreen();

void introDisplay();

void customerInformation();

void addCustomer();

void removeCustomer();

void updateCustomer();

void carListScreen();

void addCar();

void removeCar();

void editCar();

void rentOptions();

void rentCar();

void rentCheck();

void rentUpdate();

void invoiceCheck();

void historyCheck();

void histCreate(const std::string& noun1, int action, const std::string& noun2);

void databaseInitial();

#endif //CARRENTALSYSTEMV2_MAIN_H
