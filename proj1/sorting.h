#ifndef __sorting_h_
#define __sorting_h_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

long *Load_File(char *Filename, int *Size);
int Save_File(char *Filename, long *Array, int Size);
void Shell_Insertion_Sort(long *Array, int Size, double *NComp, double *NMove);
void Improved_Bubble_Sort(long *Array, int Size, double *NComp, double *NMove);
long* create_seq1(int Size, int* seqSize);
long* create_seq2(int Size, int* seqSize);
void Save_Seq1 (char *Filename, int N);
void Save_Seq2 (char *Filename, int N);

#endif 