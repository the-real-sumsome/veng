#include "Frames.hpp"
#include "PlayerNode.hpp"

PlayerNode::PlayerNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) : scene::ISceneNode(parent, mgr, id) {
    Mesh = SceneManager->getMesh("mdl/v.mdl");
    MeshNode = mgr->addAnimatedMeshSceneNode(Mesh,this);
    PlayerNameText = mgr->addTextSceneNode(mgr->getGUIEnvironment()->getBuiltInFont(),core::stringw("Player").c_str(),video::SColor(100,0,0,0),this);
    core::vector3df TPos = PlayerNameText->getPosition();
    TPos.Y+=40;
    PlayerNameText->setPosition(TPos);
    MeshNode->setFrameLoop(ANIM_IDLE);
    cam = mgr->addCameraSceneNode(this);
}

void PlayerNode::OnRegisterSceneNode() {
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);

    ISceneNode::OnRegisterSceneNode();
}

void PlayerNode::render()
{   
    core::vector3df pos = getPosition();
    cam->setPosition(core::vector3df(pos.X,pos.Y,pos.Z));
    
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