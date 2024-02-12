#!/bin/bash

# Bash script for viewing some system info.

cpuinfo=$(lscpu | grep Architecture && lscpu | grep Address && lscpu | grep Thread && lscpu | grep socket && lscpu | grep CPU && lscpu | grep Vendor && lscpu | grep Model && lscpu | grep Virtualization)
raminfo=$(lsmem)
osinfo=$(pfetch)
date=$(date)

echo "	
$osinfo
	"

echo "CPU INFO	
~~~~~~~~
$cpuinfo	

RAM INFO
~~~~~~~~
$raminfo
	"

echo "
	$date
	"





