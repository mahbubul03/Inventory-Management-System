
#include<bits/stdc++.h>
#include"modules/productHandler.h"
#include"modules/login.h"
#include"GUIelements/GUI.h"

login LogIN; // Object
user User; // Structure
GUI GUI; //Object
productHandler prdct; //Object



int main(){


 while (User.loginAttempt< 5)
    {
      GUI.cls();
      cout << "\t\t\t\t\tUser Name: ";
      cin >> User.userName;
      cout << "\t\t\t\t\tPassword: ";
      cin >> User.userPassword;
      if(LogIN.tryLogIn(User)){
      User.loginAttempt=0;
      int choice;
    do {
        GUI.cls();
        GUI.companySlogan();
        GUI.productHandlerMenu(choice);
        switch (choice) {
            case 1:
                prdct.add();
                break;
            case 2:
                prdct.finder();
                break;
            case 3:
                prdct.updater();
                break;
            case 4:
                prdct.show_all();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 5);

      }
      else{
      User.loginAttempt++;
      cout<<"Wrong Pass Try Again"<<endl;
      getchar();
      }
    }

    if(User.loginAttempt>5)cout<<"Too many login attempts"<<endl;
    exit(0);
}

