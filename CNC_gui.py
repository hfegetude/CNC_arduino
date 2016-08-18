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
        
        CLabel = Label(CenterFrame, text = "C")
        CLabel.pack(side=LEFT, padx= 5, pady=5)
        Xentry = Entry(CenterFrame, text = "X")
        Xentry.pack(padx=5, expand=True)
        Yentry = Entry(CenterFrame, text = "X")
        Yentry.pack(padx=5, expand=True)

def main():
  
    root = Tk()
    root.geometry("300x300+300+300")
    app = Example(root)
    root.mainloop()  


if __name__ == '__main__':
    main()  