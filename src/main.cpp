#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>

#include "../include/Client.h"
#include "../include/Server.h"

const in_port_t kDefaultPort = htons(49000);
const in_addr_t kDefaultIp = inet_addr("127.0.0.1");

struct Flags {
  bool need_help = false;
  in_port_t port = kDefaultPort;
  in_addr_t ip = kDefaultIp;
};

Flags ProcessFlags(int argc, char** argv) {
  Flags flags;
  for (int i = 1; i < argc; ++i) {
    const char* arg = argv[i];
    if (arg[0] == '-') {
      if (arg[1] == 'h') {
        flags.need_help = true;
      } else if (arg[1] == 'p') {
        flags.port = htons(atoi(arg + 2));
      } else if (arg[1] == 'i') {
        flags.ip = inet_addr(arg + 2);
      } else {
        printf("ERROR: unrecognized flag %s; try -h for help\n", arg);
      }
    } else {
      printf("ERROR: flag was expected, this \"%s\" found tho; try -h for help\n", arg);
    }
  }
  return flags;
}

void PrintHelp() {
  printf("default port is 49000\n");
  printf("default address is 127.0.0.1\n");
  printf("-p specify port\n");
  printf("-p specify ip address of server\n");
  printf("-h help\n\n");
  printf("Example: -h -p49000 -i127.0.0.1\n");
}

int main(int argc, char** argv) {
  Flags flags = ProcessFlags(argc, argv);
  if (flags.need_help) {
    PrintHelp();
    return 0;
  }
  ServerInitInfo info = DoesServerAlreadyExist(flags.port, flags.ip);
  if (info.does_server_already_exist) {
    Client client(flags.port, flags.ip);
    client.StartChatting();
  } else {
    Server server(info);
    server.StartChatting();
  }
}