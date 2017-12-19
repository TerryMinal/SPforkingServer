#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);


static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("luigi");
    exit(0);
  }
}

int main() {
  while (1) { 
  int server = server_setup();
  subserver(server);
  }
}

void subserver(int from_client) {
  int fd;
  fd = server_connect(from_client);
  process(fd); 
}

void process(char * str) {
  int i = 0;
  while (str[i]) {
    str[i] = toupper(str[i]);
    i++;
  }
}

