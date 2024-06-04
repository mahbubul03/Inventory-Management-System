#ifndef CONFIGS_H
#define CONFIGS_H

#define SPLITTER_PATTERN "`$`"
#define USER_DB "DB/User.txt"
#define ADMIN_DB "DB/Admin.txt"
#define PRODUCT_DB "DB/Product.txt"


#define NAME    0
#define PASS    1
#define ID      2
#define BLOOD   3
#define REGULAR 4
#define BRAND   1
#define PRICE   2
#define COUNT   3

 struct Product {
    char name[50],brand[50];
    double price;
    int count;
};

struct Product products[100];
int num_products = 0;



#endif // CONFIGS_H
