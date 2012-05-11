#include "gda/server.hpp"
#include <iostream>
#include <sys/time.h>
#include <limits>
#include <unistd.h>
#include <arpa/inet.h>
//---------------------------------------------------------------------------
// Utilities - networking server
// Alexander van Renen 2011
//---------------------------------------------------------------------------
using namespace std;
using namespace gda;
//---------------------------------------------------------------------------
Server::Server(const string& path)
: serverSocket(-1)
, serverPath(path)
, serverPort(0)
{
   //set up server Socket
   bzero((char *) &unServerAddr, sizeof(unServerAddr));
   serverSocket = socket(AF_UNIX, SOCK_STREAM, 0);
   if(serverSocket<0) {
      state = kCreateSocketFail;
      return;
   }

   //bind server Socket
   unServerAddr.sun_family = AF_UNIX;
   strcpy(unServerAddr.sun_path, serverPath.c_str());
   unlink(unServerAddr.sun_path);
   int bindSuc = bind(serverSocket, (sockaddr *) &unServerAddr, strlen(unServerAddr.sun_path) + sizeof(unServerAddr.sun_family));
   if (bindSuc<0) {
      state = kBindSocketFail;
      return;
   }

   //free server Socket at close instantly
   int on = 1;
   int optSuc = setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
   if (optSuc < 0) {
      state = kOptSocketFail;
      return;
   }

   //listen
   listen(serverSocket,5);

   state = kGoodState;
}
//---------------------------------------------------------------------------
Server::Server(uint32_t port)
: serverSocket(-1)
, serverPath("not a domain name socket")
, serverPort(port)
{
   //set up server Socket
   bzero((char *) &inServerAddr, sizeof(inServerAddr));
   serverSocket = socket(AF_INET, SOCK_STREAM, 0);
   if(serverSocket<0) {
      state = kCreateSocketFail;
      return;
   }

   //bind server Socket
   inServerAddr.sin_family = AF_INET;
   inServerAddr.sin_addr.s_addr = INADDR_ANY;
   inServerAddr.sin_port = htons(serverPort);
   int bindSuc = bind(serverSocket, (sockaddr *) &inServerAddr, sizeof(inServerAddr));
   if (bindSuc<0) {
      state = kBindSocketFail;
      return;
   }

   //listen
   listen(serverSocket,5);

   state = kGoodState;
}
//---------------------------------------------------------------------------
Server::~Server()
{
   //shutdown
   shutdown(serverSocket,2);
   if(close(serverSocket) != 0)
      std::cerr << "fail on closing server socket" << std::endl;
}
//---------------------------------------------------------------------------
bool Server::waitForConnection(Connection& conny, int64_t timeInMs)
{
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
      FD_SET(serverSocket, &rfds);
      int retval = select(serverSocket+1, &rfds, NULL, NULL, &tv);

      if(retval == -1 || !retval) // => no input
         return false;
   }

   if(state != kGoodState)
      return false;

   //accept client
   conny.addrlen = sizeof(conny.addr);
   conny.socket = accept(serverSocket, (sockaddr*) &conny.addr, &conny.addrlen);

   return conny.socket >= 0;
}
//---------------------------------------------------------------------------
bool Server::good() const
{
   return state == kGoodState;
}
//---------------------------------------------------------------------------
const string Server::getPath() const
{
   return serverPath;
}
//---------------------------------------------------------------------------
uint32_t Server::getPort() const
{
   return serverPort;
}
//---------------------------------------------------------------------------
void Server::getFailMsg(std::string& msg) const
{
   switch(state) {
      case kGoodState:
         msg = "win server is fine";
         break;
      case kCreateSocketFail:
         msg = "fail unable to create socket";
         break;
      case kBindSocketFail:
         msg = "fail unable to bind socket";
         break;
      case kOptSocketFail:
         msg = "fail unable to set socket";
         break;
      case kAcceptClientFail:
         msg = "fail unable to accept socket";
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
string Server::getFailMsg() const
{
   string result;
   getFailMsg(result);
   return result;
}
//---------------------------------------------------------------------------
Connection::Connection()
: state(0)
{
}
//---------------------------------------------------------------------------
bool Connection::read(std::string& msg, int64_t timeInMs)
{
   // check state
   if(!good()) {
      if(debug >= 3)
         cout << "server::read::fail: connection is in bad state" << endl;
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
      FD_SET(socket, &rfds);
      int retval = select(socket+1, &rfds, NULL, NULL, &tv);

      if(retval == -1 || !retval) { // => no input
         if(debug >= 3)
            cout << "server::read::fail: no input" << endl;
         return false;
      }
   }

   //read client
   char buffer[2048];
   bzero(buffer, sizeof(buffer));
   int readSuc = ::read(socket, buffer, sizeof(buffer)-1);
   if (readSuc <= 0) {
      if(debug >= 2)
         cout << "server::read::fail: fail on reading" << endl;
      return (state = -1) == 0;
   }

   //save and return
   msg = buffer;
   if(debug >= 1)
      cout << "server::read: " << msg << endl;
   return true;
}
//---------------------------------------------------------------------------
bool Connection::write(const std::string& msg)
{
   //check state
   if(!good()) {
      if(debug >= 3)
         cout << "server::write::fail: connection is in bad state" << endl;
      return false;
   }

   //send
   int writeSuc = ::write(socket, msg.c_str(), msg.size());

   //update sate
   if(writeSuc <= 0) { // => fail
      if(debug >= 2)
         cout << "server::write::fail: fail on writing" << endl;
      return (state = -1) == 0;
   } else { // => success
      if(debug >= 1)
         cout << "server::write: " << msg << endl;
      return true;
   }
}
//---------------------------------------------------------------------------
bool Connection::closeConnection()
{
   shutdown(socket, 2);
   if(close(socket) != 0)
      if(debug)
         cout << "fail on closing connection" << endl;

   return true;
}
//---------------------------------------------------------------------------
bool Connection::good()
{
   return state==0;
}
//---------------------------------------------------------------------------
uint32_t Connection::getPort() const
{
   return socket;
}
//---------------------------------------------------------------------------
const string Connection::getIp() const
{
   string result(addrlen, ' ');
   inet_ntop(AF_INET, &addr.sin_addr, &result[0], addrlen); // AAA INET vs UNIX
   return string(result.c_str()); // need to filter \0 .. stupid c ..
}
//---------------------------------------------------------------------------
