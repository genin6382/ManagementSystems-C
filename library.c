/*2.Write a program to Create a Library management system.
 Showcase the list of available books from the collection which is either available right now or the date of returning back.
Get the input from user on his choice of book. Allow the user to withdraw the book and let him know the date of returning back the book.
 Use text file as a database storing and retrieving data.
 Use memory allocations to prevent overflow.*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct book{
    
    char name[20];
    int price;
    int quantity;
    int date;
};
struct borrow{
    char name[20];
    int date;
    int quantity;
};
void WriteToDatabase(struct book* bookArray,int n){
    FILE* fp=fopen("Library.txt","w");
    for(int i=0;i<n;i++){
        fprintf(fp,"%s %d %d %d\n",bookArray[i].name,bookArray[i].price,bookArray[i].quantity,bookArray[i].date);
    }
    fclose(fp);

}
int CheckAndAdd(struct book* bookArray, struct borrow* borrowArray, int n, int* size) {
    char name[20];
    printf("Enter the name of the book you want to withdraw: ");
    scanf("%s", name);

    for (int i = 0; i < n; i++) {
        if (strcasecmp(bookArray[i].name, name) == 0) {
            printf("Enter the quantity of book you want to withdraw: ");
            int sampleqty;
            scanf("%d", &sampleqty);

            if (sampleqty > bookArray[i].quantity) {
                printf("The quantity of book is not available\n");
                return 0;
            }
            printf("The book is available\n");
            printf("The date of returning back is: %d days\n", bookArray[i].date);
            // Update borrowArray with the details of the borrowed book
            strcpy(borrowArray[*size].name, name);
            borrowArray[*size].date = bookArray[i].date;
            borrowArray[*size].quantity = sampleqty;
            bookArray[i].quantity -= sampleqty;
            *size += 1;

            return 1;
        }
    }

    printf("The book is not available\n");
    return 0;
}

void writeTofile(struct borrow* borrowArray,int* size){
    char filename[20];
    sprintf(filename,"borrow%d.txt",*size);
    FILE* fp=fopen(filename,"w");
    fprintf(fp,"%s %d %d\n",borrowArray[*size-1].name,borrowArray[*size-1].date,borrowArray[*size-1].quantity);
    fclose(fp);
}

int main(){
    int n,size=0;
    printf("Enter the number of books: ");
    scanf("%d",&n);;
    struct book* bookArray=(struct book*)malloc(n*sizeof(struct book));
    struct borrow* borrowArray=(struct borrow*)malloc(n*sizeof(struct borrow));
    for(int i=0;i<n;i++){
        printf("Enter the name of book %d: ",i+1);
        scanf("%s",bookArray[i].name);
        printf("Enter the price of book %d: ",i+1);
        scanf("%d",&bookArray[i].price);
        printf("Enter the quantity of book %d: ",i+1);
        scanf("%d",&bookArray[i].quantity);
        printf("Enter the date of returning back of book %d: ",i+1);
        scanf("%d",&bookArray[i].date);
    }
    WriteToDatabase(bookArray,n);

    printf("The list of books are:\n");
    for(int i=0;i<n;i++){
        printf("%d.\t%s\t%d\t%d\t%ddays\n",i+1,bookArray[i].name,bookArray[i].price,bookArray[i].quantity,bookArray[i].date);
    }
    char ch='y';
    while(ch=='y'){
        int flag=CheckAndAdd(bookArray,borrowArray,n,&size);
        if(flag){
            writeTofile(borrowArray,&size);
            WriteToDatabase(bookArray,n);
        }
        printf("Do you want to borrow a book? (y/n): ");
        scanf(" %c",&ch);
    }
    
    
   return 0;
}