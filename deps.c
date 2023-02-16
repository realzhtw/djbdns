#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int,char* argv[]) {
  char line[1024];
  FILE* m=fopen(argv[1]?argv[1]:"Makefile","r");
  if (!m) {
    perror("Could not open Makefile");
    return 1;
  }
  while (fgets(line,sizeof line,m)) {
    char* c = strchr(line,':');
    /* look for .o dependencies */
    if (c && c-line > 3 && c[-1]=='o' && c[-2]=='.') {
      /* found one */
      size_t i;
      *c=0;
      if (c-line > 20) {
	fprintf(stderr,"filename too long: \"%s\"\n",line);
	return 1;
      }
      for (i=0; line[i]; ++i)
	if (!isalnum(line[i]) && line[i]!='_' && line[i]!='-' && line[i]!='.') {
	  fprintf(stderr,"invalid filename: \"%s\"\n",line);
	  return 1;
	}
      char filename[35];
      char cmdline[50];
      c[-1]='c';
      strcpy(filename, line);
      snprintf(cmdline, sizeof cmdline, "gcc -MM -MG %s",filename);
//      fprintf(stderr,"running %s\n",cmdline);
      /* now eat the rest of the dependency, goes until newline */
      while (fgets(line,sizeof line,m) && line[0]!='\n') ;
      /* replace it with gcc generated dependencies */
      FILE* d=popen(cmdline,"r");
      if (!d) {
	perror("could not run gcc -MM -MG");
	return 1;
      }

      /* input: 
       * "alloc.o: alloc.c alloc.h error.h"
       * desired output:
       * "alloc.o: \\\ncompile alloc.c alloc.h error.h\n\t./compile alloc.c\n"
       */
      char unfolded[4096];
      size_t len=0,col=0,wordstart=0;
      memset(unfolded, 0, sizeof unfolded);

      int prev=0,c;
      while ((c = fgetc(d)) != EOF) {
	if (c == '\\' && prev == ' ') {
	  --len;
	  prev=c;
	  continue;
	}
	if (c == '\n' && prev == '\\') {
	  prev=c;
	  continue;
	}
	if (c == ' ' && prev == ':') {
	  if (len+100 > sizeof(unfolded))
	    goto toomuch;
	  strcpy(unfolded+len, " \\\ncompile");
	  len+=sizeof(" \\\ncompile")-1;
	  col=sizeof("compile")-1;
	}
	if (prev == ' ' || c == '\n') {	// maybe do line break
	  if (col>71) {
	    memmove(unfolded+wordstart+2, unfolded+wordstart, col=len-wordstart);
	    unfolded[wordstart]='\\';
	    unfolded[wordstart+1]='\n';
	    len+=2;
	  }
	  wordstart=len;
	}
	prev=c;
	if (len+2 > sizeof unfolded) {
toomuch:
	  fprintf(stderr, "too much dependency data. make unfolded larger in deps.c.\n");
	  return 1;
	}
	unfolded[len]=c; ++len; ++col;
      }
      pclose(d);
      unfolded[len]=0;
      printf("%s\t./compile %s\n\n",unfolded,filename);
    } else {
      printf("%s",line);
    }
  }
  return 0;
}
