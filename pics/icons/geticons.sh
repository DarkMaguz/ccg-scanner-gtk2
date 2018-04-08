#!/bin/bash

#wget http://gatherer.wizards.com/Handlers/Image.ashx?size=small&name=0&type=symbol

SYMBOLS=(`seq 0 16` x R B U G W tap RG)
SIZES=(small medium large)

for d in ${SIZES[@]}; do
	mkdir $d
done

for x in ${SYMBOLS[@]}; do
	for y in ${SIZES[@]}; do
		wget "http://gatherer.wizards.com/Handlers/Image.ashx?size=$y&name=$x&type=symbol" -O "$y/$x.gif"
	done
done

