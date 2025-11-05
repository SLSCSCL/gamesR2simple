from gamesR2simple import q
from gamesR2simple.areas import *

from tkinter.filedialog import (
    askopenfilename,
    asksaveasfile
)

__all__ = [
    "CodecError",
    "Project",
    "load_project",
    "save_project_as",
    "save_project"
]

class CodecError(Exception):
    pass

class Project:
    """Contains an entire project in string values"""
    def __init__(self, name, fps, *frames):
        self.name = name
        self.fps = fps
        self.frames = frames
        self.f_num = len(frames)

    def stream(self):
        """Stream the project"""
        f = []
        for frame in self.frames:
            f = []
            for obj in frame:
                f.append(eval(obj)) #convert the frame from string to object
            yield f #YIELD the frame - we need to go through each frame!
        #the project should be successfully completed

def load_project(self):
    """Loads a project according to this file format:
        fps60

        #whitespace is only for ease on the eye
        frame
            RectArea(10, 10, 100, 100)
            Point(175, 32)
        frame
            RectArea(15, 12, 100, 100)
        #the frames go on...

        end
    """
    name = askopenfilename(title="Open Project", initialdir="/",
                           filetypes=[("Animation Project", "*.animproj")])
    with open(name) as f:
        fps = f.readline().replace(" ", "")[3:] #get the fps
        in_frames = False
        frames = []
        cur_line = 1
        no_f = ""
        while True:
            cur_line += 1
            no_f = f.readline()
            line = no_f.replace(" ", "")
            
            if line == "" or line[0] == "#":
                continue
            elif line == "end":
                break
            elif line[:5] == "frame":
                in_frames = True
                frames.append([])
                continue
            else:
                raise CodecError(
                    "The formatting of the file is not correct on line " +
                    cur_line + ": " + no_f
                )

            if in_frames:
                try:
                    if "#" in line:
                        line = line.split()
                        while "#" in line:
                            line.pop()
                        line = ''.join(line)
                    froames[-1].append(line)
                except MemoryError:
                    q()
                    print("Not enough memory to load the project")
        
    return Project(name, fps, *frames)

def save_project_as(proj):
    pass

def save_project(proj):
    pass
