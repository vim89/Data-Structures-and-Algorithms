#include<iostream>
#include<bits/stdc++.h>
#include <stdlib.h>
using namespace std;

void merge(int input_array[], int left_index, int middle_index, int right_index){
	int i = left_index;
	int j = middle_index + 1;
	int k = left_index;
	int temp_array[right_index];

	while(i<=middle_index && j<=right_index){
		if (input_array[i]<input_array[j])
			temp_array[k++] = input_array[i++];
		else
			temp_array[k++] = input_array[j++];
	}

	while(i<=middle_index)
		temp_array[k++] = input_array[i++];

	while(j<=right_index)
		temp_array[k++] = input_array[j++];

	for (int i = left_index; i <= right_index; ++i)
		input_array[i] = temp_array[i];
}

void merge_sort(int input_array[], int left_index, int right_index){
	if (left_index<right_index){
		int middle_index = left_index + (right_index - left_index) / 2;
		merge_sort(input_array, left_index, middle_index);
		merge_sort(input_array, middle_index+1, right_index);
		merge(input_array, left_index, middle_index, right_index);
	}
}

int main(int argc, char const *argv[])
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int input_array[100000];
	//srand(0); //For only positive random numbers
	for (int i = 0; i < 100000; ++i)
		input_array[i] = rand();
	
	int array_size = sizeof(input_array) / sizeof(input_array[0]);

	cout <<"Input array unsorted: ";
	for (int i = 0; i < array_size; ++i)
		cout <<input_array[i] <<", ";
	
	merge_sort(input_array, 0, array_size);
	
	cout <<"\n" <<"Output array sorted: ";
	for (int i = 0; i < array_size; ++i)
		cout <<input_array[i] <<", ";
	
	cout <<endl;
	return 0;
}