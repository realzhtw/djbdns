#include "fcompcmdline.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char* run[100];
size_t n=0;

void addarg(char* c) {
  if (n>95) {
    fprintf(stderr,"too many command line arguments, increase size of run in fcomp.c.\n");
    exit(1);
  }
  run[n]=c;
  ++n;
}

int main(int argc,char* argv[]) {
  char* c=cmdline;
  char dashc[]="-c";
  size_t i;

  addarg(cmdline);
  while ((c=strchr(c,' '))) {
    *c=0; ++c;
    addarg(c);
  }
  addarg(dashc);
  for (i=1; i<argc; ++i)
    addarg(argv[i]);
  execvp(run[0],run);
  fprintf(stderr,"could not exec \"%s\"\n", run[0]);
  return 1;
}
