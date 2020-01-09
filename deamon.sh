#!/bin/bash

while true; do
	# Chop file if it gets too long
	if [[ $(wc -l ~/.battery_plot | awk '{print $1}') -ge 500 ]]; then
		f=$(tail -n 100 ~/.battery_plot)
		echo "$f" > ~/.battery_plot
	fi
	
	# Write current battery percentage to file
	upower -i /org/freedesktop/UPower/devices/battery_BAT0 | grep percentage | grep -Eo '[0-9]{1,3}' >> ~/.battery_plot
	
	# 5 min cycle
	sleep 180
done
