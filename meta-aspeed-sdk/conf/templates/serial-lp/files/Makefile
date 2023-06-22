#==========================================================
# Serial (RS232) Loopback Test Makefile
#	Made by JCHA, 2012-03-15
#==========================================================

PWD		:= $(shell pwd)

APP = sertest

default:
	arm-none-linux-gnueabi-gcc -o $(APP) $(APP).c

clean:
	rm -rf $(APP)
	rm -rf *.o
