#!/usr/bin/env bash
pip install --upgrade -r ./scripts/pip_build_deps.txt
ce2fs -i $(find ./dist -name 'ER_TGA_v*.CT') "$@"