#include <iostream>
#include "websocket_client.hpp"

const std::string url="wss://mitsuji.org/mchat/ws";

class chat_client
  : public mwebsock::nclient
{
public:
  chat_client( const std::string& name )
    :name_(name)
  {}
 
  void on_message( const std::string& msg)
  {
    std::cout << msg << std::endl;
  }

  void on_open()
  {
    this->send("c:" + name_);
    std::cout << ">> server connected." << std::endl;
  }

  void on_close()
  {
    std::cout << ">> server closed." << std::endl;
  }

  void on_error( int error_code, const std::string& msg )
  {
    std::cout << "error:" << msg << std::endl;
  }

private:
  std::string name_;
};


int main(int argc, char** argv)
{
  if( argc < 2 ) 
    {
      std::cout << "test [user_name]" << std::endl;
      return 1;
    }

  try
    {
      chat_client client(argv[1]);
      client.set_verify_file("..\\dist\\org.mitsuji.server.crt");
      client.connect(url);

      std::string line;
      while(std::getline(std::cin, line ))
      {
	char c = line.at(0);

	switch(c)
	  {
	  case 'q':
	    {
	      client.close();
	      std::cout << ">> client closed." << std::endl;
	      return 0;
	    }
	    break;
	  case 'u':
	    {
	      client.close();
	      std::cout << ">> client closed." << std::endl;
	    }
	    break;
	  case 'c':
	    {
	      client.connect(url);
	    }
	    break;
	  default:
	    {
	      client.send("m:" + line );
	    }
	    break;
	  }
	
      }

    }
  catch (std::exception& e)
    {
      std::cout << "Exception: " << e.what() << "\n";
    }
  
  return 0;
 
}
