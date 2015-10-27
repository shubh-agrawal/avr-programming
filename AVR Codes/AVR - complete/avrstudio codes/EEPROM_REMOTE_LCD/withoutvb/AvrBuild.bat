@ECHO OFF
"C:\Program Files\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "C:\project\withoutvb\withoutvb\labels.tmp" -fI -W+ie -o "C:\project\withoutvb\withoutvb\withoutvb.hex" -d "C:\project\withoutvb\withoutvb\withoutvb.obj" -e "C:\project\withoutvb\withoutvb\withoutvb.eep" -m "C:\project\withoutvb\withoutvb\withoutvb.map" "C:\project\withoutvb\withoutvb\withoutvb.asm"
