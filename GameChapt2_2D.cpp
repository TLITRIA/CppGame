#include "GameChapt2_2D.h"
#include <SDL_image.h>
#include <algorithm>
#include "Actor_Chap2.h"
#include "SpriteComponent_Chap2.h"
#include "Ship_Chap2.h"
#include "BGSpriteComponent_Chap2.h"


const int window_w = 1024;
const int window_h = 768;
const int FPS = 100;

GameChapt2_2D::GameChapt2_2D()
	: mWindow(nullptr)
	, mRenderer(nullptr)
	, mIsRunning(true)
	, mUpdatingActors(false)
{ }

bool GameChapt2_2D::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL:%s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programing in C++ (Chapter 2).",
		100, 100, window_w, window_h, 0);
	if (!mWindow)
	{
		SDL_Log("Fail to create mWindow:%s", SDL_GetError());
		return false;
	}
	mRenderer = SDL_CreateRenderer(mWindow, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create mRenderer: %s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	LoadData();

	mTicksCount = SDL_GetTicks();

	return true;
}

void GameChapt2_2D::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}


void GameChapt2_2D::ProcessInput()
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

	// Process ship input 
	mShip->ProcessKeyboard(state);
}

void GameChapt2_2D::UpdateGame()
{
	/* Wait until 1000/FPS has elapsed since last frame */
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + (int)(1000.0f / FPS)));
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
		deltaTime = 0.05f;
	mTicksCount = SDL_GetTicks();

	// Update all actors
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;
	// Move any pending actors to mActors
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// Add any dead actors to a temp vector
	std::vector<Actor_Chap2*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor_Chap2::EDead)
			deadActors.emplace_back(actor);
	}
	// Delete dead actors (removes them form mActors)
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void GameChapt2_2D::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
	// 添加模块的快捷键
	// Ctrl + Shift + A：添加新项到当前项目或解决方案中。这通常用于添加新的类、接口、窗体等。
	// Ctrl + Alt + A：添加现有项到当前项目或解决方案中。这通常用于将已有的文件或资源添加到项目中。
	
	//Draw all sprite components
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void GameChapt2_2D::LoadData()
{
	// create player's ship 
	mShip = new Ship_Chap2(this);
	mShip->SetPosition(Vector2(100.0f, 384.0f));
	mShip->SetScale(1.5f);

	// Create actor for the background
	Actor_Chap2* temp = new Actor_Chap2(this);
	temp->SetPosition(Vector2( 512.0f, 384.0f ));

	// Create the farBack background
	BGSpriteComponent_Chap2* bg = new BGSpriteComponent_Chap2(temp);
	bg->SetScreenSize(Vector2((float)window_w, (float)window_h));
	std::vector<SDL_Texture*> bgtexs = {
		GetTexture("Assets/Farback01.png"),
		GetTexture("Assets/Farback02.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-100.0f);

	// Create the Closer background
	bg = new BGSpriteComponent_Chap2(temp, 50);
	bg->SetScreenSize(Vector2( (float)window_w, (float)window_h ));
	bgtexs = {
		GetTexture("Assets/Stars.png"),
		GetTexture("Assets/Stars.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-200.0f);
}

void GameChapt2_2D::UnloadData()
{
	// delete actors
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// destory texture
	for (auto iter : mTextures)
	{
		SDL_DestroyTexture(iter.second);
	}
	mTextures.clear();
}


void GameChapt2_2D::AddActor(Actor_Chap2* actor)
{
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void GameChapt2_2D::RemoveActor(Actor_Chap2* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		std::iter_swap(iter, mPendingActors.end()-1);
		mPendingActors.pop_back();
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void GameChapt2_2D::AddSprite(SpriteComponent_Chap2* sprite)
{
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for ( ; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
			break;
	}
	mSprites.insert(iter, sprite);
}

void GameChapt2_2D::RemoveSprite(SpriteComponent_Chap2* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

SDL_Texture* GameChapt2_2D::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	// map
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		// load from file
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// create texture from surface	
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}
		mTextures.emplace(fileName.c_str(), tex); // 错误
	}
	return tex; // 错误
}


void GameChapt2_2D::ShutDown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}