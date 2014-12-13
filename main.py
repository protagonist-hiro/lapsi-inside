#!/usr/bin/python
import time
import os
import glib
pathOut = "/home/hiro/lapsi/fifo"+str(os.getppid()) #change this path manually
pathIn = "/home/hiro/lapsi/fifo_"+str(os.getppid()) # change this path manually 

class ipcInit:
    '''
    Internal Class To be called By backend to initialize the Ipc using FIFO
    '''
    def __init__(self):
        #We make a fifo of pathname plus the parent ID id of C process to ensure uniqueness
        #This class should only be used once and by Backend
        self.pathOut = pathOut
        self.pathIn = pathIn
        os.mkfifo(self.pathIn,0666)
        self.fileDescOut =os.open(self.pathOut,os.O_WRONLY | os.O_NONBLOCK)
        print("FROM PYLAPSI :: Outward Connection Successful in %d")%self.fileDescOut
        os.write(self.fileDescOut,"hellp")
        self.fileDescIn=os.open(self.pathIn,os.O_RDONLY | os.O_NONBLOCK)
        self.fileObj=os.fdopen(self.fileDescIn)
        glib.io_add_watch(self.fileObj,glib.IO_IN,self.inputCallback)
        print("FROM PYLAPSI :: Inward Connection Successful in %d")%self.fileDescIn
    def inputCallback(self):
		message = self.fileObj.readline()
        print("DID I GOT CALLED ANY BODY??? %s \n")%message
    def getFileDescOut(self):
        return self.fileDescOut
    def getFileDescIn(self):
        return self.fileDescIn


def pylapsi_init():
     '''
     Initializes the backend and and IPC
     '''
     ipc = ipcInit()
     back = lapsiBackend(ipc)
     return back

def main():
     #The Backend Instance of lapsi is created. Intended to be opaque.
     lapsiCom = pylapsi_init()



class lapsiBackend:
''' The Base Class for basic IPC it must be used to write other classes.\n An instance of this class to be used rather than inheritance is recommneded.'''
    def send(self,string):
        '''send(string). Sends string to the Parent and returns bytesWritten'''
        bytesWritten = os.write(self.fileDescOut,string)
    def recieve(self,string):
        pass
    def getFileDesc(self,ipc):
        self.fileDescOut = ipc.getFileDescOut()
        self.fileDescIn = ipc.getFileDescIn()
    def __init__(self,ipc):
        self.getFileDesc(ipc)
    def __del__(self):
        os.close(self.fileDescIn)
        os.close(self.fileDescOut)



if __name__=="__main__":
     main()
