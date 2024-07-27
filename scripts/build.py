#!/usr/bin/env python

import os, shutil, subprocess, sys
from pack_table_files import pack_table_files

def p(path: str): # I LOVE WINDOWS
    return path.replace("/", os.sep)

shutil.rmtree(p("./dist"), ignore_errors=True)
os.mkdir(p("./dist"))
with open(p("./dist/steam_appid.txt"), "w") as f:
    f.write("1245620")

pack_table_files(p("./table_files"), p("./CheatTable/Files"))

with open(p("./BUILD_ENV"), "r") as f: build_env = f.read().splitlines()
tbl_ver = [s.split("=", 1)[1] for s in build_env if s.split("=", 1)[0] == "TABLE_VERSION"][0]

subprocess.run(["pip", "install", "-r", p("./ce2fs/requirements.txt")], check=True)
subprocess.run(
    ["python", p("./ce2fs/ce2fs.py"), "-i", p("./CheatTable"), "-o", p(f"./dist/ER_TGA_v{tbl_ver}.CT")] 
        + build_env
        + sys.argv[1:],
    check=True
)