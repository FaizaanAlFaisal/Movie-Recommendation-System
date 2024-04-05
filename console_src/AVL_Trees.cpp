#include <iostream>

using namespace std;

template <class T> class AVLNode //Node class for BST
{
public:
    T data; //template data, generalizes code for many classes
    AVLNode<T>* leftChild;
    AVLNode<T>* rightChild;
    int height; //reduces computational complexity, since each node is inserted at height 0
    //simply perform basic arithmetic to compute height, instead of using a recursive function

    AVLNode(T value) : data(value), leftChild(NULL), rightChild(NULL), height(0) {}
    //parameterized constructor for AVLNode
};

template <class T> class AVLTree
{
public:

    AVLNode<T>* root; //the root node of the BST
    AVLNode<T>* targetNode; //keeps track of which nodes are required for pointers
    //do not need loc and ploc as insertions and deletions are done recursively

    AVLTree() : root(NULL) {} //default constructor

    bool IsEmpty() //function to check if the tree is empty
    {
        return root == NULL; //return true or false for if root is equal to NULL
    }

    void InOrderPrint(AVLNode<T>* current) //pass address of root node to print
    {
        if (current != NULL) //if not a NULL node
        {
            InOrderPrint(current->leftChild); //print left subtree
            cout << " " << current->data; //print current
            InOrderPrint(current->rightChild); //print right subtree
        }
        if (current == root) cout << endl; //when about to fully terminate, add a line
    }

    void PreOrderPrint(AVLNode<T>* current) //pass address of root node to print
    {
        if (current != NULL) //if not a NULL node
        {
            cout << " " << current->data; //print current
            PreOrderPrint(current->leftChild); //print left subtree
            PreOrderPrint(current->rightChild); //print right subtree
        }
        if (current == root) cout << endl; //when about to fully terminate, add a line
    }

    void PostOrderPrint(AVLNode<T>* current) //pass address of root node to print
    {
        if (current != NULL) //if not a NULL node
        {
            PostOrderPrint(current->leftChild); //print left subtree
            PostOrderPrint(current->rightChild); //print right subtree
            cout << " " << current->data; //print current
        }
        if (current == root) cout << endl; //when about to fully terminate, add a line
    }

    int Height(AVLNode<T>* node) //simple function to return height member, allows NULL nodes to have height -1
    {
        if (node == NULL) return -1; //return -1 for height if node is null
        else return node->height; //otherwise directly return height of node
    }


    //max() is a standard function in iostream
    AVLNode<T>* RotateRight(AVLNode<T>* x) //rotate tree right about x
    {
        AVLNode<T>* y = x->leftChild; //y is the left child of x
        x->leftChild = y->rightChild; //the right child of y is linked to left of x, which is now free
        y->rightChild = x; //the right child of y is now x
        if (x == root) root = y; //if x was the root, y is new root
        x->height = max(Height(x->leftChild), Height(x->rightChild)) + 1; //re-evaluate heights of x and y
        y->height = max(Height(x->leftChild), Height(x->rightChild)) + 1;
        return y; //return y, as we will traverse up from here
    }


    AVLNode<T>* RotateLeft(AVLNode<T>* x) //rotate tree left about x
    {
        AVLNode<T>* y = x->rightChild; //y is right child of x
        x->rightChild = y->leftChild; //the left child of y is relinked to right child of x
        y->leftChild = x; //x is now the left child of y
        if (x == root) root = y; //if x was the root, y is new root
        x->height = max(Height(x->leftChild), Height(x->rightChild)) + 1;
        y->height = max(Height(y->leftChild), Height(y->rightChild)) + 1;
        return y; //return y, as we will traverse up from here
    }


    AVLNode<T>* Rebalance(AVLNode<T>* current) //rebalance tree around current node
    {
        int balanceFactor = Height(current->leftChild) - Height(current->rightChild); //determine balance factor of current node
        //difference between left and right subtree heights is balance factor

        if (balanceFactor == -2) //right subtree of current is heavier
        {
            AVLNode<T>* y = current->rightChild; //y is right child of x
            if (Height(y->leftChild) > Height(y->rightChild)) //in the case that left subtree of y is heavier
                current->rightChild = RotateRight(y); //rotate right around y
            current = RotateLeft(current); //rotate left around x in both cases 
        }
        else if (balanceFactor == 2) //left subtree of current is heavier
        {
            AVLNode<T>* y = current->leftChild; //y is left child since left subtree is heavier
            if (Height(y->rightChild) > Height(y->leftChild)) //in the case that right subtree of y is heavier
                current->leftChild = RotateLeft(y); //rotate left around y
            current = RotateRight(current); //rotate right around x in both cases
        }
        //re-evaluate height
        current->height = max(Height(current->leftChild), Height(current->rightChild)) + 1;
        return current; //otherwise do nothing and return current
    }


    void Insert(const T& key) //calling function to make main code simpler
    {
        //making the parameters "const T &key" makes it so that the value "key" is not duplicated on function call, saves memory
        //passed by refernce and remains unchangeable for sake of insertion and deletion functions, since we never modify key value
        InsertNode(root, key);
    }

    AVLNode<T>* InsertNode(AVLNode<T>* current, const T& key) //initial current is the root of the subtree/tree 
    {
        if (IsEmpty()) //in the case the tree is empty
        {
            root = new AVLNode<T>(key); //create a new node at root
            targetNode = root;
            return root; //and return address of root
        }
        //no need for a search function since insertion is a recursive procedure anyway, simply compare key in this function
        if (current == NULL) //if current reaches a null node, this is logical position of new node
        {
            AVLNode<T>* newNode = new AVLNode<T>(key);
            targetNode = newNode;
            return newNode; //create and return address of new node
        }
        //search for logical location of value
        else if (key < current->data)
            current->leftChild = InsertNode(current->leftChild, key);
        else if (key > current->data)
            current->rightChild = InsertNode(current->rightChild, key);
        else //if value is found, do no insertion
        {
            targetNode = current; //set target to current, we have access to repeat node pointer
            return current;
        }

        return Rebalance(current); //rebalance the sub-tree rooted at current
    }


    AVLNode<T>* SuccessorNode(AVLNode<T>* current, int identifier = 0) //used to determine the logical successor of the parent of "current"
    {
        AVLNode<T>* temp = NULL; //this will hold address of successor node
        if (identifier == 0 && current->leftChild == NULL)
            return current;
        if (current->leftChild != NULL)
        {
            temp = SuccessorNode(current->leftChild, 1);
            if (temp == NULL) //uses the NULL identifier to determine address of successor node
            {
                temp = current->leftChild; //save address of successor node
                current->leftChild = temp->rightChild; //unlink successor node from tree
                //relink right child of successor node if it exists
            }
        }
        else
            return NULL; //base case, NULL is an identifier for which node is successor
        //re-evaluate heights:
        current->height = max(Height(current->leftChild), Height(current->rightChild)) + 1;
        Rebalance(current); //since the successor node is unlinked, nodes may become unbalanced
        return temp;
    }

    AVLNode<T>* Delete(AVLNode<T>* current, const T& key) //recursive deletion function that also balances tree
    {
        if (current == NULL) return NULL; //checks for tree emptiness and node not found condition

        if (key < current->data) //go left if key less than current
            current->leftChild = Delete(current->leftChild, key);
        else if (key > current->data) //go right if key greater than current
            current->rightChild = Delete(current->rightChild, key);
        else //node found
        {
            //leaf node case:
            if (current->leftChild == NULL && current->rightChild == NULL)
            {
                if (current == root) root = NULL;
                delete current;
                return NULL;
            }
            //node to delete only has left subtree/child
            else if (current->leftChild == NULL || current->rightChild == NULL)
            {
                //using conditional assignment to shorten the code
                // current->leftChild is a boolean operation as it is a pointer. returns true if not NULL, false if NULL
                AVLNode<T>* temp = (current->leftChild) ? current->leftChild : current->rightChild;
                if (current == root) root = (current->leftChild) ? current->leftChild : current->rightChild;
                delete temp;
                return current;
            }
            else
            {
                AVLNode<T>* successor = SuccessorNode(current->rightChild); //determines successor node and fixes heights of subtree
                successor->leftChild = current->leftChild;
                if (current->rightChild != successor) successor->rightChild = current->rightChild;
                if (current == root) root = successor;
                delete current;
                return Rebalance(successor);
            }
        }
        return Rebalance(current); //rebalance at end of recursive steps
    }


    void DestroyTree(AVLNode<T>* current) //delete any tree with root at current
    {
        if (current != NULL) //post order traversal
        {
            DestroyTree(current->leftChild);
            DestroyTree(current->rightChild);
            current->leftChild = current->rightChild = NULL; //clear pointers
            if (current == root) root = NULL; //make root point to nothing, otherwise it would point to garbage
            delete current; //delete current node after traversing left and right subtrees
        }
    }

    int EvaluateHeight(AVLNode<T>* current) //determine max height of tree
    {
        if (current != NULL) //base case check
            return max(EvaluateHeight(current->leftChild), EvaluateHeight(current->rightChild)) + 1; //return tallest subtree + 1
        else return -1; //if node is null, return -1
    }
};