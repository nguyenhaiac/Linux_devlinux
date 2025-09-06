##
# Project Title
#
# @file
# @version 0.1
REG_FILE = testRegFile
SYM_FILE = testSymFile
DIR_FILE = testDirFile
build:
	gcc main.c -o filestat -Wall -g

test: build
	mkdir $(DIR_FILE)
	touch $(REG_FILE)
	ln -s $(REG_FILE) $(SYM_FILE)
	echo "Test string for the new file" >> $(REG_FILE)
	./filestat $(DIR_FILE)
	./filestat $(REG_FILE)
	./filestat $(SYM_FILE)
	./filestat nonExistingfile

clean:
	rm filestat
	rm -r $(DIR_FILE)
	rm $(SYM_FILE)
	rm $(REG_FILE)
# end
