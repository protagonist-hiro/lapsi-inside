#include "lapsipc.h"
#include "lapsi-backend.h"
#include "main.h"
int main(int argc,char **argv)
{
  BackendData data;
  int fileDesc = lapsipc_init();
  gst_init (&argc, &argv);
  gtk_init (&argc,&argv);
  lapsi_backend_init(&data,&argc,&argv);
  set_uri(&data);
  play_file(&data);
  LOOP_RUN();

}
