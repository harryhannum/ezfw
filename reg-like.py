#!/usr/bin/env python3

from hydration import *
from multiprocessing import Pool
import threading, queue

import select
import socket
import sys
import Queue

HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 65432        # Port to listen on (non-privileged ports are > 1023)

handlers = {0x37: write_request_handler, 0x77: read_request_handler,
            0x3A: write_ack_handler, 0x7A: read_response}

class write_request(Struct):
    opcode = UInt8(0x37)
    address = UInt32
    value = UInt32

class read_request(Struct):
    opcode = UInt8(0x77)
    address = UInt32

class write_ack(Struct):
    opcode = UInt8(0x3A)

class nack(Struct):
    opcode = UInt8(0x5A)
    error_code = UInt32

class read_response(Struct):
    opcode = UInt8(0x7A)
    value = UInt32


def thread_read_for_cpp():
    # listen on socket to register_message
    # read from what vhdl give us
    reg_value = address # just for mock
    thread_write_for_cpp(reg_value)


def thread_write_for_cpp(value):
    # write on socket
    return 1

def thread_read_for_vhdl():
    return 1


def send_to_vhdl():
    # send to vhdl
    return 1

def read_from_vhdl():
    reg_value = 0 # just for mock
    return reg_value

def main():
    # create socket

    # queue
    q = queue.Queue()


    while True:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        conn, addr = s.accept()
        with conn:
            print('Connected by', addr)
            while True:
                opcode = conn.recv(1)
                if not opcode:
                    break
                handlers[opcode[0]](conn)

                conn.sendall(data)
        

if __name__ == '__main__':
