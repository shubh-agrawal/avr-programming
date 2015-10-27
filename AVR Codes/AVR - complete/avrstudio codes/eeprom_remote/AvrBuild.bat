@ECHO OFF
"C:\Program Files\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "C:\project\eeprom_remote\labels.tmp" -fI -W+ie -o "C:\project\eeprom_remote\eeprom_remote.hex" -d "C:\project\eeprom_remote\eeprom_remote.obj" -e "C:\project\eeprom_remote\eeprom_remote.eep" -m "C:\project\eeprom_remote\eeprom_remote.map" "C:\project\eeprom_remote\eeprom_remote.asm"
