
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

Due Date : Friday , September 12th , 2025
*/
#include <stdio.h>

// Create IR struct
struct instruction{
    int OP; 
    int L;
    int M;
};

int PAS [500] = {0};
// instruction register
struct instruction IR;
// Registers
int PC, BP, SP;

// BASE FUNCTION
int base ( int BP , int L ){
    int arb = BP ; // activation record base
    while ( L > 0) {
        arb = PAS [ arb ]; // follow static link
        L --;
    }
    return arb ;
}

/* Print out the PAS */
void print(int PAS[500]) {
    // label instructions based on opcode
    if(IR.OP == 1) {
        printf("\nLIT");
    }
    if(IR.OP == 2) {
        // label opcode 2 instructions based on memory
        if(IR.M == 0)
            printf("\nRTN");
        else if(IR.M == 1)
            printf("\nADD");
        else if(IR.M == 2)
            printf("\nSUB");
        else if (IR.M == 3)
            printf("\nMUL");
        else if (IR.M == 4)
            printf("\nDIV");
        else if (IR.M == 5)
            printf("\nEQL");
        else if (IR.M == 6)
            printf("\nNEQ");
        else if (IR.M == 7) {
            printf("\nLSS");
        }
        else if (IR.M == 8) {
            printf("\nLEQ");
        }
        else if (IR.M == 9) {
            printf("\nGTR");
        }
        else if (IR.M == 10) {
            printf("\nGEQ");
        }
    }
    if(IR.OP == 3) {
        printf("\nLOD");
    }
    if(IR.OP == 4) {
        printf("\nSTO");
    }
    if(IR.OP == 5) {
        printf("\nCAL");
    }
    if(IR.OP == 6) {
        printf("\nINC");
       
    }
    if(IR.OP == 7) {
        printf("\nJMP");
    }
    if(IR.OP == 8) {
        printf("\nJPC");
    }
    if(IR.OP == 9) {
        printf("\nSYS");

        
    }
    // print current register values
    printf("\t%d \t%d \t%d \t%d \t%d \t", IR.L, IR.M, PC, BP, SP);
    // print current stack
    for (int i = 439; 434 <= i; i--) {
        printf("%d ", PAS[i]);
        
    }
    printf("\n\n");
}

int main(int argc) {

    // Checking argument count
    if(argc != 2){
        printf("Error! Wrong number of arguments.");
        return 0;
    }
    
    // File handling
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    // Scanning instructions into PAS
    int i = 499;
    
    while(fscanf(inputFile,"%d",&PAS[i]) == 1) {
            i--;
    }

    // Setting Global Variables
    PC = 499;
    SP = i + 1;
    BP = SP - 1;

    // Initial Print
    printf("\tL \tM \tPC \tBP \tSP \tstack");
    printf("\nInitial values: \t%d \t%d \t%d", PC, BP, SP);

   // Fetch-Cycle through a while loop
    while(1){
        
        // Setting Instruction Register
        IR.OP = PAS[PC];
        IR.L = PAS[PC-1];
        IR.M = PAS[PC-2];
        
        // Decrementing PC
        PC = PC - 3;

        // Lit Instruction
        if (IR.OP == 1) {
            SP = SP - 1;  
            PAS[SP] = IR.M;
            printPAS();
        }
        // OPR Instruction
        else if (IR.OP == 2) {
            
            // RTN
            if(IR.M == 0){
                
                SP = BP + 1;
                BP = PAS[SP - 2];
                PC = PAS[SP - 3];

            // ADD
            } else if(IR.M == 1){
                PAS[SP + 1] = PAS [SP + 1] + PAS[SP];
                SP = SP + 1;
            // SUB
            } else if(IR.M == 2){
                PAS[SP + 1] = PAS [SP + 1] - PAS[SP];
                SP = SP + 1;
            // MUL
            } else if(IR.M == 3){
                PAS[SP + 1] = PAS [SP + 1] * PAS[SP];
                SP = SP + 1;
            // DIV
            } else if(IR.M == 4){
                PAS[SP + 1] = PAS [SP + 1] / PAS[SP];
                SP = SP + 1;
            // EQL
            } else if(IR.M == 5){
                PAS[SP + 1] = (PAS [SP + 1] == PAS[SP]);
                SP = SP + 1;
            // NEQ
            } else if(IR.M == 6){
                if(PAS[SP+1] != PAS[SP])
                    PAS[SP+1] = 1;
                else    
                    PAS[SP+1] = 0;
                SP++;
            // LSS
            } else if(IR.M == 7){
                if(PAS[SP+1] < PAS[SP])
                    PAS[SP+1] = 1;
                else    
                    PAS[SP+1] = 0;
                SP++;
            // LEQ
            } else if(IR.M == 8){
                if(PAS[SP+1] <= PAS[SP])
                    PAS[SP+1] = 1;
                else    
                    PAS[SP+1] = 0;
                SP++;
            // GTR
            } else if(IR.M == 9){
                if(PAS[SP+1] > PAS[SP])
                    PAS[SP+1] = 1;
                else    
                    PAS[SP+1] = 0;
                SP++;
            // GEQ
            } else if(IR.M == 10){
                if(PAS[SP+1] >= PAS[SP])
                    PAS[SP+1] = 1;
                else    
                    PAS[SP+1] = 0;
                SP++;
            } 
            printPAS();
        }
        // LOD Instruction
        else if (IR.OP == 3) {
            SP = SP - 1;
            PAS[SP] = PAS[base(BP, IR.L) - IR.M];
            printPAS();
        }
        // STO Instruction 
        else if (IR.OP == 4) {
            PAS[base(BP, IR.L) - IR.M] = PAS[SP];
            SP++;
            printPAS();
        }
        else if (IR.OP == 5) {
            // Call procedure
            PAS[SP - 1] = base(BP, IR.L);
            PAS[SP - 2] = BP;
            PAS[SP - 3] = PC;
            BP = SP - 1;
            PC = 499 - IR.M;
            printPAS();
        }
        else if (IR.OP == 6) {
            // Allocating memory on the stack
            SP = SP - IR.M;
            printPAS();
        }
        else if (IR.OP == 7) {  
            // Unconditional jumps
            PC = 499 - IR.M;
            printPAS();
        }
        else if (IR.OP == 8) {
            // Conditional jumps
            if(PAS[SP] == 0) {
                PC = 499 - IR.M;
            }
            SP = SP + 1;
            printPAS();
        }
        else if (IR.OP == 9) {
            if(IR.M== 1){
                // Output integer value at top of stack, then pop
                printf("%d", PAS[SP]);
                SP = SP + 1;
            } else if(IR.M== 2){
                // Read an integer from stdin and push it
                SP = SP - 1;
                printf("\nPlease Enter an Integer: ");
                scanf("%d, ", &PAS[SP]);

                

            } else if(IR.M == 3){
                printPAS();
                break;
            }
            printPAS();
        }
        
        
    }
    
    fclose(inputFile);

}
