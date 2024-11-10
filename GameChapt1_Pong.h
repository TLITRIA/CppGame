#pragma once

#include <SDL.h>
#include "Math.h"

class GameChapt1_Pong
{
public:
	GameChapt1_Pong();

	bool Initialize();
	void RunLoop();
	void ShutDown();
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	Uint32 mTicksCount;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	// obj
	Vector2 mBallPos;
	Vector2 mBallVel;
	Vector2 mPaddlePos; // 具体是板子的左侧边的中心点
	int mPaddleDir; // direction of paddle

	// flag
	bool mIsRunning;
};
