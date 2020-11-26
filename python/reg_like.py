#!/usr/bin/env python3

import threading
import queue
from messages import *
import socket
from mock_firmware import MultiplierModule


HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 65432        # Port to listen on (non-privileged ports are > 1023)
NUM_THREADS = 3

requests_queue = queue.Queue()
responses_queue = queue.Queue()


fw = MultiplierModule()


def write_to_vhdl(address, value):
    # send to vhdl - YUVAL IMPLEMENTATION
    global fw
    fw.write(address, value)
    return True or (address - value)


def read_from_vhdl(address):
    # YUVAL IMPLEMENTATION
    global fw
    return fw.read(address)


def send_nack(session, error_code):
    n = Nack(header=Header(opcode=Opcode.NACK.value, session=session), error_code=error_code)
    responses_queue.put(n.serialize())
    print("sent nack with error code: " + str(error_code) + " and session " + str(session))


def handle_read_request(msg):
    m = ReadRequest.from_bytes(msg)
    value = read_from_vhdl(m.address.value)
    response = ReadResponse(header=Header(opcode=Opcode.READ_RESPONSE.value, session=m.header.session), value=value)
    responses_queue.put(response.serialize())


# TODO edit this later
WRITE_FAIL = 0x13


def handle_write_request(msg):
    m = WriteRequest.from_bytes(msg)
    write_status = write_to_vhdl(m.address.value, m.value.value)
    if write_status:
        response = WriteAck(header=Header(opcode=Opcode.WRITE_ACK.value, session=m.header.session))
        responses_queue.put(response.serialize())
    else:
        send_nack(m.header.session, WRITE_FAIL)


def worker():
    while True:
        msg = requests_queue.get()
        if msg is None:
            continue
        opcode = msg[0]
        if opcode == Opcode.READ_REQUEST.value:
            handle_read_request(msg)
        else:
            handle_write_request(msg)


def main():
    # create socket
    threads = []
    for i in range(NUM_THREADS):
        threads.append(threading.Thread(target=worker, daemon=True))
        threads[i].start()

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        conn, addr = s.accept()
        with conn:
            print('Connected by', addr)
            try:
                while True:
                    opcode = conn.recv(1)
                    if not opcode:
                        continue
                    if not is_valid_opcode(opcode[0]):
                        # TODO add session and error code and make sure to flush the conn
                        send_nack(0, 1)
                        continue
                    rest_of_msg = conn.recv(lengths[opcode[0]] - 1)
                    requests_queue.put(opcode + rest_of_msg)

                    response = responses_queue.get()
                    if response is not None:
                        conn.sendall(response)
            except ConnectionResetError:
                print("connection is over")
        

if __name__ == '__main__':
    main()
