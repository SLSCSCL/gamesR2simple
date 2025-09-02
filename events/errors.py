from .._error import Error

class NoExistingEventError(Error.new(ValueError)):
    pass

class NoExistingEventTypeError(Error.new(TypeError)):
    pass

class CannotOverrideEventBehaviorError(Error):
    pass

class RequiredArgumentMissingError(Error):
    pass
