from graphics import *


def main():
	
	fileHandle = open('output.txt', 'r')
	win = GraphWin('Test', 700, 700) # give title and dimensions
	win.setCoords(-700,-700,700,700);
  	  		
  	linesList = fileHandle.readlines()
	j = 1
	x1,y1 = (int(val) for val in linesList[0].split())
	a = x1 * 30
	b = y1 * 30
	length = len(linesList); 
	for x in range(1, length):
		x2,y2 = (int(val) for val in linesList[j].split())
		c = x2
		d = y2
		j = j + 1
		if x2 > x1:
			c = a + 30
			d = b
		else:
			d = b + 30
			c = a
			
		line = Line(Point(a, b), Point(c, d))
		line.setWidth(1)
		line.draw(win)
		print a
		print b
		print c
		print d
		a = c
		b = d
		
		x1 = x2
		y1 = y2
		
	win.getMouse()
	win.close()

main()
