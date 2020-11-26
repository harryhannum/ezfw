class MultiplierModule:
    FIRST_REG = 4
    SECOND_REG = 8
    STATUS_REG = 0
    RES_REG = 12

    def __init__(self):
        self.regs = {MultiplierModule.STATUS_REG: 0}

    def read(self, addr):
        result = self.regs[addr]
        return result

    def write(self, addr, val):
        self.regs[addr] = val
        if MultiplierModule.FIRST_REG in self.regs and MultiplierModule.SECOND_REG in self.regs:
            self.regs[MultiplierModule.RES_REG] = self.regs[MultiplierModule.FIRST_REG] * self.regs[MultiplierModule.SECOND_REG]
            self.regs[MultiplierModule.STATUS_REG] = 1