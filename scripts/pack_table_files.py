#!/usr/bin/env python

from typing import BinaryIO
import io
import os

def write_anystr(stream: BinaryIO, string: str | bytes):
    stream.write(len(string).to_bytes(4, 'little'))
    stream.write(string.encode() if isinstance(string, str) else string)


def tga_archive_pack(path: str, prefix_path: str | None = None) -> bytes:
    if not os.path.isdir(path):
        raise FileExistsError("path must be a directory")

    stream = io.BytesIO()
    stream.write(b"TGA_ARCHIVE_01")
    
    for dir, dirs, files in os.walk(os.path.abspath(path)):
        relpath = os.path.relpath(dir, path)
        if prefix_path is not None:
            relpath = os.path.join(prefix_path, relpath)
        archive_path = relpath.replace("\\", "/").rstrip("/.")
        if archive_path: archive_path += "/"
        
        for file in files:
            write_anystr(stream, archive_path)
            write_anystr(stream, file)
            with open(os.path.join(dir, file), "rb") as f:
                write_anystr(stream, f.read())
            
            print(os.path.join(dir, file), "->", archive_path + file)
    
    return stream.getvalue()


def pack_table_files(res_path: str, table_files_path: str):
    os.makedirs(table_files_path, exist_ok=True)

    for file_or_folder in os.listdir(res_path):
        path = os.path.join(res_path, file_or_folder)
        if os.path.isfile(path):
            print(f"Including {file_or_folder} as table file")
            with open(path, "rb") as f:
                table_file_bytes = f.read()
        elif os.path.isdir(path):
            print(f"Including {file_or_folder} as table file archive")
            table_file_bytes = tga_archive_pack(path, file_or_folder)
        else:
            raise FileExistsError(f"{path} is not a file or a directory")

        table_file_path = os.path.join(table_files_path, file_or_folder)
        with open(table_file_path, "wb") as f:
            f.write(table_file_bytes)
        
        with open(table_file_path + ".xml", "w", encoding="utf-8") as f:
            f.write('<File Encoding="Ascii85"></File>\n')


if __name__ == '__main__':
    pack_table_files("./table_files", "./CheatTable/Files")