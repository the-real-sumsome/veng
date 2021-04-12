#include "../management/Console.hpp"
#include "Q3Map.hpp"

void q3map::LoadMap(irr::IrrlichtDevice* dev, char* name) {
    irr::scene::ISceneManager* smgr = dev->getSceneManager();
    irr::scene::IQ3LevelMesh* q3levelmesh = (irr::scene::IQ3LevelMesh*)smgr->getMesh(name);
    irr::scene::ISceneNode* q3node = 0;
    if (q3levelmesh) { 
		irr::scene::IMesh * const geometry = q3levelmesh->getMesh(irr::scene::quake3::E_Q3_MESH_GEOMETRY);
		q3node = smgr->addOctreeSceneNode(geometry, 0, -1, 4096);
		const irr::scene::IMesh * const additional_mesh = q3levelmesh->getMesh(irr::scene::quake3::E_Q3_MESH_ITEMS);
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
	}
}