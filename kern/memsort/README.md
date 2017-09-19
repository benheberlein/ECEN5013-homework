Contains implementation for the memsort system call.

This file contains the memsort system call implementation. When building with
the kernel, the memsort.c file and Makefile should be copied over into a
root directory, and the kernel build should be modified appropriately.

A diff is provided in order to make this process easier.

Once installed, the system call can be tested with the test_memsort.c file.
This file can be build with gcc with no options. The output of the test 
can be found in the dmesg logs after running, showing correct sorting.

Ben Heberlein
