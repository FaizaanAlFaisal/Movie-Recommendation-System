#ifndef REDBLACKTREES_CPP
#define REDBLACKTREES_CPP

#include <iostream>

using namespace std;

enum class Colour : bool { Red, Black }; //define a user type Colour, Black corresponds to true, Red corresponds to false

//class declarations for printing functions
class Actor;
class Director;
class Show;
class Genre;
class Country;

//actual Red Black stuff code:
template <class T> class RBTNode //Node class for Red-Black Trees
{
public:
    T data;
    RBTNode<T>* leftChild;
    RBTNode<T>* rightChild;
    RBTNode<T>* parent;
    Colour colour;

    RBTNode<T>(T value, Colour c = Colour::Red) : data(value), leftChild(NULL), rightChild(NULL), parent(NULL), colour(c) {}
};

template <class T> class RedBlackTree
{
public:
    RBTNode<T>* root; //root of the tree
    RBTNode<T>* loc, * ploc; //pointers used for searching
    RBTNode<T>* targetNode; //retrieves address of most recently accessed node after insertion process
    //if a new node is *inserted* during insert() call, targetNode is that new node
    //if a node already exists with the same value as a node already in tree, targetNode is address of already existing node
    
    RedBlackTree<T>() : loc(NULL), ploc(NULL), root(NULL), targetNode(NULL) {}

    Colour GetColour(RBTNode<T>* node)
    {
        if (node == NULL) return Colour::Black;
        else return node->colour;
    }

    bool IsEmpty() //function to check if the tree is empty
    {
        return root == NULL; //return true or false for if root is equal to NULL
    }

    void InOrderPrint(RBTNode<T>* current) //pass address of root node to print
    {
        if (current != NULL) //if not a NULL node
        {
            InOrderPrint(current->leftChild); //print left subtree
            if (current->colour == Colour::Black) cout << " b"; //to display node colour 
            else cout << " r";
            cout << " " << current->data; //print current
            InOrderPrint(current->rightChild); //print right subtree
        }
        if (current == root) cout << endl; //when about to fully terminate, add a line
    }

    void PreOrderPrint(RBTNode<T>* current) //pass address of root node to print
    {
        if (current != NULL) //if not a NULL node
        {
            cout << " " << current->data; //print current
            PreOrderPrint(current->leftChild); //print left subtree
            PreOrderPrint(current->rightChild); //print right subtree
        }
        if (current == root) cout << endl; //when about to fully terminate, add a line
    }

    void PostOrderPrint(RBTNode<T>* current) //pass address of root node to print
    {
        if (current != NULL) //if not a NULL node
        {
            PostOrderPrint(current->leftChild); //print left subtree
            PostOrderPrint(current->rightChild); //print right subtree
            cout << " " << current->data; //print current
        }
        if (current == root) cout << endl; //when about to fully terminate, add a line
    }

    //assuming no duplicates allowed
    void Search(const T& key) //search for a node with value "key" in the tree, loc and ploc are assigned
    {
        //using an iterative approach
        if (!IsEmpty())
        {
            loc = root; //initialiize loc to root
            ploc = NULL; //initialize ploc to NULL
            while (loc != NULL) //while loc is not NULL
            {
                if (loc->data == key) break; //if value is found, end searching
                ploc = loc; //advance ploc
                if (key < loc->data) //traverse left child if key is less than data at loc
                    loc = loc->leftChild;
                else //otherwise traverse right child
                    loc = loc->rightChild;
            }
        }
    }

    void LeftRotate(RBTNode<T>* x) //function to rotate the tree left around a node x
    {
        RBTNode<T>* y = x->rightChild;
        x->rightChild = y->leftChild; //right child of x becomes left child of y
        if (y->leftChild != NULL) y->leftChild->parent = x; //if y has a left child, that child's parent is now x

        y->parent = x->parent; //parent of y is now previous parent of x

        if (x->parent == NULL) root = y; //y is either now the new root
        else if (x == x->parent->leftChild) x->parent->leftChild = y; //or left or right child of parent of x
        else x->parent->rightChild = y;

        y->leftChild = x; //relink x to tree as child of y
        x->parent = y; //parent of x is now y
    }

    void RightRotate(RBTNode<T>* x) //function to rotate the tree left around a node x
    {
        RBTNode<T>* y = x->leftChild;
        x->leftChild = y->rightChild; //left child of x becomes right child of y
        if (y->rightChild != NULL) y->rightChild->parent = x; //if y has a right child, that child's parent is x

        y->parent = x->parent; //parent of y is now the previous parent of x

        if (x->parent == NULL) root = y; //y is either now the root
        else if (x == x->parent->leftChild) x->parent->leftChild = y; //or left or right child of parent of x
        else x->parent->rightChild = y;

        y->rightChild = x; //relink x to be right child of y
        x->parent = y; //parent of x is now y
    }

    void InsertTreeFix(RBTNode<T>* current) //fix tree after insertion, current is red at every step
    {
        if (current != NULL) //only perform rebalancing if current is not NULL
        {
            RBTNode<T>* uncle; //uncle of current
            while (current != root && GetColour(current->parent) == Colour::Red) //while the colour of current's parent is red
            {
                if (current->parent == current->parent->parent->rightChild) //if parent is right child of grandparent node
                {
                    uncle = current->parent->parent->leftChild; //then uncle must be left child of grandparent node
                    if (GetColour(uncle) == Colour::Red) //if uncle is red
                    {
                        uncle->colour = Colour::Black; //set it to black
                        current->parent->colour = Colour::Black; //set parent to black
                        current->parent->parent->colour = Colour::Red; //set grandparent to red
                        current = current->parent->parent; //move current up to grandparent, who is now red and may have a red parent
                    }
                    else //if uncle is black
                    {
                        if (current == current->parent->leftChild) //special case of double rotation 
                        {
                            current = current->parent; //move current up the tree
                            RightRotate(current);
                        }
                        current->parent->colour = Colour::Black; //set parent to black
                        current->parent->parent->colour = Colour::Red; //set grandparent to red
                        LeftRotate(current->parent->parent); //balance tree
                    }
                }
                else //if parent of current is left child, mirror cases to above
                {
                    uncle = current->parent->parent->rightChild; //then uncle must be right child

                    if (GetColour(uncle) == Colour::Red) //if uncle is red
                    {
                        uncle->colour = Colour::Black; //then set uncle and parent to black
                        current->parent->colour = Colour::Black;
                        current->parent->parent->colour = Colour::Red; //set grandparent to red
                        current = current->parent->parent; //move current up the tree
                    }
                    else //if uncle is black
                    {
                        if (current == current->parent->rightChild) //check if special case of double rotation 
                        {
                            current = current->parent;
                            LeftRotate(current);
                        }
                        current->parent->colour = Colour::Black; //set parent to black
                        current->parent->parent->colour = Colour::Red; //set grandparent to red
                        RightRotate(current->parent->parent); //rotate right to balance tree
                    }
                }
            }
            root->colour = Colour::Black; //ensure root is always coloured black
        }
    }

    void Insert(const T& key) //insert node and balance/manage redness-blackness
    {
        if (IsEmpty()) //if tree is empty
        {
            root = new RBTNode<T>(key, Colour::Black); //insert new black node at root
            targetNode = root; //root cointains most recently accessed node
        }
        else
        {
            Search(key); //search for the value given, loc and ploc are now initialized accordingly
            if (loc != NULL) //if the value is found
                targetNode = loc; //targetNode contains address of existing node
            else //value is not found, proceed to insert node as leaf
            {
                RBTNode<T>* newNode = new RBTNode<T>(key); //create new red node
                if (key < ploc->data) ploc->leftChild = newNode; //if less than ploc, make left child
                else ploc->rightChild = newNode; //otherwise make it right child
                newNode->parent = ploc; //ploc is parent of new node
                newNode->rightChild = NULL;
                newNode->leftChild = NULL;

                targetNode = newNode; //targetNode takes address of most recently inserted node
                if (GetColour(newNode->parent) == Colour::Red) InsertTreeFix(newNode); //fix tree from newNode and up
            }
        }
    }

    //printing function templates, coded in source.cpp
    void PrintMoviesPlayedInBy(RBTNode<Actor>* actor);
    void PrintMoviesDirectedBy(RBTNode<Director>* director);
    void PrintGenresFor(RBTNode<Show>* show); 
};
//deletion code exists for this attempt but is non-functional, another one exists that is similar to the geeksforgeeks 
//implementation. additionally, this project does not actually require a deletion function for the RBTree, so it was excluded

#endif // !REDBLACKTREES_CPP