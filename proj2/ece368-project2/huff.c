#include "huff.h"

Node * construct_bt(Node* list){
     Node * other = NULL;
     int done = 0;
     Node * fst = NULL;
     Node * snd = NULL;
     Node * temp = NULL;
     Node * tail = NULL;
     while (done == 0) {
        
        if (list == NULL) { 
            fst = other;
            other = other->next;
        }
        else { 
            if (other == NULL) {
                fst = list;
                list = list->next;
            }
            else { 
                if (list->ct <= other->ct) {
                    fst = list;
                    list = list->next;
                }
                else {
                    fst = other;
                    other = other->next;
                }
            }
        }
        
        if (list == NULL) {
            
            if (other == NULL) {
                done = 1;
            }
            else { 
                snd = other;
                other = other->next;
            }
        }
        else { 
            if (other == NULL) {
                snd = list;
                list = list->next;
            }
            else {
            
                if (list->ct <= other->ct) {
                    snd = list;
                    list = list->next;
                }
                else {
                    snd = other;
                    other = other->next;
                }
            }
        }

        if (done == 0) {
            temp = node_construct((fst->ct)+(snd->ct), '\0');

            if (fst->height >= snd->height) {
                temp->right = fst;
                temp->left = snd;

                temp->height = fst->height + 1;
            }
            else {
                temp->right = snd;
                temp->left = fst;

                temp->height = snd->height + 1;
            }

            fst->next = temp;
            snd->next = temp;

            if (other == NULL) {
                tail = temp;
                other = tail;
            }
            else {
                tail->next = temp;
                tail = temp;
            }
        }
    }
    

    Node * tree = fst;
    return tree;
}


    void free_bt(Node * root) {
        if (root == NULL) {
            return;
        }
        free_bt(root->right);
        free_bt(root->left);
        free(root);
    }

    void header(FILE *wfp, Node * root, int *bits_remain, unsigned long int *output) {
        
        if (root == NULL) {
            return;
        }
        

        if ((root->left == NULL) && (root->right == NULL)) {
            packup(wfp, bits_remain, output, 1, 1);
            if (root->character != 256) {
                packup(wfp, bits_remain, output, root->character, 8);
            }
            else {
                packup(wfp, bits_remain, output, 255, 8);
                packup(wfp, bits_remain, output, 0, 1);
            }
        }
        else {
            packup(wfp, bits_remain, output, 0, 1);
        }
        
        header(wfp, root->left, bits_remain, output);
        header(wfp, root->right, bits_remain, output);
        
        free(root);
        root = NULL;
    
    }

    char *huff_name(char *filename){
        int i = 0;
        char *newname;
        while(*(filename+i) != '\0') i++;
  
        //printf("i: %d\n",i);
        newname = malloc(sizeof(char)*(i+6));
        i = 0;
        while(*(filename + i) != '\0') {
          *(newname+i) = *(filename + i);
          i++;
        }
        *(newname+i++) = '.';
        *(newname+i++) = 'h';
        *(newname+i++) = 'u';
        *(newname+i++) = 'f';
        *(newname+i++) = 'f';
        *(newname+i) = '\0';
        //printf("Old file name: %s\n", filename);
        //printf("New file name: %s\n", newname);
        return(newname);
    }

int main(int argc, char * argv[])
{

	if (argc != 2){
		printf("Usage: %s <filename>\n",argv[0]);
		return -1;
	}
	FILE * fp = fopen(argv[1],"rb");
	if (fp == NULL){
		printf("Error: cannot open %s.\n",argv[1]);
		return -1;
	}

    
    unsigned long int cts[257][2] = {{0,0}};
      
    int curchar = 0;
    while ((fread(&curchar, 1, 1, fp)) > 0) {
        (cts[curchar][0])++;
    }
    
    int i = 0;

    Node * list = NULL;

    for (i = 255; i >= 0; i--) {
        if (cts[i][0] != 0) {

            list = insert_N(list, node_construct(cts[i][0], i));
        }
    }
    

    list = insert_N(list, node_construct(1, 256));


    Node * tree = construct_bt(list);   	
    

    unsigned long int c_len = 0;
    unsigned long int code = 0xBADFACE000ECE368;
    unsigned long int output = 0;
    int bits_remain = sizeof(output) *8;
    char * outname = huff_name(argv[1]);
    FILE *wfp = fopen(outname,"wb");

    fwrite(&code,sizeof(unsigned long), 1, wfp);
	code = 0;
    free(outname);
   	get_codes(tree, cts, &c_len, &code);
   	
   	
    header(wfp, tree, &bits_remain, &output);

    unsigned char buff[256];

    int result;

    rewind(fp);
    if(wfp) {
        result = fread(buff, sizeof(char), 256, fp);
        while( result > 0) {
            i = 0;
            while( i < result) {
                c_len = cts[(unsigned int)buff[i]][1];
                code = cts[(unsigned int)buff[i]][0];
                if(c_len < bits_remain) {
                    output = (output << c_len)|code;
                    bits_remain -= c_len;
                } 
                else if(c_len >= bits_remain) {
                    output = (output << bits_remain)|(code>>(c_len - bits_remain));
                    fwrite(&output,sizeof(output),1,wfp);
                    output = code; //bits already written out will be shifted away later
                    bits_remain = sizeof(output)*8 - (c_len - bits_remain);
                }
                i++;
            }
            result = fread(buff, sizeof(char), 256, fp);
        }
        
        c_len = cts[256][1];
        code = cts[256][0];
        if(c_len < bits_remain) {
                    output = (output << c_len)|code;
                    bits_remain -= c_len;
        } 
        else if(c_len >= bits_remain) {
                    output = (output << bits_remain)|(code>>(c_len - bits_remain));
                    fwrite(&output,sizeof(output),1,wfp);
                    output = code; //bits already written out will be shifted away
                    bits_remain = sizeof(output)*8 - (c_len - bits_remain);
        }
        if (bits_remain != sizeof(unsigned long)*8) {
        	output = output << (bits_remain);
        	fwrite(&output, sizeof(output), 1, wfp);
       	}
    }   
    else {
      printf("Failed to open output file\n");
    }
	
    fclose(fp);
    fclose(wfp);

    
    
    return 0;
}






