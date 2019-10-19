#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//branching factor
//#define FANOUT 100
//number of keys per node
//#define NODE_SIZE 50
//number of pointers per node
//#define PTR_ARR_SIZE 51

//branching factor
#define FANOUT 4
//number of keys per node
#define NODE_SIZE 3  
//number of pointers per node
#define PTR_ARR_SIZE 4


/* 
Designing your C Structs for B+Tree nodes (Chapter 10.3.1)
How will you represent a B+Tree as a C Struct (or series of C structs that work together)? There are many valid ways to do this part of your design, and we leave it open to you to try and tune this as you progress through the project.
How will you account for a B+Tree node being an internal node or a leaf node? Will you have a single node type that can conditionally be either of the two types, or will you have two distinct struct types?
How many children does each internal node have? This is called the fanout of the B+Tree.
What is the maximum size for a leaf node? How about for an internal node?
What is the minimum threshold of content for a node, before it has to be part of a rebalancing?
*/

// TODO: here you will need to define a B+Tree node(s) struct(s)


//declaring node struct for nodes
struct Node{
    int keys[NODE_SIZE];
    int keyPos; //rightmost empty position in keys
    int values[NODE_SIZE];
    struct Node * ptrs[PTR_ARR_SIZE];
    int ptrPos; //rightmost empty position in ptrs
    struct Node * prevPtr; //pointer to node to the left of this node on the same level
    struct Node * nextPtr;  //pointer to node to the right of this node on the same level
    struct Node * upperPtr; //pointer to parent node
    int isALeafNode;
};


/* 
    Declaring the root and pointer to the root of the tree
 */

struct Node *rootPtr, root;


/* The following are methods that can be invoked on B+Tree node(s).
 * Hint: You may want to review different design patterns for passing structs into C functions.
 */

void initializeUpperNode(struct Node node, struct Node *nodePtr){
	printf("%s", "hello world");
    nodePtr = &node;
    int i;
    for (i = 0; i < NODE_SIZE; ++i)
    {
        nodePtr->keys[i] = 0;
    }
    for (i = 0; i < NODE_SIZE; ++i)
    {
        nodePtr->values[i] = 0;
    }
    for (i = 0; i < PTR_ARR_SIZE; ++i)
    {
        nodePtr->ptrs[i] = NULL;
    }
    //struct nodePtr root;
    nodePtr->keyPos = 0;
    nodePtr->ptrPos = 0;
    nodePtr->prevPtr = NULL;
    nodePtr->nextPtr = NULL;
    nodePtr->upperPtr = NULL;
    nodePtr->isALeafNode = 0;
};

void initializeLeafNode(struct Node node, struct Node *nodePtr){
    nodePtr = &node;
    int i;
    for (i = 0; i < NODE_SIZE; ++i)
    {
        nodePtr->keys[i] = 5;
        printf("%d\n", nodePtr->keys[i]);
        printf("hello");
    }
    for (i = 0; i < NODE_SIZE; ++i)
    {
        nodePtr->values[i] = 0;
    }
    for (i = 0; i < PTR_ARR_SIZE; ++i)
    {
        nodePtr->ptrs[i] = NULL;
    }
    nodePtr->keyPos = 0;
    nodePtr->ptrPos = 0;
    nodePtr->prevPtr = NULL;
    nodePtr->nextPtr = NULL;
    nodePtr->upperPtr = NULL;
    nodePtr->isALeafNode = 1;
};


/* FIND (Chapter10.4)
This is an equality search for an entry whose key matches the target key exactly.
How many nodes need to be accessed during an equality search for a key, within the B+Tree? 
*/



// TODO: here you will need to define FIND/SEARCH related method(s) of finding key-values in your B+Tree.

//Quick sort algorithm
void quicksort(int number[],int first,int last){
    int i, j, pivot, temp;
    if(first<last){
        pivot=first;
        i=first;
        j=last;
        while(i<j){
            while(number[i]<=number[pivot]&&i<last)
            i++;
            while(number[j]>number[pivot])
            j--;
            if(i<j){
            temp=number[i];
            number[i]=number[j];
            number[j]=temp;
            }
        }
        temp=number[pivot];
        number[pivot]=number[j];
        number[j]=temp;
        quicksort(number,first,j-1);
        quicksort(number,j+1,last);
    }
}

//Quick sort algorithm for Node struct pointers array
void quicksortPointers(struct Node array[],int first,int last){
    int i, j, pivot;
    struct Node temp;
    if(first<last){
        pivot=first;
        i=first;
        j=last;
        while(i<j){
            while(array[i].keys[0]<=array[pivot].keys[0]&&i<last)
            i++;
            while(array[j].keys[0]>array[pivot].keys[0])
            j--;
            if(i<j){
            temp=array[i];
            array[i]=array[j];
            array[j]=temp;
            }
        }
        temp=array[pivot];
        array[pivot]=array[j];
        array[j]=temp;
        quicksortPointers(array,first,j-1);
        quicksortPointers(array,j+1,last);
    }
}

/*
//Quick sort algorithm for Node struct pointers array
void quicksortPointers(struct Node * array[],int first,int last){
    int i, j, pivot, temp;
    if(first<last){
        pivot=first;
        i=first;
        j=last;
        while(i<j){
            while(array[i].keys[0]<=array[pivot].keys[0]&&i<last)
            i++;
            while(array[j]>array[pivot])
            j--;
            if(i<j){
            temp=array[i];
            array[i]=array[j];
            array[j]=temp;
            }
        }
        temp=array[pivot];
        array[pivot]=array[j];
        array[j]=temp;
        quicksort(array,first,j-1);
        quicksort(array,j+1,last);
    }
}

//This function sorts a non-leaf node's array of keys
void sortUpperNode(Node * node){
    quicksort(node.keys);
    quicksort(node.values);
}

//This function sorts a leaf node's array of keys
void sortLeafNode(Node * node){
    quicksort(node.keys);
}

//This function splits a non-leaf node 
void splitUpperNode(Node * node, int key){

}
//This function splits a leaf node

//This function inserts a key into a non-leaf node
void insertIntoUpperNode(Node * node, int key){
    if (node.keyPos == NODE_SIZE)
        
    {
        splitUpperNode(node, key);
    }else{
        node.keys[node.keyPos] = key;
        node.keyPos += 1;
    }
}

// This function inserts a key into a leaf node
void insertIntoUpperNode(Node * node, int key, int value){
    if (node.keyPos == NODE_SIZE)
    {
        splitLeafNode(node, key, value);
    }else{
        node.keys[node.keyPos] = key;
        node.values[node.keyPos] = value;
        node.keyPos += 1;
    }
}
*/

/* INSERT (Chapter 10.5)
How does inserting an entry into the tree differ from finding an entry in the tree?
When you insert a key-value pair into the tree, what happens if there is no space in the leaf node? What is the overflow handling algorithm?
For Splitting B+Tree Nodes (Chapter 10.8.3)
*/

void insert(key, value){
    
}

// TODO: here you will need to define INSERT related method(s) of adding key-values in your B+Tree.


/* BULK LOAD (Chapter 10.8.2)
Bulk Load is a special operation to build a B+Tree from scratch, from the bottom up, when beginning with an already known dataset.
Why might you use Bulk Load instead of a series of inserts for populating a B+Tree? Compare the cost of a Bulk Load of N data entries versus that of an insertion of N data entries? What are the tradeoffs?
*/

// TODO: here you will need to define BULK LOAD related method(s) of initially adding all at once some key-values to your B+Tree.
// BULK LOAD only can happen at the start of a workload


/*RANGE (GRADUATE CREDIT)
Scans are range searches for entries whose keys fall between a low key and high key.
Consider how many nodes need to be accessed during a range search for keys, within the B+Tree?
Can you describe two different methods to return the qualifying keys for a range search? 
(Hint: how does the algorithm of a range search compare to an equality search? What are their similarities, what is different?)
Can you describe a generic cost expression for Scan, measured in number of random accesses, with respect to the depth of the tree?
*/

// TODO GRADUATE: here you will need to define RANGE for finding qualifying keys and values that fall in a key range.


void printKeys(struct Node node){
	int i;
    for (i = 0; i < NODE_SIZE; ++i)
    {
        printf("%d\n", node.keys[i]);
    }
}


int main(){
	if (&root==NULL){
		initializeLeafNode(root, rootPtr);
        //Test for quicksortPointers() function
        int i;
        srand(time(0));
        for (i = 0; i < NODE_SIZE; ++i)
        {
            root.keys[i] = 4;
        }
		//printKeys(root);
		printf("hell");
	}
    
    return 0;
}
