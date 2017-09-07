# Logs system information to a file
import platform
import os
import subprocess

with open("system_info.log", "w") as f:
    f.write("OS type:\t\t" + platform.system() + "\n")
    f.write("OS distribution:\t" + " ".join(platform.linux_distribution()) + "\n")
    f.write("Kernel version:\t\t" + subprocess.check_output(["uname", "-r"]))
    f.write("Kernel build:\t\t" + subprocess.check_output(["cat", "/proc/version"]))
    f.write("Architecture:\t\t" + platform.processor() + "\n")    
