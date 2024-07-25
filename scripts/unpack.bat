pip install -r ./ce2fs/requirements.txt
for /f %%i in ('where .\dist:ER_TGA_v*.CT') do set RESULT=%%i
python ./ce2fs/ce2fs.py -i "%RESULT%" -o .