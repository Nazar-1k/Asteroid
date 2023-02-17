#include "Sprite.h"
Sprite::Sprite(const char* path, int width, int height, SDL_Texture* texture, SDL_Renderer* renderer)
	:width(width), height(height), texture(texture), renderer(renderer)
{
	loadFromFile(path);
}

Sprite::~Sprite()
{
	free();
}

bool Sprite::loadFromFile(const char* path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image" << path << "SDL_image Error : \n" << IMG_GetError() << std::endl;
		return texture != NULL;
	}
	
	//Color key image
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if (newTexture == NULL)
	{
		std::cout << "Unable to create texture from" << path << "SDL Error: \n" << IMG_GetError() << std::endl;
		return texture != NULL;
	}

	//Get image dimensions
	width = loadedSurface->w;
	height = loadedSurface->h;
	

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);


	//Return success
	texture = newTexture;
	return texture != NULL;
}

void Sprite::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(texture, red, green, blue);
}

void Sprite::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(texture, blending);
}

void Sprite::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(texture, alpha);
}

void Sprite::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

void Sprite::getSize(int& w, int& h)
{
	w = this->width;
	h = this->height;
}

void Sprite::setSize(int w, int h)
{
	this->width = w;
	this->height = h;
}

void Sprite::setWith(int w)
{
	this->width = w;
}

void Sprite::setHeight(int h)
{
	this->height = h;
}

void Sprite::free()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
		renderer = nullptr;
		width = 0;
		height = 0;
	}
}
