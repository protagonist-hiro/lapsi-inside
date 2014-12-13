#include"lapsipc.h"
GIOChannel * channel;
int FdIn;
gboolean
inputCallback()
{
  char buf[4096];
  read(FdIn,buf,4096);
  buf[strlen(buf)+1]='\0';
  printf("FROM LAPSI :: THE FOLLOWING STRING RECIEVED FROM PYLAPSI %s OF SIZE %d :\n",buf,strlen(buf));
  printf("FROM LAPSI :: EQUATING TO THE KNOWN STRING GIVES %d \n",strcmp(buf,"hellp"));
}

int setUpIpc()
{
  int fd;
  printf("Creating a fifo BY parent\n");
  mkfifo(getFifoPath("/home/hiro/lapsi/fifo"),0666);
  pid_t pid = fork();
  if(pid == 0)
    {
      childprocess();

    }
    if(pid>0)
      {
        parentprocess();
      }
      return fd;
}

int parentprocess()
{
  FdIn = open(getFifoPath("/home/hiro/lapsi/fifo"),O_RDONLY | O_NONBLOCK);
  channel = g_io_channel_unix_new(FdIn);
  g_io_add_watch(channel,G_IO_IN,(GIOFunc)inputCallback,NULL);
  return FdIn;
}


int childprocess()
{
    execl("./main.py",NULL,(char*)NULL);

}


char * getFifoPath(char * prefixPath)
{
  char *stringPid = malloc(getpid()+1);
  char *localPrefix=malloc(strlen(prefixPath)*sizeof(char)+20+getpid()+1);
  strcpy(localPrefix,prefixPath);
  snprintf(stringPid,100,"%d",getpid());
  strcat(localPrefix,stringPid);
  return localPrefix;
}


int outIpc()
{
  char *path = getFifoPath("/home/hiro/lapsi/fifo_");
  int fd = open(path,O_WRONLY|O_NONBLOCK);
  char * buff = "HELLO JANI";
  write(fd,buff,strlen(buff)+1);
  printf("FROM LAPSI :: WROTE TO PYLAPSI CONNECTION SUCCESSFULL\n");

}


int lapsipc_init()
{
  int fifoFdIn,fifoFdOut;
  fifoFdIn = setUpIpc();
  fifoFdOut = outIpc();
}
