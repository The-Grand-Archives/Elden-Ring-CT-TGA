#!/usr/bin/env bash
mkdir ./dist
echo 1245620 >./dist/steam_appid.txt
pip install -r ./ce2fs/requirements.txt
python ./scripts/pack_table_files.py
python ./ce2fs/ce2fs.py -i ./CheatTable -o ./dist/ER_TGA_v$(sed -r 's/([0-9])$/.\1/' VERSION).CT "$@"