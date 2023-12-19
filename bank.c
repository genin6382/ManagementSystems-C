// Create a Banking operation system.
//  Create an account for the user getting in the personal details, generate a unique account number. 
//  Now allow the account holder to deposit, withdraw and transfer money accordingly.
// Also provide the option of obtaining debt, and showcase the Equitable Monthly Installment aspects for the account holder accordingly.
//  Use text file as a database for storing and retrieving data.
// Use memory allocations to prevent overflow.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
struct account{
    char name[50];
    char address[100];
    int phone;
    int account_number;
    char password[50];
    float balance;
    float debt;
    float emi;
};
void CreateAccount(struct account* accountArray,int n,int*size){
    printf("Enter the name of the account holder: ");
    scanf(" %s",accountArray[n].name);
    printf("Enter the address of the account holder: ");
    scanf(" %[^\n]s",accountArray[n].address);
    printf("Enter the phone number of the account holder: ");
    scanf(" %d",&accountArray[n].phone);
    int uniqueAccountNumber = rand();
    accountArray[n].account_number = uniqueAccountNumber;
    printf("Enter the password of the account holder: ");
    scanf(" %s",accountArray[n].password);
    printf("Enter the balance of the account holder: ");
    scanf(" %f",&accountArray[n].balance);
    accountArray[n].debt = 0;
    accountArray[n].emi = 0;
    printf("\nAccount created successfully!\n");
    (*size)++;
}
void DisplayAccount(struct account* accountArray,int n){
    printf("\nAccount Details:");
    printf("\nName: %s",accountArray[n].name);
    printf("\nAddress: %s",accountArray[n].address);
    printf("\nPhone: %d",accountArray[n].phone);
    printf("\nUnique Account Number: %d",accountArray[n].account_number);
    printf("\nPassword: %s",accountArray[n].password);
    printf("\nBalance: %f",accountArray[n].balance);
    printf("\nDebt: %f\n",accountArray[n].debt);
}
void writeToDatabase(struct account* accountArray,int n){
    FILE *fp;
    fp = fopen("Bank.txt","w");
    for(int i=0;i<n;i++){
        fprintf(fp,"%d.\t%s\t%s\t%d\t%d\t%s\t%f\t%f\t%f\n",i+1,accountArray[i].name,accountArray[i].address,
        accountArray[i].phone,accountArray[i].account_number,accountArray[i].password,accountArray[i].balance,accountArray[i].debt,
        accountArray[i].emi);
    }
    fclose(fp);
}

void DisplayDatabase(){
    FILE *fp;
    fp = fopen("Bank.txt","r");
    char c;
    printf("\nDatabase:\n");
    while((c = fgetc(fp)) != EOF){
        printf("%c",c);
    }
    fclose(fp);
}

void writeTofile(struct account* accountArray,int*size){
    FILE *fp;
    char filename[20];
    sprintf(filename,"Account%d.txt",accountArray[*size-1].account_number);
    fp = fopen(filename,"w");
    fprintf(fp,"%d.\t%s\t%s\t%d\t%d\t%s\t%f\t%f\t%f\n",*size,accountArray[*size-1].name,accountArray[*size-1].address,accountArray[*size-1].phone,
    accountArray[*size-1].account_number,accountArray[*size-1].password,accountArray[*size-1].balance,accountArray[*size-1].debt,accountArray[*size-1].emi);
    fclose(fp);
}

void Updatefile(struct account* accountArray, int index) {
    FILE *fp;
    char filename[20];
    sprintf(filename, "Account%d.txt", accountArray[index].account_number);
    fp = fopen(filename, "w");
    fprintf(fp, "%d.\t%s\t%s\t%d\t%d\t%s\t%f\t%f\t%f\n", index + 1, accountArray[index].name, accountArray[index].address,
            accountArray[index].phone, accountArray[index].account_number, accountArray[index].password,
            accountArray[index].balance, accountArray[index].debt, accountArray[index].emi);
    fclose(fp);
}

void Deposit(struct account* accountArray,int n){
    int accountNum;
    printf("\nEnter the account number: ");
    scanf(" %d",&accountNum);
    for(int i=0;i<n;i++){
        if(accountArray[i].account_number==accountNum){
            printf("\nYour current balance is: %f\n",accountArray[i].balance);
            printf("\nEnter the amount to be deposited: ");
            float amount;
            scanf(" %f",&amount);
            accountArray[i].balance += amount;
            printf("\nYour new balance is: %f\n",accountArray[i].balance);
            int index=i;
            Updatefile(accountArray,index);
            writeToDatabase(accountArray,n);
            return;
        }
    }
    printf("\nAccount not found!");

}

void Withdraw(struct account* accountArray,int n){
    int accountNum;
    printf("\nEnter the account number: ");
    scanf(" %d",&accountNum);
    for(int i=0;i<n;i++){
        if(accountArray[i].account_number==accountNum){
            printf("\nYour current balance is: %f\n",accountArray[i].balance);
            printf("\nEnter the amount to be Withdrawn: ");
            float amount;
            scanf(" %f",&amount);
            accountArray[i].balance -= amount;
            printf("\nYour new balance is: %f\n",accountArray[i].balance);
            int index=i;
            Updatefile(accountArray,index);
            writeToDatabase(accountArray,n);
            return;
        }
    }
    printf("\nAccount not found!");
}

void Transfer(struct account* accountArray,int n){
    int accountNum;
    printf("\nEnter the account number: ");
    scanf(" %d",&accountNum);
    printf("\nEnter the account number to which the amount is to be transferred: ");
    int accountNum2;
    scanf(" %d",&accountNum2);
    for(int i=0;i<n;i++){
        if(accountArray[i].account_number==accountNum){
            for(int j=0;j<n;j++){
                if(accountArray[j].account_number==accountNum2){
                    printf("\nAccounts found Successfully!");
                    printf("\nYour current balance is: %f\n",accountArray[i].balance);
                    printf("\nEnter the amount to be transferred: ");
                    float amount;
                    scanf(" %f",&amount);
                    if(amount>accountArray[i].balance){
                        printf("\nInsufficient balance!");
                        return;
                    }
                    accountArray[i].balance -= amount;
                    accountArray[j].balance += amount;
                    printf("\nYour new balance is: %f\n",accountArray[i].balance);
                    int index1=i;
                    int index2=j;
                    Updatefile(accountArray,index1);
                    Updatefile(accountArray,index2);
                    writeToDatabase(accountArray,n);
                    return;
                }
               
            }
            printf("\n2nd account not found!");
            return;
        }
    }
    printf("\nAccount not found!");
}
void Loan(struct account* accountArray,int n){
    int accountNum;
    printf("\nEnter the account number: ");
    scanf(" %d",&accountNum);
    for(int i=0;i<n;i++){
        if(accountArray[i].account_number==accountNum){
            printf("\nYour current balance is: %f\n",accountArray[i].balance);
            printf("\nEnter Loan Amount: ");
            float amount;
            scanf(" %f",&amount);
            printf("\nEnter the number of months: ");
            int months;
            scanf(" %d",&months);
            printf("\nEnter the rate of interest: ");
            float rate;
            scanf(" %f",&rate);
            float emi = (amount*rate*pow(1+rate,months))/(pow(1+rate,months)-1);
            printf("\nYour EMI is: %f\n",emi);

            accountArray[i].emi = emi;
            accountArray[i].balance += amount;
            accountArray[i].debt += amount;
            printf("\nYour new balance is: %f\n",accountArray[i].balance);
            printf("\nYour new debt is: %f\n",accountArray[i].debt);
            printf("\nYour new EMI is: %f\n",accountArray[i].emi);

            int index=i;
            Updatefile(accountArray,index);
            writeToDatabase(accountArray,n);

            
            return;
        }
    }
    printf("\nAccount not found!");
}
int main(){
    int n,size=0;
    printf("Enter the number of accounts in the bank: ");
    scanf("%d",&n);
    struct account *accountArray = (struct account *)malloc(n*sizeof(struct account));
    for(int i=0;i<n;i++){
        CreateAccount(accountArray,i,&size);
        writeTofile(accountArray,&size);
        DisplayAccount(accountArray,i);
    }
    writeToDatabase(accountArray,n);
    DisplayDatabase();
    char ch;
    char choice='y';
    while(choice=='y'){
        printf("\n1. Deposit\n2. Withdraw\n3. Transfer\n4. Loan\nEnter your choice: ");
        scanf(" %c",&ch);
        switch(ch){
            case '1':
                Deposit(accountArray, n);
                break;
            case '2':
                Withdraw(accountArray, n);
                break;
            case '3':
                Transfer(accountArray, n);
                break;
            case '4':
                Loan(accountArray, n);
                break;
            default:
                printf("Invalid choice!");
        }
        printf("\nDo you want to continue?(y/n): ");
        scanf(" %c",&choice);
    }
    
    return 0;

}