#include "../management/Console.hpp"
#include "Q3Map.hpp"

q3map::q3loaded_map* q3map::LoadMap(irr::IrrlichtDevice* dev, char* name) {
    GlobConsole->Logf("loading q3 octree map %s\n",name);
    irr::scene::ISceneManager* smgr = dev->getSceneManager();
    irr::scene::IQ3LevelMesh* q3levelmesh = (irr::scene::IQ3LevelMesh*)smgr->getMesh(name);
    irr::scene::ISceneNode* q3node = 0;
    q3map::q3loaded_map* map = (q3map::q3loaded_map*)malloc(sizeof(q3map::q3loaded_map));
    map->q3levelmesh = q3levelmesh;
    map->q3node = q3node;
    if (q3levelmesh) { 
		irr::scene::IMesh * const geometry = q3levelmesh->getMesh(irr::scene::quake3::E_Q3_MESH_GEOMETRY);
        map->geometry = geometry;
		q3node = smgr->addOctreeSceneNode(geometry, 0, -1, 4096);
		const irr::scene::IMesh * const additional_mesh = q3levelmesh->getMesh(irr::scene::quake3::E_Q3_MESH_ITEMS);
        map->additional_mesh = (irr::scene::IMesh *)additional_mesh;
		GlobConsole->Logf("additional_mesh buffer count (usually shaders) %i\n",additional_mesh->getMeshBufferCount());
		for ( irr::u32 i = 0; i!= additional_mesh->getMeshBufferCount(); ++i )
        {
            const irr::scene::IMeshBuffer* meshBuffer = additional_mesh->getMeshBuffer(i);
            const irr::video::SMaterial& material = meshBuffer->getMaterial();

            // The ShaderIndex is stored in the material parameter
            const irr::s32 shaderIndex = (irr::s32) material.MaterialTypeParam2;

            // the meshbuffer can be rendered without additional support, or it has no shader
            const irr::scene::quake3::IShader *shader = q3levelmesh->getShader(shaderIndex);
            if (0 == shader)
            {
                continue;
            }

            // we can dump the shader to the console in its
            // original but already parsed layout in a pretty
            // printers way.. commented out, because the console
            // would be full...
            // quake3::dumpShader ( Shader );
			GlobConsole->Logf("loaded shader %s\n",shader->name.c_str());
            q3node = smgr->addQuake3SceneNode(meshBuffer, shader);
        }

        irr::scene::quake3::tQ3EntityList &entityList = q3levelmesh->getEntityList();

        irr::scene::quake3::IEntity search;
        search.name = "info_veng_sky";

        irr::s32 index = entityList.binary_search(search);
        if (index >= 0)
        {
            irr::s32 notEndList;
            do
            {
                const irr::scene::quake3::SVarGroup *group = entityList[index].getGroup(1);

                irr::u32 parsepos = 0;

                irr::scene::quake3::tStringList strings = irr::scene::quake3::tStringList(6);
                
                GlobConsole->Logf("skybox info: %s\n",group->get("info").c_str());
                irr::scene::quake3::getAsStringList(strings,6,group->get("info"),parsepos);
                dev->getSceneManager()->addSkyBoxSceneNode(
                    dev->getVideoDriver()->getTexture(strings[0]),
                    dev->getVideoDriver()->getTexture(strings[1]),
                    dev->getVideoDriver()->getTexture(strings[2]),
                    dev->getVideoDriver()->getTexture(strings[3]),
                    dev->getVideoDriver()->getTexture(strings[4]),
                    dev->getVideoDriver()->getTexture(strings[5]));

                ++index;
                notEndList = index == 2;
            } while ( notEndList );
        }


        search.name = "light";

        index = entityList.binary_search(search);
        if (index >= 0)
        {
            irr::s32 notEndList;
            do
            {
                const irr::scene::quake3::SVarGroup *group = entityList[index].getGroup(1);

                irr::u32 parsepos = 0;

                // make lights

                ++index;
                notEndList = index == 2;
            } while ( notEndList );
        }
	}
}