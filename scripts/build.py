#!/usr/bin/env python

import os, subprocess, sys
from pack_table_files import pack_table_files

def p(path: str): # I LOVE WINDOWS
    return path.replace("/", os.sep)

os.makedirs(p("./dist"), exist_ok=True)
with open(p("./dist/steam_appid.txt"), "w") as f:
    f.write("1245620")

pack_table_files(p("./table_files"), p("./CheatTable/Files"))

with open(p("./BUILD_ENV"), "r") as f: build_env = f.read().splitlines()
tbl_ver = [s.split("=", 1)[1] for s in build_env if s.split("=", 1)[0] == "TABLE_VERSION"][0]

subprocess.run(
    ["ce2fs", "-i", p("./CheatTable"), "-o", p(f"./dist/ER_TGA_v{tbl_ver}.CT")] 
        + build_env
        + sys.argv[1:],
    check=True
)