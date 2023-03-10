#include "taia.h"
#include "openreadclose.h"
#include "byte.h"
#include "ip4.h"
#include "ip6.h"
#include "env.h"
#include "dns.h"

static stralloc data = {0};

static int init(unsigned char ip[256])
{
  int i;
  unsigned int j;
  int iplen = 0;
  char *x;

  x = env_get("DNSCACHEIP");
  if (x)
    while (iplen <= 60) {
      if (*x == '.')
	++x;
      else {
        i = ip6_scan(x,ip + iplen);
	if (!i) break;
	x += i;
	iplen += 16;
      }
    }

  if (!iplen) {
    i = openreadclose("/etc/resolv.conf",&data,64);
    if (i == -1) return -1;
    if (i) {
      if (!stralloc_append(&data,"\n")) return -1;
      i = 0;
      for (j = 0;j < data.len;++j)
        if (data.s[j] == '\n') {
          if (byte_equal("nameserver ",11,data.s + i) || byte_equal("nameserver\t",11,data.s + i)) {
            i += 10;
            while ((data.s[i] == ' ') || (data.s[i] == '\t'))
              ++i;
            if (iplen <= 60)
              if (ip6_scan(data.s + i,ip + iplen)) {
                iplen += 16;
	      }
          }
          i = j + 1;
        }
    }
  }

  if (!iplen) {
    byte_copy(ip,16,"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1");
    iplen = 16;
  }
  byte_zero(ip + iplen,256 - iplen);
  return 0;
}

static int ok = 0;
static unsigned int uses;
static struct taia deadline;
static unsigned char ip[256]; /* defined if ok */

int dns_resolvconfip(unsigned char s[256])
{
  struct taia now;

  taia_now(&now);
  if (taia_less(&deadline,&now)) ok = 0;
  if (!uses) ok = 0;

  if (!ok) {
    if (init(ip) == -1) return -1;
    taia_uint(&deadline,600);
    taia_add(&deadline,&now,&deadline);
    uses = 10000;
    ok = 1;
  }

  --uses;
  byte_copy(s,256,ip);
  return 0;
}
