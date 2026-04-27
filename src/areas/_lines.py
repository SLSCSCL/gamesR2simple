

class Line:
    def __init__(self, x1, y1, x2, y2):
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
        self.calculate()

    def calculate(self):
        #The x2 + 0.0001 is to prevent a DivisionByZeroError
        self.m = (self.y2 - self.y1) / ((self.x2 + 0.0001) - self.x1)
        self.b = self.y1 - self.m * self.x1

    def __repr__(self):
        return f"x1: {self.x1}, y1: {self.y1}, x2: {self.x2}, y2: {self.y2}"

    def get_x(self, y):
        #The test is to prevent a DivisionByZeroError
        return int((y - self.b) / self.m if self.m != 0 else 1)

    def get_points(self):
        if int(self.y1) == int(self.y2):  # horizontal line
            for x in range(int(self.x1), int(self.x2) + 1):
                yield x, int(self.y1)
        else:
            for y in range(int(self.y1), int(self.y2) + 1):
                yield self.get_x(y), y

class Lines(list):
    def __init__(self, *lines):
        super().__init__()
        for line in lines:
            if type(line) != Line:
                q()
                raise TypeError(
                    "All items in the first argument to Lines.__init__ must be of type Line"
                )
            self.append(line)

    def get_x(self, y):
        l = [line for line in self if line.y1 <= y and line.y2 >= y]
        if l:
            return l[0].get_x(y)
        raise ValueError(f"No line that contains a y of {y}")

