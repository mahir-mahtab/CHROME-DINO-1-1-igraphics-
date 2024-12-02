#include "iGraphics.h"
// #include"fakeigraphics.h"
#include <bits/stdc++.h>
using namespace std;
char ground[8][50] = {
	"./ground/ground_0.bmp",
	"./ground/ground_1.bmp",
	"./ground/ground_0.bmp",
	"./ground/ground_0.bmp",
	"./ground/ground_0.bmp",
	"./ground/ground_1.bmp",
	"./ground/ground_0.bmp",
	"./ground/ground_0.bmp",
};
char dino[4][50] = {
	"./dino/tile000.bmp",
	"./dino/tile001.bmp",
	"./dino/tile002.bmp",
	"./dino/tile003.bmp",
};
char dipImg[2][50] = {
	"./dip/dip0.bmp",
	"./dip/dip1.bmp",
};
char obstacleImages[4][50] = {
	"./obstacles/tile000.bmp",
	"./obstacles/tile001.bmp",
	"./obstacles/tile002.bmp",
	"./obstacles/tile003.bmp",
};
char cloudImg[2][50] = {
	"./cloud/tile000.bmp",
	"./cloud/tile001.bmp",
};
char birdImg[4][50] = {
	"./bird/tile000.bmp",
	"./bird/tile001.bmp",
	"./bird/tile002.bmp",
	"./bird/tile003.bmp",
};
int count = 0;
int birdCount = 0;
int score = 0;
int highScore = 0;
int groundInitial = 80, groundBlock = 80, groundSpeed = 25, offset = 0, fps = 0;
float dinoX = 200, dinoY = 105, dinoSpeed = 10;

int x = 300, y = 300, r = 0;
int startGameflage = 0;
float jumpflag = 0, jumpupflag = 0, jumpdownflag = 0, height = 120, speed = 1.55, a = .006;
int dip = 0;
int cloudy=400,cloudx=750;
struct Obstacle
{
	float x, y;
	int index;
};
struct Bird
{
	float x, y;
	int index;
};

vector<Obstacle> obstacles;
vector<Bird> birds;
void createBird();
void updateBird();
void birdPlot();

void createObstackles();
void updateObstackle();
void obstacklePlot();
void checkGameOver();
void gameOver();
void restartGame(int x, int y);
void displayScore();
/*
	function iDraw() is called again and again by the system.
*/
void dinoJump();
void game();
void update();
void standDino();
void dipDino();
void startGame(int x, int y)
{
	if (x > 275 && x < 520 && y > 110 && y < 220)
	{
		startGameflage = 1;
	}
}
void border()
{
	iFilledRectangle(0, 0, 50, 600);
	iSetColor(200, 200, 200);
	iFilledRectangle(0, 0, 50, 600);
	iSetColor(200, 200, 200);
	iFilledRectangle(0, 0, 800, 50);
	iSetColor(200, 200, 200);

	iFilledRectangle(750, 0, 50, 600);
	iSetColor(200, 200, 200);
	iFilledRectangle(0, 550, 800, 50);
	iSetColor(200, 200, 200);
}

void groundPlot()
{

	iShowBMP2(cloudx, cloudy-100, cloudImg[1], 0);

	for (int i = 0; i < 16; i++)
	{
		int xSpeed = groundInitial + groundBlock * i + offset;
		iShowBMP(xSpeed, 100, ground[i % 8]);
	}
}
void groundUpdate()
{
	offset -= groundSpeed;
	if (offset < -groundBlock * 8)
	{
		offset = 0;
	}
	cloudx=cloudx-30;
	cloudx<0?cloudx=750:cloudx;
}

void iDraw()
{
	// place your drawing codes here
	iClear();

	if (startGameflage == 0)
	{
		iShowBMP(0, 0, "./output.bmp");
	}
	else if (startGameflage == 1)
	{
		game();
	}
	gameOver();

	return;
}
/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my)
{
	printf("x = %d, y= %d\n", mx, my);
	// place your codes here
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
		if (startGameflage == 0)
		{
			startGame(mx, my);
		}
		if (startGameflage == 2)
		{
			restartGame(mx, my);
		}
		x += 10;
		y += 10;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// place your codes here
		x -= 10;
		y -= 10;
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
	if (key == ' ')
	{
		jumpflag = 1;
	}
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
	if (key == GLUT_KEY_PAGE_DOWN && jumpflag == 0)
	{
		dip = 1;
	}
	// place your codes for other keys here
}
int main()
{
	// place your own initialization codes here.
	PlaySound(TEXT("C:\\Users\\USER\\Desktop\\igrahics project\\music.wav"), NULL, SND_ASYNC | SND_LOOP);
	iSetTimer(100, update);
	iSetTimer(2000, standDino);
	iSetTimer(2000, createObstackles);
	iSetTimer(10000, createBird);
	iInitialize(800, 600, "demo");
	return 0;
}
void game()
{
	iSetColor(255, 255, 255);
	iFilledRectangle(50, 50, 700, 500);
	// iShowBMP2(50, 50, "./background.bmp/background.bmp",-1);
	// d
	iShowBMP2(500,400,"./sun/tile001.bmp",0);

	groundPlot();
	if (dip == 0)
	{
		standDino();
	}
	dinoJump();
	dipDino();
	obstacklePlot();
	birdPlot();
	checkGameOver();

	// last line border
	border();
	displayScore();
}
void standDino()
{

	iShowBMP2(dinoX, dinoY, dino[r % 4], 0);
}
void update()
{
	r++;

	// standDino();
	groundUpdate();
	updateObstackle();
	updateBird();
	score += 1;

	// Update high score if current score exceeds it
}
void dinoJump()
{
	if (jumpflag == 0)
	{
		return;
	}

	else if (jumpflag == 1)
	{
		if (jumpupflag == 0 && jumpdownflag == 0)
		{
			jumpupflag = 1;
		}
		if (jumpupflag == 1)
		{
			speed = speed - a;
			dinoY += speed;
			if (dinoY >= height + 105)
			{
				jumpupflag = 0;
				jumpdownflag = 1;
			}
		}
		if (jumpdownflag == 1)
		{
			speed = speed + a;
			dinoY -= speed;
			if (dinoY <= 105)
			{
				jumpdownflag = 0;
				jumpflag = 0;

				dinoY = 105;
			}
		}
	}
}
void dipDino()
{
	if (dip == 0)
	{
		return;
	}
	else if (dip == 1)
	{

		iShowBMP2(dinoX, dinoY, dipImg[(bool)(rand() % 6)], 0);
		fps++;
		if (fps == 120)
		{
			dip = 0;
			fps = 0;
		}

		printf("dip\n");
	}
	return;
}
void createObstackles()
{
	Obstacle add;
	add.x = 800;
	add.y = 105;
	add.index = rand() % 4;
	obstacles.push_back(add);
}
void updateObstackle()
{
	for (int i = 0; i < obstacles.size(); i++)
	{
		if (obstacles[i].x <= 0)
		{

			obstacles.erase(obstacles.begin() + i);
			i--;
		}
		obstacles[i].x -= groundSpeed;
	}
}
void obstacklePlot()
{
	for (int i = 0; i < obstacles.size(); i++)
	{
		iShowBMP2(obstacles[i].x, obstacles[i].y, obstacleImages[obstacles[i].index], 0);
	}
}

void checkGameOver()
{
	for (int i = 0; i < obstacles.size(); i++)
	{
		if (dinoX - 10 < obstacles[i].x && dinoX + 10 > obstacles[i].x && (dinoY < (obstacles[i].y + 20)))
		{
			startGameflage = 2;
			printf("Game Over\n");
		}
	}
	if (dip == 0)
		for (int i = 0; i < birds.size(); i++)
		{
			if (dinoX + 10 > birds[i].x && dinoX < birds[i].x + 70 && (dinoY + 55 > (birds[i].y)) && (dinoY < (birds[i].y + 45)))
			{
				startGameflage = 2;
			}
		}
}
void createBird()
{
	Bird add;
	add.x = 800;
	add.y = birdCount % 2 == 0 ? 120 : 180;
	add.index = rand() % 4;
	birds.push_back(add);
}
void updateBird()
{
	for (int i = 0; i < birds.size(); i++)
	{
		if (birds[i].x <= 0)
		{

			birds.erase(birds.begin() + i);
			i--;
		}
		birds[i].x -= (groundSpeed + 20);
	}
	birdCount++;
}
void birdPlot()
{
	for (int i = 0; i < birds.size(); i++)
	{

		iShowBMP2(birds[i].x, birds[i].y, birdImg[birdCount % 4], 16777215);
	}
}
void gameOver()
{
	if (startGameflage != 2)
	{
		return;
	}
	else
	{

		iShowBMP2(0, 0, "./asset/gameover.bmp", -1);
	}
}
void restartGame(int x, int y)
{
	if (x > 200 && x < 600 && y > 200 && y < 370)
	{
		startGameflage = 1, jumpdownflag = 0, jumpupflag = 0, jumpflag = 0, dip = 0, obstacles.clear(), birds.clear(), r = 0, birdCount = 0, dinoX = 200, dinoY = 105, fps = 0, speed = 1.55, a = .006;
	}
}
void displayScore()
{
	// White color
	char scoreText[20];
	sprintf(scoreText, "score: %d", score);
	iText(70, iScreenHeight - 100 , scoreText, GLUT_BITMAP_HELVETICA_18);
}
