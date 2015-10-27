@ECHO OFF
"C:\Program Files\Atmel\AVR Tools\AvrAssembler2\avrasm2.exe" -S "C:\project\eeprom_vb\labels.tmp" -fI -W+ie -o "C:\project\eeprom_vb\eeprom_vb.hex" -d "C:\project\eeprom_vb\eeprom_vb.obj" -e "C:\project\eeprom_vb\eeprom_vb.eep" -m "C:\project\eeprom_vb\eeprom_vb.map" "C:\project\eeprom_vb\eeprom_vb.asm"
