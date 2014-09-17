#pragma once
#ifndef Player_HPP
#define Player_HPP

#include <UtH/UtHEngine.hpp>

class Player : public uth::GameObject
{
private:


public:
	Player();
	~Player();

	void Update(float);
	void Draw();
};

#endif //Player_HPP