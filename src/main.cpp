#include <iostream>		
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <irrlicht/irrlicht.h>
#include "management/CVar.hpp"
#include "management/Console.hpp"
#include "net/Server.hpp"
#include "player/PlayerNode.hpp"
#include "player/Player.hpp"
#include "uimng/VengUI.hpp"
#include "etc/Q3Map.hpp"
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
	NetConnection* currconn;
	int* connected = (int*)malloc(sizeof(int));
	*connected = 0;
	int novars = 0;
	E_DRIVER_TYPE cDrv = video::EDT_OPENGL;

	for(int i = 1; i<argc; i++) {
		if(strcmp(argv[i],"dev")==0) {
			/// TODO: this
		IFARG_CASE("net") // connect network
			char* serv = argv[i+1];
			printf("Conencting to %s on port 8364\n");
			currconn = new NetConnection(serv,"8364");
			connected = &currconn->State;
			if(!connected) {
				puts("Error: unable to connect to remote");
				exit(1);
			}
		IFARG_CASE("host") // host server
			VengServer();
			exit(0);
		IFARG_CASE("novar")
			novars = 1;
		IFARG_CASE("license") // cat all licenses
			#ifdef DEBUG
			system("cat ../rsc/txt/LICENSE_IRR.txt");
			system("cat ../rsc/txt/LICENSE_VENG.txt");
			system("cat ../rsc/txt/LICENSE_ASIO.txt");
			#else
			system("cat rsc/txt/LICENSE_IRR.txt");
			system("cat rsc/txt/LICENSE_VENG.txt");
			system("cat rsc/txt/LICENSE_ASIO.txt");
			#endif
			exit(0);
		IFARG_CASE("null")
			cDrv = video::EDT_NULL; // This apparently throws a segmentation fault when rendering
		} else {
			puts("Unknown starting command, going as usual");
		}
		
	}

	IrrlichtDevice *device = createDevice(cDrv, core::dimension2d<u32>(800,600),16,false,true,false); // create device
 
    SAppContext context; // SAppContext is the context for the VengEventReceiver.
						 // should contain references to gui objects 4
    context.device = device;

    VengEventReceiver receiver = VengEventReceiver(context);
    device->setEventReceiver(&receiver);
	
	if(!device)
		return NULL;
	
	device->setWindowCaption(L"Veng");

	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	IFileSystem* fs = device->getFileSystem();

	GlobConsole = new VengConsole(device);
	fs->addFileArchive("rsc");
	#ifdef DEBUG
	fs->addFileArchive("../rsc");
	fs->addFileArchive("/opt/openarena/baseoa/pak0.pk3"); // OpenArena testing
	fs->addFileArchive("/opt/openarena/baseoa/pak1-maps.pk3");
	fs->addFileArchive("/opt/openarena/baseoa/pak4-textures.pk3");
	#endif
	GlobConsole->PrepFinal();

	VengManagement::CVars vars = VengManagement::CVars();
	#ifdef DEBUG
	if(novars == 0) {
		vars.Set_Cvar("dbg_internal_video",driver);
		vars.Set_Cvar("dbg_internal_driver",device);
		vars.Set_Cvar("dbg_internal_scene",smgr);
		vars.Set_Cvar("dbg_internal_fs",fs);
		vars.Set_Cvar("dbg_internal_gui",guienv);
	}
	#endif

    smgr->setShadowColor(video::SColor(150,0,0,0));

	IGUIStaticText* fpsCntr = guienv->addStaticText(L"Veng: 0fps", rect<s32>(0,0,800,10), false);

    smgr->getParameters()->setAttribute(scene::ALLOW_ZWRITE_ON_TRANSPARENT, true);

	int lastFPS = -1;
	u32 then = device->getTimer()->getTime();
	const f32 MOVEMENT_SPEED = 5.f;
    ISceneNode * node = smgr->addCubeSceneNode();
    if (node)
    {
        node->setPosition(core::vector3df(0,0,30));
        node->setMaterialTexture(0, driver->getTexture("tex/Bricks11.png"));
        //node->setMaterialFlag(video::EMF_LIGHTING, true);
    }    

	PlayerNode *pNode =
        new PlayerNode(smgr->getRootSceneNode(), smgr, 666, false);
	cPlayer = new VengPlayer();
	cPlayer->pN = pNode;

	smgr->addCameraSceneNodeFPS();

	if(novars == 0) {
		vars.Set_Cvar("d_internal_pnode",pNode);
		vars.Set_Cvar("d_internal_pobjc",cPlayer);
	}

	bool consoleDebounce = false;
	int pevWidth;
	int pevHeight;
	XWindowAttributes* attr = (XWindowAttributes*)malloc(sizeof(XWindowAttributes));
	VengUI* uiMan = new VengUI(device);
	q3map::q3loaded_map* mp = q3map::LoadMap(device,"map/stupid.bsp");
	//mp->g_node->setMaterialFlag(EMF_WIREFRAME,true);
	while(device->run()) 
	{
		const u32 now = device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;

		driver->beginScene(false,true,SColor(255,101,101,140));
		smgr->drawAll();
		guienv->drawAll();
		uiMan->Draw();
		driver->endScene();
		if(*connected) {
			currconn->SceneUpdate(device,cPlayer);
		}
		if(receiver.IsKeyDown(KEY_TAB) && !consoleDebounce) {
			consoleDebounce = true;
			if(!GlobConsole->Visbility)
				GlobConsole->Open();
			else
				GlobConsole->Close();
		} else if(!receiver.IsKeyDown(KEY_TAB) && consoleDebounce) {
			consoleDebounce = false;
		}
		if(receiver.IsKeyDown(KEY_F4)) {
			break;
		}
		int fps = driver->getFPS();
		core::stringw tmp(L"Veng: ");
		tmp += L" [";
		tmp += driver->getName();
		tmp += L"] fps: ";
		tmp += fps;
		tmp += L" | ";
		tmp += GlobConsole->LatestLine;

		fpsCntr->setText(tmp.c_str());
		device->setWindowCaption(tmp.c_str());
		lastFPS = fps;

		// evil linux dependent code
		irr::video::SExposedVideoData sv = driver->getExposedVideoData();
		XGetWindowAttributes((Display*)sv.OpenGLLinux.X11Display,sv.OpenGLLinux.X11Window,attr);
		if(pevWidth != attr->width || pevHeight != attr->height) {
			dimension2du dimensions = dimension2du(attr->width,attr->height);
			driver->OnResize(dimensions);
			GlobConsole->UpdConsoleBounds();
			GlobConsole->Logf("Resized from %ix%i -> %ix%i\n",pevWidth,pevHeight,attr->width,attr->height);
		}
		pevWidth = attr->width;
		pevHeight = attr->height;
	}
	device->drop();
	return 0;
}
