install:
	gcc -o batteryusage-plot batteryplot.c
	mkdir ~/.batteryusage
	mv batteryusage-plot ~/.batteryusage/
	cp deamon.sh ~/.batteryusage/deamon.sh
	cp deamon-cron.sh ~/.batteryusage/deamon-cron.sh
	chmod -w ~/.batteryusage/deamon.sh
	chmod +x ~/.batteryusage/deamon.sh
	chmod -w ~/.batteryusage/deamon-cron.sh
	chmod +x ~/.batteryusage/deamon-cron.sh
	chmod -w ~/.batteryusage/batteryusage-plot
