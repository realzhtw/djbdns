#ifndef RESPONSE_H
#define RESPONSE_H

#include "uint32.h"

extern char response[];
extern unsigned int response_len;

extern int response_query(const char *q,const char qtype[2],const char qclass[2]);
extern void response_nxdomain(void);
extern void response_servfail(void);
extern void response_id(const char id[2]);
extern void response_tc(void);

extern int response_addbytes(const void *,unsigned int);
extern int response_addname(const char *);
extern void response_hidettl(void);
extern int response_rstart(const char *d,const char type[2],uint32 ttl);
extern void response_rfinish(int);

#define RESPONSE_ANSWER 6
#define RESPONSE_AUTHORITY 8
#define RESPONSE_ADDITIONAL 10

extern int response_cname(const char *,const char *,uint32);

#endif
