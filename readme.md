# Direction Detection Module
This will compare the lag between the waveforms from the 6 microphones and calculate the lag with respect to one of them, and then detect the direction of the sound source.

### What is this currently capable of
For now, the three microphones connected to the arduino are just sound detection module so i cannot compare the waveforms and calculate the lag. So, I have pre-defined some thresholds for each microphone and when the analog value goes over it, it records the time and compares the lag between 3 microphones.

It is not that accurate because it is being limited by low speed or arduino (16 MHz) but it should perform better with an esp32 which runs on 240 MHz.


### What the End Goal is
We plan on using digital microphones with  the FPGA board and find the lag by comparing the waveforms which will be more accurate.

