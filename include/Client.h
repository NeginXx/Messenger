class Client {
 public:
  Client(in_port_t port, in_addr_t ip);
  void StartChatting();
  ~Client();

 private:
  // file where we will receive all messages
  int msgs_fd_ = -1;
};