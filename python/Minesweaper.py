#MineSweaper 1.0 file
from tkinter import *
from cell import Cell
import settings
import utils


root  = Tk()
# OVERRIDE SETTING OF WINDOW
root.configure(bg="black")
root.geometry(f'{settings.WIDTH}x{settings.HEIGHT}')
root.title("Minesweeper 1.0")
root.resizable(False,False)

top_frame = Frame(
    root,
    bg='black', 
    width=settings.WIDTH,
    height=utils.height_prct(25)
)
top_frame.place(
    x=0, 
    y=0
)

left_frame = Frame(
    root,
    bg='black',
    width=utils.width_prtc(25),
    height=utils.height_prct(75)
)

left_frame.place(
    x=0, 
    y=utils.height_prct(25)
)

center_frame = Frame(
    root,
    bg='black',
    width=utils.width_prtc(75),
    height=utils.height_prct(75)
)

center_frame.place(
    x=utils.width_prtc(25), 
    y=utils.height_prct(25)
 )

for x in range(settings.GRID_SIZE):
    for y in range(settings.GRID_SIZE):
        c = Cell(x, y)
        c.create_btn_object(center_frame)
        c.cell_btn_object.grid(
            column = x, row = y
        )

Cell.randomize_mines()

#RUN WINDOW
root.mainloop()
#cells.py
from tkinter import Button
import random
import settings

class Cell:
   all = []
   def __init__(self,x,y,is_mine=False):
       self.is_mine = is_mine
       self.cell_btn_object = None
       self.x = x
       self.y = y

       # Append the object to the Cell.all list
       Cell.all.append(self)

   def create_btn_object(self,location):
       btn = Button(
           location,
           width=12,
           height=4,
           text=f"{self.x},{self.y}"
        )
       btn.bind('<Button-1>', self.left_click_actions)#left click
       btn.bind('<Button-3>', self.right_click_actions)#right click
       self.cell_btn_object = btn
   
   def left_click_actions(self, event):
       if self.is_mine:
           self.show_mine()
       else:
           self.show_cell()

   def get_cell_by_axis(self, x,y):
       #return a cell object based on the value of x,y
       for cell in Cell.all:
           if cell.x == x and cell.y == y:
               return cell

    

   def show_cell(self):
       surrounded_cells = [
           self.get_cell_by_axis(self.x - 1, self.y - 1),
           self.get_cell_by_axis(self.x - 1, self.y),
           self.get_cell_by_axis(self.x - 1, self.y + 1),
           self.get_cell_by_axis(self.x, self.y - 1),
           self.get_cell_by_axis(self.x + 1, self.y - 1),
           self.get_cell_by_axis(self.x + 1, self.y),
           self.get_cell_by_axis(self.x + 1, self.y + 1),
           self.get_cell_by_axis(self.x, self.y + 1)
       ]
       print(surrounded_cells)


   def show_mine(self):
       # A logic to interupt game and show message of loss game
       self.cell_btn_object.configure(bg='red')
    

   def right_click_actions(self, event):
       print(event)
       print("i am the prince of all sayins")

   @staticmethod
   def randomize_mines():
       picked_cells = random.sample(
           Cell.all, settings.MINES_COUNT
           )
       for picked_cell in picked_cells:
           picked_cell.is_mine = True
     

   def __repr__(self):
       return f"Cell({self.x}, {self.y})"