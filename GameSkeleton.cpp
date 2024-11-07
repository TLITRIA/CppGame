#include "GameSkeleton.h"


const int thickness = 15;


GameSkeleton::GameSkeleton()
	: window(nullptr)
	, renderer(nullptr)
	,isRunning(true)
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
		SDL_Log("Unable to initialize SDL:£¥s", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow(
		"Game Programing in C++ (Chapter 1).",
		100, // x
		100, // y
		1024, // w
		768, // h
		0 // g
	);

	if (!window)
	{
		SDL_Log("Fail to create window:£¥s", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (!renderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	ballPos.x = 1024.0f / 2.0f;
	ballPos.y = 768.0f / 2.0f;
	return true;
}

void GameSkeleton::RunLoop()
{
	while (isRunning)
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

void GameSkeleton::UpdateGame()
{
}

void GameSkeleton::GenerateOutput()
{
	// background
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	
	// top wall
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect wall{ 0, 0, 1024, thickness };
	SDL_RenderFillRect(renderer, &wall);

	// ball
	SDL_Rect ball{
		static_cast<int>(ballPos.x - thickness / 2),
		static_cast<int>(ballPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(renderer, &ball);

	SDL_RenderPresent(renderer); // ·Å×îºó
}

void GameSkeleton::ShutDown()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

