# A140E-Transmission-Indicator
This code is designed as an automatic shift indicator for the A140E Aisin transmission. Please note that this will not work on all cars - it is Toyota OBDI-specific.

The OBDI port or ECU must have a Tt pin on it in order for this to work

Data is read via pin A0 from a voltage divider. 

The transmission shift signal comes from the Tt terminal on the Toyota OBDI DLC. Connect A0 to this with an attached voltage divider (47K and 33K resistors give a max voltage output of 3.3V from an 8V source) to Tt, and connect ground to E1.

More information can be found in the code. The attached photo is taken from the Toyota manual and describes the exact voltages at which shifting and lock-ups occur.

9-16 EDIT: Gear position is also displayed via an OLED screen. Just connect 3.3 or 5V to Vcc, GND to GND, A4 to SDA, and A5 to SCL. You're more than welcome to modify the font styles, choice of OLED, etc. This includes the U8g2 library as the main driver.
