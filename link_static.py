from genericpath import isdir, isfile
from os import symlink
from os.path import join

Import("env")

PROJECT_DATA_DIR = env["PROJECT_DATA_DIR"]
PROJECT_DIR = env["PROJECT_DIR"]

src = join(PROJECT_DIR, "control-panel-webpage", "static")
dst = join(PROJECT_DATA_DIR, "static")

if not isfile(dst) and not isdir(dst):
    print(f"Creating symbolic link {src} -> {dst}")
    symlink(src, dst)