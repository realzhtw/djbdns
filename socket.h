#ifndef SOCKET_H
#define SOCKET_H

#include "uint16.h"
#include "uint32.h"

extern int socket_tcp(void);
extern int socket_udp(void);
extern int socket_tcp6(void);
extern int socket_udp6(void);

extern int socket_connect4(int,const unsigned char ip[4],uint16);
extern int socket_connect6(int s,const unsigned char ip[16],uint16 port,uint32 scope_id);
extern int socket_connected(int);
extern int socket_bind4(int,const unsigned char ip[4],uint16);
extern int socket_bind4_reuse(int,const unsigned char ip[4],uint16);
extern int socket_bind6(int s,const unsigned char ip[16],uint16 port,uint32 scope_id);
extern int socket_bind6_reuse(int s,const unsigned char ip[16],uint16 port,uint32 scope_id);
extern int socket_listen(int,int);
extern int socket_accept4(int,unsigned char ip[4],uint16 *);
extern int socket_accept6(int s,unsigned char ip[16],uint16 *port,uint32 *scope_id);
extern int socket_recv4(int,char *,int,unsigned char ip[4],uint16 *);
extern int socket_send4(int,const char *,int,const unsigned char ip[4],uint16);
extern int socket_recv6(int s,char *buf,unsigned int len,unsigned char ip[16],uint16 *port,uint32 *scope_id);
extern int socket_send6(int s,const char *buf,unsigned int len,const unsigned char ip[16],uint16 port,uint32 scope_id);
extern int socket_local4(int,unsigned char ip[4],uint16 *);
extern int socket_remote4(int,unsigned char ip[4],uint16 *);
extern int socket_local6(int s,unsigned char ip[16],uint16 *port,uint32 *scope_id);
extern int socket_remote6(int s,unsigned char ip[16],uint16 *port,uint32 *scope_id);

extern void socket_tryreservein(int,int);

extern const char* socket_getifname(uint32 interface);
extern uint32 socket_getifidx(const char *ifname);

extern int noipv6;

#endif
