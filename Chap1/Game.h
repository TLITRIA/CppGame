#pragma once
#include <iostream>
#include "SDL.h"
#include "Math.h"

class Game
{
public:
	Game();

	bool Initialize();
	void RunLoop();
	void Shutdown();

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool isRunning;

	Vector2 mBallPos, mBallVel;
		
		
	// P1
	Vector2 mPaddlePos_P1;	// 代表板子的几何中心点
	int mPaddleDir_P1;

	// P2
	Vector2 mPaddlePos_P2;
	int mPaddleDir_P2;
};
