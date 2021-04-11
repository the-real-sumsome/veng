#include "Frames.hpp"
#include "PlayerNode.hpp"

PlayerNode::PlayerNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id, bool camEn) : scene::ISceneNode(parent, mgr, id) {
    Mesh = SceneManager->getMesh("mdl/v.mdl");
    MeshNode = mgr->addAnimatedMeshSceneNode(Mesh,this);
    PlayerNameText = mgr->addTextSceneNode(mgr->getGUIEnvironment()->getBuiltInFont(),core::stringw("Player").c_str(),video::SColor(100,0,0,0),this);
    core::vector3df TPos = PlayerNameText->getPosition();
    TPos.Y+=40;
    core::vector3df BPos = getPosition();
    PlayerNameText->setPosition(TPos);
    MeshNode->setFrameLoop(ANIM_LOOK_IDLE);
    if(camEn) {
        cam = mgr->addCameraSceneNode(this);
        cam->setPosition(core::vector3df(BPos.X,BPos.Y+27,BPos.Z)); // eye height is 27u off the ground
        cam->bindTargetAndRotation(true);
        MeshNode->setVisible(false);
    }
}

void PlayerNode::OnRegisterSceneNode() {
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);

    ISceneNode::OnRegisterSceneNode();
}

void PlayerNode::render()
{   
    video::IVideoDriver* driver = SceneManager->getVideoDriver();

    RelativeRotation.Y++;
    core::vector3df CamRot = RelativeRotation;
    core::vector3df BPos = getPosition();
    CamRot.Y += 90;
    cam->setRotation(CamRot);
    cam->setPosition(core::vector3df(BPos.X,BPos.Y+27,BPos.Z));

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