#ifndef PRODUCTHANDLER_H
#define PRODUCTHANDLER_H
#include"dataSerializer.h"
#include"../DB/configs.h"
#include"../GUIelements/GUI.h"
#include"txtDB.h"


txtDB product_DB(PRODUCT_DB,SPLITTER_PATTERN);
using namespace std;

class productHandler{
    GUI myGUI;
public:
    productHandler();
    void add();
    void finder();
    void updater();
    void show_all();
};

productHandler::productHandler(){
   num_products=product_DB.countRecord();
}

void productHandler::add(){
    struct Product p;
    cout<<"Enter product name: ";
    cin>>p.name;
    cout<<"Enter product brand: ";
    cin>>p.brand;
    cout<<"Enter product price: ";
    cin>>p.price;
    cout<<"Enter product count: ";
    cin>>p.count;
    string push_data=serializeData(p.name,SPLITTER_PATTERN,p.brand,SPLITTER_PATTERN,p.price,SPLITTER_PATTERN,p.count);
    if(product_DB.addRecord(product_DB.countRecord(),push_data.c_str())){
    products[num_products++] = p;
    printf("Product added successfully.\n");
    }
    else cout<<"Error Adding Product!!!"<<endl;
}


void productHandler::finder(){
   string name;
   myGUI.cls();
   myGUI.companySlogan();
   cout<<"\t\t\tEnter product name: ";
   cin>>name;
   vector<string> search_res=product_DB.searchRecord(NAME,name);
   if (search_res.empty()) {
        cout << "Product not found.\n";
        cout << "Press 'Enter Key' to go back" << endl;
        getchar(); getchar();
        myGUI.cls();
        return;
    }
   string data="";
   for(int i=0;i<search_res.size();i++){
   data=data+search_res[i]+"\n";
   }

   vector<Item> items = myGUI.parseData(data, '$');
   myGUI.printTable(items);
   cout<<"Press 'Enter Key' to go back"<<endl;
   getchar();
   getchar();
   myGUI.cls();
   return;
}



void productHandler::updater() {
    string name;
    myGUI.cls();
    myGUI.companySlogan();
    cout << "\t\t\tEnter product name to update: ";
    cin >> ws; // to consume any leading whitespace
    getline(cin, name);

    // Search for the product
    vector<pair<string, int>> search_res = product_DB.searchRecords(NAME, name);
    if (search_res.empty()) {
        cout << "Product not found.\n";
        cout << "Press 'Enter Key' to go back" << endl;
        getchar(); getchar();
        myGUI.cls();
        return;
    }

    // Display current product details
   string data="";
   for(int i=0;i<search_res.size();i++){
   data=data+to_string(search_res[i].second)+"->"+search_res[i].first+"\n";
   }
   vector<Item> items = myGUI.parseData(data, '$');
    cout << "Current product details:\n";
    myGUI.printTable(items);

    struct Product p;
    cout<<"Rename product: ";
    cin>>p.name;
    cout<<"Rename product brand: ";
    cin>>p.brand;
    cout<<"New product price: ";
    cin>>p.price;
    cout<<"New product count: ";
    cin>>p.count;
    string push_data=serializeData(p.name,SPLITTER_PATTERN,p.brand,SPLITTER_PATTERN,p.price,SPLITTER_PATTERN,p.count);

    if(search_res.size()>1){
    int index;
    cout<<"Select ID:";
    cin>>index;
    product_DB.removeRecord(index);
    product_DB.addRecord(index,push_data.c_str());
    cout<<"Successfully Updated!!"<<endl;
    }
    else {
    product_DB.removeRecord(search_res[0].second);
    product_DB.addRecord(search_res[0].second,push_data.c_str());
    cout<<"Successfully Updated!!"<<endl;
    }

    cout << "Press 'Enter Key' to go back" << endl;
    getchar();
    getchar();
    myGUI.cls();
}



void productHandler::show_all(){
    myGUI.cls();
    myGUI.companySlogan();
    vector<string> res=product_DB.getAllRecords();
    string data="";
   for(int i=0;i<res.size();i++){
   data=data+res[i]+"\n";
   }
   vector<Item> items = myGUI.parseData(data, '$');
   myGUI.printTable(items);
   cout<<"Press 'Enter Key' to go back"<<endl;
   getchar();getchar();
   myGUI.cls();

    }

#endif // PRODUCTHANDLER_H
