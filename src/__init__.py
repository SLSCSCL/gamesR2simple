import sys

import pygame

from ._converter import convert
from ._draw import Draw
from ._legends import *
from .events import Events

class BaseGame:
    def __init__(self):
        """Construct the game"""
        self.fps = 60
        #initialise pygame
        pygame.init()
        self.set_screen_size(800, 400)
        self.clock = pygame.time.Clock()
        
        self.events = Events(self)
        self.draw = Draw(self)

        self.setup()
        
        while True:
            self.events.check_events()
            self.update()
            pygame.display.flip()
            self.clock.tick(self.fps)

    def set_screen_size(self, new_width, new_height):
        """Resize the game window"""
        self.screen = pygame.display.set_mode((new_width, new_height))

    def set_fullscreen(self):
        """Set the game window to fullscreen"""
        self.screen = pygame.display.set_mode((0, 0), pygame.FULLSCREEN)
    
    def destroy(self, unnecessary = False, error = False):
        """Destroy the current game window and close Python"""
        # The variable 'unnecessary' is for if a mouse event's
        # callback is self.destroy(). If the variable is not
        # there, error will then be set to a tuple of two items
        # and will not be false
        pygame.quit()
        if not error:
            sys.exit()

    def update(self):
        self.destroy(error=True)
        raise NotImplementedError(
            "BaseGame is an abstract class, so BaseGame.update must be implemented"
        )

    def setup(self):
        self.destroy(error=True)
        raise NotImplementedError(
            "BaseGame is an abstract class, so BaseGame.setup must be implemented"
        )
