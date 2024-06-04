#ifndef LOGIN_H
#define LOGIN_H
#include"../DB/configs.h"
#include"txtDB.h"
txtDB AdminDB(ADMIN_DB,SPLITTER_PATTERN);

struct user{
    string userName;
    string userPassword;
    int loginAttempt = 0;
};

class login{
 string delimiter = "`$`";
 string extractPassword(const string& input_string, const string& delimiter);
public:
 bool tryLogIn(user &User);
};



bool login::tryLogIn(user &User){
  vector<string> search_res=AdminDB.searchRecord(NAME,User.userName);
  string credential=search_res[0];
  if(search_res.size()<=0)return false;
  else{
  string pass=extractPassword(credential,delimiter);
  if(pass==User.userPassword)return true;
  else return false;
  }
  return false;
}


string login::extractPassword(const string& input_string, const string& delimiter) {
    istringstream iss(input_string);
    string part;
    // Skip the first part
    getline(iss, part, delimiter[0]);
    // Extract the password
    getline(iss, part, delimiter[0]);
    return part;
}
#endif
