#ifndef H_demo_Server
#define H_demo_Server
//---------------------------------------------------------------------------
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <string>
//---------------------------------------------------------------------------
// Utilities - networking server
// Alexander van Renen 2011
//---------------------------------------------------------------------------
namespace gda {
//---------------------------------------------------------------------------
class Connection;
//---------------------------------------------------------------------------
/// Class for managing domain sockets
class Server {
public:
   /// Constructor for domain name sockets
   Server(const std::string& path);
   /// Constructor for tcp sockets
   Server(uint32_t port);
   /// Destructor
   ~Server();

   /// waits for a new connection and place the info about it in conny
   bool waitForConnection(Connection& conny, int64_t timeInMs = -1);

   /// For checking server
   bool good() const;
   const std::string getPath() const;
   uint32_t getPort() const;

   /// Get a nice text message about the server state
   void getFailMsg(std::string& msg);

private:
   /// Common Server data
   int32_t serverSocket;

   /// Domain name server data
   const std::string serverPath;
   sockaddr_un unServerAddr;

   /// Tcp server data
   uint32_t serverPort;
   sockaddr_in inServerAddr;

   /// Server state
   int32_t state;

   /// Constants for the server state
   static const int32_t kGoodState = 0; // => everything is all rights babe
   static const int32_t kCreateSocketFail = -1; // => socket() failed
   static const int32_t kBindSocketFail = -2; // => bind() failed
   static const int32_t kOptSocketFail = -3; // => set sock opt failed
   static const int32_t kAcceptClientFail = -4; // => accept() failed
   static const int32_t kReadFail = -5; // => read() failed
   static const int32_t kWriteFail = -6; // => write() failed
};
//---------------------------------------------------------------------------
/// Stores data and offers functionality for a single connection
class Connection {
public:
   /// Constructor
   Connection();

   /// Read and write from the underlying socket
   bool read(std::string& msg, int64_t timeInMs = -1);
   bool write(const std::string& msg);

   /// Close the connection
   bool closeConnection();

   /// Information about the Connection status
   bool good();

private:
   /// Data fields representing the internal state
   int32_t socket;
   sockaddr_un addr;
   socklen_t addrlen;
   int32_t state;

   /// Declare this function a friend because it inits this connection object
   friend bool Server::waitForConnection(Connection& conny, int64_t timeInMs = -1);
};
//---------------------------------------------------------------------------
} //end of namesapce gda
//---------------------------------------------------------------------------
#endif
