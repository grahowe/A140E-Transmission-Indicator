# A140E-Transmission-Indicator
This code is designed as an automatic shift indicator for the A140E Aisin transmission. Please note that this will not work on all cars - it is Toyota OBDI-specific.

Cars that will work with this application include:
*1992-1996 Toyota Camry

Data is read via pin A0 from a voltage divider. 

The transmission shift signal comes from the Tt terminal on the Toyota OBDI DLC. Connect A0 to this with an attached voltage divider (47K and 33K resistors give a max voltage output of 3.3V from an 8V source) to Tt, and connect ground to E1.

More information can be found in the code. The attached photo is taken from the Toyota manual and describes the exact voltages at which shifting and lock-ups occur.

In the future, I plan on adding a beeper so the circuit beeps when it shifts gears. We'll see what happens soon!
