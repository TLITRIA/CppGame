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

	Vector2 mBallPos, mBallVel, mPaddlePos;
	int mPaddleDir;

};
