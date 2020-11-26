import socket
from time import sleep

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 65432        # The port used by the server


def thread_func(s):
    read_request = bytearray(6)
    read_request[0] = 0x77

    write_request = bytearray(10)
    write_request[0] = 0x37

    for i in range(10):
        s.sendall(write_request)
        sleep(0.5)


def main():
    import threading
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        t1 = threading.Thread(target=thread_func, daemon=True, args=(s, ))
        t2 = threading.Thread(target=thread_func, daemon=True, args=(s, ))
        t1.start()
        t2.start()
        t1.join()
        t2.join()


class MockFirmWare:
    FIRST_REG = 4
    SECOND_REG = 8
    STATUS_REG = 0
    RES_REG = 12

    def __init__(self):
        self.regs = {}

    def read(self, addr):
        return self.regs[addr]

    def write(self, addr, val):
        self.reg[addr] = val
        if self.regs[MockFirmWare.FIRST_REG] is not None and self.regs[MockFirmWare.SECOND_REG] is not None:
            self.regs[MockFirmWare.RES_REG] = self.regs[MockFirmWare.FIRST_REG] * self.regs[MockFirmWare.SECOND_REG]
            self.regs[MockFirmWare.STATUS_REG] = 1


if __name__ == "__main__":
    main()
