#!/bin/bash

variable=true
start=`date +%s`

fun (){
	if [ $variable ] ; then
		start=`date +%s`
		variable=$false
	else
		end=`date +%s`
		t=$((end-start))
		start=$end 
		echo "Czas miedzy sygnalami to $t sekund"
	fi
}

trap ' fun ' SIGUSR2
trap '' SIGUSR1 #ignoruj sygnal
trap 'echo "papa!"' EXIT 
trap 'echo "musisz sie bardziej postarac by mnie zniszczyc"' SIGINT

while true
do
	echo "Moj PID = $$"
	sleep 5
done
