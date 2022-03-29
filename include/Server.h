struct ServerInitInfo {
  int socket_fd;
  bool does_server_already_exist;
};

// if server already exists socket_fd_ will be set to -1
ServerInitInfo
DoesServerAlreadyExist(in_port_t port, in_addr_t ip);

class Server {
 public:
  Server(const ServerInitInfo& info);
  void StartChatting();
  ~Server();

 private:
  Server() = default;
  int socket_fd_ = -1;
  // file where we will receive all messages
  int msgs_fd_ = -1;
};