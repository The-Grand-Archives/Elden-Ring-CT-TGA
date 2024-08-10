for /f "delims=" %%i in ('where .\dist:ER_TGA_v*.CT') do set RESULT=%%i
ce2fs -i "%RESULT%" %*