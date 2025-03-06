# Picross Image Uploader

### Project Objectives
The goal of this project is to allow the user to upload any kind of image and then let them play the game picross with that image as a base. They can choose their own difficulty and save the image when they are done.

##

### Full Plan
The player can start a game by uploading an image, which will turn itself into a picross puzzle. They can choose whether to play basic picross or the colored version, which changes the puzzle to accomodate for the colors of the image or just base it on dark/light colors. The game itself will be basic picross, with the numbers for each cell lining the side and the player having the objection to color in or cross out a cell to help them figure out the puzzle. Once they finish, they can upload another picture if they want to.

##

### Current State
![current picross state](https://github.com/user-attachments/assets/7e223ded-14b4-4037-8a25-47e8b02767bc)
Right now, the base grid calcuations are done. A square image can be uploaded to the assets folder and the program will splice it into a grid and choose the most regularly occuring colors to make into a pixelated image. Additionally, the number of colors for each row and column are stored and displayed on the side of the puzzle

##

### Future Plan
- [ ] Make playable
  - [ ] Start board off blank
  - [ ] Allow player to place colors/x's on each grid piece
  - [ ] Each row/column will gray out when completed
  - [ ] Win state
- [ ] Allow player to upload their own photos
- [ ] Player can save the finished image
- [ ] Difficulty settings
