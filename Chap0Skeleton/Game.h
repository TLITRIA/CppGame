#pragma once
#include <iostream>
#include "SDL.h"


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
	bool isRunning;
};
