#ifndef __Q3MAP_HPP__
#define __Q3MAP_HPP__
#include <irrlicht/irrlicht.h>

namespace q3map {
    typedef struct {
        irr::scene::IQ3LevelMesh* q3levelmesh;
        irr::scene::ISceneNode* q3node;
        irr::scene::ISceneNode* g_node;
        irr::scene::IMesh* geometry;
        irr::scene::IMesh* additional_mesh;
    } q3loaded_map;
    q3loaded_map* LoadMap(irr::IrrlichtDevice*, char* name);
}

#endif