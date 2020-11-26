#!/usr/bin/env python3

from hydration import *
from enum import IntEnum


class Opcode(IntEnum):
    WRITE_REQUEST = 0x37
    READ_REQUEST = 0x77
    WRITE_ACK = 0X3A
    NACK = 0x5A
    READ_RESPONSE = 0x7A


def is_valid_opcode(opcode):
    return opcode == Opcode.WRITE_REQUEST.value or opcode == Opcode.READ_REQUEST.value


class Header(Struct):
    opcode = UInt8
    session = UInt8


class WriteRequest(Struct):
    header = Header(opcode=Opcode.WRITE_REQUEST.value)
    address = UInt64
    value = UInt64


class ReadRequest(Struct):
    header = Header(opcode=Opcode.READ_REQUEST.value)
    address = UInt64


class WriteAck(Struct):
    header = Header(opcode=Opcode.WRITE_ACK.value)


class Nack(Struct):
    header = Header(opcode=Opcode.NACK.value)
    error_code = UInt64


class ReadResponse(Struct):
    header = Header(opcode=Opcode.READ_RESPONSE.value)
    value = UInt64


lengths = {
        Opcode.WRITE_REQUEST.value: len(WriteRequest),
        Opcode.READ_REQUEST.value: len(ReadRequest),
        Opcode.WRITE_ACK.value: len(WriteAck),
        Opcode.NACK.value: len(Nack),
        Opcode.READ_RESPONSE.value: len(ReadResponse)
}
