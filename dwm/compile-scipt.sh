#!/bin/bash

rm -rf config.h
sudo make clean install
sleep 0.5
rm -rf config.h
rm -rf *.o *.rej *.orig 
clear
date
figlet Compiled!
exit

