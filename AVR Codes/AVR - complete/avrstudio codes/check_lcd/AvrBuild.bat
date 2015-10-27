@ECHO OFF
"C:\Program Files\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "C:\project\check\labels.tmp" -fI -W+ie -o "C:\project\check\check.hex" -d "C:\project\check\check.obj" -e "C:\project\check\check.eep" -m "C:\project\check\check.map" "C:\project\check\check.asm"
