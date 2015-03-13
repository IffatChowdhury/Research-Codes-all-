#include <iostream>
#include <limits>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

bool compare(int,int);

int main(){
  
 int a,b;
 
 cout << "Enter the endpoints for the interval: ";
 cin >> a >> b;
 
 vector<int> interval;
 int size = b-a+1;
 
 for(int i=a; i<=b; i++)
   interval.push_back(i);
 
 for(int i=0; i<size; i++){
   
   int min = i;
   
  for(int j=i+1; j<size; j++){
    
   if(compare(interval[j],interval[min]))
     min = j;    
    
  }
  
  //cout << "Min: " << interval[min] << endl;
  int temp = interval[i];
  interval[i] = interval[min];
  interval[min] = temp;
   
 }
 
 cout << endl << "Sorted interval: " << endl;
 for(int i=0; i<size; i++)
   cout << interval[i] << " ";
 
 cout << endl << endl;
  
  
  return 0;
  
}



bool compare(int n1, int n2) //return true if n1 is less than n2
{
	while(true)
	{
		int div = 2;
		bool divides1 = true;
		bool divides2 = true;
		
		while(divides1 && divides2)
		{	
			divides1 = n1%div == 0;
			divides2 = n2%div == 0;
			
			div *= 2;
		}
		
		if(divides1 && !divides2)
			return false;
		else if(divides2 && !divides1)
			return true;
		else
		{
			n1--;
			n2--;
		}
  }
}