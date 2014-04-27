#!/bin/bash
while :
do
heure=$(date "+%H%M")

if [ $heure = "0630" ]
	then
		madplay /usr/karotz/res/sounds/karotz_loop2.mp3
		echo Le réveil sonne : $heure
	else
		echo Le réveil sonne pas : $heure
fi
sleep 1
done

