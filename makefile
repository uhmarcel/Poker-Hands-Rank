#-------------------------------------#
#  Makefile for CardsShuffle program  #
#      Author:  Marcel Riera	      #
#-------------------------------------#

# Files required for compilation:
FILES = MainCards.c CardsValidation.c CardsFunctions.c PokerFunctions.c

# Name for executable:
OUT = PokerHands.out

# Compile program
build: $(FILES)
	gcc $(FILES) -o $(OUT)
	
# Remove Object files	
clean: 
	rm -f *.o core

# Remove and recompile
rebuild: clean build