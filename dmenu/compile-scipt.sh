#!/bin/bash

rm -rf config.h
sudo make clean install
sleep 0.5
clear
date
figlet Compiled!
rm -rf config.h

