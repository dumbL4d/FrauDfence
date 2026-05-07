//Including standard library
#include<iostream>
#include<stdlib.h>
#include<stdexcept>
#include<string>
#include<conio.h>
#include<windows.h>

// Time Libraries
#include<chrono>
#include<thread>

//Including MySQL Libraries 
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_driver.h>

using namespace std;

class transaction{

private:
  string transactionDateTime;
  string creditCardNumber;
  string merchantName;
  string merchantCategory;
  float amount;
  string firstName;
  string lastName;
  string street;
  string city;
  string state;
  int zipcode;
  double clintLatitude;
  double clientLongitude;
  string clientJob;
  string transactionNumber;
  double merchantLatitude;
  double merchantLongitude;
  int flag;

public:
  transaction(){
    flag = 0;
  }
  
};

int main(){
  return 0;
}
