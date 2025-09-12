
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

struct instruction{
    int OP; 
    int L;
    int M;
};

// array to represent the entire PAS
int PAS [500] = {0};

int base ( int BP , int L ){
    int arb = BP ; // activation record base
    while ( L > 0) {
        arb = PAS [ arb ]; // follow static link
        L --;
    }
    return arb ;
}

/* Print out the PAS */
void print(int PAS[500]){
    printf("\t\tL\tM\tPC\tBP\tSP\tstack\n");
    printf("Initial values: \t ");
}

int main(int argc) {

    if(argc != 1){
        printf("Error! Wrong number of arguments.");
        return 0;
    }
    
    // instruction register
    struct instruction IR;
    
    // Registers
    int PC, BP, SP;
    
    FILE *inputFile = fopen("../input.txt", "r");

    if (inputFile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    int check; 
    int i = 499;
    
    while(fscanf(inputFile,"%d",&PAS[i]) == 1) {
            //printf(" %d ", PAS[i]);
            i--;
    }
    
    //printf("%d", i);

    
    PC = 499;
    SP = i;
    BP = SP - 1;
    

    while(!(PAS[i] == 9 && PAS[i-1] == 0 && PAS[i-2] == 3)){
        //printf("I");
        IR.OP = PAS[PC];
        IR.L = PAS[PC-1];
        IR.M = PAS[PC-2];
        
        PC = PC -3;

        if (IR.OP == 1) {
            SP = SP - 1;  
            PAS[SP] = IR.M;
        }
        else if (IR.OP == 2) {
            if(IR.M == 0){
                SP = BP + 1;
                BP = PAS[SP - 2];
                PC = PAS[SP - 3];

            } else if(IR.M == 1){
                PAS[SP + 1] = PAS [SP + 1] + PAS[SP];
                SP = SP + 1;

            } else if(IR.M == 2){
                PAS[SP + 1] = PAS [SP + 1] - PAS[SP];
                SP = SP + 1;

            } else if(IR.M == 3){
                PAS[SP + 1] = PAS [SP + 1] * PAS[SP];
                SP = SP + 1;

            } else if(IR.M == 4){
                PAS[SP + 1] = PAS [SP + 1] / PAS[SP];
                SP = SP + 1;

            } else if(IR.M == 5){
                PAS[SP + 1] = (PAS [SP + 1] == PAS[SP]);
                SP = SP + 1;

            } else if(IR.M == 6){
                if(PAS[SP+1] != PAS[SP])
                    PAS[SP+1] = 1;
                else    
                    PAS[SP+1] = 0;
                SP++;

            } else if(IR.M == 7){
                if(PAS[SP+1] < PAS[SP])
                    PAS[SP+1] = 1;
                else    
                    PAS[SP+1] = 0;
                SP++;

            } else if(IR.M == 8){
                if(PAS[SP+1] <= PAS[SP])
                    PAS[SP+1] = 1;
                else    
                    PAS[SP+1] = 0;
                SP++;

            } else if(IR.M == 9){
                if(PAS[SP+1] > PAS[SP])
                    PAS[SP+1] = 1;
                else    
                    PAS[SP+1] = 0;
                SP++;

            } else if(IR.M == 10){
                if(PAS[SP+1] >= PAS[SP])
                    PAS[SP+1] = 1;
                else    
                    PAS[SP+1] = 0;
                SP++;
            } 
        }
        else if (IR.OP == 3) {
            SP = SP - 1;
            PAS[SP] = PAS[base(BP, IR.L) - IR.M];
        }
        else if (IR.OP == 4) {
            PAS[SP] = PAS[base(BP, IR.L) - IR.M];
            SP++;
        }
        else if (IR.OP == 5) {
            PAS[SP - 1] = base(BP, IR.L);
            PAS[SP - 2] = BP;
            PAS[SP - 3] = PC;
            BP = SP - 1;
            PC = IR.M;
        }
        else if (IR.OP == 6) {
            SP = SP - IR.M;
        }
        else if (IR.OP == 7) {  
            PC = PC + 3 - IR.M;
        }
        else if (IR.OP == 8) {
            if(PAS[SP] == 0) {
                PC = IR.M;
            }
            SP = SP + 1;
        }
        else if (IR.OP == 9) {
            if(IR.M== 1){
                printf("%d", PAS[SP]);
                SP = SP + 1;
            } else if(IR.M== 2){
                SP = SP - 1;
                printf("Please Enter an Integer: ");
                scanf("%d", &PAS[SP]);
            }
        }

    }
    
    fclose(inputFile);

}
