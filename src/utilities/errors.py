from .._error import Error

class MappingKeyError(Error.new(KeyError)):
    pass

class ActionNotNoneError(Error):
    pass

class OptionTypeNotImageError(Error):
    pass

class NoExistingOptionError(Error):
    pass

class NoExistingActionError(Error):
    pass

class EventHandlerNotProvidedError(Error):
    pass
