#ifndef VECTORSIMPLEMENTATION_CPP
#define VECTORSIMPLEMENTATION_CPP

#include <iostream>
#include <vector>
using namespace std;

template <class T> class Vector
{
public:
	int capacity; //max storage of vector
	int numElements; //number of elements currently within vector
	T* arr; //data

	Vector(int Size = 10) //constructor to receive initial value of capacity
	{
		capacity = Size;
		numElements = 0;
		arr = new T[capacity];
	}
	
	//cannot free up memory after deletion in case of addresses being stored in array, as those get lost as well, which is not helpful
	//~Vector() 
	//{
	//	delete[] arr; //free up memory
	//}

	bool empty() //check if array is empty/entirely zero, return true if so, otherwise false
	{
		return numElements == 0;
	}

	bool full() //check if array is full/entirely non-zero elements, return true if so, otherwise false
	{
		return numElements == capacity;
	}

	int size() //return number of elements of array
	{
		return numElements;
	}

	//no check for following two functions if array is empty, use carefully
	T front() //return front element of array
	{
		return arr[0];
	}

	T end() //return last element
	{
		return arr[numElements - 1];
	}

	void printList()
	{
		if (!empty())
		{
			for (int i = 0; i < numElements; i++)
				cout << " " << arr[i];
			cout << "\n";
		}
	}

	void push_back(const T& key) //insert a value at back of array, no need to perform shifts
	{
		/*T* newVal = new T(key);*/ 
		DynamicExpansion(); //expand array if full
		arr[numElements++] = key; //last element previously was at numElements - 1, meaning that new element must be at numElements
	}

	void pop_back() //remove last element of array
	{
		numElements--; //simply decrementing numElements allows us to logically remove value from list
		DynamicReduction();
	}

	void erase(int index) // deletes a value if a user enters a valid position (1 <= pos <= size of a list)
	{
		if (index < size && index >= 0) {
			for (int i = index; i < size - 1; i++)
				arr[i] = arr[i + 1];
			numElements--;
			DynamicReduction();
		}
	}

	void DynamicExpansion() //Increases capacity of the array when the list becomes full.
	{
		if (full())
		{
			T* tempArray = new T[capacity]; //create a temporary array initialized to 0
			int tempSize = capacity;

			for (int i = 0; i < tempSize; i++)
				tempArray[i] = arr[i];
			delete[] arr; //deallocate array stored on arr

			capacity *= 1.5; //expand capacity of array by 50%
			capacity += 2; //incase increasing capacity by 50% does not result in a new slot being added, add slots anyway

			arr = new T[capacity]; //create a new array of increased capacity, all values initialized to 0
			for (int i = 0; i < tempSize; i++)
				arr[i] = tempArray[i];
			delete[] tempArray;
		}
	}

	void DynamicReduction()  //decreases capacity of the array when the capacity of a list becomes less than 50% after deletion operation
	{
		double percentSize = (double)numElements / (double)capacity; //calculate percentage of array empty

		if (percentSize < 0.5) //if over half of the array is empty, then reduce capacity of array by 50%
		{
			capacity /= 2; //divide capacity by 2
			capacity += 1; //in case capacity rounding down leaves it out of bounds

			T* tempArray = new T[capacity]; //create a temporary array of capacity "capacity", initialized to 0
			for (int i = 0; i < capacity; i++) //copy current array to temp array
				tempArray[i] = arr[i];
			delete[] arr; //deallocate memory of array stored on arr

			arr = new T[capacity]; //create a arr of new, smaller capacity

			for (int i = 0; i < capacity; i++) //copy values to fill the new smaller array
				arr[i] = tempArray[i];
			delete[] tempArray; //deallocate memory stored on temp array
		}
		//else do nothing
	}

	void clear()
	{
		numElements = 0;
		capacity = 10;
		delete[] arr;
		arr = new T[capacity];
	}
};

#endif // !VECTORSIMPLEMENTATION_CPP