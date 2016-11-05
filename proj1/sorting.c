#include "sorting.h"


long *Load_File(char *Filename, int *Size)
{
    FILE * fptr = fopen(Filename, "r");
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


int Save_File(char *Filename, long *Array, int Size)
{
    int i;
    FILE *fptr = fopen(Filename,"w");
    fprintf(fptr, "%d\n", Size);
    for(i = 0; i<Size-1; i++)
    {    
        fprintf(fptr, "%ld\n", Array[i]);  
    }
    fprintf(fptr, "%ld", Array[i]);
    
    fclose(fptr);
    
    return 0;
}


long* create_seq1(int Size, int* seqSize)
{
	printf("seq Size = %d\n", Size);
	int p2 = 0;
	int p3 = 0;
	int i;
	int u2;
	int u3;
	*seqSize = Size;
	long * array = malloc(Size * sizeof(long));

	array[0] = 1L;
	for(i = 1; i < Size; i++ )
	{
		if (array[p2] * 2 == array[i - 1])
		{
			p2 += 1;
		}

		if (array[p3] * 3 == array[i-1])
		{
			p3 += 1;
		}

		u2 = array[p2] * 2;
		u3 = array[p3] * 3;
		if (u2 < u3)
		{
			p2 += 1;
			array[i] = u2;
		}
		else
		{
			p3 += 1;
			array[i] = u3;
		}
		printf("array[%d] = %ld\n", i, array[i]);
		if(array[i] >= Size)
		{
			*seqSize = i;
			break;
		}	
	}
	return array;
}

long* create_seq2(int Size, int* seqSize)
{
	*seqSize = 1 +  log(Size) / log(1.3);
	fprintf(stderr, "Size: %d\n", *seqSize);
	long* array = malloc((*seqSize)*sizeof(long));
	int i;
	for(i = 0; i < *seqSize; i++)
	{
		array[i] = Size / pow(1.3,i+1);
		if(array[i] == 1){
			*seqSize = i + 1;
			break;
		}
		if(array[i] == 9 || array[i] == 10){
			array[i] = 11;
		}
	}
	return array;
}

void Shell_Insertion_Sort (long *Array, int Size, double *NComp, double *NMove)
{
	int seqSize;
	long* seq1 = create_seq1(Size, &seqSize);
	int k;
	long i,j,temp;
	for( i =0; i< seqSize; i++){
		printf("%ld\n",seq1[i]);
	}
	printf("size = %d\n", seqSize);
	for (i = seqSize - 1; i >= 0; i--)
	{
		for(j = seq1[i]; j < Size; j++)
		{
			temp = Array[j];
			(*NMove)++;
			for( k = j - seq1[i]; k >= 0; k -= seq1[i])
			{
				*NComp += 1;
				if ( Array[k] <= temp )
				{
					break;
				}
				Array[k+seq1[i]]=Array[k];
				(*NMove)++;
			}
			Array[k+seq1[i]] = temp;
			(*NMove)++;
		}
	}
	free(seq1);
}

void Improved_Bubble_Sort(long *Array, int Size, double *NComp, double *NMove)
{
	int seqSize;
	long * seq2 = create_seq2(Size, &seqSize);
	int i,j,k,temp;
	//int bool;
	for(i = 0; i < seqSize; i++)
	{
		for(j = seq2[i]; j < Size; j++)
		{
			//bool = 1;
			temp = Array[j];
			(*NMove)++;
				for(k = j-seq2[i]; k >= 0; k -= seq2[i])
				{
					*NComp += 1;
					if(Array[k] >= temp){
						*NMove += 2;
						Array[k+seq2[i]]=Array[k];
						Array[k] = temp;
					}
					temp = Array[k];
					(*NMove)++;
				}
		}
	}
	free(seq2);
}



void Save_Seq1 (char *Filename, int N)
{
	int i;
	int seqSize;
	FILE * f = fopen(Filename,"w");
	if(f == NULL){
		fprintf(stderr, "File Pointer is NULL\n");
	}
	long* array = create_seq1(N, &seqSize);
	for(i = 0; i<seqSize; i++)
	{
		fprintf(f,"%ld\n",array[i]);
	}

	free(array);
	if(f){
		fclose(f);
	}	
	return;
}

void Save_Seq2 (char *Filename, int N)
{
	int i;
	int seqSize;
	FILE * f = fopen(Filename,"w");

	long* array = create_seq2(N, &seqSize);
	for(i = 0; i<seqSize; i++)
	{
		fprintf(f,"%ld\n",array[i]);
	}

	fclose(f);
	fprintf(stderr, "After close\n");
	free(array);
	return;
}

/*int main()
{	
	int sb = 17;
	int size;
	long * seq = create_seq2(sb, &size);
 	int j;
	for(j=0;j<size;j++){
		fprintf(stdout, "%ld\n", seq[j]);
	}
	free(seq);
	double s = 0;
	double b = 0;
	long a[] = {3,4,51,1245,1,5,12,561,5,351,25,124,1,251,23,125,1};
	Shell_Insertion_Sort(a,17,&s,&b);
	int i;
	for(i=0;i<17;i++){
		fprintf(stdout, "%ld\n", a[i]);
	
	}
	fprintf(stdout, "move = %lf, comp = %lf\n",b,s);
	Save_Seq1("file.txt", 17);
	
	long m[] = {3,4,51,1245,1,5,12,561,5,351,25,124,1,251,23,125,1};
	double c =0;
	double n = 0;
	Improved_Bubble_Sort(m,17,&c,&n);
	int k;
	for(i=0;i<17;i++){
		fprintf(stdout,"%ld\n",m[i]);
	}
	fprintf(stdout, "comp=%lf,move=%lf\n",c,n);

	Save_File("saved_file", m, 17);

	long * r = Load_File("saved_file", &sb);
	for(i=0;i<17;i++){
		fprintf(stdout,"%ld\n",r[i]);
	}
	free(r);
	return 0;
}*/
