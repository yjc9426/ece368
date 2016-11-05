#include "unhuff.h"

char * unhuff_name(char*filename){
        int i = 0;
        char *newname;
        while(*(filename+i) != '\0') i++; 
        newname = malloc(sizeof(char)*(i+8)); 
        i = 0;

        while(*(filename + i) != '\0') {
          *(newname+i) = *(filename + i);
          i++;
        }

        *(newname+i++) = '.';
        *(newname+i++) = 'u';
        *(newname+i++) = 'n';
        *(newname+i++) = 'h';
        *(newname+i++) = 'u';
        *(newname+i++) = 'f';
        *(newname+i++) = 'f';
        *(newname+i) = '\0';
        return(newname);
}

void free_bt(Node* root){
        if (root == NULL) {
            return;
        }
        free_bt(root->right);
        free_bt(root->left);
        free(root);
}




int main(int argc, char * argv[])
{
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    FILE * fp = fopen(argv[1], "rb");
        

    if (fp == NULL) {
        printf("Error: cannot open %s.\n", argv[1]);
        return -1;
    }

    
    head = NULL;
    Node * cpos = NULL;
    int read_result = 0;
    int bits_remaining = 0;
    unsigned char mybit;
    unsigned char mybyte;
    mybyte = 0;
    unsigned long int ibuff;

	read_result = fread(&ibuff, sizeof(unsigned long), 1, fp);
	if(ibuff != 0xBADFACE000ECE368){
		printf("Error: Didn't use my huff program.\n");
		return 0;
	}

    do{
		if(bits_remaining == 0) {
			
			read_result = fread(&ibuff, sizeof(unsigned long), 1, fp);

			bits_remaining = sizeof(unsigned long)*8;
		}

		mybit = (ibuff >> (--bits_remaining)) & 0x0000000000000001;

		if(mybit) {
			if(bits_remaining >= 8) {
				mybyte = (ibuff >> (bits_remaining - 8)) & 0x00000000000000FF;
				bits_remaining -= 8;
			} else {

				mybyte = (ibuff << (8-bits_remaining)) & 0x00000000000000FF;

				read_result = fread(&ibuff, sizeof(unsigned long), 1, fp);

				mybyte = mybyte | ((ibuff >> (sizeof(unsigned long)*8 - 8 + bits_remaining)) & 0x00000000000000FF);

				bits_remaining = sizeof(unsigned long)*8 - (8-bits_remaining);
			} 
		}
		cpos = tree(mybit, mybyte, cpos);
    } while(cpos != NULL);
    

    cpos = head;
    char * outname = unhuff_name(argv[1]);
    ofp = fopen(outname,"wb");
    free(outname); 

    do{
        if(bits_remaining == 0){
			read_result = fread(&ibuff, sizeof(unsigned long), 1, fp);
			bits_remaining = sizeof(unsigned long)*8;
			if(read_result < 1) {
				printf("\n**ERROR:END OF FILE**\n");
				return 0;
			}
		}

        mybit = (ibuff >> (--bits_remaining)) & 0x0000000000000001;
		cpos = tree2(mybit, cpos);
    } while (cpos != NULL);
    free_bt(head);
    fclose(fp);
    fclose(ofp);
    return 0;
}
