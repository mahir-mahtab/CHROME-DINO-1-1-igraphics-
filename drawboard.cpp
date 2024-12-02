#include "fakeigraphics.h"
#include<bits/stdc++.h>

using namespace std;
int x = 0, y = 0, dx = 5, dy = 5;
vector<pair<int, int>> points;
int r=255,g=2,b=255;
int imageId = iLoadImage("./output.bmp");


/*
	function iDraw() is called again and again by the system.

	*/

// void drawhomepage();
void functionality();

void iDraw()
{
	 iClear();
	 
    //  iFilledRectangle(0, 0, 800, 600);
    //  iSetColor(255, 255, 255);
	iSetColor(255, 255, 255);
	iFilledRectangle(0, 0, 800, 600);
	iShowImage(0,0,"output.bmp");

    int a=points.size();
    for(int i=0;i<a;i++){
	iSetColor(r, g, b);
    iFilledCircle(points[i].first, points[i].second,3);
    }
	functionality();
	
	
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my)
{
	printf("x = %d, y= %d\n", mx, my);
	// place your codes here
    x=mx;
    y=my;
    points.push_back(make_pair(x, y));

}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)

	{
       
		// place your codes here
		//	printf("x = %d, y= %d\n",mx,my);
		//  x += 10;
		//  y += 10;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// place your codes here
		//  x -= 10;
		//  y -= 10;
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key)
{
	if (key == 'q')
	{
		exit(0);
	}
	// place your codes for other keys here
}


/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	// place your codes for other keys here
}

int main()
{
	// place your own initialization codes here.
	iInitialize(800, 600, "demo");
	return 0;
}
void functionality(){
	iSetColor(200,200,200);
	iFilledRectangle(0,560,800,40);

}