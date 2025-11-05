class Combination:
    def __eq__(self, other):
        if self.size == other.size: #a KeyError will occur with uneven sizes
            for key in [attr for attr in dir(self) if attr[:3] == "key"]:
                if not eval(f"self.{key} == other.{key}"):
                    return False
            return True
        return False

class KeyCombination(Combination):
    size = 2
    def __init__(self, key1, key2, key3, callback):
        self.key1 = key1
        self.key2 = key2
        if key3:
            self.key3 = key3
            self.size += 1
        self.callback = callback

class MouseKeyCombination(Combination):
    size = 1
    def __init__ (self, key1, key2, key3, callback):
        self.key1 = key1
        if key2:
            self.key2 = key2
            self.size += 1
        if key3:
            self.key3 = key3
            self.size += 1
        self.callback = callback
