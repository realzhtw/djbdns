#ifndef IP4_H
#define IP4_H

extern unsigned int ip4_scan(const char *,unsigned char ip[4]);
extern unsigned int ip4_fmt(char *,const unsigned char ip[4]);

#define IP4_FMT 20

#endif
