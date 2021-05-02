//
// Created by Alan Ta on 4/24/21.
//
#include <map>
#define BOOST_TEST_DYN_LINK
#include <boost/lexical_cast.hpp>


#include "main.h"

std::string dateNow(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%m/%d/%Y/", timeinfo);
    std::string str(buffer);
    return str;
}

std::string timeNow(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%I:%M:%S", timeinfo);
    std::string str(buffer);
    return str;
}

std::string rentalCost(const std::string& carType, const std::string& carMake, const std::string& daysRented){
    std::multimap<std::string, double > priceMenu = {
            {"Acura", 1.25 },{"Lexus", 1.25},{"AlfaRomeo", 1.25 },{"Jaguar", 1.25 },
            {"Jeep", 1.25 },{"LandRover", 1.25 },{"Lotus", 1.25 },{"Mercedes-Benz", 1.25 },
            {"Rolls-Royce", 1.25 },{"Tesla", 1.25 },{"Volvo", 1.25 },{"Infiniti", 1.25 },
            {"Genesis", 0.25 },

            {"Ford", 1.10 },{"GMC", 1.15 },{"Honda", 1.10 },{"Hyundai", 1.10 },
            {"Kia", 1.10 },{"Lincoln", 1.15 },{"Mazda", 1.10 },{"Mini", 1.15 },
            {"Mitsubishi", 1.15 },{"Nissan", 1.15 },{"Ram", 1.15 },{"Scion", 1.15 },
            {"Subaru", 1.15 },{"Toyota", 1.10 },{"Volkswagen", 1.10 },{"VW", 1.10 },

            {"Coupe", 1.10 },{"Sedan", 1.08 },{"SUV", 1.12 },{"Convertible", 1.12 },
            {"Van", 1.08 },{"Hatchback", 1.10 }
    };
    auto days = boost::lexical_cast<double>(daysRented);
    double cost = 75.0;
    for(std::multimap<std::string, double>::iterator it = priceMenu.begin(); it != priceMenu.end(); ++it){
        if( it->first == carMake){
            cost = cost * it->second;
        }
        if(it->first == carType){
            cost = cost * it->second;
        }
    }
    cost = cost * days;
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << cost;
    std::string totalCost = "$" + ss.str();
    return totalCost;

}

std::string invoiceNum(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%m%d%Y%I%M%S", timeinfo);
    std::string str(buffer);
    return str;
}

void loadingScreen(){
    std::cout << std::string( 100, '\n' );
    printf("\t\t\t\t\tLoading...\n");
    sleep(3);
    std::cout << std::string( 100, '\n' );
}

void ClearScreen()
{
    std::cout << std::string( 100, '\n' );
}

void printFileToScreen(const std::string& fileName){
    std::string line;
    std::ifstream titleFile (fileName);
    if(titleFile.is_open()){
        while( getline(titleFile,line)){
            std::cout << line << std::endl;
        }
        titleFile.close();
    }
    else{
        std::cout << "UNABLE TO OPEN:" << fileName << std::endl;
    }
}

void introDisplay(){
    chdir("/Users/alanta/CLionProjects/CarRentalSystemV2");
    std::string line;
    printFileToScreen("titleCard.txt");
    sleep(4);
}
