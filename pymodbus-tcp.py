from pymodbus.client.sync import ModbusTcpClient
import time

#modbus connection
client = ModbusTcpClient('123.45.0.101')
connection = client.connect()
print(connection)

time_on = 0
time_on_prev = 0

while True:
    #read register
    request = client.read_holding_registers(address=0,count=8,unit=1) #covert to float
    #
    
    
    time_on = time.time() - time_on_prev
    if (time_on < 4):
        write  = client.write_register(4,0,unit=1)
        print("on")
        
    else:
        write  = client.write_register(4,5555,unit=1)
        print("off")
        
    if (time_on > 6):
        time_on_prev = time.time()
    
    
    try:
        print(request.registers)
        
    except AttributeError:
        pass
