#include "stdafx.h"
#include "utility.h"

#define Rows 4000
#define Cols 25

void insertion_sort(short int arr[], int length)
{	
	int j;
	short int temp;
	for (int i = 0; i < length; i++)
	{
		j = i;
		while (j > 0 && arr[j] < arr[j - 1])
		{
			temp = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = temp;
			j--;
		}
	}
}

void main()
{	
	clock_t tStart = clock(); //Timer started
	int k = 0;
	short int A[Rows][Cols], Shift[Rows][Cols+1], B[100000], C[4000]; //2-D arrays declared
	ifstream myfile("test.txt"); //Taking the input file
	while (!myfile.eof())
		for (int i = 0; i < 100000; i++)
			myfile >> B[i]; //Copying the contents of the text file
	std::ofstream outfile;
	outfile.open("Part1Data.txt", std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Cols; j++)
				A[i][j] = B[k++];
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
			outfile << A[i][j] << " ";
		outfile << endl; //Creating r*s matrix of the input data
	}
	//Column sort algorithm starts here
	for (int j = 0; j < Cols; j++)
	{
		for (int i = 0; i < Rows; i++)
			C[i] = A[i][j];
		insertion_sort(C, 4000);
		for (k = 0; k < Rows; k++)
			A[k][j] = C[k];
	}
	std::ofstream tempfile;
	tempfile.open("sort1col.txt", std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
			tempfile << A[i][j] << " ";
		tempfile << endl;
	}
	//Step-1 ends here
	std::ofstream transfile;
	transfile.open("trans.txt", std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < Cols; i++)
	{
		for (int j = 0; j < Rows; j++)
			transfile << A[j][i] << " ";
		transfile << endl;
	}
	//Step-2 ends here
	for (int j = 0; j < Rows; j++)
	{
		for (int i = 0; i < Cols; i++)
			C[i] = A[j][i];
		insertion_sort(C, 25);
		for (k = 0; k < Cols; k++)
			A[j][k] = C[k];
	}
	std::ofstream tempsfile;
	tempsfile.open("sort2col.txt", std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < Cols; i++)
	{
		for (int j = 0; j < Rows; j++)
			tempsfile << A[j][i] << " ";
		tempsfile << endl;
	}
	//Step-3 ends here
	std::ofstream rev_file;
	rev_file.open("rev_step2.txt", std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
			rev_file << A[i][j] << " ";
		rev_file << endl;
	}
	//Step-4 ends here
	for (int j = 0; j < Rows; j++)
	{
		for (int i = 0; i < Cols; i++)
			C[i] = A[j][i];
		insertion_sort(C, 25);
		for (k = 0; k < Cols; k++)
			A[j][k] = C[k];
	}
	std::ofstream sortfile;
	sortfile.open("sort3col.txt", std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
			sortfile << A[i][j] << " ";
		sortfile << endl;
	}
	//Step-5 ends here

	std::ofstream shift1;
	shift1.open("shift1.txt", std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < Rows/2; i++)
		Shift[i][0] = -32766;
	for (int i = Rows/2; i < Rows; i++)
		Shift[i][0] = 32767;
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Cols; j++)
			Shift[i][j+1] = A[i][j];
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols+1; j++)
			shift1 << Shift[i][j] << " ";
		shift1 << endl;
	}
	//Step-6 ends here
	for (int j = 0; j < Cols+1; j++)
	{
		for (int i = 0; i < Rows; i++)
			C[i] = Shift[i][j];
		insertion_sort(C, 4000);
		for (k = 0; k < Rows; k++)
			Shift[k][j] = C[k];
	}
	std::ofstream shift_sortfile;
	shift_sortfile.open("shift_sortfile.txt", std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols + 1; j++)
			shift_sortfile << Shift[i][j] << " ";
		shift_sortfile << endl;
	}
	//Step-7 ends here
	std::ofstream Final_sort;
	Final_sort.open("Results.txt", std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Cols+1; j++)
			A[i][j] = Shift[i][j+1];
	for (int i = 0; i < Rows; i++)
		for (int j = 0; j < Cols; j++)
			Final_sort << A[i][j] << endl;
	//Step-8 ends here
	myfile.close();
	outfile.close();
	tempfile.close();
	transfile.close();
	tempsfile.close();
	rev_file.close();
	sortfile.close();
	shift1.close();
	shift_sortfile.close();
	Final_sort.close();
	printf("Time taken: %.3fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	getchar();
}