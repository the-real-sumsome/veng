#include <iostream>
#include <irrlicht/irrlicht.h>
#include "management/CVar.hpp"
#include "player/Player.hpp"
#include "net/Server.hpp"
#include "player/PlayerNode.hpp"
#include "VengEventReceiver.hpp"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

VengPlayer* cPlayer;

#define IFARG_CASE(S) } else if(strcmp(argv[i],S)==0) {

int main(int argc, char** argv) {
	VengEventReceiver receiver;
	NetConnection* currconn;

	for(int i = 0; i<argc; i++) {
		if(strcmp(argv[i],"dev")==0) {
			
		IFARG_CASE("net")
			currconn = new NetConnection(argv[++i],8364);
		IFARG_CASE("serv")
			VengServer();
			exit(0);
		}
		
	}

	IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(640,480),16,false,true,false,&receiver);

	if(!device)
		return NULL;
	
	device->setWindowCaption(L"Veng");
	device->setResizable(true);

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	IFileSystem* fs = device->getFileSystem();

	VengManagement::CVars vars = VengManagement::CVars();
	#ifdef DEBUG
	vars.Set_Cvar("dbg_internal_video",driver);
	vars.Set_Cvar("dbg_internal_driver",device);
	vars.Set_Cvar("dbg_internal_scene",smgr);
	vars.Set_Cvar("dbg_internal_fs",fs);
	vars.Set_Cvar("dbg_internal_gui",guienv);
	#endif

	fs->addFileArchive("rsc");
	#ifdef DEBUG
	fs->addFileArchive("../rsc");
	#endif

    smgr->setShadowColor(video::SColor(150,0,0,0));

    smgr->addSkyBoxSceneNode(
        driver->getTexture("tex/sky/d3.png"),
        driver->getTexture("tex/sky/d2.png"),
        driver->getTexture("tex/sky/d4.png"),
        driver->getTexture("tex/sky/d5.png"),
        driver->getTexture("tex/sky/d0.png"),
        driver->getTexture("tex/sky/d1.png"));

	guienv->addStaticText(L"VENG: Preview Build",
        	rect<s32>(0,0,260,22), false);
	int lastFPS = -1;
	u32 then = device->getTimer()->getTime();
	const f32 MOVEMENT_SPEED = 5.f;
    scene::ISceneNode * node = smgr->addCubeSceneNode();
    if (node)
    {
        node->setPosition(core::vector3df(0,0,30));
        node->setMaterialTexture(0, driver->getTexture("tex/Bricks11.png"));
        node->setMaterialFlag(video::EMF_LIGHTING, false);
    }    

	PlayerNode *pNode =
        new PlayerNode(smgr->getRootSceneNode(), smgr, 666);
	VengPlayer *pObj = new VengPlayer();
	pObj->pN = pNode;

	vars.Set_Cvar("d_internal_pnode",pNode);
	vars.Set_Cvar("d_internal_pobjc",pObj);

	while(device->run()) 
	{
		const u32 now = device->getTimer()->getTime();
        	const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        	then = now;

		driver->beginScene(true,true,SColor(255,101,101,140));
		smgr->drawAll();
		
		guienv->drawAll();
		driver->endScene();
		if(!currconn) {
			currconn->SceneUpdate(device);
		}
		int fps = driver->getFPS();
		core::stringw tmp(L"Veng: ");
		tmp += (wchar_t*)vars.Get_Cvar("d_window_name");
		tmp += L" [";
		tmp += driver->getName();
		tmp += L"] fps: ";
		tmp += fps;

		device->setWindowCaption(tmp.c_str());
		lastFPS = fps;
	}
	device->drop();
	return 0;
}
