#include <stdio.h>
#include <stdlib.h>
//#include <math.h>




double mypow(double x, double y){
    
    double sum = 0;
    
    int i;
    
    if(y == 0){
        
        return 1;
    }
    
    for(i = 0; i < y; i++){
        if(sum == 0){
            sum = x;
        }
        else{
            sum = sum * x;
        }
    }
    
    
    return sum;
    
}




double mylog2(double x){
    
    double iterator = 0;
    
    while(x > 2){
        
        x = (x/(2.00));
        
        iterator += 1;
        
    }
    
    
    return iterator;
    
    
}


double mylog3(double x){
    
    double iterator = 0;
    
    while(x > 3){
        
        x = (x/(3.00));
        
        iterator += 1;
        
    }
    
    
    return iterator;
    
    
}



long *Load_File(char *Filename, int *Size){
    

    
    //create the file pointer
    FILE * fptr = fopen(Filename, "r");
    
    //check if the file pointer exists
    if(fptr == NULL){
        fclose(fptr);
        *Size = -1;
        return NULL;
    }
    
    int i;
    
    fscanf(fptr, "%i", Size);
    
    long * array = malloc((*Size)*sizeof(long));

    for(i=0; i<*Size; i++){
        fscanf(fptr, "%ld", array+i);
    }
    

    fclose(fptr);
    return array;
    
    
}




int Save_File(char *Filename, long *Array, int Size){
    
    
    int i;
    
    FILE *fptr = fopen(Filename,"w");
    
    
    for(i = 0; i<Size-1; i++){
        
        fprintf(fptr, "%ld\n", Array[i]);
        
    }
    
    fprintf(fptr, "%ld", Array[i]);
    
    fclose(fptr);
    
    return 0;
}


long * create_sequence_1(int Size, int * sequenceSize){
    
    
    //*sequenceSize = log(Size)/log(2); //works with math.h
    
    *sequenceSize = mylog2(Size); //Added to replace math.h
    
    
    
    long * sequenceArray = malloc((*sequenceSize)*sizeof(long));
    
    int i;
    
    int temp;
    
    for( i = *sequenceSize; i>0;i--){
        
        temp = mypow(2,i) - 1;
        
        sequenceArray[*sequenceSize-i] = mypow(2,i) - 1;
        
        
    }
    
    return sequenceArray;
}




int Print_Seq_1(char *Filename, int Size){
    
    
    int i;
    
    int sequenceSize;
    
    FILE *fptr = fopen(Filename,"w");
    
    long * sequenceArray = create_sequence_1(Size, &sequenceSize);
    
    
    for(i = 0; i<sequenceSize-1; i++){
        
        fprintf(fptr, "%ld\n", sequenceArray[i]);
        
    }
    
    fprintf(fptr, "%ld", sequenceArray[i]);
    
    fclose(fptr);
    
    free(sequenceArray);
    
    return 0;
}




long * create_sequence_2(int Size, int * sequenceSize){
    
    //*sequenceSize = log(Size)/log(3); //works with math.h
    
    *sequenceSize = mylog3(Size); //Added to replace math.h
    
    int tempSequenceSize = *sequenceSize;
    
    *sequenceSize += 1;
    
    *sequenceSize = (*sequenceSize + 1)*((double)*sequenceSize/2);
    
    long * sequenceArray = malloc((*sequenceSize)*sizeof(long));
        
    int i;
    
    int secondInternalCounter = tempSequenceSize;
    
    for(i = 0; i<*sequenceSize; i++){
        
        if(secondInternalCounter == tempSequenceSize){
            
            sequenceArray[i] = mypow(3,tempSequenceSize);
            tempSequenceSize--;
            secondInternalCounter = -2;
            
        }
        
        else{
            
            sequenceArray[i] = (sequenceArray[i-1]/3)*2;
            
        }
        
        secondInternalCounter++;
    
    }
    
    return sequenceArray;
}




int Print_Seq_2(char *Filename, int Size){
    
    
    int i;
    
    int sequenceSize;
    
    FILE *fptr = fopen(Filename,"w");
    
    long * sequenceArray = create_sequence_2(Size, &sequenceSize);
    
    
    for(i = 0; i<sequenceSize-1; i++){
        
        fprintf(fptr, "%ld\n", sequenceArray[i]);
        
    }
    
    fprintf(fptr, "%ld", sequenceArray[i]);
    
    fclose(fptr);
    
    free(sequenceArray);
    
    return 0;
}




void Shell_Insertion_Sort_Seq1(long *Array, int Size, double *N_Comp, double *N_Move){
    
    int sequenceSize;
    
    long * kSequence = create_sequence_1(Size, &sequenceSize);
    
    int k;
    long j;
    long temp_r;
    long i;
    
    
    for(k = 0; k < sequenceSize; k++){
        for(j = kSequence[k]; j<Size; j++){
            temp_r = Array[j];
            *N_Move += 1;
            i = j;
            while( (i >= kSequence[k]) && (Array[i-kSequence[k]] > temp_r) ){
                *N_Comp += 1;
                Array[i] = Array[i-kSequence[k]];
                *N_Move += 1;
                i = i-kSequence[k];
            }
            Array[i] = temp_r;
            *N_Move += 1;
        }
    }
    
    
    free(kSequence);
    
}

void Shell_Bubble_Sort_Seq1(long *Array, int Size, double *N_Comp, double *N_Move){
    
    int sequenceSize;
    
    long * kSequence = create_sequence_1(Size, &sequenceSize);
    
    int k;
    long temp_r;
    long i = 0;
    int pishposh = 0;
    int lastExchange;
    int newLastExchange;
    int swapped;
    
    
    for(k = 0; k < sequenceSize; k++){
        
        for(pishposh = 0; pishposh<kSequence[k]; pishposh++){
            swapped = 1;
            lastExchange  = Size;
            while(swapped){
                swapped = 0;
                for(i = 0;((i+1)*kSequence[k]+pishposh)<lastExchange; i++){
                    *N_Comp += 1;
                    if(Array[i*kSequence[k]+pishposh] > Array[(i+1)*kSequence[k]+pishposh]){
                        temp_r = Array[i*kSequence[k]+pishposh];
                        Array[i*kSequence[k]+pishposh] = Array[(i+1)*kSequence[k]+pishposh];
                        Array[(i+1)*kSequence[k]+pishposh] = temp_r;
                        *N_Move += 3;
                        swapped = 1;
                        newLastExchange = (i+1)*kSequence[k] + pishposh;
                    } 
                }
                lastExchange = newLastExchange;
            }
            
        }
    }
    
    
    free(kSequence);
    
}




void Shell_Insertion_Sort_Seq2(long *Array, int Size, double *N_Comp, double *N_Move){
    
    int sequenceSize;
    
    long * kSequence = create_sequence_2(Size, &sequenceSize);
    
    int k;
    long j;
    long temp_r;
    long i;
    
    
    for(k = 0; k < sequenceSize; k++){
        for(j = kSequence[k]; j<Size; j++){
            temp_r = Array[j];
            *N_Move += 1;
            i = j;
            while( (i >= kSequence[k]) && (Array[i-kSequence[k]] > temp_r) ){
                *N_Comp += 1;
                Array[i] = Array[i-kSequence[k]];
                *N_Move += 1;
                i = i-kSequence[k];
            }
            Array[i] = temp_r;
            *N_Move += 1;
        }
    }
    
    
    free(kSequence);
    
}



void Shell_Bubble_Sort_Seq2(long *Array, int Size, double *N_Comp, double *N_Move){
    
    int sequenceSize;
    
    long * kSequence = create_sequence_2(Size, &sequenceSize);
    
    int k;
    long temp_r;
    long i = 0;
    int pishposh = 0;
    int lastExchange;
    int newLastExchange;
    int swapped;
    
    
    for(k = 0; k < sequenceSize; k++){
        
        for(pishposh = 0; pishposh<kSequence[k]; pishposh++){
            swapped = 1;
            lastExchange  = Size;
            while(swapped){
                swapped = 0;
                for(i = 0;((i+1)*kSequence[k]+pishposh)<lastExchange; i++){
                    *N_Comp += 1;
                    if(Array[i*kSequence[k]+pishposh] > Array[(i+1)*kSequence[k]+pishposh]){
                        temp_r = Array[i*kSequence[k]+pishposh];
                        Array[i*kSequence[k]+pishposh] = Array[(i+1)*kSequence[k]+pishposh];
                        Array[(i+1)*kSequence[k]+pishposh] = temp_r;
                        *N_Move += 3;
                        swapped = 1;
                        newLastExchange = (i+1)*kSequence[k] + pishposh;
                    }
                }
                lastExchange = newLastExchange;
            }
            
        }
    }
    
    
    free(kSequence);
    
}
