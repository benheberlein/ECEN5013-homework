This is a kernel module test containing a kernel module that uses a timer to
print a count every 500ms. After loading the count, the output can be seen
in the dmesg logs. Use the Makefile to build, and then load the module using
'insmod timermod.ko'. Remove the module with rmmod.

Ben Heberlein

