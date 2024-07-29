#!/usr/bin/env bash
pip install --upgrade -r ./scripts/pip_build_deps.txt
ce2fs -i ./CheatTable --check "$@"