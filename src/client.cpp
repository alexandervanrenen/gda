#include "gda/client.hpp"
#include <limits>
#include <netdb.h> 
#include <iostream>
//---------------------------------------------------------------------------
// Utilities - networking client
// Alexander van Renen 2011
//---------------------------------------------------------------------------
using namespace std;
using namespace gda;
//---------------------------------------------------------------------------
Client::Client(const std::string& path)
: clientSocket(-1)
, clientPath(path)
, clientPort(0)
{
   initUn();
}
//---------------------------------------------------------------------------
Client::Client(const string& ip, uint32_t port)
: clientSocket(-1)
, clientPath(ip)
, clientPort(port)
{
   initIn();
}
//---------------------------------------------------------------------------
Client::~Client()
{
   if(clientSocket != -1)
      close(clientSocket);
}
//---------------------------------------------------------------------------
bool Client::read(std::string& msg, int64_t timeInMs)
{
   // check state
   if(!good()) {
      if(debug >= 3)
         cout << "client::read::fail: client is in bad state" << endl;
      return false;
   }

   // wait if needed
   if(timeInMs >= 0) {
      if(timeInMs/1000 > numeric_limits<int32_t>::max())
         throw "specified time is too large";

      //set time
      struct timeval tv;
      tv.tv_sec = timeInMs/1000;
      tv.tv_usec = timeInMs%1000*1000;

      //add the socket of this client to the set on which select will listen
      fd_set rfds;   
      FD_ZERO(&rfds);
      FD_SET(clientSocket, &rfds);
      int retval = select(clientSocket+1, &rfds, NULL, NULL, &tv);

      if(retval == -1 || !retval) { // => no input
         if(debug == 3)
            cout << "client::read::fail: no input" << endl;
         return false;
      }
   }

   //read client
   char buffer[2048];
   bzero(buffer, sizeof(buffer));
   int readSuc = ::read(clientSocket, buffer, sizeof(buffer)-1);
   if(readSuc <= 0) {
      if(debug >= 2)
         cout << "client::read::fail: fail on reading" << endl;
      return (state = kReadFail) == kGoodState;
   }

   //save and return
   msg = buffer;
   if(debug >= 1)
      cout << "client::read: " << msg << endl;
   return true;
}
//---------------------------------------------------------------------------
bool Client::write(const std::string& msg)
{
   //check state
   if(!good()) {
      if(debug >= 3)
         cout << "client::write::fail: client is in bad state" << endl;
      return false;
   }

   //send
   int writeSuc = ::write(clientSocket, msg.c_str(), msg.size());

   //update sate
   if(writeSuc <= 0) { // => fail
      if(debug >= 2)
         cout << "client::write::fail: fail on writing" << endl;
      return (state = kWriteFail) == kGoodState;
   } else { // => success
      if(debug >= 1)
         cout << "client::write: " << msg << endl;
      return true;
   }
}
//---------------------------------------------------------------------------
bool Client::good() const
{
   return state == kGoodState;
}
//---------------------------------------------------------------------------
void Client::getFailMsg(std::string& msg) const {
   switch(state) {
      case kGoodState:
         msg = "win client is fine";
         break;
      case kCreateSocketFail:
         msg = "fail unable to create socket";
         break;
      case kConnectSocketFail:
         msg = "fail unable to connect the socket";
         break;
      case kReadFail:
         msg = "fail unable to read from socket";
         break;
      case kWriteFail:
         msg = "fail unable to write to socket";
         break;
      default:
         msg = "fail unknown fail";
         break;
   }
}
//---------------------------------------------------------------------------
void Client::reconnect()
{
   if(clientPort == 0)
      initUn(); else
      initIn();
}
//---------------------------------------------------------------------------
void Client::initIn()
{
   //create socket
   clientSocket = socket(AF_INET, SOCK_STREAM, 0);
   if(clientSocket<0) {
      state = kCreateSocketFail;
      return;
   }

   //resolve host name
   hostent* server = gethostbyname(clientPath.c_str());
   if(server==NULL) {
      state = kResolveHostNameFail;
      return;
   }

   //connect socket
   bzero((char*) &inClientAddr, sizeof(inClientAddr));
   inClientAddr.sin_family = AF_INET;
   bcopy((char*)server->h_addr, (char*)&inClientAddr.sin_addr.s_addr, server->h_length);
   inClientAddr.sin_port = htons(clientPort);
   int connectSuc = connect(clientSocket,(struct sockaddr *) &inClientAddr,sizeof(inClientAddr));
   if (connectSuc<0) {
      state = kConnectSocketFail;
      return;
   }

   state = kGoodState;
}
//---------------------------------------------------------------------------
void Client::initUn()
{
   //create socket
   clientSocket = socket(AF_UNIX, SOCK_STREAM, 0);
   if(clientSocket<0) {
      state = kCreateSocketFail;
      return;
   }

   int on = 1;
   int optSuc = setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
   if (optSuc < 0) {
      state = kOptSocketFail;
      return;
   }

   //connect socket
   unClientAddr.sun_family = AF_UNIX;
   strcpy(unClientAddr.sun_path, clientPath.c_str());
   int connectSuc = connect(clientSocket, (struct sockaddr *)&unClientAddr, strlen(unClientAddr.sun_path) + sizeof(unClientAddr.sun_family));
   if(connectSuc<0) { 
      state = kConnectSocketFail;
      return;
   }

   state = kGoodState;
}
//---------------------------------------------------------------------------
