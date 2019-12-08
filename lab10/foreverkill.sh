#!/bin/bash

while true
do 
	kill -s $1 $2   #1-sygnal  2-pid
       	sleep 5
done
