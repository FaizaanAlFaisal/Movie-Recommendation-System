#ifndef MERGESORT_CPP
#define MERGESORT_CPP

#include <iostream>
#include "VectorImplementation.cpp"

template <class T> void Merge(T* input, int leftFirst, int leftLast, int rightFirst, int rightLast)
{
	int tempFirst = leftFirst;
	int index = 0;
	
	Vector<T> tempArray(rightLast - leftFirst + 1); //auto deletes at the end of functional call

	//loop to make comparisons of left and right half, while storing them in order in a temp array
	while (leftFirst <= leftLast && rightFirst <= rightLast)
	{
		if (input[leftFirst] > input[rightFirst])
			tempArray.arr[index++] = input[leftFirst++];
		else
			tempArray.arr[index++] = input[rightFirst++];
	}
	//loop to empty left half into temp array
	while (leftFirst <= leftLast) tempArray.arr[index++] = input[leftFirst++];
	//loop to empty right half into temp array
	while (rightFirst <= rightLast)  tempArray.arr[index++] = input[rightFirst++];
	//loop to copy values over to original array
	for (index = tempFirst; index <= rightLast; index++) input[index] = tempArray.arr[index - tempFirst]; 
}

template <class T> void MergeSort(T* input, int first, int last)
{
	if (first < last)
	{
		int middle = (first + last) / 2; //determine middle point of array
		MergeSort<T>(input, first, middle); //merge sort left half 
		MergeSort<T>(input, middle + 1, last); //merge sort right half
		Merge<T>(input, first, middle, middle + 1, last); //combine and sort both halves 
	}
}

#endif 