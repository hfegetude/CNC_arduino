#!/usr/bin/python
# -*- coding: utf-8 -*-

from Tkinter import *
from ttk import *

class Example(Frame):
  
    def __init__(self, parent):
        Frame.__init__(self, parent)   
         
        self.parent = parent
        self.initUI()

        
    def initUI(self):
      
        self.parent.title("CNC GUI")
        self.pack(fill=BOTH, expand=True)

        ButtonCircleFrame = Frame(self)
        ButtonCircleFrame.pack(fill = X)

        CircleButton = Button(ButtonCircleFrame, text="Draw Circle")
        CircleButton.pack(side=LEFT, padx=5, pady=5)  

        CenterFrame = Frame(self)
        CenterFrame.pack(fill = X)
        
        CLabel = Label(CenterFrame, text = "Center", width=6)
        CLabel.pack(side=LEFT, padx= 5, pady=5)
        Xentry = Entry(CenterFrame, width=5)
        Xentry.pack(side=LEFT, padx=5)
        Xentry.insert(0, "X")
        Yentry = Entry(CenterFrame, width=5)
        Yentry.pack(side=LEFT, padx=5 )
        Yentry.insert(0, "Y")

        RadiusFrame = Frame(self)
        RadiusFrame.pack(fill = X)

        RLabel = Label(RadiusFrame, text="Radius", width=6)
        RLabel.pack(side=LEFT, padx=5, pady=5)
        Rentry = Entry(RadiusFrame, width=5)
        Rentry.pack(side=LEFT, padx = 5)
        Rentry.insert(0, "R")

        AngleFrame = Frame(self)
        AngleFrame.pack(fill = X)

        ALabel = Label(AngleFrame, text="Angle", width=6)
        ALabel.pack(side=LEFT, padx=5, pady=5)
        A1Entry = Entry(AngleFrame, width=5)
        A1Entry.pack(side=LEFT, padx=5)
        A1Entry.insert(0, "From")
        A2Entry = Entry(AngleFrame, width=5)
        A2Entry.pack(side=LEFT, padx=5)
        A2Entry.insert(0, "To")

        LineFrame = Frame(self)
        LineFrame.pack(fill=X)

        LineButton = Button(LineFrame, text="Draw lline")
        LineButton.pack(side=LEFT, padx=5, pady=9)

        ToFrame = Frame(self)
        ToFrame.pack(fill=X)
        ToLabel = Label(ToFrame, text="To", width=6)
        ToLabel.pack(side=LEFT, padx=5, pady=5)
        ToXEntry = Entry(ToFrame, width=5)
        ToXEntry.pack(side=LEFT, padx=5)
        ToXEntry.insert(0, "X")
        ToYEntry = Entry(ToFrame, width=5)
        ToYEntry.pack(side=LEFT, padx=5)
        ToYEntry.insert(0, "Y")

        FromFrame = Frame(self)
        FromFrame.pack(fill=X)
        FromLabel = Label(FromFrame, text="From", width=6)
        FromLabel.pack(side=LEFT, padx=5, pady=5)
        FromXEntry = Entry(FromFrame, width=5)
        FromXEntry.pack(side=LEFT, padx=5)
        FromXEntry.insert(0, "X")
        FromYEntry = Entry(FromFrame, width=5)
        FromYEntry.pack(side=LEFT, padx=5)
        FromYEntry.insert(0, "Y")

        OutMessageFrame = Frame(self, borderwidth=1, relief=SUNKEN, width=15, height=5)
        OutMessageFrame.pack(fill=X)
        OutMessageLabel = Label(OutMessageFrame, width=15)
        OutMessageLabel.pack(side=LEFT, padx=5)


def main():
  
    root = Tk()
    root.geometry("300x300+300+300")
    app = Example(root)
    root.mainloop()  


if __name__ == '__main__':
    main()  