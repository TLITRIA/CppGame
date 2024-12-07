/*规定P1在左，P2在右
* 
*/
#include "Game.h"


const int window_h = 768;
const int window_w = 124;
const int wall_thinkness = 20;		// 墙的厚度
const int paddle_thinkness = 10;	// 板的厚度
const int paddle_length = 100;		// 板的长度
const int ball_r = 5;				// “球”的半径
const int FPS = 144;
Game::Game()
	: mWindow(nullptr)
	, mRenderer(nullptr)
	, mTicksCount(0)
	, isRunning(true)
	, mPaddleDir_P1(0)
	, mPaddleDir_P2(0)
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
	mBallVel = Vector2{ 50.0f, 0.0f };
	mPaddlePos_P1 = Vector2{ 20.0f, window_h / 2 };
	mPaddlePos_P2 = Vector2{ window_w -  20.0f, window_h / 2 };
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
	std::cout << " Game Over! " << std::endl;
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

	// paddle
	mPaddleDir_P1 = 0;
	if (state[SDL_SCANCODE_W])
		mPaddleDir_P1 -= 1;
	if (state[SDL_SCANCODE_S])
		mPaddleDir_P1 += 1;

	mPaddleDir_P2 = 0;
	if (state[SDL_SCANCODE_I])
		mPaddleDir_P2 -= 1;
	if (state[SDL_SCANCODE_J])
		mPaddleDir_P2 += 1;
}

void Game::UpdateGame()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + static_cast<int>(1000.0f / FPS)));
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
		deltaTime = 0.05f;
	mTicksCount = SDL_GetTicks();
	
	// paddle 
	if (mPaddleDir_P1 != 0)
	{
		mPaddlePos_P1.y += mPaddleDir_P1 * 300.0f * deltaTime;
		if (mPaddlePos_P1.y + paddle_length / 2 + wall_thinkness > window_h)
			mPaddlePos_P1.y = window_h - (paddle_length / 2 + wall_thinkness);
		if (mPaddlePos_P1.y < paddle_length / 2 + wall_thinkness)
			mPaddlePos_P1.y = paddle_length / 2 + wall_thinkness;
	}

	if (mPaddleDir_P2 != 0)
	{
		mPaddlePos_P2.y += mPaddleDir_P2 * 300.0f * deltaTime;
		if (mPaddlePos_P2.y + paddle_length / 2 + wall_thinkness > window_h)
			mPaddlePos_P2.y = window_h - (paddle_length / 2 + wall_thinkness);
		if (mPaddlePos_P2.y < paddle_length / 2 + wall_thinkness)
			mPaddlePos_P2.y = paddle_length / 2 + wall_thinkness;
	}

	// ball
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;
	if (mBallPos.y > window_h - wall_thinkness - ball_r)// 底
	{
		mBallPos.y -= 2 * (mBallPos.y - (window_h - wall_thinkness - ball_r));
		mBallVel.y *= -1;
	}

	if (mBallPos.y < wall_thinkness + ball_r)	// 顶
	{
		mBallPos.y += 2 * (wall_thinkness + ball_r - mBallPos.y);
		mBallVel.y *= -1;
	}

	//if (mBallPos.x > window_w - wall_thinkness - ball_r) // 右墙
	//{
	//	mBallPos.x -= 2 * (mBallPos.x - (window_w - wall_thinkness - ball_r));
	//	mBallVel.x *= -1;
	//}

	if (mBallPos.x + ball_r > mPaddlePos_P2.x - paddle_thinkness / 2 	// 右板子
		&& mBallPos.y + ball_r > mPaddlePos_P2.y - paddle_length / 2
		&& mBallPos.y - ball_r < mPaddlePos_P2.y + paddle_length / 2)
	{
		mBallPos.x -= 2 * (mBallPos.x + ball_r - mPaddlePos_P2.x + paddle_thinkness / 2);
		mBallVel.x *= -1;
	}

	if (mBallPos.x < mPaddlePos_P1.x + paddle_thinkness/2 + ball_r	// 左板子
		&& mBallPos.y + ball_r > mPaddlePos_P1.y - paddle_length / 2
		&& mBallPos.y - ball_r < mPaddlePos_P1.y + paddle_length / 2)
	{
		mBallPos.x += 2 * (mBallPos.x - mPaddlePos_P1.x - paddle_thinkness / 2 + ball_r);
		mBallVel.x *= -1;
	}

	if (mBallPos.x < ball_r || mBallPos.x + ball_r > window_w)
		isRunning = false;
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
	//fillRect = { window_w-wall_thinkness,0, wall_thinkness, window_h };
	//SDL_RenderFillRect(mRenderer, &fillRect);
	// 板子
	SDL_Rect paddle = {
		static_cast<int>(mPaddlePos_P1.x - paddle_thinkness / 2),
		static_cast<int>(mPaddlePos_P1.y - paddle_length / 2),
		paddle_thinkness,
		paddle_length
	};
	SDL_RenderFillRect(mRenderer, &paddle);
	paddle = {
		static_cast<int>(mPaddlePos_P2.x - paddle_thinkness / 2),
		static_cast<int>(mPaddlePos_P2.y - paddle_length / 2),
		paddle_thinkness,
		paddle_length
	};
	SDL_RenderFillRect(mRenderer, &paddle);
	// 球
	SDL_Rect ball = {
		static_cast<int>(mBallPos.x - ball_r),
		static_cast<int>(mBallPos.y - ball_r),
		ball_r*2,
		ball_r*2		
	};
	SDL_RenderFillRect(mRenderer, &ball);

	SDL_RenderPresent(mRenderer);
}
