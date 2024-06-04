#ifndef GUI_H
#define GUI_H
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

struct Item {
    string name;
    std::string brand;
    std::string price;
    std::string quantity;
};


class GUI{
 private:
   string slogan="\t\t\t\tInventory Management System\n\n\n\n";

public:
     void companySlogan();
     void productHandlerMenu(int& choice);
     void cls();
     vector<Item> parseData(const string &data, char splitter);
     void printLine(int length);
     void printTable(const vector<Item> &items);
};










void GUI::cls(){
system("cls");
}

void GUI::companySlogan(){
cout<<slogan;
}

void GUI::productHandlerMenu(int& choice){
          cout<< "\t\t\t1) Add product\n"
              << "\t\t\t2) Search product\n"
              << "\t\t\t3) Update product\n"
              << "\t\t\t4) View all products\n"
              << "\t\t\t5) Exit\n"
              << "\t\t\tEnter your choice: ";
         cin>>choice;

}



vector<Item> GUI::parseData(const string &data, char splitter) {
    vector<Item> items;
    istringstream stream(data);
string line;

    while (getline(stream, line)) {
        istringstream lineStream(line);
        string segment;
        vector<string> segments;

        while (getline(lineStream, segment, splitter)) {
            segments.push_back(segment);
        }

        if (segments.size() == 4) {
            Item item;
            item.name = segments[0];
            item.brand = segments[1];
            item.price = segments[2];
            item.quantity =segments[3];
            items.push_back(item);
        }
    }

    return items;
}

void GUI::printLine(int length) {
    cout << '+' << string(length - 2, '-') << '+' << endl;
}

void GUI::printTable(const vector<Item> &items) {
    const int nameWidth = 15;
    const int brandWidth = 15;
    const int priceWidth = 10;
    const int quantityWidth = 10;
    const int totalWidth = nameWidth + brandWidth + priceWidth + quantityWidth + 5;

    printLine(totalWidth);
    cout << '|'
              << left << setw(nameWidth) << "Name" << '|'
              << left << setw(brandWidth) << "Brand" << '|'
              << left << setw(priceWidth) << "Price" << '|'
              << left << setw(quantityWidth) << "Quantity" << '|'
              << endl;
    printLine(totalWidth);

    for (const auto &item : items) {
        cout << '|'
                  << left << setw(nameWidth) << item.name << '|'
                  << left << setw(brandWidth) << item.brand << '|'
                  << left << setw(priceWidth) << item.price << '|'
                  << left << setw(quantityWidth) << item.quantity << '|'
                  << endl;
    }

    printLine(totalWidth);
}








#endif // GUI_H
