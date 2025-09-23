#include "iGraphics.h"

void drawOpenPage();
void drawHomePage();
void drawPlayPage();
void drawOptionsPage();
void drawCreditsPage();

void homePageHandler();
void playButtonHandler();
void optionsButtonHandler();
void creditsButtonHandler();
void backButtonHandler();

int openPage = 1;
int homePage = 0;
int optionsPage = 0;
int creditsPage = 0;
int playHover[5] = { 0, 0, 0, 0, 0 };


int button1 = -1;
int button2 = -1;

#define TOTAL_RUN_FRAMES 60
#define TOTAL_RUN_FRAMES2 72
#define TOTAL_KICK_FRAMES 41
#define TOTAL_BACKGROUNDS 6


int frameIndex = 0;
int runFrames[TOTAL_RUN_FRAMES];
int runFrames2[TOTAL_RUN_FRAMES2];
int defaultFrame = -1;
int defaultFrame2 = -1;


int backgrounds[TOTAL_BACKGROUNDS];
int selectedBackground = -1;
int backgroundSelectionMode = 0;


int characterX = 15;
int characterY = 15;

int imagesLoaded = 0;
int isRunningRight = 0;
int isRunningLeft = 0;

int isChar2RunningRight = 0;
int isChar2RunningLeft = 0;
int character2X = 800;
int character2Y = 15;
int char2FrameIndex = 0;

int kickFrames[TOTAL_KICK_FRAMES];
int isKicking = 0;
int kickFrameIndex = 0;

int x = 0;
int y = 0;


void loadImages() {
	char path[64];

	for (int i = 0; i < TOTAL_RUN_FRAMES; i++) {
		sprintf_s(path, sizeof(path), "Images/WalkF/%d.png", i + 1);
		runFrames[i] = iLoadImage(path);
	}

	for (int i = 0; i < TOTAL_KICK_FRAMES; i++) {
		sprintf_s(path, sizeof(path), "Images/KickF/%d.png", i + 19);
		kickFrames[i] = iLoadImage(path);
	}

	for (int i = 0; i < TOTAL_RUN_FRAMES2; i++) {
		sprintf_s(path, sizeof(path), "Images/WalkA/%d.png", i + 1);
		runFrames2[i] = iLoadImage(path);
	}

	for (int i = 0; i < TOTAL_BACKGROUNDS; i++) {
		sprintf_s(path, sizeof(path), "Images/BG/background%d.png", i + 1);
		backgrounds[i] = iLoadImage(path);
	}

	defaultFrame = iLoadImage("Images/default.png");
	defaultFrame2 = iLoadImage("Images/default1.png");
	imagesLoaded = 1;
}

void iDraw()
{
	iClear();
	if (openPage == 1){
		drawOpenPage();
	}
	else if (homePage == 1){
		drawHomePage();
	}
	else if (backgroundSelectionMode == 1){
		drawPlayPage();
	}
	else if (homePage == 0 && optionsPage == 0 && openPage == 0 && backgroundSelectionMode == 0 && creditsPage == 0) {
		iShowImage(0, 0, 1280, 720, backgrounds[selectedBackground]);

		if (isKicking) {
			iShowImage(characterX, characterY, 350, 350, kickFrames[kickFrameIndex]);
		}
		else if (isRunningRight || isRunningLeft) {
			iShowImage(characterX, characterY, 350, 350, runFrames[frameIndex]);
		}
		else {
			iShowImage(characterX, characterY, 350, 350, defaultFrame);
		}

		if (isChar2RunningRight || isChar2RunningLeft) {
			iShowImage(character2X, character2Y, 350, 350, runFrames2[char2FrameIndex]);
		}
		else {
			iShowImage(character2X, characterY, 350, 350, defaultFrame2);
		}
	}


	else if (optionsPage == 1){
		drawOptionsPage();
	}
	else if (creditsPage == 1){
		drawCreditsPage();
	}

}

void iMouseMove(int mx, int my)
{

}

void iPassiveMouseMove(int mx, int my)
{
	if (homePage == 1 && mx >= 980 && mx <= 1170 && my >= 380 && my <= 440){
		playHover[0] = 1;
	}
	else{
		playHover[0] = 0;
	}
	if (homePage == 1 && mx >= 980 && mx <= 1170 && my >= 280 && my <= 340){
		playHover[1] = 1;
	}
	else{
		playHover[1] = 0;
	}
	if (homePage == 1 && mx >= 980 && mx <= 1170 && my >= 180 && my <= 240){
		playHover[2] = 1;
	}
	else{
		playHover[2] = 0;
	}
	if (homePage == 1 && mx >= 980 && mx <= 1170 && my >= 80 && my <= 140){
		playHover[3] = 1;
	}
	else{
		playHover[3] = 0;
	}
	if ((backgroundSelectionMode == 1 || optionsPage == 1 || creditsPage == 1) && mx >= 30 && mx <= 110 && my >= 30 && my <= 102){
		playHover[4] = 1;
	}
	else{
		playHover[4] = 0;
	}

}

void iMouse(int button, int state, int mx, int my)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("%d %d\n", mx, my);
		if ((openPage == 1) && (mx >= 0 && mx <= 1280 && my >= 0 && my <= 720)){
			homePageHandler();
		}
		else if ((homePage == 1) && (mx >= 980 && mx <= 1170 && my >= 380 && my <= 440)){
			playButtonHandler();
		}
		else if ((homePage == 1) && (mx >= 980 && mx <= 1170 && my >= 280 && my <= 340)){
			optionsButtonHandler();
		}
		else if ((homePage == 1) && (mx >= 980 && mx <= 1170 && my >= 180 && my <= 240)){
			creditsButtonHandler();
		}
		else if ((backgroundSelectionMode == 1 || optionsPage == 1 || creditsPage == 1) && mx >= 30 && mx <= 110 && my >= 30 && my <= 102){
			backButtonHandler();
		}

	}
	if (backgroundSelectionMode && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		for (int i = 0; i < TOTAL_BACKGROUNDS; i++) {
			int row = i / 3;
			int col = i % 3;
			int x = 200 + col * 300;
			int y = 400 - row * 250;

			if (mx >= x && mx <= x + 200 && my >= y && my <= y + 150) {
				selectedBackground = i;
				backgroundSelectionMode = 0;
				break;
			}
		}
	}
}

void drawOpenPage(){
	iFilledRectangle(0, 0, 1280, 720);
	iShowBMP2(0, 0, "Images//openPage.bmp", 0);
}
void homePageHandler(){
	openPage = 0;
	homePage = 1;
}
void drawHomePage(){
	iShowBMP2(0, 0, "Images//homePage1.bmp", 0);

	if (playHover[0] == 1){
		iShowBMP2(980, 380, "Images//playGlow.bmp", 0);
	}
	else if (playHover[0] == 0){
		iShowBMP2(980, 380, "Images//play.bmp", 0);
	}
	if (playHover[1] == 1){
		iShowBMP2(980, 280, "Images//optionGlow.bmp", 0);
	}
	else if (playHover[1] == 0){
		iShowBMP2(980, 280, "Images//option.bmp", 0);
	}
	if (playHover[2] == 1){
		iShowBMP2(980, 180, "Images//creditGlow.bmp", 0);
	}
	else if (playHover[2] == 0){
		iShowBMP2(980, 180, "Images//credit.bmp", 0);
	}
	if (playHover[3] == 1){
		iShowBMP2(980, 80, "Images//quitGlow.bmp", 0);
	}
	else if (playHover[3] == 0){
		iShowBMP2(980, 80, "Images//quit.bmp", 0);
	}



}
void playButtonHandler(){
	homePage = 0;
	backgroundSelectionMode = 1;
}
void drawPlayPage(){
	iSetColor(255, 255, 255);
	iText(500, 650, "Select a background:", GLUT_BITMAP_TIMES_ROMAN_24);


	for (int i = 0; i < TOTAL_BACKGROUNDS; i++) {
		int row = i / 3;
		int col = i % 3;
		int x = 200 + col * 300;
		int y = 400 - row * 250;


		iSetColor(200, 200, 200);
		iFilledRectangle(x - 5, y - 5, 210, 160);
		iShowImage(x, y, 200, 150, backgrounds[i]);
	}

	if (playHover[4] == 1){
		iShowBMP2(30, 30, "Images//backBig.bmp", 0);
	}
	else if (playHover[4] == 0){
		iShowBMP2(30, 30, "Images//back.bmp", 0);
	}
}
void optionsButtonHandler(){
	homePage = 0;
	optionsPage = 1;
}
void drawOptionsPage(){

	iShowBMP2(0, 0, "Images//instruction.bmp",0);

	if (playHover[4] == 1){
		iShowBMP2(30, 30, "Images//backBig.bmp", 0);
	}
	else if (playHover[4] == 0){
		iShowBMP2(30, 30, "Images//back.bmp", 0);
	}

}
void creditsButtonHandler(){
	homePage = 0;
	creditsPage = 1;
}
void drawCreditsPage(){
	iSetColor(123, 0, 123);
	iShowBMP2(0, 0, "Images//backgroundForCredits11280720.bmp", 0);

	if (playHover[4] == 1){
		iShowBMP2(30, 30, "Images//backBig.bmp", 0);
	}
	else if (playHover[4] == 0){
		iShowBMP2(30, 30, "Images//back.bmp", 0);
	}
}

void backButtonHandler(){
	backgroundSelectionMode = 0;
	optionsPage = 0;
	creditsPage = 0;
	homePage = 1;
}

void fixedUpdate() {
	
}

void character1(){
	if (homePage == 0 && optionsPage == 0 && openPage == 0 && backgroundSelectionMode == 0 && creditsPage == 0) {

		if (isKeyPressed(' ') && !isKicking) {
			isKicking = 1;
			kickFrameIndex = 0;
		}

		if (!isKicking) {
			if (isKeyPressed('a') || isKeyPressed('A')) {
				isRunningLeft = 1;
				isRunningRight = 0;
				frameIndex = (frameIndex - 1 + TOTAL_RUN_FRAMES) % TOTAL_RUN_FRAMES;
				characterX -= 5;
				if (characterX < 0) {
					characterX = 0;
				}
			}
			else if (isKeyPressed('d') || isKeyPressed('D')) {
				isRunningRight = 1;
				isRunningLeft = 0;
				frameIndex = (frameIndex + 1) % TOTAL_RUN_FRAMES;
				characterX += 5;
				if (characterX > 1280 - 350) {
					characterX = 1280 - 350;
				}
			}
			else {
				isRunningLeft = 0;
				isRunningRight = 0;
			}
		}
		else {
			isRunningLeft = 0;
			isRunningRight = 0;
		}
	}
}

void character1_kick() {

	if (isKicking) {
		kickFrameIndex++;

		if (kickFrameIndex >= TOTAL_KICK_FRAMES) {
			isKicking = 0;
		}
	}
}

void character2(){
	if (homePage == 0 && optionsPage == 0 && openPage == 0 && backgroundSelectionMode == 0 && creditsPage == 0) {
		if (isSpecialKeyPressed(GLUT_KEY_LEFT)) {
			isChar2RunningLeft = 1;
			isChar2RunningRight = 0;
			char2FrameIndex = (char2FrameIndex - 1 + TOTAL_RUN_FRAMES2) % TOTAL_RUN_FRAMES2;
			character2X -= 5;
			if (character2X < 0) {
				character2X = 0;
			}
		}
		else if (isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
			isChar2RunningRight = 1;
			isChar2RunningLeft = 0;
			char2FrameIndex = (char2FrameIndex + 1) % TOTAL_RUN_FRAMES2;
			character2X += 5;
			if (character2X > 1280 - 350) {
				character2X = 1280 - 350;
			}
		}
		else {
			isChar2RunningLeft = 0;
			isChar2RunningRight = 0;
		}
	}
}


int main() {
	iInitialize(1280, 720, "1v1 - Fight To The Death");
	loadImages();
	iSetTimer(50, character1_kick);
	iSetTimer(30, character1);
	iSetTimer(30, character2);
	iStart();
	return 0;
}
