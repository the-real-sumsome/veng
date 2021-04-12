#ifndef __PLAYERNODE_HPP__
#define __PLAYERNODE_HPP__

#include <irrlicht/irrlicht.h>
using namespace irr;

class PlayerNode : public scene::ISceneNode {
public:
    PlayerNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id, bool camEn);
    virtual void render();
    virtual void OnRegisterSceneNode();
    virtual const core::aabbox3d<f32>& getBoundingBox() const;
    virtual u32 getMaterialCount() const;
    virtual video::SMaterial& getMaterial(u32 i);

    scene::IAnimatedMesh* Mesh;
    scene::IAnimatedMeshSceneNode* MeshNode;
    scene::ITextSceneNode* PlayerNameText;
    scene::ICameraSceneNode* cam;
    scene::ISceneNodeAnimator* anim;
    float EyeHeight;
private:
    bool camEn;
};

#endif