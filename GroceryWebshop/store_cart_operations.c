#include "store_cart_operations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayMenu() {
    
    printf("1. Load webshop store from a file\n");
    printf("2. Write the content of the store to a file\n");
    printf("3. Insert an item to cart\n");
    printf("4. Get the price of cart\n");
    printf("5. Buy the products\n");
    printf("6. Exit the program\n");
    printf("Enter your choice: ");
}

void loadWebshopStore(GroceryStore* webshopStore) {
    printf("Enter the filename to load the webshop store from: ");
    char filename[100];
    scanf("%s", filename);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fscanf(file, "%s %d %d", webshopStore->products[webshopStore->numProducts].name,
                                   &webshopStore->products[webshopStore->numProducts].price,
                                   &webshopStore->products[webshopStore->numProducts].quantity) != EOF) {
        webshopStore->numProducts++;
    }

    fclose(file);
}

void writeStoreToFile(const GroceryStore* webshopStore, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < webshopStore->numProducts; i++) {
        fprintf(file, "%s %d %d\n", webshopStore->products[i].name,
                                     webshopStore->products[i].price,
                                     webshopStore->products[i].quantity);
    }

    fclose(file);
}
void insertItemToCart(GroceryStore* webshopStore, Cart* cart) {
    printf("Enter the product name: ");
    char productName[100];
    scanf("%s", productName);

    int webshopProductIndex = findProductIndex(webshopStore, productName);
    if (webshopProductIndex == -1) {
        printf("Product not found in the webshop store.\n");
        return;
    }

    printf("Enter the quantity: ");
    int quantity;
    scanf("%d", &quantity);

    // if (webshopStore->products[webshopProductIndex].quantity < quantity) {
    //     printf("Not enough quantity in the webshop store.\n");
    //     return;
    // }

    cart->products[webshopProductIndex].quantity += quantity;
}

int getPriceOfCart(const GroceryStore* webshopStore, const Cart* cart) {
    int totalPrice = 0;

    for (int i = 0; i < webshopStore->numProducts; i++) {
        totalPrice += cart->products[i].quantity * webshopStore->products[i].price;
    }

    return totalPrice;
}

void buyProducts(GroceryStore* webshopStore, Cart* cart) {
    for (int i = 0; i < webshopStore->numProducts; i++) {
        int availableQuantity = webshopStore->products[i].quantity;
        int requestedQuantity = cart->products[i].quantity;

        
        if (requestedQuantity > 0) {
            if (requestedQuantity > availableQuantity) {
                printf("Not enough quantity of %s in the webshop store. Available: %d\n",
                       webshopStore->products[i].name, availableQuantity);
                printf(" %d %s Are missing.\n", requestedQuantity - availableQuantity, webshopStore->products[i].name);
            } else {
                
                webshopStore->products[i].quantity -= requestedQuantity;

                
                cart->products[i].quantity = 0;  

                printf("Successfully bought %d %s.\n", requestedQuantity, webshopStore->products[i].name);
            }
        }
    }
}
int findProductIndex(const GroceryStore* webshopStore, const char* productName) {
    for (int i = 0; i < webshopStore->numProducts; i++) {
        if (strcmp(webshopStore->products[i].name, productName) == 0) {
            return i;
        }
    }

    return -1;
}