#ifndef UINT16_H
#define UINT16_H

typedef unsigned short uint16;

extern void uint16_pack(char dst[2],uint16);
extern void uint16_pack_big(char dst[2],uint16);
extern void uint16_unpack(const char src[2],uint16 *);
extern void uint16_unpack_big(const char src[2],uint16 *);

#endif
