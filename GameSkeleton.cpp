#include "GameSkeleton.h"


const int window_w = 1024;
const int window_h = 768;
const int FPS = 1000;

GameSkeleton::GameSkeleton()
	: mWindow(nullptr)
	, mRenderer(nullptr)
	, mIsRunning(true)
{ }

bool GameSkeleton::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to initialize SDL:%s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programing in C++.",
		20, 20, window_w, window_h, 0);
	if (!mWindow)
	{
		SDL_Log("Fail to create mWindow:%s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(	mWindow, -1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!mRenderer)
	{
		SDL_Log("Failed to create mRenderer: %s", SDL_GetError());
		return false;
	}

// 初始化变量
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
		}
	}

	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	if (state[SDL_SCANCODE_W])
	{
	}

	if (state[SDL_SCANCODE_S])
	{
	}
}

void GameSkeleton::UpdateGame()
{
	/* Wait until 1000/FPS has elapsed since last frame */
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + (int)(1000.0f / FPS))); 
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
		deltaTime = 0.05f;
	mTicksCount = SDL_GetTicks();

}

void GameSkeleton::GenerateOutput()
{
	SDL_RenderClear(mRenderer);

	SDL_RenderPresent(mRenderer); 
}

void GameSkeleton::ShutDown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

