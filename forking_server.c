#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);


static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("wkp");
    exit(0);
  }
}

int main() {
  while (1) {
    subserver(server_setup());
  }
}

void subserver(int from_client) {
  char buffer[BUFFER_SIZE];
  int p = fork();
  if (p == 0) {
    int to_client = server_connect(from_client);
    while (1) {
      if(read(from_client, buffer, sizeof(buffer)) == -1) {//read in next message and error handling
        printf("ERROR: %s\n", strerror(errno));
      }
      printf("%s\n", buffer); // print text received
      process(buffer); // edits input text
      printf("msg to be sent: %s\n", buffer);
      if (write(to_client, buffer, sizeof(buffer)) == -1) { // writes edited message to client and error handling
        printf("ERROR: %s\n", strerror(errno));
      }
    }
  }
}


void process(char * str) {
  int i = 0;
  while (str[i]) {
    str[i] = toupper(str[i]);
    i++;
  }
}
