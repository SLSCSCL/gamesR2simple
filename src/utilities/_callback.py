def do_nothing(*args):
    pass

class Callback:
    def __init__(self, f = do_nothing):
        self.set(f)

    def set(self, f):
        self.f = f

    def __call__(self, *args):
        arg_count = self.f.__code__.co_argcount
        try:
            if self.f.__self__ is not None:
                arg_count -= 1
        except:
            pass

        self.f(*args[:arg_count + 1])
