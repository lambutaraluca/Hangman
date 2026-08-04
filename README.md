# Hangman

  Building Hangman project I used an Arduino Uno R4 Wifi, LCD display and one potentiometer(only to set the contrast/brightness). 
  
  Imagine the game being played by two people, one is choosing the world and the other one is trying to guess. The first one is asked to write in the Serial Monitor the word wanted to be guessed, but it can be good, too long or not valid(it contains other characters besides letters), accordingly a text will display.
  
  If the word is valid, on the first row will be indicated the number of letters(through underscores) and chances the player has. If the letter guessed is correct, present once or more times in word, it will be positioned in the right place.
  
  If the player wins, a congratulation message shows up, otherwise... . In either case the "Mai jucam?" question will be asked. If the answer is "da" the player needs to wait for a reset, if "no" the game end, "Joc terminat".
