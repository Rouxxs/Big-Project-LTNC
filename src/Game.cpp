#include "Game.h"

void Game::initSDL()
{
    int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;
	
	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        printf("Couldn't initialize SDL Mixer\n");
		exit(1);
    }

    Mix_AllocateChannels(MAX_SND_CHANNELS);

	window = SDL_CreateWindow("Battle Arena DONK! 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    renderer = SDL_CreateRenderer(window, -1, rendererFlags);
	
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	
	SDL_ShowCursor(0);
}

void Game::initGame()
{

}

void Game::cleanup()
{
	SDL_DestroyRenderer(renderer);
	
	SDL_DestroyWindow(window);
	
	SDL_Quit();
}

void Game::doInput()
{
    SDL_Event event;
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				cleanup();
				exit(0);
				break;
				
			case SDL_KEYDOWN:
				if (event.key.repeat == 0 && event.key.keysym.scancode < MAX_KEYBOARD_KEYS)
	            {
		            keyboard[event.key.keysym.scancode] = 1;
	            }
				break;
				
			case SDL_KEYUP:
				if (event.key.repeat == 0 && event.key.keysym.scancode < MAX_KEYBOARD_KEYS)
	            {
		            keyboard[event.key.keysym.scancode] = 0;
	            }
				break;

			default:
				break;
		}
	}
	
	SDL_GetMouseState(&mouse.x, &mouse.y);
}

void Game::prepareScene()
{
	SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
	SDL_RenderClear(renderer);
}

void Game::presentScene()
{
	SDL_RenderPresent(renderer);
}

SDL_Texture *Game::getTexture(std::string name)
{
	Texture *t;
	
	for (t = textureHead.next ; t != NULL ; t = t->next)
	{
		if (t->name == name)
		{
			return t->texture;
		}
	}
	
	return NULL;
}

void Game::addTextureToCache(std::string name, SDL_Texture *Tex)
{
	Texture *texture = new Texture(name, Tex);
	textureTail->next = texture;
	//textureTail = texture;
}

SDL_Texture *Game::loadTexture(const char* filename)
{
	SDL_Texture *texture;
	
	texture = getTexture(filename);
	
	if (texture == NULL)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s ...", filename);
		texture = IMG_LoadTexture(renderer, filename);
		addTextureToCache(filename, texture);
	}

	return texture;
}

void Game::blit(SDL_Texture *texture, int x, int y, int center)
{
	SDL_Rect dest;
	
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	
	if (center)
	{
		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;
	}
	
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Game::blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
{
	SDL_Rect dest;
	
	dest.x = x;
	dest.y = y;
	dest.w = src->w;
	dest.h = src->h;
	
	SDL_RenderCopy(renderer, texture, src, &dest);
}

void Game::blitRotated(SDL_Texture *texture, int x, int y, float angle)
{
	SDL_Rect dstRect;

	dstRect.x = x;
	dstRect.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);
	dstRect.x -= (dstRect.w / 2);
	dstRect.y -= (dstRect.h / 2);

	SDL_RenderCopyEx(renderer, texture, NULL, &dstRect, angle, NULL, SDL_FLIP_NONE);
}