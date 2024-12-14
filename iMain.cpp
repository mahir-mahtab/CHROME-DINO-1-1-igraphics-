// #include "iGraphics.h"
#include "igraphicsex.h"
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
char coin[20] = "./coin/coin.bmp";
int count = 0;
int birdCount = 0;
int score = 0;
int obstackleTime=1400;

int groundInitial = 80, groundBlock = 80, groundSpeed, offset = 0, fps = 0;
float dinoX = 200, dinoY = 105, dinoSpeed = 10;
int life, lifecordinatex = 700, lifecordinatey = 480, spacingLife = 30;
bool musicon = false , scoreSaved = false;


int x = 300, y = 300, r = 0;
int startGameflage = 0; // 0=menu,1=game,2=game over,3=name enter,4=leaderboard,5=level selection;
float jumpflag = 0, jumpupflag = 0, jumpdownflag = 0, height, speed = 1.55, a = .006;
int dip = 0;
int cloudy = 400, cloudx = 750, nameIndex = 0;
char gameSound[25] = "./sound/gamesound.wav";
char name[20] = "";
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
struct Coin
{
	float x, y;
	int index;
};
struct Player
{
	char n[20];
	int scoreName;
};
vector<Player> Players(3);

vector<Obstacle> obstacles;
vector<Bird> birds;
vector<Coin> coins;
vector<pair<string, int>> leaderboard; // Vector to store the leaderboard data
const char *leaderboardFile = "leaderboard.txt";
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
void updateCoin();
void createCoin();
void coinPlot();
void lifePlot();
void enterName();
void saveLeaderboard();
void loadLeaderboard();
void updateLeaderboard(const char *name, int score);
void displayLeaderboard();
void displayLead();
void levelselection();
void easy();
void medium();
void hard();
void checklevel(int x,int y);
/*
	function iDraw() is called again and again by the system.
*/
void dinoJump();
void game();
void update();
void standDino();
void dipDino();
void updateStand();
void info();
void startGame(int x, int y)
{
	if (x > 275 && x < 520 && y > 110 && y < 220)
	{
		startGameflage = 3;
		
	}
	if (x > 600 && x < 780 && y > 45 && y < 100){
			startGameflage=4;
	}
	if (x > 720 && x < 760 && y > 490 && y < 530){
			startGameflage=6;
	}

}

void border()
{
	iFilledRectangle(0, 0, 50, 600);
	iSetColor(0, 147, 153);
	iFilledRectangle(0, 0, 50, 600);
	iSetColor(0, 147, 153);
	iFilledRectangle(0, 0, 800, 50);
	iSetColor(0, 147, 153);

	iFilledRectangle(750, 0, 50, 600);
	iSetColor(0, 147, 153);
	iFilledRectangle(0, 550, 800, 50);
	iSetColor(0, 147, 153);
}

void groundPlot()
{

	iShowBMP2(cloudx, cloudy - 100, cloudImg[1], 0);

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
	cloudx = cloudx - 30;
	cloudx < 0 ? cloudx = 750 : cloudx;
}

void iDraw()
{
	// place your drawing codes here
	iClear();

	if (startGameflage == 0)
	{
		iShowBMP(0, 0, "./output.bmp");
		iShowBMP2(719,489,"./icon/info.bmp",0);
	}
	else if (startGameflage == 1)
	{
		game();
	}
	else if (startGameflage == 3)
	{
		enterName();
	}
	if(startGameflage==5){
		levelselection();
	}
	gameOver();
	if (startGameflage == 4)
	{
		displayLead();
	}
	if(startGameflage==6){
		info();
	}

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
		if(startGameflage==5){
			checklevel(mx,my);
			
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
void iPassiveMouseMove(int mx, int my)
{
	iMouseX = mx;
	iMouseY = my;
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key)
{
	if (key == 's' && jumpflag == 0)
	{
		dip=1;
	}
	if (key == 'q' && startGameflage == 1)
	{
		exit(0);
	}
	// place your codes for other keys here
	if (key == ' ' && startGameflage == 1)
	{
		jumpflag = 1;
	}
	if (key != '\b' && key != '\r' && startGameflage == 3)
	{
		name[nameIndex] = key;
		name[nameIndex + 1] = '\0';
		nameIndex++;
	}
	if (key == '\r' && startGameflage == 3)
	{
		startGameflage = 5;
	}
	if (key == '\b' && startGameflage == 3)
	{
		nameIndex--;
		name[nameIndex]='\0';
	}
	if (key = 'x' && startGameflage == 2)
	{
		startGameflage = 4;
	}
	if(key = 'b'&&startGameflage==6){
		startGameflage=0;
	}
	if(key = 'b'&&startGameflage==4){
		startGameflage=0;
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
	
	// place your codes for other keys here
}
void game()
{
	iSetColor(255, 255, 255);
	iFilledRectangle(50, 50, 700, 500);
	// iShowBMP2(50, 50, "./background.bmp/background.bmp",-1);
	// d
	iShowBMP2(500, 400, "./sun/tile001.bmp", 0);
	musicon = true;
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
	coinPlot();

	// last line border
	border();
	displayScore();
	lifePlot();
}
void standDino()
{

	iShowBMP2(dinoX, dinoY, dino[r % 4], 0);
}
void update()
{
	r++;

	// standDino();
	if (startGameflage == 1)
	{
		groundUpdate();
		updateObstackle();
		updateBird();
		updateCoin();
		score += 1;
	}

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
			life--;
			obstacles.erase(obstacles.begin() + i);
			if (life == 0)
			{
				startGameflage = 2;
				PlaySound(0, 0, 0);
				
				
			}
			printf("Game Over\n");
		}
	}
	if (dip == 0)
		for (int i = 0; i < birds.size(); i++)
		{
			if (dinoX + 10 > birds[i].x && dinoX < birds[i].x + 70 && (dinoY + 55 > (birds[i].y)) && (dinoY < (birds[i].y + 45)))
			{
				birds.erase(birds.begin() + i);
				life--;

				if (life == 0)
					startGameflage = 2;
				musicon = false;
			}
		}
	for (int i = 0; i < coins.size(); i++)
	{
		if (coins[i].y + 20 > dinoY && dinoX + 50 > coins[i].x && dinoX < coins[i].x + 28)
		{
			life++;
			coins.erase(coins.begin() + i);
		}
	}
}
void createBird()
{
	if (startGameflage == 1)
	{
		Bird add;
		add.x = 800;
		add.y = birdCount % 2 == 0 ? 120 : 180;
		add.index = rand() % 4;
		birds.push_back(add);
	}
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
		birds[i].x -= (groundSpeed + 30);
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
		if (!scoreSaved)
		{ // Write the score only once
			updateLeaderboard(name, score);
			displayLeaderboard();
			scoreSaved = true; // Prevent multiple writes
		}
		char scoreText[20];
		sprintf(scoreText, "%d", score);
		ishowmanualtext(500, 178, scoreText, 20);
	}
}
void restartGame(int x, int y)
{
	
	if (x > 200 && x < 600 && y > 200 && y < 370)
	{
		startGameflage = 3,jumpdownflag = 0, jumpupflag = 0, jumpflag = 0, dip = 0, obstacles.clear(), birds.clear(), r = 0, birdCount = 0, dinoX = 200, dinoY = 105, fps = 0, speed = 1.55, a = .006, score = 0,scoreSaved=false;
		
	}
	if(x > 730 && x < 755 && y > 535 && y < 565){
		startGameflage = 0,jumpdownflag = 0, jumpupflag = 0, jumpflag = 0, dip = 0, obstacles.clear(), birds.clear(), r = 0, birdCount = 0, dinoX = 200, dinoY = 105, fps = 0, speed = 1.55, a = .006, score = 0,scoreSaved=false;
	}

}
void displayScore()
{
	// White color
	char scoreText[20];
	sprintf(scoreText, "score: %d", score);
	iSetColor(0, 0, 0);
	iText(70, iScreenHeight - 100, scoreText, GLUT_BITMAP_HELVETICA_18);
}
void updateStand()
{
	if (startGameflage == 1)
	{

		standDino();
		createObstackles();
	}
		
}
void createCoin()
{
	if (startGameflage == 1)
	{
		Coin add;
		add.x = 800;
		add.y = 120;
		add.index = 1;
		coins.push_back(add);
	}
}
void updateCoin()
{
	for (int i = 0; i < coins.size(); i++)
	{
		if (coins[i].x <= 0)
		{

			coins.erase(coins.begin() + i);
			i--;
		}
		coins[i].x -= groundSpeed;
	}
}
void coinPlot()
{
	for (int i = 0; i < coins.size(); i++)
	{
		iShowBMP2(coins[i].x, coins[i].y, coin, 0);
	}
}
void lifePlot()
{
	for (int i = 0; i < life; i++)
	{
		iShowBMP2(lifecordinatex - spacingLife * i, lifecordinatey, coin, 0);
	}
}
// Function to load the leaderboard from the file
void loadLeaderboard()
{
	leaderboard.clear();
	ifstream inFile(leaderboardFile);
	string name;
	int score;
	while (inFile >> name >> score)
	{
		leaderboard.push_back({name, score});
	}
	inFile.close();
}

// Function to save the leaderboard to the file
void saveLeaderboard()
{
	ofstream outFile(leaderboardFile);
	for (const auto &entry : leaderboard)
	{
		outFile << entry.first << " " << entry.second << endl;
	}
	outFile.close();
}

// Function to update the leaderboard with a new score
void updateLeaderboard(const char *name, int score)
{
	// Read existing leaderboard data
	FILE *file = fopen("leaderboard.txt", "r");
	std::vector<std::pair<int, std::string>> leaderboard;

	if (file != NULL)
	{
		char playerName[50];
		int playerScore;
		while (fscanf(file, "%s %d", playerName, &playerScore) == 2)
		{
			leaderboard.push_back({playerScore, playerName});
		}
		fclose(file);
	}

	// Add the new score
	leaderboard.push_back({score, name});
	

	// Sort by score (highest first)
	std::sort(leaderboard.rbegin(), leaderboard.rend());

	// Write the sorted data back to the file
	file = fopen("leaderboard.txt", "w"); // Open in write mode to overwrite
	if (file == NULL)
	{
		printf("Error opening leaderboard file!\n");
		return;
	}

	for (const auto &entry : leaderboard)
	{
		fprintf(file, "%s %d\n", entry.second.c_str(), entry.first);
	}
	fclose(file);
	
}
void displayLeaderboard()
{

	FILE *fil = fopen("leaderboard.txt", "r");

	for (int i = 0; i < 3; i++)
	{
		fscanf(fil, "%s %d", Players[i].n, &Players[i].scoreName);
	}
	fclose(fil);
}
int main()
{
	// place your own initialization codes here.
	displayLeaderboard();
	iSetTimer(100, update);
	iSetTimer(1800, updateStand);
	iSetTimer(7400, createBird);
	iSetTimer(21540, createCoin);
	iInitialize(800, 600, "demo");
	return 0;
}
void enterName()
{
	iShowBMP2(0, 0, "./dificulty/nameEnter.bmp", -1);
	iSetColor(10, 57, 129);
	iText(320, 165, name, GLUT_BITMAP_HELVETICA_18);
}
void displayLead()
{

	iShowBMP(0, 0, "./dificulty/leaderboard.bmp");
	for (int i = 0; i < 3; i++)
	{
		char scoreN[20];
		char scoreNum[10];
		sprintf(scoreNum, "%d", Players[i].scoreName);
		sprintf(scoreN, "%s", Players[i].n);
		iText(220, 270 - i * 50, scoreN, GLUT_BITMAP_HELVETICA_18);
		iSetColor(255, 255, 255);
		iText(350, 270 - i * 50, scoreNum, GLUT_BITMAP_HELVETICA_18);
		iSetColor(255, 255, 255);
	}
}
void levelselection(){
	iShowBMP2(0,0,"./dificulty/diff.bmp",-1);
	
	
}
void checklevel(int x,int y){
	if(x>275&&x<530&&y<380&&y>290){
		easy();
		startGameflage=1;
	}
	if(x>275&&x<530&&y<270&&y>180){
		medium();
		startGameflage=1;
	}
	if(x>275&&x<530&&y<160&&y>70){
		hard();
		startGameflage=1;
	}
	PlaySound(TEXT("sound//gamesound.wav"), NULL, SND_LOOP | SND_ASYNC);

}
void easy(){
	groundSpeed=15;
	life=3;
	height=100;
	
}
void medium(){
	 groundSpeed = 25;
	 life=3;
	 height=110;
}
void hard(){
	groundSpeed=30;
	life=2;
	height=120;
}
void info(){
	iShowBMP2(0,0,"./INTRO/Instructions.bmp",-1);

}