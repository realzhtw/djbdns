#ifndef PRINTRECORD_H
#define PRINTRECORD_H

#include "stralloc.h"

extern unsigned int printrecord_cat(stralloc *out,const char *buf,unsigned int len,unsigned int pos,const char *q,const char qtype[2]);
extern unsigned int printrecord(stralloc *out,const char *buf,unsigned int len,unsigned int pos,const char *q,const char qtype[2]);

#endif
