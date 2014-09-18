#pragma once
#ifndef BackGround_HPP
#define BackGround_HPP

#include <UtH/UtHEngine.hpp>

class BackGround : public uth::GameObject
{
private:


public:
	BackGround(std::string textureName, float yPos);
	~BackGround();

	void Update(float);
	void Draw();
};

#endif //BackGround_HPP