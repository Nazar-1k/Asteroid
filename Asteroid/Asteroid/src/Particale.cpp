#include "Particale.h"

static bool texture_is_load{ false };

static Sprite RedTexture;
static Sprite OrangeTexture;
static Sprite GreyTexture;
static Sprite ShimmerTexture;

static const char pathRed[] = "data/Particles/red.png";
static const char pathOrange[] = "data/Particles/orange.png";
static const char pathGrey[] = "data/Particles/grey.png";
static const char pathShimmer[] = "data/Particles/shimmer.png";

Particle::Particle(float x, float y, int side, float angle, SDL_Renderer* renderer)
	:dead(false),dx(0),dy(0),Texture(nullptr)
{
	if (!texture_is_load)
	{
		RedTexture.setRenderer(renderer);
		OrangeTexture.setRenderer(renderer);
		GreyTexture.setRenderer(renderer);
		ShimmerTexture.setRenderer(renderer);
		//Load red texture
		if (!RedTexture.loadFromFile(pathRed))
		{
			std::cout<<"Failed to load Red texture! path ->"<< pathRed<<std::endl;
		}

		//Load green texture
		if (!OrangeTexture.loadFromFile(pathOrange))
		{
			std::cout << "Failed to load Orange texture!path ->" << pathOrange << std::endl;

		}

		//Load blue texture
		if (!GreyTexture.loadFromFile(pathGrey))
		{
			std::cout << "Failed to load Grey texture!path ->" << pathGrey << std::endl;


		}

		//Load shimmer texture
		if (!ShimmerTexture.loadFromFile(pathShimmer))
		{
			std::cout << "Failed to load Shimmer texture!path ->" << pathShimmer << std::endl;

		}

		//Set texture transparency
		RedTexture.setAlpha(192);
		OrangeTexture.setAlpha(192);
		GreyTexture.setAlpha(192);
		ShimmerTexture.setAlpha(192);

		texture_is_load = true;
	}

	// Визначення позиції вогню
	float fireX = x;
	float fireY = y - side / 2;

	float angleInRadians = static_cast<float>(angle * M_PI / 180.0);
	// Обертання корабля навколо своїх координат
	this->x = (x - fireX) * cos(angleInRadians) - (y - fireY) * sin(angleInRadians) + fireX+rand()%5;
	this->y = (x - fireX) * sin(angleInRadians) + (y - fireY) * cos(angleInRadians) + fireY + side/2+rand() % 5;

    //Initialize animation
    Frame = rand() % 5;

    //Set type
    switch (rand() % 3)
    {
    case 0: Texture = &RedTexture; break;
    case 1: Texture = &OrangeTexture; break;
    case 2: Texture = &GreyTexture; break;
    }
}

Particle::Particle(float x, float y,int side, SDL_Renderer* renderer)
	:dead(false),  dx(0), dy(0), Texture(nullptr)
{
	if (!texture_is_load)
	{
		RedTexture.setRenderer(renderer);
		OrangeTexture.setRenderer(renderer);
		GreyTexture.setRenderer(renderer);
		ShimmerTexture.setRenderer(renderer);
		//Load red texture
		if (!RedTexture.loadFromFile(pathRed))
		{
			std::cout<< "Failed to load texture! path ->"<< pathRed;
		}

		//Load green texture
		if (!OrangeTexture.loadFromFile(pathOrange))
		{
			std::cout << "Failed to load texture! path ->" << pathRed;

		}

		//Load blue texture
		if (!GreyTexture.loadFromFile(pathGrey))
		{
			std::cout << "Failed to load texture! path ->" << pathGrey;

		}

		//Load shimmer texture
		if (!ShimmerTexture.loadFromFile(pathShimmer))
		{
			std::cout << "Failed to load texture! path ->" << pathShimmer;
		}

		//Set texture transparency
		RedTexture.setAlpha(192);
		OrangeTexture.setAlpha(192);
		GreyTexture.setAlpha(192);
		ShimmerTexture.setAlpha(192);

		texture_is_load = true;
	}
	this->x = x - side + rand() % side*2;
	this->y = y - side + rand() % side *2;
	
	//Initialize animation
	Frame = rand() % 5;

	//Set type
	switch (rand() % 2)
	{
	case 0: Texture = &ShimmerTexture; break;
	case 1: Texture = &GreyTexture; break;
	}
}

void Particle::render() 
{
	
    // Show image
    Texture->render(x,y);


    //Show shimmer
    if (Frame % 2 == 0)
    {
        ShimmerTexture.render(x,y);
    }

    //Animate
    Frame++;
	if (Frame > 10)
	{
		dead = true;
	}
}

void Particle::setdead(bool dead)
{
	this->dead = dead;
}

void Particle::setAlfa(Uint8 alpha)
{
	Texture->setAlpha(alpha);
}

