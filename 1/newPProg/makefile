O = ./obj/
C = ./src/
H = ./includes/
OBJECTS = command.o link.o game.o game_loop.o graphic_engine.o inventory.o screen.o space.o object.o player.o game_management.o set.o die.o game_rules.o  dialogue.o
DIST= $(C)command.c $(C)link.c $(C)game.c $(C)game_loop.c $(C)graphic_engine.c $(C)inventory.c $(C)screen.c $(C)space.c $(C)object.c $(C)player.c $(C)game_management.c $(C)set.c $(C)die.c $(C)game_rules.c $(C)dialogue.c
FLAGS = -Wall -Wextra -pedantic -ansi -g -I./includes
test = die_test set_test space_test object_test player_test inventory_test link_test dialogue_test integration_test
.PHONY: all clean dist
all: clean ocabas $(test) dist doxygen

################ COMPILATION ################
link.o: $(C)link.c $(H)link.h $(H)types.h
	gcc -c $(FLAGS) $<

inventory.o: $(C)inventory.c $(H)inventory.h $(H)types.h $(H)set.h $(H)object.h
	gcc -c $(FLAGS) $<

command.o: $(C)command.c $(H)command.h
	gcc -c $(FLAGS) $<

game.o:	$(C)game.c $(H)game.h $(H)game_management.h $(H)object.h $(H)player.h $(H)set.h $(H)space.h $(H)die.h $(H)link.h $(H)dialogue.h
	gcc -c $(FLAGS) $<

game_loop.o: $(C)game_loop.c $(H)game.h $(H)graphic_engine.h $(H)command.h
	gcc -c $(FLAGS) $<

graphic_engine.o: $(C)graphic_engine.c $(H)graphic_engine.h $(H)game.h $(H)command.h
	gcc -c $(FLAGS) $<

screen.o: $(C)screen.c $(H)screen.h
	gcc -c $(FLAGS) $<

space.o: $(C)space.c $(H)space.h $(H)types.h $(H)set.h
	gcc -c $(FLAGS) $<

object.o: $(C)object.c $(H)object.h $(H)types.h
	gcc -c $(FLAGS) $<

player.o: $(C)player.c $(H)player.h $(H)types.h $(H)object.h $(H)space.h $(H)set.h
	gcc -c $(FLAGS) $<
	
game_management.o: $(C)game_management.c $(H)game_management.h $(H)types.h $(H)game.h $(H)die.h
	gcc -c $(FLAGS) $<

set.o: $(C)set.c $(H)set.h
	gcc -c $(FLAGS) $<

die.o: $(C)die.c $(H)die.h
	gcc -c $(FLAGS) $<

game_rules.o: $(C)game_rules.c $(H)game_rules.h $(H)game.h $(H)types.h 
	gcc -c $(FLAGS) $<

dialogue.o: $(C)dialogue.c $(H)dialogue.h $(H)game.h $(H)types.h $(H)command.h $(H)space.h $(H)player.h
	gcc -c $(FLAGS) $<


set_test.o: $(C)set_test.c $(H)set.h
	gcc -c $(FLAGS) $<

die_test.o: $(C)die_test.c $(H)die.h
	gcc -c $(FLAGS) $<

link_test.o: $(C)link_test.c $(H)link.h
	gcc -c $(FLAGS) $<

space_test.o: $(C)space_test.c $(H)space.h $(H)set.h
	gcc -c $(FLAGS) $<

object_test.o: $(C)object_test.c $(H)object.h
	gcc -c $(FLAGS) $<

player_test.o: $(C)player_test.c $(H)player.h $(H)inventory.h $(H)set.h
	gcc -c $(FLAGS) $<

inventory_test.o: $(C)inventory_test.c $(H)inventory.h $(H)inventory.h $(H)set.h
	gcc -c $(FLAGS) $<

dialogue_test.o: $(C)dialogue_test.c $(H)dialogue.h $(H)dialogue_test.h $(H)types.h
	gcc -c $(FLAGS) $<

integration_test.o: $(C)integration_test.c $(H)game.h  $(H)command.h
	gcc -c $(FLAGS) $<

#################### LINK ####################
ocabas: $(OBJECTS)
	gcc $^ $(FLAGS) -o  cyberscape
	mv *.o ./obj/

die_test: die_test.o $(O)die.o
	gcc $^ $(FLAGS) -o  $@
	mv *.o ./obj/
set_test: set_test.o $(O)set.o 
	gcc $^ $(FLAGS) -o  $@
	mv *.o ./obj/
link_test: link_test.o $(O)link.o
	gcc $^ $(FLAGS) -o  $@
	mv *.o ./obj/
space_test: space_test.o $(O)space.o $(O)set.o
	gcc $^ $(FLAGS) -o  $@
	mv *.o ./obj/
object_test: object_test.o $(O)object.o  $(O)set.o
	gcc $^ $(FLAGS) -o  $@
	mv *.o ./obj/
player_test: player_test.o $(O)player.o $(O)inventory.o $(O)set.o
	gcc $^ $(FLAGS) -o  $@
	mv *.o ./obj/
inventory_test: inventory_test.o $(O)inventory.o $(O)set.o
	gcc $^ $(FLAGS) -o  $@
	mv *.o ./obj/
dialogue_test: dialogue_test.o $(O)command.o $(O)link.o $(O)game.o $(O)inventory.o $(O)space.o $(O)object.o $(O)player.o $(O)game_management.o $(O)set.o $(O)die.o $(O)dialogue.o
	gcc $^ $(FLAGS) -o  $@
	mv *.o ./obj/
integration_test: integration_test.o $(O)command.o $(O)link.o $(O)game.o $(O)inventory.o $(O)space.o $(O)object.o $(O)player.o $(O)game_management.o $(O)set.o $(O)die.o $(O)dialogue.o $(O)game_rules.o
	gcc $^ $(FLAGS) -o  $@
	mv *.o ./obj/



################ MISCELANIOUS ################
clean:	
	rm -rf *.o ocabas *_test *.tgz doc obj .vscode/ipch integration_test.txt 
	mkdir obj doc

doxygen:
	rm -rf doc 
	mkdir doc
	doxygen Doxyfile
	
dist: $(DIST)
	tar -cvzf s3-cod_OcaBasicaIni-3.tgz ./src ./includes

runv: clean ocabas
	valgrind --leak-check=full ./cyberscape data.dat
