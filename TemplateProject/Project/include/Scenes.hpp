#ifndef SCENES_H
#define SCENES_H
#define UTHDefaultScene -1

// Enumeration of scenes, giving name for each scene number
enum SceneName
{
	DEFAULT = UTHDefaultScene,
	MENU,
	GAME,
	COUNT // Keep this last, it tells how many scenes there are
};

#endif //SCENES_H

#ifdef NEWSCENEFUNC
#undef NEWSCENEFUNC

#include <MenuScene.hpp> //Your scene header.
#include <ProtoScene.hpp>
#include <GameScene.hpp>

// Create function for a new scene, having a case for every user made scene
uth::Scene* NewSceneFunc(int SceneID)
{
	switch (SceneID)
	{
	case MENU:		return new /*Menu*/MenuScene();
	case GAME:		return new /*Game*/GameScene();
	default:		return nullptr;
	}
}

#endif // NEWSCENEFUNC