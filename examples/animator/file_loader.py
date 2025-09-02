from tkinter.filedialog import askopenfilename, asksaveasfilename

class Project:
    def __init__(self, fps, *frames, **vars_):
        self.fps = fps
        self.frames = frames
        self.vars_ = vars_

def open_project():
    with open("p.txt") as f:
        direct = f.readline()
        if direct != "":
            name = direct
        else:
            name = askopenfilename(title="Open Project", initialdir="/")
    
    with askopenfilename(title="Open Project", initialdir="/") as f:
        """
        File format:
            fps60

            #whitespace is only for ease on the eye
            vars:
                r1=rect(10, 10, 100, 100)
                p1=point(175, 32)
            frame1:
                r1
                p1
            frame2:
                r1>(5, 2)
            #the frames go on...

            end
        """
        fps = f.readline().replace(" ", "")[3:] #get the fps
        cur_sect = ""
        cur_frame = 0
        frames = []
        _vars = {}
        while True:
            line = f.readline().replace(" ", "")
            if line == "" or line[0] == "#":
                continue
            elif line[:3] == "end":
                break
            elif line[:4] == "vars":
                cur_sect = "vars"
                continue
            elif line[:5] == "frame":
                cur_sect = "frame"
                cur_frame += 1
                frames.append([])
                continue

            if cur_sect == "vars":
                pass
            elif cur_sect == "frame":
                pass
    return Project(fps, *frames, **vars_)

open_project()
