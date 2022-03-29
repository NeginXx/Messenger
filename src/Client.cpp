#include <arpa/inet.h>
#include <assert.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../include/Chatting.h"
#include "../include/Client.h"

Client::Client(in_port_t port, in_addr_t ip) {
  msgs_fd_ = socket(AF_INET, SOCK_STREAM, 0);
  assert(msgs_fd_ != -1);

  sockaddr_in sin = {};
  sin.sin_family = AF_INET;
  sin.sin_port = port;
  sin.sin_addr.s_addr = ip;
  assert(connect(msgs_fd_, (const sockaddr*)&sin, sizeof(sin)) == 0);
}

void Client::StartChatting() {
  static bool is_called_first_time = true;
  assert(is_called_first_time &&
  "Repeated call of this function leads to leaks and incorrect work");
  is_called_first_time = false;

  Chat(msgs_fd_);
}

Client::~Client() {
  shutdown(msgs_fd_, SHUT_RDWR);
  close(msgs_fd_);
}