

#include "store_cart_operations.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    GroceryStore webshopStore;
    Cart cart;
    int choice;

    webshopStore.products = malloc(MAX_PRODUCTS * sizeof(Product));
    webshopStore.numProducts = 0;

    cart.products = malloc(MAX_PRODUCTS * sizeof(Product));
    cart.numProducts = 0;

    do {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                loadWebshopStore(&webshopStore);
                break;
            case 2:
                writeStoreToFile(&webshopStore, "storedata.txt");
                break;
            case 3:
                insertItemToCart(&webshopStore, &cart);
                break;
            case 4:
                printf("Total price of cart: %d\n", getPriceOfCart(&webshopStore, &cart));
                break;
            case 5:
                buyProducts(&webshopStore, &cart);
                break;
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    
    free(webshopStore.products);
    free(cart.products);

    return 0;
}