Design Document
===============

Chatroom Discovery
-------------------

Function
~~~~~~~~~

While running the ChronoChat application, a list of ongoing chatrooms
is maintained with the basic chatroom information which can be
presented to the user whenever he requests. The user can select to
join a chatroom. The application will check if the user is allow to
join the chatroom. For chatrooms with hierarchical trust model, the
user will join immediately. For chatroom with web of trust trust
model, if one of the user's chatroom contact is in the chatroom, the
user will send a request for invitation. Otherwise, the application
will tell the user that he is not allow to join in the chatroom.

Detailed Design
~~~~~~~~~~~~~~~~

Discovery
+++++++++++++

When a user turns on a ChronoChat application, the application will
begin to discover ongoing chatrooms. Each of the participants in a
chatroom needs to maintain a list of all the participants in the
chatroom for other users to query.

A user sends a broadcast interest to query for all the ongoing
chatroom information as soon as he turns on ChronoChat
application. When the participant in a chatroom recieve the interest,
the participant will send a data package with all the information of
the chatroom. The user then send the same interest back, with already
fetched chatroom in the exclude filter. And he will recieve more data
packages with more chatrooms' information. When the interest expired
which means that there is no more new chatrooms, the list of chatroom
is completely generated.

Enumerate the Existed Chatrooms
+++++++++++++++++++++++++++++++

To enumerate all the existed chatrooms and avoid retrieving the same
data package from routing cache, after receiving a data package, the
user  add the data name into the interest's exclude filter and send
the interest again, while putting the information of the conference into
a list. Continue sending the interest package with more exclusions
until the interest is expired which means there is no more ongoing
chatrooms.

Maintain the Chatroom List
++++++++++++++++++++++++++

After the list of chatrooms are generated for the first time, the
lists will be maintained in the application. For both kinds of
chatroom, new queries are sent to discover new chatrooms and to
checked if old chatrooms are still exist.

+ **Resicovery:**
To discover new chatrooms, the user sends an interest with all the
existed chatrooms in the exclude filter. If recieving a data package,
it means that there are new chatrooms. The user adds the newly recieved
chatroom name in the exclude filter and send the interest back
again. Continue sending the interest package with more exclusions
until the interest is expired. The frequency of sending the interest
can be set as a difault time or set by the user. For every user, there
is a redicovery time which measures the frequency of dicover new
chatrooms. The time can be difined by the user.

+ **Refreshing:**
To check the existence of the old chatroom, the user sends an interest
with the specific name of the chatroom. If recieving a data package,
it means that the specific chatroom still exists. If the interest is
expired, the chatroom do not exist. For every chatroom there is a
refreshing time which measures the frequency of checking the
existance. The refreshing time can be defined in the data package as
FreshnessPeriod and after the time expired, the user will send a new
interest to check the existence of the specific chatroom. And finally,
the chatroom list changes according to the query result.

Security Consideration
~~~~~~~~~~~~~~~~~~~~~~~

In the design above, it is very hard for the user to identify if the
information he recieve is true. Therefore, although the data
package can be verified by hierarchical trust model or web of trust,
an attacker can attack the design by sending a great number of fake
chatroom information to the network. In this case, the user can verify
the data, but cannot decide if the information is true or not. Therefore,
some assumptions are made below.

For every chatroom, it is assumed that every participants of a
chatroom will not intend to send fake information to other users.

Under this assumption, all the data can be verified by the public key
generated according to the corresponding trust model and the security can
be garanteed in this level.

Conference Discovery Protocol
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

+ **Names:**

When a user request for all the ongoing chatrooms, he will send interests with the name:

 ``ndn/broadcast/chronochat/chatroom-list/``

After receiving a request interest, the information provider will return a data package with the name:

 ``ndn/broadcast/chronochat/chatroom-list/chatroom-name/``

In maintaining a chatroom, when a user is query for a new chatroom, he will send interest with the name:

 ``ndn/broadcast/chronochat/chatroom-list/``

And with the all the exist chatroom in the exclude filter.

In maintaining a chatroom, when a user is query for the existance of a chatroom, he will send interst with the name:

 ``ndn/broadcast/chatroom-name/``

+ **Structure of the Data Package**

Because users can obtain the chatroom name through the
data name, the data package that the information provider sends back
only need to contains: the name space of every participants, the nick
name of every participants and the chatroom's trust model.

For every participants, the data structure can be defined as:
::

   Participant := PARTICIPANT-TYPE TLV-LENGTH
                         Namespace
                         Nickname

For every chatroom,
::

   Chatroom := CHATROOM-TYPE TLV-LENGTH
                        TrustModel
                        Participant+

TLV assignments:

+------------------+----------------+----------------------+
| Type             | Assigned value | Assigned value (hex) |
+==================+================+======================+
| PARTICIPANT-TYPE |  128           |  0x80                |
+------------------+----------------+----------------------+
| CHATROOM-TYPE    |  129           |  0x81                |
+------------------+----------------+----------------------+



+ **Sending Data Back**

Every chatroom participants maintain a interest filter under the
prefix:

``ndn/broadcast/chronochat/chatroom-list``

When recieving interest with the corresponding prefix, the participant
will send out the data package with the chatroom name append in the
data package's name.

+ **Timing**

Two kinds of time needs to be defined when maintaining the list of
chatroom:

- **Refreshing time:** Every chatroom has a refreshing time defined when
    the chatroom build and as the data chatroom freshness time. If the
    time expired, requester need to send an interest to query for the
    existance of the chatroom.

- **Rediscovery time:** Rediscovery time is defined by the user. When
    the time expired, the user need to send an interest to query for new
    chatrooms.

+ **Chatroom List Data Structure**

For every participants:

::

   struct participant

   {

     Name nameSpace;

     string nickName;

   };

For every chatroom:

::

   struct chatroom

   {

     vector<struct participant> participants;

     bool isHierarchicalTrustModel;

     bool hasContact;

   };


The whole chatroom list:

::

   vector<struct chatroomList> chatrooms;
