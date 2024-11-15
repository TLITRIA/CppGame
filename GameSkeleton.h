#pragma once
#include <SDL.h>

#include <iostream>
class GameSkeleton
{
public:
	GameSkeleton();

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
	
	// flag
	bool mIsRunning;
};

