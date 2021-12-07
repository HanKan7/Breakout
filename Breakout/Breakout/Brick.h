#pragma once
#include"ParentBrick.h"

class Brick : public ParentBrick
{
	public:
	
	int numberOfHitsTakenToDestroy;
	

	Brick(int numberOfHitTakenToDestroy, sf::Vector2f pos);
	void BrickInit(int numberOfHitTakenToDestroy, sf::Vector2f pos);
};

