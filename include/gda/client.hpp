#ifndef H_demo_Client
#define H_demo_Client
//---------------------------------------------------------------------------
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <string>
#include <sys/types.h> 
//---------------------------------------------------------------------------
// Utilities - networking client
// Alexander van Renen 2011
//---------------------------------------------------------------------------
namespace gda {
//---------------------------------------------------------------------------
class Client {

public:
   /// Constructor for domain name sockets
   Client(const std::string& path);
   /// Constructor for tcp sockets
   Client(const std::string& ip, uint32_t port);
   /// Destructor
   ~Client();

   /// Read and write from the underlying socket
   bool read(std::string& msg, int64_t timeInMs);
   bool write(const std::string& msg);

   /// For checking client
   bool good() const;
   const std::string& getPath() const;

   /// Get a nice text message about the client state
   void getFailMsg(std::string& msg) const;
   
   /// To repair the connection
   void reconnect();

private:
   /// Common client data
   int32_t clientSocket;
   const std::string clientPath; // == ip @ tcp

   /// Domain name client data
   sockaddr_un unClientAddr;

   /// Tcp client data
   sockaddr_in inClientAddr;
   const uint32_t clientPort;

   /// Client state
   int32_t state;
   
   /// init tcp
   void initIn();
   
   /// init domain name
   void initUn();

   /// Constants for the client state
   static const int32_t kGoodState = 0; // => everything is all rights babe
   static const int32_t kCreateSocketFail = -1; // => socket() failed
   static const int32_t kConnectSocketFail = -2; // => copnnect() failed
   static const int32_t kNotInitialized = -3; // => not init
   static const int32_t kResolveHostNameFail = -4; // => could not find host
   static const int32_t kReadFail = -5; // => read() failed
   static const int32_t kWriteFail = -6; // => write() failed
};
//---------------------------------------------------------------------------
} //end of namesapce gda
//---------------------------------------------------------------------------
#endif
