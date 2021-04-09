#include <iostream>
#include <irrlicht/irrlicht.h>
#include "input.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main() {
	VengEventReceiver receiver;

	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640,480),16,false,true,false,&receiver);

	if(!device)
		return NULL;

	device->setWindowCaption(L"Veng");
	device->setResizable(true);

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	IFileSystem* fs = device->getFileSystem();
	fs->addFileArchive("rsc");
	#ifdef DEBUG
	fs->addFileArchive("../rsc");
	#endif

	smgr->addCameraSceneNodeFPS();
	device->getCursorControl()->setVisible(false);

    smgr->setShadowColor(video::SColor(150,0,0,0));

	guienv->addStaticText(L"VENG: Preview Build",
        	rect<s32>(10,10,260,22), false);
	int lastFPS = -1;
	u32 then = device->getTimer()->getTime();
	const f32 MOVEMENT_SPEED = 5.f;
    scene::ISceneNode * node = smgr->addCubeSceneNode();
    if (node)
    {
        node->setPosition(core::vector3df(0,0,30));
        node->setMaterialTexture(0, driver->getTexture("tex/Bricks11.png"));
        node->setMaterialFlag(video::EMF_LIGHTING, true);
    }    

    scene::ISceneNode * lnode = smgr->addLightSceneNode(0, core::vector3df(2,2,0),
        video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 800.0f);
	while(device->run()) {
		const u32 now = device->getTimer()->getTime();
        	const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        	then = now;

		driver->beginScene(true,true,SColor(255,101,101,140));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();
		int fps = driver->getFPS();
		core::stringw tmp(L"Veng [");
		tmp += driver->getName();
		tmp += L"] fps: ";
		tmp += fps;

		device->setWindowCaption(tmp.c_str());
		lastFPS = fps;
	}
	device->drop();
	return 0;
}
