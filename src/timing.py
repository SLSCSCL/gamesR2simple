from threading import Thread
from time import sleep

class Interval:
    def __init__(self, func, *args, **kwargs):
        self.func = func
        self.args = args
        self.kwargs = kwargs
        self.running = True

    def __call__(self):
        self.func(*self.arg, **self.kwargs)

def setTimeout(f, millisecs: int, *args, **kwargs):
    millisecs /= 1000
    def call():
        sleep(millisecs)
        f(*args, **kwargs)
    Thread(target=call, daemon=True).start()

def setInterval(interval: Interval, millisecs: int):
    millisecs /= 1000
    def call():
        while f.running:
            sleep(millisecs)
            interval()
    Thread(target=call, daemon=True).start()
