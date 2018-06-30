import os
rootdir = '.'

for subdir, dirs, files in os.walk(rootdir):
    for dir in dirs:
        if dir == "include":
            print os.path.join(subdir, dir)