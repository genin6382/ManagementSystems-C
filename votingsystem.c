// Create a Voting System for election. Create voter id by obtaining the voters personal details. 
// Create Voter id by obtaining the Voter details. Each voter id should be allowed to vote only once.
// Obtain the voter id, check if it is first time, showcase the list of Voters, allow voting. 
// Finally summarize the count and percentage of votes obtained by each Voter and declare winning.
// Use text file as database. Use memory allocations to prevent overflow.

#include<Stdio.h>
#include<string.h>
#include<stdlib.h>

struct Voter{
    int voter_id;
    char name[20];
    char dob[15];
    int phno;
};

struct Candidate{
    char name[20];;
    char party[20];
    int votes;
};

int  CheckAndAdd(struct Voter* VoterArray,int n,int *size){
    int id;
    printf("\nEnter the Voter ID: ");
    scanf("%d",&id);
    for(int i=0;i<n;i++){
        if(VoterArray[i].voter_id==id){
            printf("\nYou have already voted");
            return 0;
        }
    }
    VoterArray[*size].voter_id=id;
    printf("\nEnter the Name: ");
    scanf("%s",VoterArray[*size].name);
    printf("\nEnter the Date of Birth: ");
    scanf("%s",VoterArray[*size].dob);
    printf("\nEnter the Phone Number: ");
    scanf("%d",&VoterArray[*size].phno);
    (*size)++;
    return 1;
}

void WriteToFile(struct Voter* VoterArray,int *size){
    char filename[20];
    sprintf(filename,"Voter%d.txt",*size);
    FILE* file=fopen(filename,"w");
    if(file==NULL){
        printf("\nError opening file");
        return;
    }
    fprintf(file,"%d %s %s %d",VoterArray[*size-1].voter_id,VoterArray[*size-1].name,VoterArray[*size-1].dob,VoterArray[*size-1].phno);    
    fclose(file);
}

void WriteToDatabase(struct Candidate* CandidateArray,int count){
    FILE *fptr=fopen("Candidate.txt","w");
    for(int i=0;i<count;i++){
        fprintf(fptr,"%s\t%s\t%d\n",CandidateArray[i].party ,CandidateArray[i].name,CandidateArray[i].votes);
    }
    fclose(fptr);
}

void VoteCandidate(struct Candidate* CandidateArray,int count){
    printf("\nList of Candidates: ");
    for(int i=0;i<count;i++){
        printf("\n%d. %s",i+1,CandidateArray[i].name);
    }
    int ch;
    printf("\nEnter the Candidate Number: ");
    scanf("%d",&ch);
    CandidateArray[ch-1].votes++;
    WriteToDatabase(CandidateArray,count); //updating database
}


void ShowWinner(struct Candidate* CandidateArray,int count){
    int max=CandidateArray[0].votes;
    char winner[200]="";
    int total=0;
    for(int i=0;i<count;i++){
        total+=CandidateArray[i].votes;
        if(CandidateArray[i].votes>max){           
            max=CandidateArray[i].votes;
            strcpy(winner,CandidateArray[i].name);
        }
    }
    printf("\n%s is the winner",winner);
    printf("\nPercentage of Votes Obtained: %f%",((float)max/total)*100);
}

int main()
{   
    int n,size=0;
    printf("Enter the number of Voters in the locality: ");
    scanf("%d",&n);
    struct Voter* VoterArray=(struct Voter*)calloc(n,sizeof(struct Voter));
    struct Candidate* CandidateArray=(struct Candidate*)malloc(3*sizeof(struct Candidate));
    //Taking details of the candidates
    for(int i=0;i<3;i++){
        printf("\nEnter the details of the %dth Candidate: ",i+1);
        printf("\nEnter the Name: ");
        scanf("%s",CandidateArray[i].name);
        printf("\nEnter the Party: ");
        scanf("%s",CandidateArray[i].party);
        CandidateArray[i].votes=0;
    }
    WriteToDatabase(CandidateArray,3); //writing to the database
    
    //Taking details of the voters

    for(int i=0;i<n;i++){
        printf("\nEnter the details of the %dth Voter: ",i+1);
        int flag=CheckAndAdd(VoterArray,i,&size);
        if (flag){
            WriteToFile(VoterArray,&size);
            VoteCandidate(CandidateArray,3);
        }
    }
    printf("\nRESULTS......:");
    ShowWinner(CandidateArray,3);
    return 0;
}