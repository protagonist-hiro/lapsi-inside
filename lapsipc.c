#include"lapsipc.h"
#define PATHIN "/home/hiro/lapsi/fifo"
#define PATHOUT "/home/hiro/lapsi/fifo_"
GIOChannel * channel;
int FDIN,FDOUT;
gboolean
inputCallback()
{
  char buf[4096];
  read(FDIN,buf,4096);
  buf[strlen(buf)+1]='\0';
  printf("FROM LAPSI :: THE FOLLOWING STRING RECIEVED FROM PYLAPSI %s OF SIZE %d :\n",buf,strlen(buf));
  printf("FROM LAPSI :: EQUATING TO THE KNOWN STRING GIVES %d \n",strcmp(buf,"hellp"));
}

int setUpIpc()
{

  printf("Creating a fifo BY parent\n");
  mkfifo(getFifoPath(PATHIN),0666); //fix this manually sorry
  mkfifo(getFifoPath(PATHOUT),0666);
  pid_t pid = fork();
  if(pid == 0)
    {
      childprocess();

    }
    if(pid>0)
      {
        parentprocess();
      }
  return 0;
}

int parentprocess()
{
  FDIN = open(getFifoPath(PATHIN),O_RDONLY | O_NONBLOCK);
  FDOUT = open(getFifoPath(PATHOUT),O_WRONLY);
  channel = g_io_channel_unix_new(FDIN);
  g_io_add_watch(channel,G_IO_IN,(GIOFunc)inputCallback,NULL);
  return FDIN;
}


int childprocess()
{
    printf("executing the python process");
    execl("./main.py","",(char*)NULL);

}


char * getFifoPath(char * prefixPath)
{
  char *stringPid = malloc(getpid()+1);
  char *localPrefix=malloc(strlen(prefixPath)*sizeof(char)+20+getpid()+1);
  strcpy(localPrefix,prefixPath);
  snprintf(stringPid,40,"%d",getpid());
  strcat(localPrefix,stringPid);
  return localPrefix;
}


int outIpc()
{
  printf("Fd of Outward fifoo and its path %d and %s \n",FDOUT,PATHOUT);
  char * buff = "success";
  write(FDOUT,buff,strlen(buff)+1);
  printf("FROM LAPSI :: WROTE TO PYLAPSI CONNECTION SUCCESSFULL\n");

}


int lapsipc_init()
{
  int fifoFDIN,fifoFDOUT;
  fifoFDIN = setUpIpc();
  fifoFDOUT = outIpc();
}
