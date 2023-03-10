#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "byte.h"
#include "socket.h"

int socket_accept4(int s,unsigned char ip[4],uint16 *port)
{
  struct sockaddr_in sa;
  socklen_t dummy = sizeof sa;
  int fd;

  fd = accept(s,(struct sockaddr *) &sa,&dummy);
  if (fd == -1) return -1;

  byte_copy(ip,4,(char *) &sa.sin_addr);
  uint16_unpack_big((char *) &sa.sin_port,port);

  return fd;
}
