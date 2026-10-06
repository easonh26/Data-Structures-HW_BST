#include <stdio.h>
#include <string.h>
#include "BSTHW.c"
//==========================================================
// My comparison function
//==========================================================
int compareInts(void* a, void* b) {
    int ia = *(int*)a;
    int ib = *(int*)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

int compareLongLong(void* a, void* b) {
    long long ia = *(long long*)a;
    long long ib = *(long long*)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

int compareFloat(void* a, void* b) {
    float fa = *(float*)a;
    float fb = *(float*)b;
    if (fa < fb) return -1;
    if (fa > fb) return 1;
    return 0;
}

int compareDouble(void* a, void* b) {
    double da = *(double*)a;
    double db = *(double*)b;
    if (da < db) return -1;
    if (da > db) return 1;
    return 0;
}

int compareChar(void* a, void* b) {
    char ca = *(char*)a;
    char cb = *(char*)b;
    if (ca < cb) return -1;
    if (ca > cb) return 1;
    return 0;
}

int compareString(void* a, void* b) {
    char* sa = (char*)a;
    char* sb = (char*)b;
    int cmp = strcmp(sa, sb);
    if (cmp < 0) return -1;
    if (cmp > 0) return 1;
    return 0;
}
//==========================================================

//==========================================================
// Test function
//==========================================================

void testBSTInt() {
    int intArr[] = {10, 20, 5, -3, 7};
    bst* b = (bst*)mloc(sizeof(bst));
    init(b);
    for (int i = 0; i < 5; i++) {
        insert(b, &intArr[i], compareInts, sizeof(int));
    }
    printf("[Int] Max: %d\n", *(int*)max(b)->key);
    printf("[Int] Min: %d\n", *(int*)min(b)->key);

    int target = 10;
    bst* s = search(b, &target, compareInts);
    printf("[Int] Search 10: %s\n", s ? "Found" : "Not found");

    deleteNode(&b, &target, compareInts, sizeof(int));
    s = search(b, &target, compareInts);
    printf("[Int] After delete 10, Search 10: %s\n", s ? "Found" : "Not found");
}

void testBSTFloat() {
    float arr[] = {3.14f, 2.71f, -1.0f, 0.0f, 100.1f};
    bst* b = (bst*)mloc(sizeof(bst));
    init(b);
    for (int i = 0; i < 5; i++) {
        insert(b, &arr[i], compareFloat, sizeof(float));
    }
    printf("[Float] Max: %f\n", *(float*)max(b)->key);
    printf("[Float] Min: %f\n", *(float*)min(b)->key);

    float target = 0.0f;
    bst* s = search(b, &target, compareFloat);
    printf("[Float] Search 0.0: %s\n", s ? "Found" : "Not found");

    deleteNode(&b, &target, compareFloat, sizeof(float));
    s = search(b, &target, compareFloat);
    printf("[Float] After delete 0.0, Search 0.0: %s\n", s ? "Found" : "Not found");
}

void testBSTDouble() {
    double arr[] = {3.14159, 2.71828, -1.5, 0.0, 99.99};
    bst* b = (bst*)mloc(sizeof(bst));
    init(b);
    for (int i = 0; i < 5; i++) {
        insert(b, &arr[i], compareDouble, sizeof(double));
    }
    printf("[Double] Max: %lf\n", *(double*)max(b)->key);
    printf("[Double] Min: %lf\n", *(double*)min(b)->key);

    double target = 99.99;
    bst* s = search(b, &target, compareDouble);
    printf("[Double] Search 99.99: %s\n", s ? "Found" : "Not found");

    deleteNode(&b, &target, compareDouble, sizeof(double));
    s = search(b, &target, compareDouble);
    printf("[Double] After delete 99.99, Search 99.99: %s\n", s ? "Found" : "Not found");
}

void testBSTLongLong() {
    long long arr[] = {10000000000LL, 50000000000LL, -1000000000LL, 0LL, 9999999999LL};
    bst* b = (bst*)mloc(sizeof(bst));
    init(b);
    for (int i = 0; i < 5; i++) {
        insert(b, &arr[i], compareLongLong, sizeof(long long));
    }
    printf("[LongLong] Max: %lld\n", *(long long*)max(b)->key);
    printf("[LongLong] Min: %lld\n", *(long long*)min(b)->key);

    long long target = 0LL;
    bst* s = search(b, &target, compareLongLong);
    printf("[LongLong] Search 0: %s\n", s ? "Found" : "Not found");

    deleteNode(&b, &target, compareLongLong, sizeof(long long));
    s = search(b, &target, compareLongLong);
    printf("[LongLong] After delete 0, Search 0: %s\n", s ? "Found" : "Not found");
}

void testBSTChar() {
    char arr[] = {'g', 'x', 'm', 'e', 'f'};
    bst* b = (bst*)mloc(sizeof(bst));
    init(b);
    for (int i = 0; i < 5; i++) {
        insert(b, &arr[i], compareChar, sizeof(char));
    }
    printf("[Char] Max: %c\n", *(char*)max(b)->key);
    printf("[Char] Min: %c\n", *(char*)min(b)->key);

    char target = 'e';
    bst* s = search(b, &target, compareChar);
    printf("[Char] Search 'e': %s\n", s ? "Found" : "Not found");

    deleteNode(&b, &target, compareChar, sizeof(char));
    s = search(b, &target, compareChar);
    printf("[Char] After delete 'e', Search 'e': %s\n", s ? "Found" : "Not found");
}

void testBSTString() {
    char* arr[] = {"apple", "banana", "cherry", "date", "grape"};
    bst* b = (bst*)mloc(sizeof(bst));
    init(b);
    
    for (int i = 0; i < 5; i++) {
        insert(b, arr[i], compareString, sizeof(char*));
    }
    
    printf("[String] Max: %s\n", (char*)max(b)->key);
    printf("[String] Min: %s\n", (char*)min(b)->key);
    
    char* target = "date";
    bst* s = search(b, target, compareString);
    printf("[String] Search 'date': %s\n", s ? "Found" : "Not found");
    
    deleteNode(&b, target, compareString, sizeof(char*));
    s = search(b, target, compareString);
    printf("[String] After delete 'date', Search 'date': %s\n", s ? "Found" : "Not found");
}

void testPredecessorSuccessor() {
    int arr[] = {20, 10, 30, 5, 15, 25, 35};
    bst* b = (bst*)mloc(sizeof(bst));
    init(b);

    for (int i = 0; i < 7; i++) {
        insert(b, &arr[i], compareInts, sizeof(int));
    }

    int target = 25;
    // ===getPred_child===
    bst* predChild = getPred_child(b, &target, compareInts);
    if (predChild != NULL) {
        printf("[getPred_child] Pred of %d: %d\n", target, *(int*)predChild->key);
    } else {
        printf("[getPred_child] Pred of %d: NULL\n", target);
    }

    // ===getSucc_child===
    bst* succChild = getSucc_child(b, &target, compareInts);
    if (succChild != NULL) {
        printf("[getSucc_child] Succ of %d: %d\n", target, *(int*)succChild->key);
    } else {
        printf("[getSucc_child] Succ of %d: NULL\n", target);
    }

    // ===getPred===
    void* pre = NULL;
    void* ans = NULL;
    getPred(b, &target, compareInts, &pre, &ans);
    if (ans != NULL) {
        printf("[getPred] Pred of %d: %d\n", target, *(int*)ans);
    } else {
        printf("[getPred] Pred of %d: NULL\n", target);
    }

    // ===getSucc===
    int type = 0;
    ans = NULL;
    getSucc(b, &target, compareInts, &type, &ans);
    if (ans != NULL) {
        printf("[getSucc] Succ of %d: %d\n", target, *(int*)ans);
    } else {
        printf("[getSucc] Succ of %d: NULL\n", target);
    }
}
//==========================================================

int main() {
    testBSTInt();
    testBSTFloat();
    testBSTDouble();
    testBSTLongLong();
    testBSTChar();
    testBSTString();
    testPredecessorSuccessor();
    return 0;
}
