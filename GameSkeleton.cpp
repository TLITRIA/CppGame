#include "GameSkeleton.h"

#include <iostream>


const int thickness = 15;
const int window_w = 1024;
const int window_h = 768;
const int FPS = 1000;
const float paddleH = 100.0f;

// area & wall
SDL_Rect tWall{ 0, 0, 1024, thickness };
SDL_Rect bWall{ 0, window_h - thickness, 1024, thickness };
SDL_Rect rWall{ window_w - thickness, 0, thickness,  window_h};

// 可移动区域就是离边thinkness距离的区域，包括左边



GameSkeleton::GameSkeleton()
	: mWindow(nullptr)
	, mRenderer(nullptr)
	, mIsRunning(true)
	, mPaddleDir(0)
{

}

bool GameSkeleton::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	/* Flag 
	* SDL_INIT_AUDIO
	* SDL_INIT_VIDEO
	* SDL_INIT_HAPTIC
	* SDL_INIT_GAMECONTROLLER
	*/
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL:％s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programing in C++ (Chapter 1).",
		20, 20, window_w, window_h, 0);
	if (!mWindow)
	{
		SDL_Log("Fail to create mWindow:％s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(	mWindow, -1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!mRenderer)
	{
		SDL_Log("Failed to create mRenderer: %s", SDL_GetError());
		return false;
	}

	mBallPos.x = (float)window_w / 2.0f;
	mBallPos.y = (float)window_h / 2.0f;
	mPaddlePos.x = 10.0f;
	mPaddlePos.y = window_h / 2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;
	return true;
}

void GameSkeleton::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}


void GameSkeleton::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
		{
			mIsRunning = false;
			break;
		}
		//default: 
		//	break;
		// 这些不能加，否则键盘输入会出错，为什么？
		}
	}

	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W]) // 还得切英文输入法
	{
		mPaddleDir -= 1;
	}

	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
}

void GameSkeleton::UpdateGame()
{
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + (int)(1000.0f / FPS))); 
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
		deltaTime = 0.05f;
	mTicksCount = SDL_GetTicks();

	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		if (mPaddlePos.y < (paddleH / 2.0f + thickness))
			mPaddlePos.y = paddleH / 2.0f + thickness;
		else if (mPaddlePos.y > window_h - paddleH / 2.0f - thickness)
			mPaddlePos.y = window_h - paddleH / 2.0f - thickness;
	}
	
}

void GameSkeleton::GenerateOutput()
{
	// background
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderClear(mRenderer);
	
	// wall
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(mRenderer, &tWall);
	SDL_RenderFillRect(mRenderer, &bWall);
	SDL_RenderFillRect(mRenderer, &rWall);

	// paddle
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	// ball
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	SDL_RenderPresent(mRenderer); 
}

void GameSkeleton::ShutDown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

