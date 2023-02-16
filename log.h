#ifndef LOG_H
#define LOG_H

#include "uint64.h"

extern void log_startup(void);

extern void log_query(uint64 *,const unsigned char client[16],unsigned int port,const char id[2],const char *q,const char qtype[2]);
extern void log_querydrop(uint64 *);
extern void log_querydone(uint64 *,unsigned int);

extern void log_tcpopen(const unsigned char client[16],unsigned int);
extern void log_tcpclose(const unsigned char client[16],unsigned int);

extern void log_cachedanswer(const char *q,const char type[2]);
extern void log_cachedcname(const char *,const char *);
extern void log_cachednxdomain(const char *);
extern void log_cachedns(const char *,const char *);

extern void log_tx(const char *q,const char qtype[2],const char *control,const unsigned char servers[256],unsigned int gluelessness);
extern void log_merge(const char *, const char *, const char *);

extern void log_nxdomain(const unsigned char server[16],const char *q,unsigned int ttl);
extern void log_nodata(const unsigned char server[16],const char *q,const char qtype[2],unsigned int ttl);
extern void log_servfail(const char *);
extern void log_lame(const unsigned char server[16],const char *control,const char *referral);

extern void log_rr(const unsigned char server[16],const char *q,const char type[2],const char *buf,unsigned int len,unsigned int ttl);
extern void log_rrns(const unsigned char server[16],const char *q,const char *data,unsigned int ttl);
extern void log_rrcname(const unsigned char server[16],const char *q,const char *data,unsigned int ttl);
extern void log_rrptr(const unsigned char server[16],const char *q,const char *data,unsigned int ttl);
extern void log_rrmx(const unsigned char server[16],const char *q,const char *mx,const char pref[2],unsigned int ttl);
extern void log_rrsoa(const unsigned char server[16],const char *q,const char *n1,const char *n2,const char misc[20],unsigned int ttl);

extern void log_stats(void);

#endif
