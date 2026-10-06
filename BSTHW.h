#ifndef BSTHW_H
#define BSTHW_H

//==============================
// Memory Management Functions
//==============================

// Allocate memory from the fixed-size pool
// Parameters: size - number of bytes to allocate
// Returns: pointer to allocated memory, or NULL if pool is full
void* mloc(int size);

// Copy memory from source to destination
// Parameters: dest - destination pointer, src - source pointer, size - bytes to copy
void mcpy(void* dest, void* src, int size);
//==============================



// =============================
// Binary Search Tree (BST) Structure and Functions
// =============================

// Node structure for BST
// key - pointer to the data stored in this node
// left - pointer to left subtree (smaller values)
// right - pointer to right subtree (larger values)
struct BstNode {
    void* key;
    struct BstNode* left;
    struct BstNode* right;    
};
typedef struct BstNode bst;

// Initialize an empty BST node
bst* init(bst* root);

// =============================
// --IMPORTAT!!-- About comparison function
// =============================
/*
In comparison function...
You need to define your own comparison function
Return (int)0  if they equal
Return (int)1  if they larger
Return (int)-1 if they smaller
*/
// =============================


// Insert data into BST in sorted order
// Parameters: root - tree root, data - data to insert, compare - comparison function, data_size - size of data
void insert(bst* root, void* data,int compare(void*, void*),int data_size);

// Search for a value in BST
// Parameters: root - tree root, data - data to search, compare - comparison function
// Returns: node containing the value, or NULL if not found
bst* search(bst* root, void* data,int compare(void*, void*));

// Delete a node from BST
// Parameters: root - pointer to tree root, data - value to delete
void deleteNode(bst** root, void* data, int compare(void*, void*),int data_size);

// Find the node with maximum value
// Parameters: root - tree root
// Returns: node containing the value, or NULL if not found
bst* max(bst* root);

// Find the node with minimum value
// Parameters: root - tree root
// Returns: node containing the value, or NULL if not found
bst* min(bst* root);

// Find predecessor (largest value smaller than target) by checking left subtree
// Parameters: root - tree root, data - data to search, compare - comparison function
// Returns: predecessor node, or NULL if target has no left child
bst* getPred_child(bst* root, void* target, int compare(void*, void*));

// Find successor (smallest value larger than target) by checking right subtree
// Parameters: root - tree root, data - data to search, compare - comparison function
// Returns: successor node, or NULL if target has no right child
bst* getSucc_child(bst* root, void* target, int compare(void*, void*));

// Find predecessor using in-order traversal
// Parameters: root - tree root, data - data to search, compare - comparison function, pre - tracks previous value during traversal, ans - stores result
// You need to initialize (void** pre) and (void** ans) like...
// ..................
// void* pre = NULL;
// void* ans = NULL;
// ..................
// Read ans to getPred node
void getPred(bst* root, void* target, int compare(void*, void*), void** pre, void** ans);

// Find successor using in-order traversal
// Parameters: root - tree root, data - data to search, compare - comparison function, type - flag to indicate when target is found, ans - stores result
// You need to initialize (int* type) and (void** ans) like...
// ..................
// int type = 0;[ IMPORTANT!! ] [ NEED TO BE ZERO!! ]
// void* ans = NULL;
// ..................
// Read ans to getSucc node
void getSucc(bst* root, void* target, int compare(void*, void*), int* type, void** ans);

#endif
