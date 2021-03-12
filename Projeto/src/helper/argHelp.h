#ifndef LIB_ARGHELP_H
#define LIB_ARGHELP_H

extern char *optarg;
extern int optind;

int getArguments(int argc, char *argv[], char *optstring);

void incrementOptind();

/**/

#endif