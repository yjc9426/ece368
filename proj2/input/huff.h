#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    typedef struct binode {
        unsigned long int ct;
        unsigned int character;
        int height;
        struct binode *left;
        struct binode *right;
        struct binode *next;
    } Node;
    

    Node* node_construct(int ct, unsigned int character) {
        Node * n = malloc(sizeof(Node));
        n->ct = ct;
        n->character = character;
        n->height = 0;
        n->left = NULL;
        n->right = NULL;
        n->next = NULL;
        return n;
    }
        

    Node* insert_N(Node * head, Node * n) {

        if (head == NULL) {
            return n;
        }

        Node* prev = NULL;
        Node* current = head;
        while ((current != NULL) && (current->ct < n->ct)) {
            prev = current;
            current = current->next;
        }

        if (current == head) {
            n->next = current;
            return n;
        }

        prev->next = n;
        n->next = current;
        return head;
    }
    

    void free_bt(Node * root);


    void packup(FILE *wfp, int *bits_remaining, unsigned long int *output, unsigned long int input, unsigned long length) {
        if(length < *bits_remaining){
            *output = (*output << length)|input;
            *bits_remaining -= length;            
        }
        else {
            *output = (*output << *bits_remaining)|(input>>(length - *bits_remaining));
            fwrite(output,sizeof(char),8,wfp);
            *output = input; //bits already written out will be shifted away
            *bits_remaining = sizeof(unsigned long)*8 - (length - *bits_remaining);
        }
    }

    
    void get_codes(Node * root, unsigned long int codetable[257][2], unsigned long int * length, unsigned long int * code) {
    	
    	if (root == NULL) {
    		return;
    	}
    	
    	if (root->height == 0) {
    		codetable[root->character][0] = *code;
    		codetable[root->character][1] = *length;
    		return;  	
    	}
    	

    	(*length)++;
    	*code = (*code)<<1;
    	get_codes(root->left, codetable, length, code);

    	(*code)++;
    	get_codes(root->right, codetable, length, code);
    	
    	(*length)--;
    	*code = (*code)>>1; 
    }
    
    void print_header(FILE *wfp, Node * root, int *bits_remaining, unsigned long int *output);
            

    char *huff_name(char *filename);




