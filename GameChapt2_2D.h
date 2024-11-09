#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <string>
#include <vector>

class GameChapt2_2D
{
public:
	GameChapt2_2D();
	bool Initialize();
	void RunLoop();
	void ShutDown();

	void AddActor(class Actor_Chap2* actor);
	void RemoveActor(class Actor_Chap2* actor);

	void AddSprite(class SpriteComponent_Chap2* sprite);
	void RemoveSprite(class SpriteComponent_Chap2* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	std::unordered_map<std::string, SDL_Texture*> mTextures;
	std::vector<class Actor_Chap2*> mActors;
	std::vector<class Actor_Chap2*> mPendingActors;
	std::vector<class SpriteComponent_Chap2*> mSprites;

	Uint32 mTicksCount;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	
	bool mIsRunning;
	bool mUpdatingActors;

	class Ship_Chap2* mShip;
};

