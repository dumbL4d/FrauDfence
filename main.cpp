#include <iostream>

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
  
}

int main(){
  return 0;
}
