#ifndef QUERY_H
#define QUERY_H

#include "dns.h"
#include "uint32.h"

#define QUERY_MAXLEVEL 5
#define QUERY_MAXALIAS 16
#define QUERY_MAXNS 16

struct query {
  unsigned int loop;
  unsigned int level;
  char *name[QUERY_MAXLEVEL];
  char *control[QUERY_MAXLEVEL]; /* pointing inside name */
  char *ns[QUERY_MAXLEVEL][QUERY_MAXNS];
  unsigned char servers[QUERY_MAXLEVEL][256];
  char *alias[QUERY_MAXALIAS];
  uint32 aliasttl[QUERY_MAXALIAS];
  unsigned char ipv6[QUERY_MAXLEVEL];
  unsigned char localip[16];
  uint32 scope_id;
  char type[2];
  char class[2];
  struct dns_transmit dt;
} ;

extern int query_start(struct query *z,char *dn,char type[2],char class[2],unsigned char localip[16],unsigned int scope_id);
extern void query_io(struct query *,iopause_fd *,struct taia *);
extern int query_get(struct query *,iopause_fd *,struct taia *);

extern void query_forwardonly(void);

#endif
