import random

class Car:
  def __init__(self,name):
    self.name = name
    self.speed = random.randint(60,100)
    self.max_distance = random.randint(450,550)

  def __str__(self):
    return f"Car {self.name} Speed: {self.speed} Max_distance: {self.max_distance}"
    # return a string formatted with info for the name, speed, and max distance

class Race:
  def __init__(self):
    self.distance = 500

    self.racer_list = []
  def start_race(self,num):
    x = 0
    while x <= num:
      car = Car(x)
      x += 1
      self.racer_list.append(car)
    print(*self.racer_list,sep = '\n')
    
  def get_winner(self):
    winner = 'No winner'    
    
    for racer in self.racer_list:
      if racer.max_distance >= self.distance:
        winner = racer
        print(f'the winner {winner}')
      if racer.speed > winner:
        winner = racer
        print(f'the winner {winner}')
    return winner
        

        
         
    return winner
    #create a variable called winner and set it equal to 'No winner'
    #loop through all racers in the list of racers
      #check if its max distance is greater than the race distance
      #if the current winner is 'No winner' set this to the winner
      #otherwise, check if the speed of this racer is faster than winner.speed
      #update the current winner accordingly
    #after finishing the loop, return the winner
def main():
  indy = Race()
  indy.start_race(18)
  print(f'Winner: {indy.get_winner()}')

if __name__=="__main__":
  main() 