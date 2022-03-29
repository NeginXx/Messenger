#include <arpa/inet.h>
#include <assert.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../include/Chatting.h"
#include "../include/Server.h"

// if server already exists socket_fd_ will be set to -1
ServerInitInfo
DoesServerAlreadyExist(in_port_t port, in_addr_t ip) {
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  assert(socket_fd != -1);

  sockaddr_in sin = {};
  sin.sin_family = AF_INET;
  sin.sin_port = port;
  sin.sin_addr.s_addr = ip;

  if (bind(socket_fd, (const sockaddr*)&sin, sizeof(sin)) != 0) {
    close(socket_fd);
    return {-1, true};
  }
  return {socket_fd, false};
}

Server::Server(const ServerInitInfo& info)
: Server()
{
  socket_fd_ = info.socket_fd;
  assert(listen(socket_fd_, 1) == 0);
}

Server::~Server() {
  shutdown(socket_fd_, SHUT_RDWR);
  close(socket_fd_);
  if (msgs_fd_ != -1) {
    close(msgs_fd_);
  }
}

void Server::StartChatting() {
  static bool is_called_first_time = true;
  assert(is_called_first_time &&
  "Repeated call of this function leads to leaks and incorrect work");
  is_called_first_time = false;

  msgs_fd_ = accept(socket_fd_, nullptr, nullptr);
  assert(msgs_fd_ != -1);

  Chat(msgs_fd_);
}