#!/bin/bash

while true; do
	# Chop file if it gets too long
	if [[ $(wc -l ~/.batteryusage/battery_data | awk '{print $1}') -ge 500 ]]; then
		f=$(tail -n 100 ~/.batteryusage/battery_data)
		echo "$f" > ~/.batteryusage/battery_data
	fi
	
	# Write current battery percentage to file
	upower -i /org/freedesktop/UPower/devices/battery_BAT0 | grep percentage | grep -Eo '[0-9]{1,3}' >> ~/.batteryusage/battery_data
	
	# 3 min cycle
	sleep 180
done
