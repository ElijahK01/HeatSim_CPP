
# import the pygame module
import pygame

f = open("SimulationOutput.dat", "rb")
  
# Define the background colour
# using RGB color coding.
background_colour = (11, 11, 100);
white=(255,255,255)

pygame.init()
# Define the dimensions of
# screen object(width,height)
screen = pygame.display.set_mode((1000, 1000))
  
# Set the caption of the screen
pygame.display.set_caption('Heat Sim Playback')
  
# Fill the background colour to the screen
screen.fill(background_colour)
  
# Update the display using flip
pygame.display.flip()

# Variable to keep our game loop running
running = True

dimension_x = 10;
dimension_y = 10;

rectW = 10;
rectH = 10;
halfOffset = rectH/2;

SPEED = 100

line = f.read(2)
dimension_x = int.from_bytes(line, 'little')
dimension_y = dimension_x

counter = 0;
# game loop
while running:
    
# for loop through the event queue  
    for i in range(SPEED - 1):
        line = f.read(dimension_x * dimension_y * 2)

    if(line):
        for i in range(int(dimension_x)):
            for j in range(int(dimension_y)):
                num = int.from_bytes(f.read(2), 'little')
                red = num/3
                if (red > 255):
                    red = 255
                color = (red,0,100)
                # Drawing Rectangle
                pygame.draw.rect(screen, color, pygame.Rect(i*rectW, j*rectH + (halfOffset * (i % 2)), rectW, rectH))

        
        pygame.display.flip()
    else:
        running = False
    counter += SPEED;
    print("Time: " + str(counter) + "ms")