#ifndef LAPSIPC_H
#define LAPSIPC_H
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<gtk/gtk.h>

int
 parentProcess();

int
 childProcess();

char *
 getFifoPath(char *);

int
 lapsiInit();
int
  checkConnection(int );
#endif
