//
//  main.cpp
//  CppConfidenceCourse
//
//  Created by Jia Yee Lim on 12/1/18.
//  Copyright © 2018 nus.cs3217.a0136070r. All rights reserved.
//

#include <iostream>
#include <math.h>
using namespace std;

int factorial(int n);
int binom(int n, int k);

/*
 int main(int argc, const char * argv[]) {
 // insert code here...
 std::cout << "Hello, World!\n";
 return 0;
 }
 */

/*
 int main() {
 int i = factorial(5);
 cout << i << endl;
 return 0;
 }
 */

/*
 .cpp (g++) -> Assembly (-s) -> Machine code (-o) -> exe
 Static type: Easy to debug because type checks are done during compile time and thus type errors will be caught early
 */

int factorial(int n) {
    if (n==0 || n==1) {
        return n;
    } else {
        return n * factorial(n-1);
    }
}

/*
 short
 int
 long       (usually 64-bit integer)    long l = 1234567890L;
 char
 wchar_t    (unicode character)         wchar_t c = L'a;
 double
 boolean
 */

int binom(int n, int k) {
    // return factorial(n) / (factorial(k) * factorial(n-k)); // Can overflow
    if (k==0 || k==n) {
        return 1;
    } else {
        return binom(n-1,k-1) + binom(n-1,k);
    }
}

int fib(int n) {
    if (n <= 1) {
        return n;
    } else {
        int a = 0;
        int b = 1;
        int answer = 0;
        for (int i = 2; i <= n; i++) {
            answer = a + b;
            a = b;
            b = answer;
        }
        return answer;
    }
}

/*
 int main() {
 int n;
 int k;
 cin >> n;
 cin >> k;
 cout << binom(n, k) << endl;
 for (int i = 0; i < 10; i++) {
 cout << fib(i) << endl;
 }
 return 0;
 }
 */

/*
 Every box has an address. Pointers are types that store these addresses.
 Pointer is just another kind of variable.
 32-bit machines can have max RAM of 4GB because of 32-bit pointers, so address space is limited.
 An array is a pointer. Spans a contiguous block of memory. Can be indexed.
 */

/*
 We can allocate memory dynamically with the "new" keyword.
 */

/*
 int main() {
 char c;     // Allocates 1 byte box somewhere in memory
 c = 'x';    // Puts the value into the allocated memory
 
 char* p1 = &c;  // p1 is a pointer to a character, and stores the address of the variable c
 char* p2 = p1;  // Now there's two pointers to the same box (i.e. one address pointed to by two pointers)
 char d = *p1;   // Dereferencing: Copy value pointed to by p1 (not the address of p1!) into d
 char* p3 = &d;  // Note that the address stored by p3 (its value) is different from the address stored by p1 and p2
 
 // Basically, char* does not create extra value boxes for access. But yes it contains a memory address of int type, so 4-byte space needed
 // cout << p1 << endl;
 // cout << p2 << endl;
 // cout << p3 << endl;
 // cout << *p1 << endl;
 // cout << *p2 << endl;
 // cout << *p3 << endl;
 
 // int arr[3](); // To do default filling, must do the heap way
 int arr[3] = {1}; // Will pad following elements with 0
 
 cout << arr[0] << endl;
 cout << arr[1] << endl;
 cout << arr[2] << endl;
 cout << arr[3] << endl; // How come no seg fault?
 for (int i = 0; i < 3; i++) arr[i] = 2*i;
 cout << *(arr) << endl;
 cout << *(arr+1) << endl; // When you +1 here, because this is int[], +1 -> +4 bytes
 cout << *(arr+2) << endl;
 cout << *(arr+3) << endl; // How come no seg fault?
 
 int n;
 cin >> n; // Size only known at runtime!
 int* brr = new int[n]; // brr is a pointer to the start of this array
 delete[] brr; // No need mention size because the size is stored somewhere else
 
 // For non-arrays, call new and delete without "[]"
 int* x = new int;
 int* y = x;
 *x = 10; // Cannot x=10 because you are pointing to address 10, you don't know what is inside there!
 cout << *y << endl;
 delete x; // Actually don't do this: Because you only delete the pointer, but the box is still there.
 *y = 15; // Why cannot do this!?!?
 // Don't double-delete because something else might belong there in the meantime
 // Possible explanation for "Why cannot do this!?!?" would be that deleting x removes the ownership of the box so y is rendered useless too
 return 0;
 }
 */

/*
 C++ ppl usually use vectors because arrays are so dangerous.
 
 Instead of <function_name>(double* values) {
 ...
 delete[] values; // Ded
 }
 
 Do a reference:
 <function_name>(double& values) {
 ...
 // No pointer arithmetic
 // Cannot delete because cannot allocate / free (important!)
 // No direct access to address
 }
 
 Reference is kind of like Java's reference.
 */

int* merge(int* A, int* B) {
    int i = 0;
    int j = 0;
    int sizeA = 0;
    int sizeB = 0;
    int totalSize = 0;
    
    while (A[i++] != 0) sizeA += 1; // Faster way is just int sizeA = 0; while (A[sizeA++] != 0);
    while (B[j++] != 0) sizeB += 1;
    totalSize = sizeA + sizeB;
    int* C = new int[totalSize+1]; // +1 to store 0
    
    i = 0;
    j = 0;
    int k = 0;
    while (i < sizeA && j < sizeB && k < totalSize) {
        if (A[i] <= B[j]) {
            C[k++] = A[i++];
        } else {
            C[k++] = B[j++];
        }
    }
    
    while (i < sizeA && k < totalSize) C[k++] = A[i++];
    while (j < sizeB && k < totalSize) C[k++] = B[j++];
    C[totalSize] = 0;
    return C;
}

int* mergeSort(int* C) { // Got a warning: All paths through this function will call itself. Why?
    int k = 0;
    int sizeC = 0;
    while (C[k++] != 0) sizeC += 1;
    
    int sizeA = floor(sizeC / 2);
    int sizeB = sizeC - sizeA;
    int* A = new int[sizeA + 1]; // +1 to store 0
    int* B = new int[sizeB + 1];
    
    k = 0;
    int i = 0;
    int j = 0;
    while (i < sizeA && k < sizeA) A[i++] = C[k++];
    A[sizeA] = 0;
    k = sizeA;
    while (j < sizeB && k >= sizeA && k < sizeB) B[j++] = C[k++];
    B[sizeB] = 0;
    
    return merge(mergeSort(A), mergeSort(B));
}

int* heapify(int* C, int sizeC) {
    // TODO: Finish this!
    // Call bubbleUp on half of the array
    return C;
}

int* heapSort(int* C) {
    int sizeC = 0;
    while (C[sizeC++] != 0);
    int* D = heapify(C, sizeC);
    // Pop from D here
    return C;
}

/*
 int main() {
 int x = 5;
 int& rx = x; // rx is an invisible arrow (cannot mutate)
 rx = 4; // Implicitly dereferencing! Different from pointers: *px = 4
 // cout << x << endl; // 4
 int A[4] = {1,5,9,0}; // Array initialization!
 int B[5] = {2,4,6,8,0};
 int D[4] = {5,9,1,0}; // Array initialization!
 int E[5] = {6,4,8,2,0};
 int* C = merge(A, B);
 for (int i = 0; i < 7; i++) {
 // cout << *(C+i) << endl;
 }
 int* F = merge(D, E);
 for (int i = 0; i < 7; i++) {
 cout << *(C+i) << endl;
 }
 delete[] C; // Only for dynamically allocated ones
 delete[] F;
 return 0;
 }
 */

/*
 Methods in class takes in an invisble first parameter, this (type is a pointer to Box)
 public     Anyone can access
 protected  Child classes can access
 private    Only this class can access
 */

class Box {
private: // Access specifier. Anyone can access anything in the class because of "public"
    double length;
    double breadth;
    double height;
    
public:
    Box(double l, double b, double h) {
        this->length = l;
        this->breadth = b;
        this->height = h;
    }
    
    double getVolume() {
        return length * breadth * height;
    }
    
    void setHeight(double h) { // Hidden parameter in signature: void setHeight(Box* this, double h)
        if (h >= 0) { // So that we will not assign height to meaningless values (e.g. negative height)
            height = h;
        }
    }
};

class FixedArray {
    int* arr;
    int length;
    
public:
    FixedArray(int n) {
        this->arr = new int[n];
        this->length = n;
    }
    
    // Destructor
    // "virtual" is similar to "abstract" in Java
    virtual ~FixedArray() {
        delete[] this->arr;
    }
    
    void setAllTo(int x) {
        for (int i = 0; i < length; i++) arr[i] = x;
    }
    
    // Can same function name, as long as parameter list is different (i.e. overloading)
    // "this" can be implicit when LHS and RHS are different in name
    FixedArray(FixedArray& o) { // Should use this signature to make o immutable: FixedArray(FixedArray const& o)
        this->length = o.length;
        for (int i = 0; i < this->length; i++) {
            this->arr[i] = o.arr[i];
        }
    }
    
    // Changing the meaning of assignment
    // So that FixedArray b = a; and b = a; <- this statement
    // Will do a copy as well
    FixedArray& operator=(FixedArray const& o) {
        FixedArray copy(length);
        for (int i = 0; i < length; i++) copy.arr[i] = o.arr[i];
        return copy; // Warning: Reference to stack memory associated with local variable 'copy' returned
    }
};

class Complex {
private:
    double x;
    double y;

public:
    Complex(double x, double y) {
        this->x = x;
        this->y = y;
    }
    Complex(Complex const& o) {
        this->x = o.x;
        this->y = o.y;
    }
    
    double modulus() {
        return sqrt(x*x + y*y);
    }
    double argument() {
        return atan2(x, y);
    }
    
    // Just "Complex other" is pass-by-value, so must duplicate and this is slow!
    // Operator "+" is overriden for this class
    Complex operator+(Complex const& o) {
        int sx = this->x + o.x;
        int sy = this->y + o.y;
        Complex sum(sx, sy);
        return sum;
    }
    
    // equalTo
    bool operator==(Complex const& o) {
        return this->x == o.x && this-> y == o.y;
    }
};

class DynamicArray {
public: // Idgaf here
    int* arr;
    int currLength;
    int maxLength;

public:
    DynamicArray(int maxLength) {
        this->maxLength = maxLength;
        currLength = 0;
        arr = new int[maxLength];
    }
    
    void add(int x) {
        if (currLength < maxLength) {
            arr[currLength] = x;
        } else {
            int newMaxLength = maxLength * 2;
            int* brr = new int[newMaxLength];
            for (int i = 0; i < maxLength; i++) brr[i] = arr[i];
            brr[maxLength] = x;
            maxLength = newMaxLength;
            arr = brr;
        }
        currLength += 1;
    }
    
    int remove() {
        if (currLength == 0) {
            return -1;
        } else {
            int popped = arr[currLength-1];
            currLength -= 1;
            if (currLength*4 < maxLength) {
                int newMaxLength = floor(maxLength / 2);
                int* brr = new int[newMaxLength];
                for (int i = 0; i < currLength; i++) brr[i] = arr[i];
                maxLength = newMaxLength; // Can optimize this part
                arr = brr;
            }
            return popped;
        }
    }
    
    // Should abstract away the resize function
    int remove(int pos) {
        if (currLength == 0) {
            return -1;
        } else {
            int popped = arr[pos];
            currLength -= 1;
            if (currLength*4 < maxLength) {
                int newMaxLength = floor(maxLength / 2);
                int* brr = new int[newMaxLength];
                // Can be optimized
                for (int i = 0; i < currLength; i++) brr[i] = arr[i];
                for (int j = pos; j < newMaxLength-1; j++) brr[j] = brr[j+1];
                maxLength = newMaxLength; // Can optimize this part
                arr = brr;
            }
            return popped;
        }
    }
};

// Example of R^3 vector is [1,2,3]
class Vector3 {
public:
    int* vec;
    int dim;
    
    Vector3(int* vec, int dim) {
        this->vec = vec;
        this->dim = dim;
    }
    
    Vector3 operator+(Vector3 const& o) {
        Vector3 newVec(new int[dim], dim);
        for (int i = 0; i < dim; i++) {
            newVec.vec[i] = vec[i] + o.vec[i];
        }
        return newVec;
    }
    
    Vector3 operator*(double c) {
        Vector3 newVec(new int[dim], dim);
        for (int i = 0; i < dim; i++) {
            newVec.vec[i] = vec[i] * c;
        }
        return newVec;
    }
    
    Vector3 operator*(Vector3 const& o) {
        Vector3 newVec(new int[dim], dim);
        for (int i = 0; i < dim; i++) {
            newVec.vec[i] = vec[i] * o.vec[i];
        }
        return newVec;
    }
};

int main() {
    int a(5);
    
    // There's only 2 boxes here
    Box boxA(5.0, 1.0, 1.0);
    Box* boxB = new Box(3.0, 2.0, 4.0); // new creates a pointer to a Box by: 1. Allocate memory, 2. Call constructor, 3. Return pointer to (1) (this)
    Box* boxC = boxB;
    Box& boxD = boxA;
    
    cout << a << endl;
    cout << boxA.getVolume() << endl;
    cout << boxB->getVolume() << endl; // Note that boxB is a pointer
    cout << (*boxB).getVolume() << endl; // This is like Java
    boxA.setHeight(100.0);
    boxB->setHeight(50.0);
    
    cout << boxC->getVolume() << endl;
    cout << boxD.getVolume() << endl; // boxD is a reference to boxA so there's implicit dereferencing and we can use dot notation
    
    // TODO: Fix all these
    /*
    FixedArray a(10);
    a.setAllTo(42);
    FixedArray b = a; // Shallow copy if you simply copy the pointer!
    FixedArray b(a); // Deep copy! :D
    b.setAllTo(420);
    */
    Complex z1(1.2, 3.4);
    Complex z2(5.6, 7.8);
    Complex z3 = z1 + z2;
    
    cout << "Hello, world!" << endl;
    
    DynamicArray da(2);
    for (int i = 0; i < 10; i++) da.add(i);
    cout << da.currLength << endl;
    cout << da.maxLength << endl;
    for (int i = 0; i < da.currLength; i++) cout << da.arr[i] << endl;
    
    cout << "remove pos" << endl;
    cout << da.remove(5) << endl;
    cout << da.currLength << endl;
    cout << da.maxLength << endl;
    
    for (int i = 0; i < 8; i++) da.remove();
    cout << da.currLength << endl;
    cout << da.maxLength << endl;
    for (int i = 0; i < da.currLength; i++) cout << da.arr[i] << endl;
    
    cout << "Final destination" << endl;
    int dim = 5;
    Vector3 vec(new int[dim] {1,2,3,4,5}, dim);
    vec = vec * 3;
    for (int i = 0; i < dim; i++) cout << vec.vec[i] << endl;
}
