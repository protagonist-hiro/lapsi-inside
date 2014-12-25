#!/usr/bin/python
import os
import glib
pathOut = "/home/hiro/lapsi/fifo"+str(os.getppid()) #change this path manually
pathIn = "/home/hiro/lapsi/fifo_"+str(os.getppid()) # change this path manually

#Global Main.Loop Context
MainLoop = glib.MainLoop()
class backEnd:
    '''
    The Base Class Provides Privmitive
    '''
    def __init__(self):
        #We make a fifo of pathname plus the parent ID id of C process to ensure uniqueness
        #This class should only be used once and by Backend
        self.pathOut = pathOut
        self.pathIn = pathIn
        self.parseFuncDict ={
            "error":self.onError,
            "success":self.onSuccess,
            "exit":self.onExit,
            "playBackEnd":self.onPlaybackEnd
            }
        self.parseValDict = dict()
        self.fileDescOut =os.open(self.pathOut,os.O_WRONLY | os.O_NONBLOCK)
        print("FROM::PYLAPSI :: Fifo created in %d")%self.fileDescOut
        self.sendString("play")#For Debugging Only
        self.fileDescIn=os.open(self.pathIn,os.O_RDONLY | os.O_NONBLOCK)
        print("FROM::PYLAPSI :: checking if connection Successful %d")%self.fileDescIn
        self.fileObj=os.fdopen(self.fileDescIn)
        glib.io_add_watch(self.fileObj,glib.IO_IN,self.parseString)

    def onError(self,stringList):
        '''
        Function that will be called if CLapsi passes error string.
        Overload this.
        This will recieve a list of strings.
        '''
        for i in stringList:
            print("FROM::PLapsi::error Recieved")%stringList[i]

    def onSuccess(self,stringList):
        '''
        Function that will be called if CLapsi passes error string.
        Overload this.
        This will recieve a list of strings.
        '''
        for i in stringList:
            print("FROM::PLapsi::success Recieved %s")%i

    def onExit(self):
        '''
        Function that will be called when the CLapsi is closed
        '''
        print("FROM::PLapsi::exit Recieved")

    def onPlaybackEnd(self,string):
        '''
        Function that will be called when Clapsi is abou to finish playing
        a file.
        '''
        pass

    def sendString(self,string):
        '''
        Sends a String to The Clapsi Low Level
        '''
        os.write(self.fileDescOut,string)

    def parseString(self,fd,condition,userData=None):
        '''
        A CallBack Function To be called in case there are bytes to read
        Low Level
        '''
        self.message = os.read(self.fileDescIn,100000)
        print("the recieved string is %s")%r''+self.message
        self.__executeCommands(self.message)
        return True

    def __executeCommands(self,string):
        __commandList =string.split('+')
        for i in __commandList:
            __varList=i.split()
            self.parseFuncDict[i.rstrip('\0')](__varList)


    def getFileDescOut(self):
        return self.fileDescOut
    def getFileDescIn(self):
        return self.fileDescIn



def main():
    print("Do I get called or he is just bluffing for gods shake Huhuhu")
    transferHandle = backEnd()
    MainLoop.run()






if __name__=="__main__":
     main()