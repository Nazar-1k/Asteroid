#include "FireParticale.h"

static bool texture_is_load{ false };

static Sprite RedTexture;
static Sprite OrangeTexture;
static Sprite GreyTexture;
static Sprite ShimmerTexture;

Particle::Particle(float x, float y, float side, float angle, SDL_Renderer* renderer)
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

	/*float angleInRadians = angle * M_PI / 180.0;

	this->x = x_botom * cos(angleInRadians) - y_botom * sin(angleInRadians) + x;
	this->y = x_botom * sin(angleInRadians) + y_botom * cos(angleInRadians) + y + side / 2;*/
	// Âèçíà÷åííÿ êîîğäèíàò íèæíüî¿ òî÷êè êîğàáëÿ
	 float x_botom = x;
	 float y_botom = y + side / 2;

	// Ïîâîğîò êîîğäèíàò òî÷êè ïğèºäíàííÿ íàâêîëî öåíòğà êîğàáëÿ
	float angleInRadians = angle * M_PI / 180.0;
	this->x = x_botom * cos(angleInRadians) - y_botom * sin(angleInRadians) + x; (rand() % 25);
	this->y = x_botom * sin(angleInRadians) + y_botom * cos(angleInRadians) + (rand() % 25);

	// Âèçíà÷åííÿ êîîğäèíàò òî÷êè ïğèºäíàííÿ ç óğàõóâàííÿì ğîçì³ğ³â îá'ºêòó
	
	
	





	/*this->x =x +(rand() % 25);
	this->y =y +(rand() % 25);*/
   
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
