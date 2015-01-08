Intended for Project Peers
===========

![Lapsi Media Player](http://www.fsd2010.org/data/Image/phototheque/Fruits%20and%20seeds/Choerospondias_axillaris_Nepal.jpg "Lapsi in Nepali Post Mail Ticket" )


#The Glapsi Media Player.
####A University Third Semester Project

This repository is being built. It is pretty far from working condition. You can fork it and laugh at our code. Since, this is university
project we wouldn't add your edit to this repo. Outside codes will only be added after this project has been evaluated.


#About

Glapsi Media Player is a media player based on Gstreamer exteded with python. It is written with the goal of giving
power to extend with few lines of code in python. A good API in python must be written so that a normal user can add 
feature with few lines of code or if possible from a gui interface.

#Dependencies

It is written using GTK+3.0 Gstreamer 1.0. You are going to need those to build it.
To play a specific file you will need the specific Gstreamer plugins. The 'Good' plugins are avialable in most distros
however you might have to install the 'ugly' and 'bad' plugins to play certain files. Google it!!

#Building

###After you make sure you have all the dependencies.
If you haven't downloaded this project. Download it first.
```
  $ git clone https://github.com/protagonist-hiro/lapsi-inside.git
```
After you have this project in your machine
```
  $ cd lapsi-inside
  $ make
  $ chmod +x main.py
````

You will get error because I have hardcoded the filenames into the codes. Find those and edit. Maybe put your local 
media files. 

After everything is done. You must have a some text both from Python and C in your stdout signaling the connection
between those are successful.

####Start Coding Please!!!



