#pragma once
#ifndef GameScene_HPP
#define GameScene_HPP

#include <UtH\UtHEngine.hpp>
#include <Player.hpp>
#include <BackGroundManager.hpp>

class GameScene : public uth::Scene
{
private:

	uth::Shader  m_shader;
	uth::SpriteBatch m_spriteBatch;
	uth::Camera* m_gameCamera;

	//uth::ca

	Player m_player;

public:

	GameScene();
	~GameScene();

	virtual bool Init();
	virtual bool DeInit();

	virtual bool Update(float dt);
	virtual bool Draw();

};


#endif //GameScene_HPP