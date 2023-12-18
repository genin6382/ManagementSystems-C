#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct inventory {
    int id;
    char item[100];
    int qty;
    int price;
};

struct bill {
    char name[100];
    char product[100];
    int qty;
    int total;
};

void writeDatabase(struct inventory *arr, int n) {
    FILE *fptr = fopen("inventory.txt", "w");

    for (int i = 0; i < n; i++) {
        fprintf(fptr, "%s %d %d\n", arr[i].item, arr[i].qty, arr[i].price);
    }

    fclose(fptr);
}

void writeUser(struct bill *arr2, int *size, int *userCount) {
    char filename[20];
    sprintf(filename, "user%d.txt", *userCount);
    *userCount += 1;
    FILE *fptr = fopen(filename, "a");
    if (*size > 0) {
        fprintf(fptr, "Name: %s\nProduct: %s\nQuantity: %d\nTotal: %d\n",
                arr2[*size - 1].name, arr2[*size - 1].product, arr2[*size - 1].qty, arr2[*size - 1].total);
        fprintf(fptr, "\n");
    }


    fclose(fptr);
}
int checkandUpdate(struct inventory *arr, struct bill *arr2, int *size, int itemid, int n) {
    int flag=0;
    for (int i = 0; i < n; i++) {
        if (arr[i].id == itemid) {
            printf("Enter the quantity: ");
            int sampleqty;
            scanf("%d", &sampleqty);
            if (sampleqty > arr[i].qty) {
                printf("The quantity entered is more than the available quantity!");
                return 0;
            } else {
                    printf("Enter the name of the customer: ");
                    scanf("%s", arr2[*size].name);
                    strcpy(arr2[*size].product, arr[i].item);
                    arr2[*size].qty = sampleqty;
                    arr2[*size].total = arr[i].price * arr2[*size].qty;
                    printf("The total price is: %d\n", arr2[*size].total);
                    arr[i].qty -= arr2[*size].qty;
                    *size += 1;
                    writeDatabase(arr, n);
                    return 1;
                }
        }
    }
}


int main() {
    int n;
    printf("SIZE:");
    scanf("%d", &n);
    struct inventory *arr = (struct inventory *)calloc(n, sizeof(struct inventory));
    struct bill *arr2 = (struct bill *)calloc(n, sizeof(struct bill));
    int size = 0;
    int usercount = 1;
    printf("Enter the details of the INVENTORY DATABASE: \n");

    for (int i = 0; i < n; i++) {
        printf("Enter the id: ");
        scanf("%d", &arr[i].id);
        printf("Enter the item: ");
        scanf("%s", arr[i].item);
        printf("Enter the quantity: ");
        scanf("%d", &arr[i].qty);
        printf("Enter the price: ");
        scanf("%d", &arr[i].price);
    }
    writeDatabase(arr, n);

    printf("The file has been written successfully!\n");

    printf("The contents of the file are: \n");

    FILE *fptr2 = fopen("inventory.txt", "r");

    char ch;
    while ((ch = fgetc(fptr2)) != EOF) {
        printf("%c", ch);
    }

    fclose(fptr2);
    printf("\n");
    char choice;
    printf("Do you want to purchase an item? (y/n): ");
    scanf(" %c", &choice);
    while(choice == 'y'){
        printf("Enter the item id to be purchased: ");
        int itemid;
        scanf("%d", &itemid);
        int flag=checkandUpdate(arr, arr2, &size, itemid, n);
        if (flag==1){
            writeUser(arr2, &size, &usercount);
        }  
        printf("Do you want to purchase an item? (y/n): ");
        scanf(" %c", &choice);
    }

    return 0;
}
