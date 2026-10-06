#include "BSTHW.h"
#include <stddef.h>

// ============================
// Memory Pool Management
// ============================

// Static memory pool - fixed 100KB for all allocations
char memory_pool[100000];
// Current position in memory pool
int pool_index=0;

// Simple memory allocation from fixed pool
// If pool is full, returns NULL
void* mloc(int size) {
    if (pool_index+size>100000) {
        return (void*)0;  
    }
    void* ptr=(void*)(&memory_pool[pool_index]);
    pool_index+=size;
    return ptr;
}

// Copy data from source to destination
// Uses byte-by-byte copy (equivalent to memcpy)
void mcpy(void* dest, void* src, int size) {
    char* d=(char*)dest;
    char* s=(char*)src;
    for (int i=0; i<size; i++) {
        d[i]=s[i];
    }
}

// ============================
// BST Core Operations
// ============================

// Initialize a new BST node
bst* init(bst* root){
	root->key=NULL;
	root->left=NULL;
	root->right=NULL;
	return root;
}

// Insert data into BST maintaining BST property
// If node is empty, store data here
// Otherwise, recursively insert left or right based on comparison
void insert(bst* root, void* data,int compare(void*, void*),int data_size){
	int type=1;  // type = 0 means root is empty, type = 1 means root already has data
	if(root->key==NULL){
		type=0;
		root->key=mloc(data_size);
		if(root->key!=NULL){
			mcpy(root->key,data,data_size);
		}
	}
	if(type){
		int c=compare(data,root->key);
		if(c==1){  // data > root, insert to right
			if(root->right==NULL){
				root->right=(bst*)mloc(sizeof(bst));
				root->right->left=NULL;
				root->right->right=NULL;
				root->right->key=mloc(data_size);
				if(root->right->key!=NULL){
					mcpy(root->right->key,data,data_size);
				}
			}else{
				insert(root->right,data,compare,data_size);
			}
		}
		if(c==-1){  // data < root, insert to left
			if(root->left==NULL){
				root->left=(bst*)mloc(sizeof(bst));
				root->left->left=NULL;
				root->left->right=NULL;
				root->left->key=mloc(data_size);
				if(root->left->key!=NULL){
					mcpy(root->left->key,data,data_size);
				}
			}else{
				insert(root->left,data,compare,data_size);
			}			
		}
		//if(c==0) equal!! Do nothing!!
	}
}

// Search for a value in BST using binary search
bst* search(bst* root, void* data,int compare(void*, void*)){
	if(root==NULL) return NULL;
	int c=compare(data,root->key);
	if(c==0) return root;
	else if(c==1) return search(root->right, data, compare);
	else if(c==-1) return search(root->left, data, compare);
	else return root;
}

// Delete a node from BST
// Three cases: (1) no children - remove node
//              (2) one child - replace with child
//              (3) two children - replace with successor, then delete successor
void deleteNode(bst** root, void* data, int compare(void*, void*),int data_size){
	bst* cur;
	int type=1;
	if(*root==NULL){
		type=0;
	}
	if(type){
		int c=compare(data,(*root)->key);
		if(c==1){
			deleteNode(&(*root)->right,data,compare,data_size);
		}
		else if(c==-1){
			deleteNode(&(*root)->left,data,compare,data_size);
		}else if(c==0){
			cur= *root;
			if(cur->right==NULL){
				*root=cur->left;
			}
			else if(cur->left==NULL){
				*root=cur->right;
			}
			else{
				bst* minnode=cur->right;
				while(minnode->left!=NULL){
					minnode=minnode->left;
				}
				mcpy(cur->key,minnode->key,data_size);
				deleteNode(&(cur->right),minnode->key,compare,data_size);
			}
		}		
	} 
}

// Find maximum value 
bst* max(bst* root){
	if(root==NULL) return NULL;
	while(root->right!=NULL){
		root=root->right;
	}
	return root;
}

// Find minimum value 
bst* min(bst* root){
	if(root==NULL) return NULL;
	while(root->left!=NULL){
		root=root->left;
	}
	return root;
}

// ============================
// Predecessor & Successor Operations
// Two kinds of search method
// ============================

// Find predecessor using left subtree
// Predecessor = maximum value in left subtree
bst* getPred_child(bst* root, void* target, int compare(void*, void*)){
	bst* temp=search(root, target, compare);
	if(temp!=NULL){
		bst* ans=max(temp->left);
		if(ans!=NULL) return ans;
		else return NULL;
	}else{
		return NULL;
	}
}

// Find successor using right subtree
// Successor = minimum value in right subtree
bst* getSucc_child(bst* root, void* target, int compare(void*, void*)){
	bst* temp=search(root, target, compare);
	if(temp!=NULL){
		bst* ans=min(temp->right);
		if(ans!=NULL) return ans;
		else return NULL;
	}else{
		return NULL;
	}
}

// Find predecessor using in-order traversal
// LVR traversal visits nodes in ascending order
// Track the last visited node as we pass the target value
void getPred(bst* root, void* target, int compare(void*, void*), void** pre, void** ans){
	if(root!=NULL){
		getPred(root->left, target, compare, pre, ans);
		int c=compare(root->key,target);
		if(c==0) *ans=*pre;  // Found target, predecessor is previous node
		*pre=(root->key);  // Update previous node
		getPred(root->right, target, compare, pre, ans);
	}else{
		return;
	}
}

// Find successor using in-order traversal
// LVR traversal visits nodes in ascending order
// Once target is found (type=1), the next visited node is the successor
void getSucc(bst* root, void* target, int compare(void*, void*), int* type, void** ans){
	if(root!=NULL){
		getSucc(root->left, target, compare, type, ans);
		int c=compare(root->key,target);
		if(*ans != NULL) return;  // Already found successor, stop traversal
		if(*type){
			*ans=root->key;  // This is the first node after target
			return;
		}
		if(c==0) *type=1;  // Mark that when found the target
		getSucc(root->right, target, compare, type, ans);
	}else{
		return;
	}
}




