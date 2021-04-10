#include "Player.hpp"
#include "../net/Serialization.h"

VengPlayer::VengPlayer() {

}

void VengPlayer::SyncNet(NetConnection net) {
    VengWriteString(net.SockFd,"sP");
    VengReadInt(net.SockFd,&Health);
    VengReadInt(net.SockFd,&Armor);
    Username = VengReadString(net.SockFd);
    float pX = 0;
    float pY = 0;
    float pZ = 0;
    VengReadFloat(net.SockFd,&pX);
    VengReadFloat(net.SockFd,&pY);
    VengReadFloat(net.SockFd,&pZ);
    pN->setPosition(core::vector3df());
}