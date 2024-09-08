import serial

started = False
while not started:
    try:
        ser = serial.Serial('/dev/ttyACM0', 9600)
        started = True
    except Exception as E:
        pass

while True:
    line = ser.readline()
    print(str(line.strip()))
