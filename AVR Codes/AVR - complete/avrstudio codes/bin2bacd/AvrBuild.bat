@ECHO OFF
del "e:\avrstudio\bin2bacd\bin2bacd.map"
del "e:\avrstudio\bin2bacd\labels.tmp"
"C:\Program Files\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "e:\avrstudio\bin2bacd\labels.tmp" -fI  -o "e:\avrstudio\bin2bacd\bin2bacd.hex" -d "e:\avrstudio\bin2bacd\bin2bacd.obj" -e "e:\avrstudio\bin2bacd\bin2bacd.eep" -m "e:\avrstudio\bin2bacd\bin2bacd.map" -W+ie   "E:\avrstudio\bin2bacd\bin2bacd.asm"
