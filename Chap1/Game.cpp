#include "Game.h"


const int window_h = 768;
const int window_w = 1024;
const int wall_thinkness = 20;		// 墙的厚度
const int paddle_thinkness = 10;	// 板的厚度
const int paddle_length = 100;		// 板的长度
Game::Game()
	: mWindow(nullptr)
	, mRenderer(nullptr)
	, mTicksCount(0)
	, isRunning(true)
	, mPaddleDir(0)
{
}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL:%s", SDL_GetError());
		return false;
	}
	mWindow = SDL_CreateWindow("Game Programing in C++ (Chapter 1).",100,100, window_w, window_h,0);
	if (!mWindow)
	{
		SDL_Log("Fail to create window:%s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC	);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	mBallPos = Vector2{ window_w / 2, window_h / 2 };
	mBallVel = Vector2{ -200.0f, 234.0f };
	mPaddlePos = Vector2{ 20.0f, window_h / 2 };
	return true;
}

void Game::RunLoop()
{
	while (isRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
		{
			isRunning = false;
			break;
		}
		default:
			break;
		}
	}
	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}
}

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderClear(mRenderer);

	/* 关键函数 SDL_Rect
	* SDL_RenderFillRect
	* SDL_SetRenderDrawColor
	*/

	SDL_Rect fillRect{ 0,0,0,0 };

	// 顶
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	fillRect = {0,0, window_w, wall_thinkness};
	SDL_RenderFillRect(mRenderer, &fillRect);
	// 底
	fillRect = { 0,window_h-wall_thinkness, window_w, wall_thinkness };
	SDL_RenderFillRect(mRenderer, &fillRect);
	// 右
	fillRect = { window_w-wall_thinkness,0, wall_thinkness, window_h };
	SDL_RenderFillRect(mRenderer, &fillRect);
	// 板子
	SDL_Rect paddle = {
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddle_length / 2),
		paddle_thinkness,
		static_cast<int>(paddle_length)
	};
	SDL_RenderFillRect(mRenderer, &paddle);





	SDL_RenderPresent(mRenderer);
}
