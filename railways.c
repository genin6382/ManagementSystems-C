// Create a railway ticket reservation system.
//  Provide the information of the train number, date, number of seats available, reserve the seats based 
//  on user requirement by taking the input and generate a ticket. 
//  Allow user to cancel the ticket and update the database accordingly. Use text file as a database storing and retrieving data.
//  Use memory allocations to prevent overflow.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct train{
    int train_no;
    char date[20];
    int seats;
};
struct ticket{
    int ticket_no;
    int train_no;
    char date[20];
    int seats;  
};
void WriteToDatabase(struct train* trainArray,int n){
    FILE *fptr=fopen("Train.txt","w");
    for(int i=0;i<n;i++){
        fprintf(fptr,"%d\t%s\t%d\n",trainArray[i].train_no,trainArray[i].date,trainArray[i].seats);
    }
    fclose(fptr);
}
void ReadFromDatabase(struct train* trainArray,int n){
    FILE *fptr=fopen("Train.txt","r");
    for(int i=0;i<n;i++){
        fscanf(fptr,"%d\t%s\t%d\n",&trainArray[i].train_no,trainArray[i].date,&trainArray[i].seats);
        printf("%d\t%s\t%d\n",trainArray[i].train_no,trainArray[i].date,trainArray[i].seats);
    }
    fclose(fptr);

}

void writeTicketToFile(struct ticket* ticketArray,int *size){
    char filename[20];
    sprintf(filename,"%d.txt",ticketArray[*size-1].ticket_no); // or sprintf(filename,"Ticket%d.txt",*size);
    FILE *fptr=fopen(filename,"w");
    fprintf(fptr,"%d\t%d\t%s\t%d\n",ticketArray[*size-1].ticket_no,ticketArray[*size-1].train_no,ticketArray[*size-1].date,ticketArray[*size-1].seats);
    fclose(fptr);
}

int  CheckAndAddTicket(struct train* trainArray,struct ticket* tickerArray,int n,int *size){
        printf("\nEnter the train number: ");
        int train_no;
        scanf("%d",&train_no);
        printf("\nEnter the date: ");
        char date[20];
        scanf("%s",date);
        for(int i=0;i<n;i++){
            if(trainArray[i].train_no==train_no && strcmp(trainArray[i].date,date)==0){
                printf("\nEnter the number of seats: ");
                int seats;
                scanf("%d",&seats);
                if(trainArray[i].seats>=seats){
                    trainArray[i].seats-=seats;
                    printf("\nTicket booked successfully");
                    int unique=rand();
                    //printing ticket

                    printf("\nYour ticket number is %d",unique);
                    printf("\nYour train number is %d",train_no);
                    printf("\nYour date of journey is %s",date);
                    printf("\nYour number of seats is %d",seats);

                    //adding to ticket array
                    tickerArray[*size].ticket_no=unique;
                    tickerArray[*size].train_no=train_no;
                    strcpy(tickerArray[*size].date,date);
                    tickerArray[*size].seats=seats;
                    *size+=1;
                }
                else{
                    printf("\nSeats not available");
                    return 0;
                }                
            }
        }
        return 1;
}


void CancelTicket(struct ticket* ticketArray,struct train* trainArray,int n,int *size){
    printf("\nEnter the ticket number: ");
    int ticket_no;
    scanf("%d",&ticket_no);
    for(int i=0;i<*size;i++){
        if(ticketArray[i].ticket_no==ticket_no){
            for(int j=0;j<n;j++){
                //matching the train number and date
                if(trainArray[j].train_no==ticketArray[i].train_no && strcmp(trainArray[j].date,ticketArray[i].date)==0){
                    trainArray[j].seats+=ticketArray[i].seats;
                    ticketArray[i].seats=0;
                    printf("\nTicket cancelled successfully");
                    int index=i;
                    //now we have to shift the array and update the file and size
                    for(int k=index;k<*size-1;k++){
                        ticketArray[k]=ticketArray[k+1];
                    }
                    writeTicketToFile(ticketArray,size);
                    *size-=1;
                    return;
                }
            }
        }
    }
    printf("\nTicket not found");
}
int main(){
    int n,size=0;
    printf("Enter the number of trains: ");
    scanf("%d",&n);
    struct train *trainArray=(struct train*)malloc(n*sizeof(struct train));
    struct ticket *ticketArray=(struct ticket*)malloc(n*sizeof(struct ticket));
    for(int i=0;i<n;i++){
        printf("\nEnter the train number: ");
        scanf("%d",&trainArray[i].train_no);
        printf("\nEnter the date: ");
        scanf("%s",trainArray[i].date);
        printf("\nEnter the number of seats: ");
        scanf("%d",&trainArray[i].seats);
    }
    WriteToDatabase(trainArray,n);//writing to database
    ReadFromDatabase(trainArray,n);//Printing the database
    
    char ch='y';
    while(ch=='y'){
        int flag=CheckAndAddTicket(trainArray,ticketArray,n,&size);
        if(flag){
            writeTicketToFile(ticketArray,&size);
            WriteToDatabase(trainArray,n);
        }
        printf("\nDo you want to book a ticket?(y/n): ");
        scanf(" %c",&ch);
    }
    printf("\nDo you want to cancel a ticket?(y/n): ");
    char ch2;
    scanf(" %c",&ch2);
    while(ch2=='y'){
        CancelTicket(ticketArray,trainArray,n,&size);
        WriteToDatabase(trainArray,n);
        printf("\nDo you want to cancel a ticket?(y/n):");
        scanf(" %c",&ch2);
    }
    return 0;
}