#!/usr/bin/env python3

from hydration import *

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
