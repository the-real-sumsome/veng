#include "Player.hpp"
#include "../net/Serialization.h"

VengPlayer::VengPlayer() {

}

void VengPlayer::SyncNet(NetConnection net) {
    VengWriteString(net.SockFd,"sP");
    Health = VengReadInt(net.SockFd);
    Armor = VengReadInt(net.SockFd);
    Username = VengReadString(net.SockFd);
    pN->setPosition(core::vector3df(VengReadFloat(net.SockFd),VengReadFloat(net.SockFd),VengReadFloat(net.SockFd)));
}