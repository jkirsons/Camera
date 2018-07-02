import os
import sys
rootdir = '.'

for subdir, dirs, files in os.walk(rootdir):
    for dir in dirs:
        if dir == "include":
            sys.stdout.write("-I" + os.path.join(subdir, dir)[2:] + " ")