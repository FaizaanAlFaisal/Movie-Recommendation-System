#ifndef DOUBLYLINKEDLIST_CPP
#define DOUBLYLINKEDLIST_CPP

//using exclusively as deque for sake of project, just that backend implementation is doubly linked list for O(1) insertions
//and deletions and front and back

#include <iostream>

using namespace std;

template <class T> class DLLNode
{
public:
	T data;
	DLLNode<T>* next; //points to node after this node in the list
	DLLNode<T>* prev; //points to predecessor of this node in the list

	DLLNode(T value) //parameterized constructor
	{
		data = value;
		next = NULL;
		prev = NULL;
	}
};


template <class T> class DoublyLinearList
{
public:
	DLLNode<T>* start; //used to keep track of first and last nodes in the list
	DLLNode<T>* last;

	DLLNode<T>* loc; //used in the search functions to aid in insertion and deletion operations
	DLLNode<T>* ploc;

	int numElements;

	DoublyLinearList() //constructor to initialize all pointers to null
	{
		start = NULL;
		last = NULL;
		loc = NULL;
		ploc = NULL;
		numElements = 0;
	}


	bool IsEmpty() //function to check if list is empty
	{
		return start == NULL;
	}

	int size() //return number of elements within list
	{
		return numElements;
	}

	void printList(bool direction = true) //if true, prints from start to last. if false, prints from last to start
	{
		if (!IsEmpty()) //if the list is not empty
		{
			DLLNode<T>* temp;

			if (direction == true)
			{
				temp = start;
				cout << " ";
				while (temp != NULL) //print from start to last
				{
					cout << temp->data << "  ";
					temp = temp->next;
				} //print all values in list
				cout << "\033[0m" << endl; //move onto next line automatically
			}

			else
			{
				temp = last;
				cout << " ";
				while (temp != NULL) //print from last to start
				{
					cout << temp->data << "  ";
					temp = temp->prev;
				} //print all values in list
				cout << "\033[0m" << endl; //move onto next line automatically
			}
		}

		else
			cout << "\033[0m The List is Empty " << endl;
	}


    //unused for project, since dll is being used as deque
	void Search(T value)
	{
		loc = NULL;
		ploc = NULL; //force set loc and ploc to null for sake of ensuring no errors in logic

		if (!IsEmpty())
		{
			loc = start; //initialize loc to start

			while (loc != NULL && loc->data < value) //while loc is not past the last element in the list and the data is less than the key in value
			{
				ploc = loc; //advance both ploc and loc
				loc = loc->next;
			}

			if (loc != NULL && loc->data != value) //if loc was non-NULL and the data value was not found, this means that the logical position
			{ //of value is between loc and ploc, but does not actually exist in the list
				loc = NULL; //used to signify that value is not found
			}
		}
		//otherwise do nothing
	}

    T front() //return value at front
	{
		return start->data;
	}

    T end() //return value at end
	{
		return last->data; 
	}

    void push_front(T value) //insert value at front
	{
		DLLNode<T>* newNode = new DLLNode<T>(value);
		numElements++;
		if (IsEmpty()) //if the list is empty, then the new node is both first and last nodes of the list
		{
			start = newNode;
			last = newNode;
		}

		else //if list is not empty
		{
			newNode->next = start; //connect next pointer of new node to start
			start->prev = newNode; //connect prev pointer of previously first node to new node
			start = newNode; //inserted element is now the first node
		}
	}


    void push_back(T value) //insert value at end
	{
		DLLNode<T>* newNode = new DLLNode<T>(value);
		numElements++;
		if (IsEmpty()) //if the list is empty, then inserting a new node will make it the first and last elements of the list
		{
			start = newNode;
			last = newNode;
		}

		else //if the list is not empty
		{
			last->next = newNode; //newNode is inserted after previously last node
			newNode->prev = last; //connect the prev pointer of the new node to formerly last node
			last = newNode; //reassign value of last pointer to new ndoe
		}
	}


    //unused for project, since dll is being used as deque
	void InsertSorted(T value) //insert values sorted in an ascending order
	{
		Search(value);

		if (loc == NULL) //ie value was not found in the list
		{
			if (ploc == NULL)
				push_front(value);

			else if (ploc == last)
				push_back(value);

			else
			{
				DLLNode<T>* newNode = new DLLNode<T>(value);

				newNode->next = ploc->next; //next pointer of new node is assigned to node logically after new node
				(ploc->next)->prev = newNode; //node logically after new node points to newNode with its previous pointer
				ploc->next = newNode;
				newNode->prev = ploc;
			}
			numElements++;
		}

		else return; //do nothing if the value is a duplicate value
	}


	void pop_front() //delete first node of the list
	{
		if (!IsEmpty()) //if the list is not empty
		{
			DLLNode<T>* temp = start;
			numElements--;
			if (start == last) //ie only one node in the list
			{
				delete temp;
				start = NULL;
				last = NULL;
			}
			else
			{
				start = start->next;
				start->prev = NULL;
				temp->next = NULL;
				delete temp;
			}
		}
		//otherwise do nothing, since no front node exists
	}


	void pop_back() //delete last node of the list
	{
		if (!IsEmpty()) //if the list is not empty
		{
			DLLNode<T>* temp = last;
			numElements--;

			if (start == last) //ie only one node in the list
			{
				delete temp;
				start = NULL;
				last = NULL;
			}
			else //if more than one elements in the list, then logic can be generalized
			{
				last = last->prev;
				last->next = NULL;
				temp->prev = NULL;
				delete temp;
			}
		}
		//otherwise do nothing, since no front node exists
	}

    //unused for project, since dll is being used as deque
	void DeleteValue(T value) 
	{
		if (IsEmpty()) return;

		Search(value);

		if (loc != NULL) //if loc is not equal to null, that means a valid value has been found
		{
			if (ploc == NULL) //if node to be deleted is first node
				pop_front(); //delete the front node

			else if (loc == last) //if node to be deleted is the last node
				pop_back(); //delete the last node

			else //if the node is in the middle of the list:
			{
				ploc->next = loc->next; //node after ploc after deletion is the successor of node at loc
				(loc->next)->prev = ploc; //the node after logic now points to ploc instead of loc with "prev" pointer
				loc->next = NULL;
				loc->prev = NULL;
				delete loc;
			}
			numElements--;
		}
	}


	void clear() //clear list 
	{
		if (IsEmpty()) return; //do nothing if the list is empty

		while (!IsEmpty()) //while the list is not empty
			pop_front(); //delete the front node
	}
};

#endif // !DOUBLYLINKEDLIST_CPP
