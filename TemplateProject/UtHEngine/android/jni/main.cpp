/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Math/Math.hpp>
#include <UtH/Platform/Android/AndroidEngine.hpp>
#include <UtH/Platform/Window.hpp>
#include <UtH/Platform/WindowSettings.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/FileReader.h>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Input.hpp>
#include <UtH/Engine/DefaultScene.hpp>

#include "../../../Project/include/MenuScene.hpp" //Your scene header.

// Enumeration of scenes, giving name for each scene number
enum SceneName
{
    DEFAULT = UTHDefaultScene,
    MENU = 0,
    COUNT // Keep this last, it tells how many scenes there are
};

// Create function for a new scene, having a case for every user made scene
void NewSceneFunc(int SceneID, uth::Scene* &CurScene)
{
    switch (SceneID)
    {
    case MENU:
        CurScene = new MenuScene();
        break;
    default:
        CurScene = new uth::DefaultScene();
        break;
    }
}


void handle_cmd(android_app* app, int cmd)
{
	uthAndroidEngine.message = cmd;
	((uth::Window*)app->userData)->processMessages();
}

void windowEventHandler(void* handle)
{
	uthEngine.SetWindow((uth::Window*)handle);
}

void android_main(android_app* state)
{
	app_dummy();
	WriteLog("app_dummy");

	uthAndroidEngine.initialized = false;
	WriteLog("uthAndroidEngine.initialized = false");

	uth::Window* wndw;
	uth::FileReader::m_manager = state->activity->assetManager;

	state->onAppCmd = handle_cmd;
	state->onInputEvent = uth::TouchInput::DroidMessage;

	uthAndroidEngine.app = state;

    uthAndroidEngine.settings.position = umath::vector2(0, 0);
	uthAndroidEngine.settings.contextVersionMajor = 2;
	uthAndroidEngine.settings.contextVersionMinor = 0;
    uthAndroidEngine.settings.fullScreen = true;

	state->userData = &wndw;

	uthAndroidEngine.winEveHand = windowEventHandler;
	WriteLog("uthAndroidEngine.winEveHand");


    uthSceneM.registerNewSceneFunc(NewSceneFunc, COUNT);
	WriteLog("uthSceneM.registerNewSceneFunc");

	while(1)
	{
		int ident;
		int events;
		android_poll_source* source;
		while ((ident=ALooper_pollAll(0, NULL, &events,(void**)&source)) >= 0)
		{
			//Insteads of these two 'if' statement proper exit should be placed
			if (source != NULL)
			{
				source->process(state, source);
			}
			if (state->destroyRequested != 0)
			{
				wndw->destroy();
				return;
			}
		}

		if(uthAndroidEngine.initialized && uthAndroidEngine.display != NULL)
		{
			uthEngine.Update();
			uthEngine.Draw();
		}
	}
}