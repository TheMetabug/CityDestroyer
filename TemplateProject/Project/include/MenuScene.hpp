#pragma once
#ifndef MenuScene_HPP
#define MenuScene_HPP

#include <UtH/Engine/Scene.hpp>
#include <UtH/Core/Shader.hpp>

class MenuScene : public uth::Scene
{
private: // Just place everything else as private.
	uth::Shader m_shader;
public: // Every one of these public functions are required.
	MenuScene();
	~MenuScene();

	virtual bool Init();
	virtual bool DeInit();

	virtual bool Update(float dt);
	virtual bool Draw();
};

#endif //MenuScene_HPP