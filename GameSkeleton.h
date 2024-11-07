#pragma once
#include <SDL.h>


struct Vector2
{
	float x;
	float y;
};
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

	SDL_Window* window;
	SDL_Renderer* renderer;

	Vector2 ballPos;
	bool isRunning;
};

