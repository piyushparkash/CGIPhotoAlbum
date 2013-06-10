SRC		=	src
OUTPUT	=	main.cgi
RES_FOL	=	cgi_thing
DOC_FOL	=	doc

#--------------------------------------------------------------------
#				TARGETS
#--------------------------------------------------------------------
all: $(SRC)/ $(RES_FOL)/
	make -C $(SRC)
	mkdir -p ../../photos
	cp -r $(RES_FOL)/ ../../$(RES_FOL)/
	cp -r $(DOC_FOL)/ ../../$(RES_FOL)/$(DOC_FOL)/
	chmod -R 777 ../../photos/
	cp $(SRC)/$(OUTPUT) $(OUTPUT)

clean:
	rm $(OUTPUT) && make -C $(SRC) clean
#	rm -Rf ../../photos/
	rm -Rf ../../cgi_thing/
