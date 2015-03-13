#include <iostream>
#include <math.h>
//#include <string>

using namespace std;

float computeHausdorff(int x1, int y1, int x2, int y2)
{
	return sqrt( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

float computeX(int sum, int y)
{
	return sum - y;
}
	
float computeY(int a, int b, float slope, int sum)
{
	return (slope * sum + slope * a + b) / (1 + slope);
}

int main()
{
	int x1, x2, y1, y2;
	float x, y, hausdorffDistance, maxHausdorffDistance = 0.0;
	int digCoord[][2]={2,2,3,2,3,3,3,4,4,4,4,5,5,5,5,6,5,7,5,8,6,8,6,9,6,10,7,10,8,10,9,10,10,10,10,11};
	cout << "enter the coordinates" << endl;
	cin >> x1 >> y1 >> x2 >> y2;
	
	float m = (float) (y2 - y1)/(x2 - x1);
	cout << "the slope is " << m << endl;
	for (int i = 0; i < 18; i++)
	{
		int j = 0;
		y = computeY(digCoord[i][j], digCoord[i][j + 1], m, digCoord[i][j] + digCoord[i][j+1]);
		x = computeX(digCoord[i][j] + digCoord[i][j+1], y);
		hausdorffDistance = computeHausdorff(digCoord[i][j], digCoord[i][j + 1], x, y);
		if (maxHausdorffDistance < hausdorffDistance)
			maxHausdorffDistance = hausdorffDistance;
	}
	cout << "hausdorff distance " << hausdorffDistance << endl;
}
