#include "iGraphics.h"
#include <stdlib.h>

void resetMyGame();
void drawOpenPage();
void drawHomePage();
void drawPlayPage();
void drawOptionsPage();
void drawCreditsPage();
void drawGamePage();
void drawConfirmationPage();
void drawVictoryPage(int winner);

void homePageHandler();
void playButtonHandler();
void optionsButtonHandler();
void creditsButtonHandler();
void gamePageHandler();
void confirmationPageHandler();
void backButtonHandler();
void victoryPageHandler(int winner);

bool isCharacter1Blocking();
bool isCharacter2Blocking();

void playRound1BGM();
void playRound2BGM();
void playRound3BGM();
void stopBGM();

void updateVictoryPage();
void updateCharacter1Animation();
void updateCharacter2Animation();
void character1_kick();
void character2_actions();
void updateDefaultAnimation();
void checkCollisions();
void updateHealthBars();
void drawHealthBars();
void resetGame();
void playOpenBGM();
void stopOpenBGM();
void health1Update();
void health2Update();
void showMessage(const char *msg);
void updateMessageTimer();
void checkRoundEnd();
void drawRoundStatus();
void loadMatchRecord();
void saveMatchRecord();

int openPage = 1;
int homePage = 0;
int optionsPage = 0;
int creditsPage = 0;
int gamePage = 0;
int confirmationPage = 0;
int playHover[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int button1 = -1;
int button2 = -1;
int openBGMPlaying = 0;
int changeHealth1 = 0;
int changeHealth2 = 0;
int totalMatchesWon1 = 0;
int totalMatchesWon2 = 0;
int totalWinsP1 = 0;        
int totalWinsP2 = 0;

int currentBGM = 0;

int victoryPage = 0;       // 0 = no, 1 = yes
int victoryWinner = 0;     // 1 = player 1, 2 = player 2


#define TOTAL_RUN_FRAMES 42
#define TOTAL_BACKWARD_FRAMES 53  
#define TOTAL_KICK_FRAMES 53
#define TOTAL_KICKUP_FRAMES 61
#define TOTAL_KICKDOWN_FRAMES 56
#define TOTAL_SWORD_FRAMES 51
#define TOTAL_SWORDUP_FRAMES 49
#define TOTAL_SWORDDOWN_FRAMES 66

#define TOTAL_BACKGROUNDS 6

#define TOTAL_RUN_FRAMES2 61
#define TOTAL_BACKWARD_FRAMES2 64
#define TOTAL_KICK_FRAMES2 56
#define TOTAL_KICKUP_FRAMES2 56
#define TOTAL_KICKDOWN_FRAMES2 48  
#define TOTAL_AXE_FRAMES2 63
#define TOTAL_AXEUP_FRAMES2 46
#define TOTAL_AXEDOWN_FRAMES2 64   

//Test Block Frames


#define TOTAL_BLOCKUP_FRAMES1 21
#define TOTAL_BLOCKDOWN_FRAMES1 35
#define TOTAL_BLOCKMID_FRAMES2 17
#define TOTAL_BLOCKUP_FRAMES2 20


int blockUpFrames1[TOTAL_BLOCKUP_FRAMES1];
int blockDownFrames1[TOTAL_BLOCKDOWN_FRAMES1];
int blockMidFrames2[TOTAL_BLOCKMID_FRAMES2];
int blockUpFrames2[TOTAL_BLOCKUP_FRAMES2];


int isBlockingUp1 = 0;
int isBlockingDown1 = 0;
int isBlockingMid2 = 0;
int isBlockingUp2 = 0;
int blockUpFrameIndex1 = 0;
int blockDownFrameIndex1 = 0;
int blockMidFrameIndex2 = 0;
int blockUpFrameIndex2 = 0;

//Block Frames


int frameIndex = 0;
int runFrames[TOTAL_RUN_FRAMES];
int backwardFrames[TOTAL_BACKWARD_FRAMES];
int kickFrames[TOTAL_KICK_FRAMES];
int kickUpFrames[TOTAL_KICKUP_FRAMES];
int kickDownFrames[TOTAL_KICKDOWN_FRAMES];
int swordFrames[TOTAL_SWORD_FRAMES];
int swordUpFrames[TOTAL_SWORDUP_FRAMES];
int swordDownFrames[TOTAL_SWORDDOWN_FRAMES];

int runFrames2[TOTAL_RUN_FRAMES2];
int backwardFrames2[TOTAL_BACKWARD_FRAMES2];
int kickFrames2[TOTAL_KICK_FRAMES2];
int kickUpFrames2[TOTAL_KICKUP_FRAMES2];
int kickDownFrames2[TOTAL_KICKDOWN_FRAMES2];
int axeFrames2[TOTAL_AXE_FRAMES2];
int axeUpFrames2[TOTAL_AXEUP_FRAMES2];
int axeDownFrames2[TOTAL_AXEDOWN_FRAMES2];

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
int isRunningBackward = 0;
int isKicking = 0;
int isKickingUp = 0;
int isKickingDown = 0;
int isSword = 0;
int isSwordUp = 0;
int isSwordDown = 0;

int isChar2RunningRight = 0;
int isChar2RunningLeft = 0;
int isChar2RunningBackward = 0;
int isChar2Kicking = 0;
int isChar2KickingUp = 0;
int isChar2KickingDown = 0;
int isChar2Axe = 0;
int isChar2AxeDown = 0;
int isChar2AxeUp = 0;

int character2X = 800;
int character2Y = 15;
int char2FrameIndex = 0;

int kickFrameIndex = 0;
int kickUpFrameIndex = 0;
int kickDownFrameIndex = 0;
int swordFrameIndex = 0;
int swordUpFrameIndex = 0;
int swordDownFrameIndex = 0;

int kickFrameIndex2 = 0;
int kickUpFrameIndex2 = 0;
int kickDownFrameIndex2 = 0;
int axeFrameIndex2 = 0;
int axeUpFrameIndex2 = 0;
int axeDownFrameIndex2 = 0;

int char2KickFrameIndex = 0;
int char2KickUpFrameIndex = 0;
int char2KickDownFrameIndex = 0;
int char2AxeFrameIndex = 0;
int char2AxeUpFrameIndex = 0;
int char2AxeDownFrameIndex = 0;

int health1 = 0;
int health2 = 0;

bool damageGiven1 = false;
bool damageGiven2 = false;

int bgPrime = -1;
int leftButton = -1;
int rightButton = -1;
int currentBgIndex = 0;

int x = 0;
int y = 0;
int char1 = 0;
int char2 = 0;

bool canDamage1 = false;
bool canDamage2 = false;

int roundNumber = 1;     // current round
int score1 = 0;          // points of character 1
int score2 = 0;          // points of character 2
bool roundActive = true; // is round currently playing
bool gameOver = false;   // is final result decided
bool showRoundMessage = false;   // show "Round X Start/Over"
char roundMessage[50];           // store message text
int messageTimer = 0;


void loadImages() {
	char path[64];


	for (int i = 0; i < TOTAL_RUN_FRAMES; i++) {
		sprintf_s(path, sizeof(path), "Images/Character 1/Forward/%d.png", i + 1);
		runFrames[i] = iLoadImage(path);
	}


	for (int i = 0; i < TOTAL_BACKWARD_FRAMES; i++) {
		sprintf_s(path, sizeof(path), "Images/Character 1/Backward/%d.png", i + 1);
		backwardFrames[i] = iLoadImage(path);
	}


	for (int i = 0; i < TOTAL_KICK_FRAMES; i++) {
		sprintf_s(path, sizeof(path), "Images/Character 1/Kick/%d.png", i + 1);
		kickFrames[i] = iLoadImage(path);
	}


	for (int i = 0; i < TOTAL_KICKUP_FRAMES; i++) {
		sprintf_s(path, sizeof(path), "Images/Character 1/KickUp/%d.png", i + 1);
		kickUpFrames[i] = iLoadImage(path);
	}


	for (int i = 0; i < TOTAL_KICKDOWN_FRAMES; i++) {
		sprintf_s(path, sizeof(path), "Images/Character 1/KickDown/%d.png", i + 1);
		kickDownFrames[i] = iLoadImage(path);
	}


	for (int i = 0; i < TOTAL_SWORD_FRAMES; i++) {
		sprintf_s(path, sizeof(path), "Images/Character 1/Sword/%d.png", i + 1);
		swordFrames[i] = iLoadImage(path);
	}


	for (int i = 0; i < TOTAL_SWORDUP_FRAMES; i++) {
		sprintf_s(path, sizeof(path), "Images/Character 1/SwordUp/%d.png", i + 1);
		swordUpFrames[i] = iLoadImage(path);
	}


	for (int i = 0; i < TOTAL_SWORDDOWN_FRAMES; i++) {
		sprintf_s(path, sizeof(path), "Images/Character 1/SwordDown/%d.png", i + 1);
		swordDownFrames[i] = iLoadImage(path);
	}


	for (int i = 0; i < TOTAL_RUN_FRAMES2; i++) {
		sprintf_s(path, sizeof(path), "Images/Character 2/Forward/%d.png", i + 1);
		runFrames2[i] = iLoadImage(path);
	}


	for (int i = 0; i < TOTAL_BACKWARD_FRAMES2; i++) {
		sprintf_s(path, sizeof(path), "Images/Character 2/Backward/%d.png", i + 1);
		backwardFrames2[i] = iLoadImage(path);
	}


	for (int i = 0; i < TOTAL_KICK_FRAMES2; i++) {
		sprintf_s(path, sizeof(path), "Images/Character 2/Kick/%d.png", i + 1);
		kickFrames2[i] = iLoadImage(path);
	}


	for (int i = 0; i < TOTAL_KICKUP_FRAMES2; i++) {
		sprintf_s(path, sizeof(path), "Images/Character 2/KickUp/%d.png", i + 1);
		kickUpFrames2[i] = iLoadImage(path);
	}


	for (int i = 0; i < TOTAL_KICKDOWN_FRAMES2; i++) {
		sprintf_s(path, sizeof(path), "Images/Character 2/KickDown/%d.png", i + 1);
		kickDownFrames2[i] = iLoadImage(path);
	}


	for (int i = 0; i < TOTAL_AXE_FRAMES2; i++) {
		sprintf_s(path, sizeof(path), "Images/Character 2/Axe/%d.png", i + 1);
		axeFrames2[i] = iLoadImage(path);
	}

	for (int i = 0; i < TOTAL_AXEUP_FRAMES2; i++) {
		sprintf_s(path, sizeof(path), "Images/Character 2/AxeUp/%d.png", i + 1);
		axeUpFrames2[i] = iLoadImage(path);
	}

	for (int i = 0; i < TOTAL_AXEDOWN_FRAMES2; i++) {
		sprintf_s(path, sizeof(path), "Images/Character 2/AxeDown/%d.png", i + 1);
		axeDownFrames2[i] = iLoadImage(path);
	}


	for (int i = 0; i < TOTAL_BACKGROUNDS; i++) {
		sprintf_s(path, sizeof(path), "Images/BG/background%d.png", i + 1);
		backgrounds[i] = iLoadImage(path);
	}

	//Block Images Load

	for (int i = 0; i < TOTAL_BLOCKUP_FRAMES1; i++) {
		sprintf_s(path, sizeof(path), "Images/Reaction/Character 1/BlockUp/%d.png", i + 1);
		blockUpFrames1[i] = iLoadImage(path);
	}

	for (int i = 0; i < TOTAL_BLOCKDOWN_FRAMES1; i++) {
		sprintf_s(path, sizeof(path), "Images/Reaction/Character 1/BlockDown/%d.png", i + 1);
		blockDownFrames1[i] = iLoadImage(path);
	}

	for (int i = 0; i < TOTAL_BLOCKMID_FRAMES2; i++) {
		sprintf_s(path, sizeof(path), "Images/Reaction/Character 2/BlockMid/%d.png", i + 1);
		blockMidFrames2[i] = iLoadImage(path);
	}

	for (int i = 0; i < TOTAL_BLOCKUP_FRAMES2; i++) {
		sprintf_s(path, sizeof(path), "Images/Reaction/Character 2/BlockUp/%d.png", i + 1);
		blockUpFrames2[i] = iLoadImage(path);
	}

	//Block Images

	defaultFrame = iLoadImage("Images/default.png");
	defaultFrame2 = iLoadImage("Images/default1.png");

	bgPrime = iLoadImage("Images/BGPrime.png");
	leftButton = iLoadImage("Images/Left.png");
	rightButton = iLoadImage("Images/Right.png");

	 char1 = iLoadImage("Images//C2Default.png");
	 char2 = iLoadImage("Images//C1Default.png");

	imagesLoaded = 1;
}

void iDraw()
{
	iClear();
	if (openPage == 1 || homePage == 1 || backgroundSelectionMode == 1 || optionsPage == 1 || creditsPage == 1 ) {
		playOpenBGM();
	}
	else if (gamePage == 1 || confirmationPage == 1) {
		stopOpenBGM();
	}

	if (openPage == 1){
		drawOpenPage();
	}
	else if (homePage == 1){
		drawHomePage();
	}
	else if (backgroundSelectionMode == 1){
		drawPlayPage();
	}
	else if (gamePage == 1) {
		drawGamePage();
	}
	else if (optionsPage == 1){
		drawOptionsPage();
	}
	else if (creditsPage == 1){
		drawCreditsPage();
	}
	else if (confirmationPage == 1){
		drawConfirmationPage();
	}
	if (victoryPage == 1){
		updateVictoryPage();
	}

	// Show round number and scores (when game is not over)
	if (gamePage == 1) {
		if (!gameOver) {
			char buffer[100];
			sprintf_s(buffer, "Round: %d", roundNumber);
			iSetColor(0, 255, 0);
			iText(600, 650, buffer, GLUT_BITMAP_TIMES_ROMAN_24);

			sprintf_s(buffer, "Player1: %d  Player2: %d", score1, score2);
			iText(530, 600, buffer, GLUT_BITMAP_TIMES_ROMAN_24);
		}

		if (showRoundMessage) {
			iSetColor(255, 255, 0);
			iText(580, 400, roundMessage, GLUT_BITMAP_TIMES_ROMAN_24);
		}

		if (!gameOver) {
			checkRoundEnd();
		}
	}
	drawRoundStatus();
	

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
	if (confirmationPage == 1 && mx >= 545 && mx <= 735 && my >= 420 && my <= 480){
		playHover[4] = 1;
	}
	else{
		playHover[4] = 0;
	}
	if (confirmationPage == 1 && mx >= 545 && mx <= 735 && my >= 300 && my <= 360){
		playHover[5] = 1;
	}
	else{
		playHover[5] = 0;
	}
	if ((backgroundSelectionMode == 1 || optionsPage == 1 || creditsPage == 1 || gamePage == 1) && mx >= 30 && mx <= 110 && my >= 30 && my <= 102){
		playHover[9] = 1;
	}
	else{
		playHover[9] = 0;
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
		else if ((homePage == 1) && (mx >= 980 && mx <= 1170 && my >= 80 && my <= 140)){
			exit(0);
		}
		else if ((victoryPage == 1) && (mx >= 0 && mx <= 1280 && my >= 0 && my <= 720)){
			homePageHandler();
		}

		else if (backgroundSelectionMode == 1) {
			int centerX = 1280 / 2;
			int centerY = 720 / 2;

			int leftBgX = centerX - 400;
			int rightBgX = centerX + 200;
			int leftButtonX = leftBgX - 120;
			int rightButtonX = rightBgX + 200 + 20;
			int buttonY = centerY - 50;

			if (mx >= leftButtonX && mx <= leftButtonX + 100 && my >= buttonY && my <= buttonY + 100) {
				currentBgIndex = (currentBgIndex - 1 + TOTAL_BACKGROUNDS) % TOTAL_BACKGROUNDS;
			}

			else if (mx >= rightButtonX && mx <= rightButtonX + 100 && my >= buttonY && my <= buttonY + 100) {
				currentBgIndex = (currentBgIndex + 1) % TOTAL_BACKGROUNDS;
			}

			else if (mx >= centerX - 175 && mx <= centerX + 175 && my >= centerY - 112 && my <= centerY + 113) {
				selectedBackground = currentBgIndex;
				gamePageHandler();
			}
		}

		else if ((confirmationPage == 1) && (mx >= 545 && mx <= 735 && my >= 300 && my <= 360)){
			homePageHandler();
		}
		else if ((confirmationPage == 1) && (mx >= 545 && mx <= 735 && my >= 420 && my <= 480)){
			gamePage = 1;
			//gamePageHandler();
		}
		if ((backgroundSelectionMode == 1 || optionsPage == 1 || creditsPage == 1 || gamePage == 1) && mx >= 30 && mx <= 110 && my >= 30 && my <= 102){
			backButtonHandler();
		}
	}
}
void resetMyGame() {
	// Reset character positions
	int characterX = 15;
	int characterY = 15;
	character2X = 800;
	character2Y = 15;

	// Reset health
	health1 = 0;
	health2 = 0;

	// Reset attack flags for both characters
	isKicking = 0;
	isKickingUp = 0;
	isKickingDown = 0;
	isSword = 0;
	isSwordUp = 0;
	isSwordDown = 0;

	isChar2Kicking = 0;
	isChar2KickingUp = 0;
	isChar2KickingDown = 0;
	isChar2Axe = 0;
	isChar2AxeUp = 0;
	isChar2AxeDown = 0;

	isBlockingUp1 = 0;
	isBlockingDown1 = 0;
	isBlockingMid2 = 0;
	isBlockingUp2 = 0;
	blockUpFrameIndex1 = 0;
	blockDownFrameIndex1 = 0;
	blockMidFrameIndex2 = 0;
	blockUpFrameIndex2 = 0;

	changeHealth1 = 0;
	changeHealth2 = 0;

	// Reset animation frame indices
	kickFrameIndex = kickUpFrameIndex = kickDownFrameIndex = 0;
	swordFrameIndex = swordUpFrameIndex = swordDownFrameIndex = 0;

	char2KickFrameIndex = char2KickUpFrameIndex = char2KickDownFrameIndex = 0;
	char2AxeFrameIndex = char2AxeUpFrameIndex = char2AxeDownFrameIndex = 0;

	// Reset running flags
	isRunningRight = isRunningLeft = isRunningBackward = 0;
	isChar2RunningRight = isChar2RunningBackward = 0;

	// Reset damage flags
	damageGiven1 = damageGiven2 = false;
	canDamage1 = canDamage2 = false;
}

void victoryPageHandler(int winner)
{
	gamePage = 0;
	victoryPage = 1;       // start showing victory page
	victoryWinner = winner;

}

// Call this inside your main draw function
void drawVictoryPage(int winner)
{
	// Draw the victory background BMP
	

	// Draw the winner's character on top
	if (winner == 1)
	{
		iShowBMP2(0, 0, "Images//Winner1.bmp", 0);
		iShowImage(515, 60, 250, 550, char1);
		
	}
	else if (winner == 2)
	{
		iShowBMP2(0, 0, "Images//Winner2.bmp", 0);
		iShowImage(515, 60, 250, 550, char2);
		
	}
}

void updateVictoryPage()
{
	if (victoryPage)
	{
		
		drawVictoryPage(victoryWinner);

		iSetColor(255, 255, 255);
		iText(530, 30, "Click anywhere to return to Home", GLUT_BITMAP_HELVETICA_18);
	}
}

void showMessage(const char *msg) {
	strcpy_s(roundMessage, msg);
	showRoundMessage = true;
	messageTimer = 100;  // show ~4 seconds (assuming iSetTimer(30,...))

}
void updateMessageTimer() {
	if (showRoundMessage) {
		messageTimer--;

		if (messageTimer <= 0) {
			showRoundMessage = false;
			if (gameOver) {
				gamePage = 0;
				homePageHandler();
			}
		}

	}
}
void checkRoundEnd() {
	// If the round is active, watch for a KO and end the round.
	if (roundActive) {
		if (health1 >= 5) {
			score2++;
			roundActive = false;
			sprintf_s(roundMessage, "Round %d Over! Player 2 Wins", roundNumber);
			showMessage(roundMessage);
		}
		else if (health2 >= 5) {
			score1++;
			roundActive = false;
			sprintf_s(roundMessage, "Round %d Over! Player 1 Wins", roundNumber);
			showMessage(roundMessage);


		}
		
		return; // done while round is active
	}


	// If the round is NOT active, wait for the message to disappear,
	// then either start next round or finish the game.
	if (!showRoundMessage && !roundActive) {
		if (roundNumber == 1) {
			resetMyGame();
			roundNumber = 2;
			roundActive = true;
			showMessage("Round 2 Start!");
			playRound2BGM();
		}
		else if (roundNumber == 2 && score1 == score2) {
			resetMyGame();
			roundNumber = 3; // bonus round
			roundActive = true;
			showMessage("Bonus Round Start!");
			playRound3BGM();
		}
		else {
			if (score1 > score2){
				totalMatchesWon1++;
				saveMatchRecord();
				victoryPageHandler(1);
			}
			if (score1 < score2){
				totalMatchesWon2++;
				saveMatchRecord();
				victoryPageHandler(2);
			}
		}

	}
}

void drawRoundStatus(){
	int gap = 25;   
	if (gamePage){
		for (int i = 0; i < 3; i++) {
			if (i < score1) {
				iShowBMP2(300 + (i*gap), 595, "Images//roundUpdateGlow.bmp", 0);  // glow
			}
			else {
				iShowBMP2(300 + (i*gap), 595, "Images//roundUpdate.bmp", 0); // normal
			}
		}
		for (int i = 0; i < 3; i++) {
			if (i < score2) {
				iShowBMP2(965 - (i*gap), 595, "Images//roundUpdateGlow.bmp", 0);
			}
			else{
				iShowBMP2(965 - (i*gap), 595, "Images//roundUpdate.bmp", 0);
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
	gamePage = 0;
	confirmationPage = 0;
	victoryPage = 0;
	homePage = 1;
	/*stopBGM();*/
}
void drawHomePage(){
	resetMyGame();
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
	gamePage = 0;
	optionsPage = 0;
	creditsPage = 0;
	confirmationPage = 0;
}



void optionsButtonHandler(){
	homePage = 0;
	optionsPage = 1;
}
void drawOptionsPage(){
	iShowBMP2(0, 0, "Images//instruction.bmp", 0);

	if (playHover[9] == 1){
		iShowBMP2(30, 30, "Images//backBig.bmp", 0);
	}
	else if (playHover[9] == 0){
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

	if (playHover[9] == 1){
		iShowBMP2(30, 30, "Images//backBig.bmp", 0);
	}
	else if (playHover[9] == 0){
		iShowBMP2(30, 30, "Images//back.bmp", 0);
	}
}

void gamePageHandler(){
	backgroundSelectionMode = 0;
	gamePage = 1;

	roundNumber = 1;
	score1 = 0;
	score2 = 0;
	gameOver = false;
	roundActive = true;

	resetMyGame();
	showMessage("Round 1 Start!");
	stopOpenBGM();
	playRound1BGM();
}
void drawGamePage(){
	iShowImage(0, 0, 1280, 720, backgrounds[selectedBackground]);

	char hb1[100];
	sprintf_s(hb1, "Images//healthbar1//%d.bmp", health1);
	iShowBMP2(150, 600, hb1, 0);

	char hb2[100];
	sprintf_s(hb2, "Images//healthbar2//%d.bmp", health2);
	iShowBMP2(730, 600, hb2, 0);



	if (isBlockingUp1) {
		iShowImage(characterX, characterY, 350, 350, blockUpFrames1[blockUpFrameIndex1]);
	}
	else if (isBlockingDown1) {
		iShowImage(characterX, characterY, 350, 350, blockDownFrames1[blockDownFrameIndex1]);
	}
	else if (isKicking) {
		iShowImage(characterX, characterY, 350, 350, kickFrames[kickFrameIndex]);
	}
	else if (isKickingUp) {
		iShowImage(characterX, characterY, 350, 350, kickUpFrames[kickUpFrameIndex]);
	}
	else if (isKickingDown) {
		iShowImage(characterX, characterY, 350, 350, kickDownFrames[kickDownFrameIndex]);
	}
	else if (isSword) {
		iShowImage(characterX, characterY, 350, 350, swordFrames[swordFrameIndex]);
	}
	else if (isSwordUp) {
		iShowImage(characterX, characterY, 350, 350, swordUpFrames[swordUpFrameIndex]);
	}
	else if (isSwordDown) {
		iShowImage(characterX, characterY, 350, 350, swordDownFrames[swordDownFrameIndex]);
	}
	else if (isRunningRight) {
		iShowImage(characterX, characterY, 350, 350, runFrames[frameIndex]);
	}
	else if (isRunningBackward) {
		iShowImage(characterX, characterY, 350, 350, backwardFrames[frameIndex]);
	}
	else {
		iShowImage(characterX, characterY, 350, 350, defaultFrame);
	}


	if (isBlockingUp2) {
		iShowImage(character2X, character2Y, 350, 350, blockUpFrames2[blockUpFrameIndex2]);
	}
	else if (isBlockingMid2) {
		iShowImage(character2X, character2Y, 350, 350, blockMidFrames2[blockMidFrameIndex2]);
	}
	else if (isChar2Kicking) {
		iShowImage(character2X, character2Y, 350, 350, kickFrames2[char2KickFrameIndex]);
	}
	else if (isChar2KickingUp) {
		iShowImage(character2X, character2Y, 350, 350, kickUpFrames2[char2KickUpFrameIndex]);
	}
	else if (isChar2KickingDown) {
		iShowImage(character2X, character2Y, 350, 350, kickDownFrames2[char2KickDownFrameIndex]);
	}
	else if (isChar2Axe) {
		iShowImage(character2X, character2Y, 350, 350, axeFrames2[char2AxeFrameIndex]);
	}
	else if (isChar2AxeUp) {
		iShowImage(character2X, character2Y, 350, 350, axeUpFrames2[char2AxeUpFrameIndex]);
	}
	else if (isChar2AxeDown) {
		iShowImage(character2X, character2Y, 350, 350, axeDownFrames2[char2AxeDownFrameIndex]);
	}
	else if (isChar2RunningRight) {
		iShowImage(character2X, character2Y, 350, 350, runFrames2[char2FrameIndex]);
	}
	else if (isChar2RunningBackward) {
		iShowImage(character2X, character2Y, 350, 350, backwardFrames2[char2FrameIndex]);
	}
	else {
		iShowImage(character2X, character2Y, 350, 350, defaultFrame2);
	}
	char record[100];

	iSetColor(255, 255, 255);

	sprintf_s(record, "Player 1 won %d matches", totalMatchesWon1);
	iText(75, 560, record, GLUT_BITMAP_TIMES_ROMAN_24);

	sprintf_s(record, "Player 2 won %d matches", totalMatchesWon2);
	iText(1036, 560, record, GLUT_BITMAP_TIMES_ROMAN_24);


	if (playHover[9] == 1){
		iShowBMP2(30, 30, "Images//backBig.bmp", 0);
	}
	else if (playHover[9] == 0){
		iShowBMP2(30, 30, "Images//back.bmp", 0);
	}
}

void drawPlayPage(){

	iShowImage(0, 0, 1280, 720, bgPrime);

	int centerX = 1280 / 2;
	int centerY = 720 / 2;

	int leftIndex = (currentBgIndex - 1 + TOTAL_BACKGROUNDS) % TOTAL_BACKGROUNDS;
	int leftBgX = centerX - 400;
	int leftBgY = centerY - 75;
	iShowImage(leftBgX, leftBgY, 200, 150, backgrounds[leftIndex]);

	int centerBgX = centerX - 175;
	int centerBgY = centerY - 112;
	iShowImage(centerBgX, centerBgY, 350, 225, backgrounds[currentBgIndex]);

	int rightIndex = (currentBgIndex + 1) % TOTAL_BACKGROUNDS;
	int rightBgX = centerX + 200;
	int rightBgY = centerY - 75;
	iShowImage(rightBgX, rightBgY, 200, 150, backgrounds[rightIndex]);

	int leftButtonX = leftBgX - 120;
	int rightButtonX = rightBgX + 200 + 20;
	int buttonY = centerY - 50;

	iShowImage(leftButtonX, buttonY, 50, 50, leftButton);
	iShowImage(rightButtonX, buttonY, 50, 50, rightButton);

	if (playHover[9] == 1){
		iShowBMP2(30, 30, "Images//backBig.bmp", 0);
	}
	else {
		iShowBMP2(30, 30, "Images//back.bmp", 0);
	}
}

void confirmationPageHandler(){
	gamePage = 0;
	confirmationPage = 1;
}
void drawConfirmationPage(){
	iShowBMP2(0, 0, "Images//confirmPage.bmp", 0);
	if (playHover[4] == 1){
		iShowBMP2(545, 420, "Images//resumeGlow.bmp", 0);
	}
	else if (playHover[4] == 0){
		iShowBMP2(545, 420, "Images//resume.bmp", 0);
	}
	if (playHover[5] == 1){
		iShowBMP2(545, 300, "Images//exitGlow.bmp", 0);
	}
	else if (playHover[5] == 0){
		iShowBMP2(545, 300, "Images//exit.bmp", 0);
	}
}
void backButtonHandler(){
	 if (backgroundSelectionMode == 1 || optionsPage == 1 || creditsPage == 1){
		backgroundSelectionMode = 0;
		optionsPage = 0;
		creditsPage = 0;
		homePage = 1;
	}
	else if (gamePage == 1){
		confirmationPageHandler();
	}
}

void fixedUpdate() {

}

void character1(){
	if (homePage == 0 && optionsPage == 0 && openPage == 0 && backgroundSelectionMode == 0 && creditsPage == 0) {


		if (isKeyPressed(27)) {
			if (gamePage == 1) {
				if (confirmationPage == 0) {
					confirmationPageHandler();
				}
				else {
					gamePageHandler();
				}
			}
		}


		if (isKeyPressed(' ') && isKeyPressed('w') && !isKickingUp) {
			isKickingUp = 1;
			isKicking = 0;
			isKickingDown = 0;
			kickUpFrameIndex = 0;
			damageGiven1 = false;
			canDamage1 = true;
		}
		if (isKeyPressed('q') && !isBlockingUp1 && !isBlockingDown1) {
			isBlockingUp1 = 1;
			blockUpFrameIndex1 = 0;
		}

		if (isKeyPressed('e') && !isBlockingUp1 && !isBlockingDown1) {
			isBlockingDown1 = 1;
			blockDownFrameIndex1 = 0;
		}
		else if (isKeyPressed(' ') && isKeyPressed('s') && !isKickingDown) {
			isKickingDown = 1;
			isKicking = 0;
			isKickingUp = 0;
			kickDownFrameIndex = 0;
			damageGiven1 = false;
			canDamage1 = true;
		}
		else if (isKeyPressed(' ') && !isKicking && !isKickingUp && !isKickingDown) {
			isKicking = 1;
			kickFrameIndex = 0;
			damageGiven1 = false;
			canDamage1 = true;
		}


		else if (isKeyPressed('f') && isKeyPressed('w') && !isSwordUp) {
			isSwordUp = 1;
			isSword = 0;
			isSwordDown = 0;
			swordUpFrameIndex = 0;
			damageGiven1 = false;
			canDamage1 = true;
		}
		else if (isKeyPressed('f') && isKeyPressed('s') && !isSwordDown) {
			isSwordDown = 1;
			isSword = 0;
			isSwordUp = 0;
			swordDownFrameIndex = 0;
			damageGiven1 = false;
			canDamage1 = true;
		}
		else if (isKeyPressed('f') && !isSword && !isSwordUp && !isSwordDown) {
			isSword = 1;
			swordFrameIndex = 0;
			damageGiven1 = false;
			canDamage1 = true;
		}


		if (!isKicking && !isKickingUp && !isKickingDown && !isSword && !isSwordUp && !isSwordDown) {
			if (isKeyPressed('a') || isKeyPressed('A')) {
				isRunningBackward = 1;
				isRunningRight = 0;
				isRunningLeft = 0;
				frameIndex = (frameIndex + 1) % TOTAL_BACKWARD_FRAMES;
				characterX -= 5;
				if (characterX < 0) {
					characterX = 0;
				}
			}
			else if (isKeyPressed('d') || isKeyPressed('D')) {
				isRunningRight = 1;
				isRunningLeft = 0;
				isRunningBackward = 0;
				frameIndex = (frameIndex + 1) % TOTAL_RUN_FRAMES;
				characterX += 5;
				if (characterX > 1280 - 350) {
					characterX = 1280 - 350;
				}
			}
			else if (isKeyPressed('w') || isKeyPressed('W')) {

			}
			else if (isKeyPressed('s') || isKeyPressed('S')) {

			}
			else {
				isRunningLeft = 0;
				isRunningRight = 0;
				isRunningBackward = 0;
			}
		}
		else {

			isRunningLeft = 0;
			isRunningRight = 0;
			isRunningBackward = 0;
		}
	}
}

void character2(){
	if (homePage == 0 && optionsPage == 0 && openPage == 0 && backgroundSelectionMode == 0 && creditsPage == 0) {

		if (isKeyPressed(VK_RETURN) && isSpecialKeyPressed(GLUT_KEY_DOWN) && !isChar2AxeDown) {
			isChar2AxeDown = 1;
			isChar2AxeUp = 0;
			isChar2Axe = 0;
			char2AxeDownFrameIndex = 0;
			damageGiven2 = false;
			canDamage2 = true;
		}
		else if (isKeyPressed(VK_RETURN) && isSpecialKeyPressed(GLUT_KEY_UP) && !isChar2AxeUp) {
			isChar2AxeDown = 0;
			isChar2AxeUp = 1;
			isChar2Axe = 0;
			char2AxeUpFrameIndex = 0;
			damageGiven2 = false;
			canDamage2 = true;
		}
		else if (isKeyPressed(VK_RETURN) && !isChar2Axe && !isChar2AxeDown && !isChar2AxeUp) {
			isChar2Axe = 1;
			char2AxeFrameIndex = 0;
			damageGiven2 = false;
			canDamage2 = true;
		}

		else if (isKeyPressed('/') && isSpecialKeyPressed(GLUT_KEY_UP) && !isChar2KickingUp) {
			isChar2KickingUp = 1;
			isChar2Kicking = 0;
			isChar2KickingDown = 0;
			char2KickUpFrameIndex = 0;
			damageGiven2 = false;
			canDamage2 = true;
		}
		else if (isKeyPressed('/') && isSpecialKeyPressed(GLUT_KEY_DOWN) && !isChar2KickingDown) {
			isChar2KickingDown = 1;
			isChar2Kicking = 0;
			isChar2KickingUp = 0;
			char2KickDownFrameIndex = 0;
			damageGiven2 = false;
			canDamage2 = true;
		}
		else if (isKeyPressed('/') && !isChar2Kicking && !isChar2KickingUp && !isChar2KickingDown) {
			isChar2Kicking = 1;
			char2KickFrameIndex = 0;
			damageGiven2 = false;
			canDamage2 = true;
		}

		if (isKeyPressed(']') && !isBlockingMid2 && !isBlockingUp2) {
			isBlockingMid2 = 1;
			blockMidFrameIndex2 = 0;
		}

		if (isKeyPressed('[') && !isBlockingMid2 && !isBlockingUp2) {
			isBlockingUp2 = 1;
			blockUpFrameIndex2 = 0;
		}

		if (!isChar2Kicking && !isChar2KickingUp && !isChar2KickingDown && !isChar2Axe && !isChar2AxeDown && !isChar2AxeUp) {
			if (isSpecialKeyPressed(GLUT_KEY_LEFT)) {
				isChar2RunningRight = 1;
				isChar2RunningBackward = 0;
				char2FrameIndex = (char2FrameIndex + 1) % TOTAL_RUN_FRAMES2;
				character2X -= 5;
				if (character2X < 0) {
					character2X = 0;
				}
			}
			else if (isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
				isChar2RunningBackward = 1;
				isChar2RunningRight = 0;
				char2FrameIndex = (char2FrameIndex + 1) % TOTAL_BACKWARD_FRAMES2;
				character2X += 5;
				if (character2X > 1280 - 350) {
					character2X = 1280 - 350;
				}
			}
			else {
				isChar2RunningRight = 0;
				isChar2RunningBackward = 0;
			}
		}
		else {
			isChar2RunningRight = 0;
			isChar2RunningBackward = 0;
		}
	}
}

void character1_kick() {
	if (isKicking) {
		kickFrameIndex++;
		if (kickFrameIndex >= TOTAL_KICK_FRAMES) {
			if (changeHealth2){
				health2Update();
				changeHealth2 = 0;
			}
			isKicking = 0;
			canDamage1 = false;
		}
	}

	if (isKickingUp) {
		kickUpFrameIndex++;
		if (kickUpFrameIndex >= TOTAL_KICKUP_FRAMES) {
			if (changeHealth2){
				health2Update();
				changeHealth2 = 0;
			}
			isKickingUp = 0;
			canDamage1 = false;
		}
	}

	if (isKickingDown) {
		kickDownFrameIndex++;
		if (kickDownFrameIndex >= TOTAL_KICKDOWN_FRAMES) {
			if (changeHealth2){
				health2Update();
				changeHealth2 = 0;
			}
			isKickingDown = 0;
			canDamage1 = false;
		}
	}

	if (isSword) {
		swordFrameIndex++;
		if (swordFrameIndex >= TOTAL_SWORD_FRAMES) {
			if (changeHealth2){
				health2Update();
				changeHealth2 = 0;
			}
			isSword = 0;
			canDamage1 = false;
		}
	}

	if (isSwordUp) {
		swordUpFrameIndex++;
		if (swordUpFrameIndex >= TOTAL_SWORDUP_FRAMES) {
			if (changeHealth2){
				health2Update();
				changeHealth2 = 0;
			}
			isSwordUp = 0;
			canDamage1 = false;
		}
	}

	if (isSwordDown) {
		swordDownFrameIndex++;
		if (swordDownFrameIndex >= TOTAL_SWORDDOWN_FRAMES) {
			if (changeHealth2){
				health2Update();
				changeHealth2 = 0;
			}
			isSwordDown = 0;
			canDamage1 = false;
		}
	}
}

void character2_actions() {
	if (isChar2Kicking) {
		char2KickFrameIndex++;
		if (char2KickFrameIndex >= TOTAL_KICK_FRAMES2) {
			if (changeHealth1){
				health1Update();
				changeHealth1 = 0;
			}
			isChar2Kicking = 0;
			canDamage2 = false;
		}
	}

	if (isChar2KickingUp) {
		char2KickUpFrameIndex++;
		if (char2KickUpFrameIndex >= TOTAL_KICKUP_FRAMES2) {
			if (changeHealth1){
				health1Update();
				changeHealth1 = 0;
			}
			isChar2KickingUp = 0;
			canDamage2 = false;
		}
	}

	if (isChar2KickingDown) {
		char2KickDownFrameIndex++;
		if (char2KickDownFrameIndex >= TOTAL_KICKDOWN_FRAMES2) {
			if (changeHealth1){
				health1Update();
				changeHealth1 = 0;
			}
			isChar2KickingDown = 0;
			canDamage2 = false;
		}
	}

	if (isChar2Axe) {
		char2AxeFrameIndex++;
		if (char2AxeFrameIndex >= TOTAL_AXE_FRAMES2) {
			if (changeHealth1){
				health1Update();
				changeHealth1 = 0;
			}
			isChar2Axe = 0;
			canDamage2 = false;
		}
	}

	if (isChar2AxeUp) {
		char2AxeUpFrameIndex++;
		if (char2AxeUpFrameIndex >= TOTAL_AXEUP_FRAMES2) {
			if (changeHealth1){
				health1Update();
				changeHealth1 = 0;
			}
			isChar2AxeUp = 0;
			canDamage2 = false;
		}
	}

	if (isChar2AxeDown) {
		char2AxeDownFrameIndex++;
		if (char2AxeDownFrameIndex >= TOTAL_AXEDOWN_FRAMES2) {
			if (changeHealth1){
				health1Update();
				changeHealth1 = 0;
			}
			isChar2AxeDown = 0;
			canDamage2 = false;
		}
	}
}

void health2Update(){
	health2++;
	if (health2 > 5) health2 = 5;
	damageGiven1 = true;
	canDamage1 = false;
}

void health1Update(){
	health1++;
	if (health1 > 5) health1 = 5;
	damageGiven2 = true;
	canDamage2 = false;
}

void checkCollisions() {
	// Char1 hitting Char2
	if ((canDamage1 == true) && abs(characterX - character2X) < 300) {
		if (!damageGiven1) {
			// Check if character2 is blocking - if so, no damage
			if (!isCharacter2Blocking()) {
				changeHealth2 = 1;
			}
			damageGiven1 = true; // Mark damage as given to prevent multiple hits
		}
	}

	// Char2 hitting Char1
	if ((canDamage2 == true) && abs(character2X - characterX) < 300) {
		if (!damageGiven2) {
			// Check if character1 is blocking - if so, no damage
			if (!isCharacter1Blocking()) {
				changeHealth1 = 1;
			}
			damageGiven2 = true; // Mark damage as given to prevent multiple hits
		}
	}
}

void updateBlockingAnimations() {
	// Character 1 blocking animations
	if (isBlockingUp1) {
		blockUpFrameIndex1++;
		if (blockUpFrameIndex1 >= TOTAL_BLOCKUP_FRAMES1) {
			isBlockingUp1 = 0;
		}
	}

	if (isBlockingDown1) {
		blockDownFrameIndex1++;
		if (blockDownFrameIndex1 >= TOTAL_BLOCKDOWN_FRAMES1) {
			isBlockingDown1 = 0;
		}
	}

	// Character 2 blocking animations
	if (isBlockingMid2) {
		blockMidFrameIndex2++;
		if (blockMidFrameIndex2 >= TOTAL_BLOCKMID_FRAMES2) {
			isBlockingMid2 = 0;
		}
	}

	if (isBlockingUp2) {
		blockUpFrameIndex2++;
		if (blockUpFrameIndex2 >= TOTAL_BLOCKUP_FRAMES2) {
			isBlockingUp2 = 0;
		}
	}
}

void playOpenBGM() {
	if (!openBGMPlaying) {
		PlaySound("Audios/CODBGM.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		openBGMPlaying = 1;
	}
}

void stopOpenBGM() {
	if (openBGMPlaying)
	{
		PlaySound(NULL, 0, 0);
		openBGMPlaying = 0;
	}

}

void playRound1BGM() {
	if (currentBGM != 1) {
		stopBGM();
		PlaySound("Audios/BGM1.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		currentBGM = 1;
	}
}

void playRound2BGM() {
	if (currentBGM != 2) {
		stopBGM();
		PlaySound("Audios/BGM2.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		currentBGM = 2;
	}
}

void playRound3BGM() {
	if (currentBGM != 3) {
		stopBGM();
		PlaySound("Audios/BGM3.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		currentBGM = 3;
	}
}

void stopBGM() {
	PlaySound(NULL, 0, 0);
	currentBGM = 0;
}
void saveMatchRecord() {
	FILE *fptr;
	if (fopen_s(&fptr, "match_record.txt", "w") == 0) {   // fopen_s returns 0 on success
		fprintf(fptr, "Player 1 has won %d matches.\n", totalMatchesWon1);
		fprintf(fptr, "Player 2 has won %d matches.\n", totalMatchesWon2);
		fclose(fptr);
	}
}
void loadMatchRecord() {
    FILE *fptr;
    if (fopen_s(&fptr, "match_record.txt", "r") == 0) {   // open for reading
        fscanf_s(fptr, "Player 1 has won %d matches.\n", &totalMatchesWon1);
        fscanf_s(fptr, "Player 2 has won %d matches.\n", &totalMatchesWon2);
        fclose(fptr);
    }
}



bool isCharacter1Blocking() {
	return isBlockingUp1 || isBlockingDown1;
}


bool isCharacter2Blocking() {
	return isBlockingMid2 || isBlockingUp2;
}




int main() {
	loadMatchRecord();
	iSetTimer(30, updateMessageTimer);
	iInitialize(1280, 720, "1v1 - Fight To The Death");
	loadImages();
	iSetTimer(20, checkCollisions);
	iSetTimer(30, character1_kick);
	iSetTimer(30, character2_actions);
	iSetTimer(60, updateBlockingAnimations);
	iSetTimer(30, character1);
	iSetTimer(30, character2);
	

	iStart();
	return 0;
}