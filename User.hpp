#ifndef User_hpp
#define User_hpp
#include <string>
using namespace std;

class User {
public:
    //Data fields
    string surname;
    string name;
    string phoneNumber;
    
    // Constructor
    User(const string &s, const string &n, const string &phone);
};
#endif /* User_hpp */
