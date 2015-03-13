from graphics import *


def main():
	
	anchorpoint=Point(150,150)
	height=300
	width=300

	image=Image(anchorpoint, height, width)
	
	
	
	fileHandle = open('output_projection_blue.txt', 'r')
	win = GraphWin('Test', 1000, 1000) # give title and dimensions
	win.setCoords(-60,-300,1500,2000);
	count = 0
  	linesList = fileHandle.readlines()
	length = len(linesList); 
	while count != length:
	
		noOfMovements = int(linesList[count])
		count = count + 1
		noOfMovements = noOfMovements + 2
		x1,y1 = (int(val) for val in linesList[count].split())
		count = count + 1
		a = x1 * 30
		b = y1 * 30
		j = count
	
		for x in range(2, noOfMovements):
			x2,y2 = (int(val) for val in linesList[j].split())
			count = count + 1
			c = x2
			d = y2
			j = j + 1
			if x2 > x1:
				c = a + 30
				d = b
			else:
				d = b + 30
				c = a
				
			line = Line(Point(a, b + 650), Point(c, d + 650)) #650
			line.setWidth(4)
			line.setFill("blue")
			line.draw(win)
			#print a
			#print b
			#print c
			#print d
			a = c
			b = d
			
			x1 = x2
			y1 = y2
	
	
	
	fileHandle2 = open('output_star_red.txt', 'r')
	#win2 = GraphWin('Test', 800, 800) # give title and dimensions
	#win2.setCoords(0,0,2000,2000);
	count2 = 0
  	linesList2 = fileHandle2.readlines()
	length = len(linesList2); 
	while count2 != length:
	
		noOfMovements = int(linesList2[count2])
		count2 = count2 + 1
		noOfMovements = noOfMovements + 2
		x1,y1 = (int(val) for val in linesList2[count2].split())
		count2 = count2 + 1
		a = x1 * 30
		b = y1 * 30
		j = count2
	
		for x in range(2, noOfMovements):
			x2,y2 = (int(val) for val in linesList2[j].split())
			count2 = count2 + 1
			c = x2
			d = y2
			j = j + 1
			if x2 > x1:
				c = a + 30
				d = b
			else:
				d = b + 30
				c = a
			
			
			line2 = Line(Point(a, b), Point(c, d))
			line2.setWidth(2)
			line2.setFill("red")
			line2.draw(win)
			#print a
			#print b
			#print c
			#print d
			a = c
			b = d
			
			x1 = x2
			y1 = y2
			
	fileHandle2 = open('output_projection_red.txt', 'r')
	#win2 = GraphWin('Test', 800, 800) # give title and dimensions
	#win2.setCoords(0,0,2000,2000);
	count2 = 0
  	linesList2 = fileHandle2.readlines()
	length = len(linesList2); 
	while count2 != length:
	
		noOfMovements = int(linesList2[count2])
		count2 = count2 + 1
		noOfMovements = noOfMovements + 2
		x1,y1 = (int(val) for val in linesList2[count2].split())
		count2 = count2 + 1
		a = x1 * 30
		b = y1 * 30
		j = count2
	
		for x in range(2, noOfMovements):
			x2,y2 = (int(val) for val in linesList2[j].split())
			count2 = count2 + 1
			c = x2
			d = y2
			j = j + 1
			if x2 > x1:
				c = a + 30
				d = b
			else:
				d = b + 30
				c = a
			
			
			line2 = Line(Point(a, b - 0), Point(c, d - 0))
			line2.setWidth(4)
			line2.setFill("red")
			line2.draw(win)
			#print a
			#print b
			#print c
			#print d
			a = c
			b = d
			
			x1 = x2
			y1 = y2
	
	win.postscript(file="oneStarOneProj.eps", colormode='color')

	# Convert from eps format to gif format using PIL
	from PIL import Image as NewImage
	img = NewImage.open("oneStarOneProj.eps")
	img.save("oneStarOneProj.gif", "gif")
	win.getMouse()
	win.close()

main()
