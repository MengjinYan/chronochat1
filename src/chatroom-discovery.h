
#ifndef CHRONOS_CHATROOM_DISCOVERY_H
#define CHRONOS_CHATROOM_DISCOVERY_H

#include <ndn-cxx/face.hpp>
#include <ndn-cxx/security/key-chain.hpp>


namespace chronos{

  struct participant
  {
    ndn::Name& nameSpace;
    std::string nickName;

    participant& operator= ( participant copy )
    {
      this->nameSpace = copy.nameSpace;
      this->nickName = copy.nickName;
      return *this;
    }
  };

  struct chatroom
  {
    std::vector<struct participant> participants;
    bool isHierarchicalTrustModel;
    bool hasContact;
  };


  class ChatroomDiscovery
    {
public:

      ChatroomDiscovery(const std::vector<struct chronos::chatroom>& chatroomlist);

      ChatroomDiscovery();

      ~ChatroomDiscovery();

      
    

private:
      std::vector<struct chatroom> m_chatroomList;

    };

}


#endif
