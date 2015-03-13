#include <iostream>
#include <cmath>
#include <fstream>

#define MAX 1000;
using namespace std;

void checkDiagonal(int n, int arr[], int hori);
int findIndex(int number, int a[], int totalEle);
ofstream myfile("result.xls");

int main(){
	int noOfEleTO = 0;
	
	/*cout << "Enter number of elements in total order" << endl;
	cin >> noOfEleTO;
	int totalOrder[noOfEleTO];
	for(int i = 0; i < noOfEleTO; i++){
		cin >> totalOrder[i];
		}*/
	int totalOrder[11] = {7, 3, 5, 9, 1, 6, 10, 2, 4, 8, 0};
	noOfEleTO = 11;
	for(int i = 1; i < noOfEleTO; i++ )
		checkDiagonal(noOfEleTO, totalOrder, i);
	return 0;
	}

void checkDiagonal(int n, int arr[], int hori){
	double horiDesired = (double) hori / n, result = 0.0;
	cout << "horiDesired " << horiDesired << endl;
	int horizontalMove, savedDiag;
	for(int j = 2; j < n; j++){			//for each diagonal starting from 2
		horizontalMove = 0;
		for(int i = 0; i < j; i++){		//iterate through the values from 0 to d-1
			int index = findIndex(i, arr, n);
			if (index == -1)
				return;
			else{
				if(index < hori)
					horizontalMove++;
				}
		}
		double horiActual = (double) horizontalMove / j;
		cout << "horiActual " << horiActual << endl;
		double value = j * fabs(horiActual - horiDesired);
		cout << "value " << value << " diagonal " << j << endl;
		if (value > result){
			result = value;
			savedDiag = j;
		}
	}
	//cout << "Horizontal movement " << hori << " on diagonal " << savedDiag << " result is " << result << endl;
	myfile << "Horizontal movement " << hori << " diagonal " << savedDiag << " result " << result << endl;
}
	
int findIndex(int number, int a[], int totalEle){
	for (int inn = 0; inn < totalEle; inn++){
		if(a[inn] == number)
			return inn;
		}
		return -1;
	}
