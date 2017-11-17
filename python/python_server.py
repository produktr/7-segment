import cmd
import struct
import random      #for testing
import socket      #UDP communication
import os          #Clearing print
import asyncore    #Serial communication
import serial      #Serial communication
import time        #Sleep
import struct
import sys

print("=====START====") 
print("PYTHON VERSION: ",sys.version)

def menu():
    print 30 * "-" , "SELECT GAME" , 30 * "-"
    print "0. Codemasters"
    print "1. Project Cars"
    print "2. Assetto Corsa"
    print 67 * "-"
    choice = input("Enter your choice [0-1]: ")
    return choice

def main():
    game = menu()
    ports = [20775, 0, 0]
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    arduino = serial.Serial("COM5", 115200, timeout=1)   # open serial port that Arduino is using
    while True:
        sock.bind(('', ports[game]))
        data = sock.recv(512)
        sock.close()
        if not data:
            stat = [1] * 256
            #break # Lost connection
        else:
            stat = struct.unpack('64f', data[0:256])
    
        del data
        # set gear
        gear = stat[33]
        gear = int(gear)
        
        # set shift
        rpm = stat[37] * 10
        rpm_max = stat[63] * 10
        if ((rpm / rpm_max) * 100) > 90:
            shift = int(1)
        else:
            shift = int(0)

        #print("-------------------------------------------------------")
        print("GEAR----: ", gear)
        print("REDLINE-: ", shift)
        #print("SEND----: ", struct.pack('h', gear))
        arduino.write(struct.pack('hh', gear, shift))
        #cin = arduino.readline()
        #if cin:
            #print("ANSWER--: ", cin)
            #print("ANSWER--: ", struct.unpack("I", cin))
        #time.sleep(0.5)

main()