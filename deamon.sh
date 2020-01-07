#!/bin/bash

while true; do
	if [[ $(wc -l ~/.battery_plot | awk '{print $1}') -ge 74 ]]; then
		f=$(tail -n 60 ~/.battery_plot)
		echo "$f" > ~/.battery_plot
	fi
	
	upower -i /org/freedesktop/UPower/devices/battery_BAT0 | grep percentage | grep -Eo '[0-9]{1,3}' >> ~/.battery_plot
	
	#5 min cycle
	sleep 300
done
