import minimalmodbus
import serial

instrument = minimalmodbus.Instrument('COM3', 1)  # port name, slave address (in decimal)
instrument.serial.port = 'COM3'                     # this is the serial port name
instrument.serial.baudrate = 9600         # Baud
instrument.serial.bytesize = 8
instrument.serial.parity   = serial.PARITY_EVEN
instrument.serial.stopbits = 1
instrument.serial.timeout  = 2        # seconds
instrument.address = 1                         # this is the slave address number
instrument.mode = minimalmodbus.MODE_RTU   # rtu or ascii mode
#nstrument.clear_buffers_before_each_transaction = True
try:
    temperature = instrument.read_long(registeraddress=1, functioncode=3,
                                        byteorder=0)  # Registernumber, number of decimals

    print(temperature)


except:
    pass