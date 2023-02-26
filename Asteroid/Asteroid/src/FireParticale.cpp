#include "FireParticale.h"

static bool texture_is_load{ false };

static Sprite RedTexture;
static Sprite OrangeTexture;
static Sprite GreyTexture;
static Sprite ShimmerTexture;

Particle::Particle(float x, float y, int side, float angle, SDL_Renderer* renderer)
	:dead(false)
{
	if (!texture_is_load)
	{
		RedTexture.setRenderer(renderer);
		OrangeTexture.setRenderer(renderer);
		GreyTexture.setRenderer(renderer);
		ShimmerTexture.setRenderer(renderer);
		//Load red texture
		if (!RedTexture.loadFromFile("data/red.png"))
		{
			printf("Failed to load red texture!\n");
		}

		//Load green texture
		if (!OrangeTexture.loadFromFile("data/orange.png"))
		{
			printf("Failed to load green texture!\n");

		}

		//Load blue texture
		if (!GreyTexture.loadFromFile("data/grey.png"))
		{
			printf("Failed to load blue texture!\n");

		}

		//Load shimmer texture
		if (!ShimmerTexture.loadFromFile("data/shimmer.png"))
		{
			printf("Failed to load shimmer texture!\n");

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

	float angleInRadians = angle * M_PI / 180.0;
	// Обертання корабля навколо своїх координат
	this->x = (x - fireX) * cos(angleInRadians) - (y - fireY) * sin(angleInRadians) + fireX+rand()%5;
	this->y = (x - fireX) * sin(angleInRadians) + (y - fireY) * cos(angleInRadians) + fireY + side/2+rand() % 5;

	std::cout << angleInRadians << std::endl;

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

bool Particle::isDead()
{
    return dead;
}

void Particle::setdead(bool dead)
{
	this->dead = dead;
}
