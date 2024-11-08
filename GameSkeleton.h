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

	Uint32 mTicksCount;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	// obj
	Vector2 mBallPos;
	Vector2 mBallVel;
	Vector2 mPaddlePos; // �����ǰ��ӵ����ߵ����ĵ�
	int mPaddleDir; // direction of paddle

	// flag
	bool mIsRunning;
};

