
# import the pygame module
import pygame
  
# Define the background colour
# using RGB color coding.
background_colour = (11, 11, 100);
  
# Define the dimensions of
# screen object(width,height)
screen = pygame.display.set_mode((800, 800))
  
# Set the caption of the screen
pygame.display.set_caption('Heat Sim Playback')
  
# Fill the background colour to the screen
screen.fill(background_colour)
  
# Update the display using flip
pygame.display.flip()
  
# Variable to keep our game loop running
running = True
  
# game loop
while running:
    
# for loop through the event queue  
    for event in pygame.event.get():
      
        # Check for QUIT event      
        if event.type == pygame.QUIT:
            running = False