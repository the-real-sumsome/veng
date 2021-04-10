#include "Player.hpp"

VengPlayer::VengPlayer() {

}

void VengPlayer::SyncNet(NetConnection net) {
    VengNet::WriteString(net.SockFd,"sP");
    Health = VengNet::ReadInt(net.SockFd);
    Armor = VengNet::ReadInt(net.SockFd);
    Username = VengNet::ReadString(net.SockFd);
    pN->setPosition(core::vector3df(VengNet::ReadFloat(net.SockFd),VengNet::ReadFloat(net.SockFd),VengNet::ReadFloat(net.SockFd)));
}