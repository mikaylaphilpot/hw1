/*
Assignment :
vm . c - Implement a P - machine virtual machine

Authors : Mikayla Philpot and Sindhuja Sesham

Language : C ( only )

To Compile :
gcc - O2 - Wall - std = c11 -o vm vm . c

To Execute ( on Eustis ) :
./ vm input . txt

where :
input . txt is the name of the file containing PM /0 instructions ;
each line has three integers ( OP L M )

Notes :
- Implements the PM /0 virtual machine described in the homework
instructions .
- No dynamic memory allocation or pointer arithmetic .
- Does not implement any VM instruction using a separate function .
- Runs on Eustis .

Class : COP 3402 - Systems Software - Fall 2025

Instructor : Dr . Jie Lin

Due Date : Friday , September 12 th , 2025
*/
#include <stdio.h>

int base ( int BP , int L ){
    return 0;
}

/* Print out the PAS */
void print(int PAS[500]){

}

int main() {
    // array to represent the entire PAS
    int PAS [500] = {0};
    // instruction addresses
    int OP; 
    int L;
    int M;
    // Registers
    int PC, BP, SP;
    int IR[3];
    
    FILE *inputFile = fopen("../input.txt", "r");

    if (inputFile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    int check; 
    int i = 499;
    
    while(fscanf(inputFile,"%d",&PAS[i]) == 1) {
            printf(" %d ", PAS[i]);
            i--;
    }
    
    //printf("%d", i);

    
    PC = 499;
    SP = i + 1;
    BP = i;

    while(!(PAS[i] == 9 && PAS[i-1] == 0 && PAS[i-2] == 3)){
        IR[0] = PAS[PC];
        IR[1] = PAS[PC-1];
        IR[2] = PAS[PC-2];
        

        PC = PC -3;

        if (IR[0] == 1) {
            SP = SP - 1;  
            PAS[SP] = IR[2];
        }
        else if (IR[0] == 2) {
            if(IR[2] == 0){
                SP = BP + 1;
                BP = PAS[SP - 2];
                PC = PAS[SP - 3];

            } else if(IR[2] == 1){
                PAS[SP + 1] = PAS [SP + 1] + PAS[SP];
                SP = SP + 1;

            } else if(IR[2] == 2){
                PAS[SP + 1] = PAS [SP + 1] - PAS[SP];
                SP = SP + 1;

            } else if(IR[2] == 3){
                PAS[SP + 1] = PAS [SP + 1] * PAS[SP];
                SP = SP + 1;

            } else if(IR[2] == 4){
                PAS[SP + 1] = PAS [SP + 1] / PAS[SP];
                SP = SP + 1;

            } else if(IR[2] == 5){
                PAS[SP + 1] = (PAS [SP + 1] == PAS[SP]);
                SP = SP + 1;

            } else if(IR[2] == 6){
                if(PAS[SP+1] != PAS[SP])
                    PAS[SP+1] = 1;
                else    
                    PAS[SP+1] = 0;
                SP++;

            } else if(IR[2] == 7){
                if(PAS[SP+1] < PAS[SP])
                    PAS[SP+1] = 1;
                else    
                    PAS[SP+1] = 0;
                SP++;

            } else if(IR[2] == 8){
                if(PAS[SP+1] <= PAS[SP])
                    PAS[SP+1] = 1;
                else    
                    PAS[SP+1] = 0;
                SP++;

            } else if(IR[2] == 9){
                if(PAS[SP+1] > PAS[SP])
                    PAS[SP+1] = 1;
                else    
                    PAS[SP+1] = 0;
                SP++;

            } else if(IR[2] == 10){
                if(PAS[SP+1] >= PAS[SP])
                    PAS[SP+1] = 1;
                else    
                    PAS[SP+1] = 0;
                SP++;
            } 
        }
        else if (IR[0] == 3) {
            SP = SP - 1;
            PAS[SP] = PAS[base(BP, IR[1]) - IR[2]];
        }
        else if (IR[0] == 4) {
            PAS[SP] = PAS[base(BP, IR[1]) - IR[2]];
            SP++;
        }
        else if (IR[0] == 5) {
            PAS[SP - 1] = base(BP, IR[1]);
            PAS[SP - 2] = BP;
            PAS[SP - 3] = PC;
            BP = SP - 1;
            PC = IR[2];
        }
        else if (IR[0] == 6) {
            SP = SP - IR[2];
        }
        else if (IR[0] == 7) {  
            PC = IR[2];
        }
        else if (IR[0] == 8) {
            if(PAS[SP] == 0) {
                PC = IR[2];
            }
            SP = SP + 1;
        }
        else if (IR[0] == 9) {
            if(IR[2]== 1){
                printf("%d", PAS[SP]);
                SP = SP + 1;
            } else if(IR[2]== 2){
                SP = SP - 1;
                scanf("%d", PAS[SP]);
            }
        }

    }
    
    fclose(inputFile);

}



