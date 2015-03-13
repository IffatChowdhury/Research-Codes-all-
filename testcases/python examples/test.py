from graphics import *


def main():
	
	win = GraphWin('Test', 700, 700) # give title and dimensions
    win.setCoords(-700,-700,700,700);
  	
  	a = -1000
	b = 1000
	c = 1000
	for x in range(0, 1402):
		line1 = Line(Point(a, b), Point(c, b))
		line1.setWidth(1)
		line1.draw(win)
		b = b - 30; 
	
	
	b = -1000
	a = 1000
	c = -1000
	for x in range(0, 1402):
		line2 = Line(Point(b, a), Point(b, c))
		line2.setWidth(1)
		line2.draw(win)
		b = b + 30; 

	win.getMouse()
	win.close()

main()
