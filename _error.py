from ._cpp.quit import q

class Error(Exception):
    def __init__(self, msg):
        q()
        super().__init__(msg)

    @staticmethod
    def new(parent):
        class NewError(parent, Error):
            def __init__(self):
                q()
                super().__init__()

        return NewError
