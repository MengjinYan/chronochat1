

#include "chatroom-discovery.h"

using namespace ndn;
using namespace chronos;

ChatroomDiscovery::ChatroomDiscovery(const std::vector<struct chatroom>& chatroomlist)
{
  m_chatroomList = chatroomlist;
}

ChatroomDiscovery::ChatroomDiscovery()
{

}  

ChatroomDiscovery::~ChatroomDiscovery()
{}



