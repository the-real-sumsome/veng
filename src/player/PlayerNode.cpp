#include "Frames.hpp"
#include "PlayerNode.hpp"

PlayerNode::PlayerNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) : scene::ISceneNode(parent, mgr, id) {
    Mesh = SceneManager->getMesh("mdl/v.mdl");
    MeshNode = mgr->addAnimatedMeshSceneNode(Mesh,this);
    PlayerNameText = mgr->addTextSceneNode(mgr->getGUIEnvironment()->getBuiltInFont(),core::stringw("Player").c_str());
    MeshNode->setFrameLoop(ANIM_IDLE);
}

void PlayerNode::OnRegisterSceneNode() {
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);

    ISceneNode::OnRegisterSceneNode();
}

void PlayerNode::render()
{
    u16 indices[] = {   0,2,3, 2,1,3, 1,0,3, 2,0,1  };
    video::IVideoDriver* driver = SceneManager->getVideoDriver();

    driver->draw3DBox(MeshNode->getBoundingBox());
}

const core::aabbox3d<f32>& PlayerNode::getBoundingBox() const
{
    return MeshNode->getBoundingBox();
}

u32 PlayerNode::getMaterialCount() const
{
    return MeshNode->getMaterialCount();
}

video::SMaterial& PlayerNode::getMaterial(u32 i)
{
    return MeshNode->getMaterial(i);
}   