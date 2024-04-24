
#define MAX_PRODUCTS 100 
#ifndef STORE_CART_OPERATIONS_H
#define STORE_CART_OPERATIONS_H


typedef struct {
    char name[100];
    int price;
    int quantity;
} Product;

typedef struct {
    Product* products;
    int numProducts;
} GroceryStore;

typedef struct {
    Product* products;
    int numProducts;
} Cart;


void loadWebshopStore(GroceryStore* webshopStore);
void writeStoreToFile(const GroceryStore* webshopStore, const char* filename);
void insertItemToCart(GroceryStore* webshopStore, Cart* cart);
int getPriceOfCart(const GroceryStore* webshopStore, const Cart* cart);
void buyProducts(GroceryStore* webshopStore, Cart* cart);
int findProductIndex(const GroceryStore* webshopStore, const char* productName);
void displayMenu(); 

#endif 