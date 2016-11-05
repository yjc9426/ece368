#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huff.h"
     Node * head;
     FILE * ofp;
     Node * tree(unsigned char bit, unsigned char byte, Node * cpos) {

		if (head == NULL) {
		    if (bit == 0) {
		        head = node_construct(0, 0);
		        return head;
		    }
		    else {
		        head = node_construct(0, byte);
		        return  NULL;
		    }
		}

		if (cpos == NULL) {
		    Node * n = head;
		    while (n->right != NULL) {
		        n = n->right;
		    }
		    n->character = 256;
		    return NULL;
		}
		 

		if (bit == 0) {

		    if (cpos->left == NULL) {
		        Node * n = node_construct(0,0);
		        cpos->left = n;
		        n->next = cpos;
		        return n;
		    }

		    else if (cpos->right == NULL) {
		        Node * n = node_construct(0,0);
		        cpos->right = n;
		        n->next = cpos;
		        return n;
		    }

		    else {
		        return tree(bit, byte, cpos->next);
		    }
		}
		

		if (bit == 1) {
		    if (cpos->left == NULL) {
		        Node * n = node_construct(0, byte);
		        cpos->left = n;
		        n->next = cpos;
		        return cpos;
		    }
		    else if (cpos->right == NULL) {
		        Node * n = node_construct(0, byte);
		        cpos->right = n;
		        n->next = cpos;
		        return cpos;
		    }
		    else {
		        return tree(bit, byte, cpos->next);
		    }
		}
		 
		return NULL;
	} 
	
	
	
	Node * tree2(unsigned char bit, Node * cpos) {
		
		if (cpos == NULL) {
		    return NULL;
		    
		}
		
		if (bit == 1) {
		    cpos = cpos->right;
		}
		else if (bit == 0) {
		    cpos = cpos->left;
		}
		
		if ((cpos->right == NULL) && (cpos->left == NULL)) {
		    if (cpos->character == 256) {
		        return NULL;
		    }
		    unsigned char temp = (unsigned char) cpos->character;
		    fwrite(&temp, sizeof(unsigned char), 1, ofp);
		    return head;
		}
		 
		
		
		return cpos;
	} 


    char *unhuff_name(char *filename);
    void free_bt(Node * root);
