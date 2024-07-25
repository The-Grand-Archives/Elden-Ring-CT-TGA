#!/usr/bin/env bash
pip install -r ./ce2fs/requirements.txt
python ./ce2fs/ce2fs.py -i $(find ./dist -name 'ER_TGA_v*.CT') -o .