#include <cstdio>
#include <thread>
#include <unistd.h>

#include "../include/Chatting.h"

const size_t kMsgMaxlen = 512;

void WriteMessages(int msgs_fd) {
  char buf[kMsgMaxlen] = {};
  // TODO: replace while(true) with
  // system sleep until any input is present
  while (true) {
    scanf("%s", buf);
    write(msgs_fd, buf, kMsgMaxlen);
  }
}

void GetMessages(int msgs_fd) {
  char buf[kMsgMaxlen] = {};
  // TODO: replace while(true) with
  // system sleep until any input is present
  while (true) {
    read(msgs_fd, buf, kMsgMaxlen);
    printf("New message: %s\n", buf);
  }
}

void Chat(int msgs_fd) {
  std::thread write_thread(WriteMessages, msgs_fd);
  std::thread read_thread(GetMessages, msgs_fd);
  write_thread.join();
  read_thread.join();
}