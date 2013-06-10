SQLITE  = -lsqlite3
RUDECGI = -lrudecgi
PARAMS  = $(SQLITE) $(RUDECGI)
#--------------------------------------------------------------------
#					Header Files
#--------------------------------------------------------------------
MAINAPP_HEADER	= MainApp.h
ALBUM_HEADER	= Album.h
PHOTO_HEADER	= Photo.h
FUNCTION_HEADER	= Functions.h

#--------------------------------------------------------------------
#					DEFINATIONS
#--------------------------------------------------------------------
MAINAPP		= MainApp.cc
ALBUM		= Album.cc
PHOTO		= Photo.cc
FUNCTION	= Functions.cc

#--------------------------------------------------------------------
#					OUTPUT
#--------------------------------------------------------------------
OUTPUT = main.cgi

#--------------------------------------------------------------------
#					TARGETS
#--------------------------------------------------------------------
all: $(OUTPUT)

Photo.o: $(PHOTO) $(PHOTO_HEADER)
	g++ -c $(PHOTO)

Album.o: $(ALBUM) $(ALBUM_HEADER)
	g++ -c $(ALBUM) $(PARAMS)

MainApp.o: $(MAINAPP) $(MAINAPP_HEADER)
	g++ -c $(MAINAPP) $(PARAMS)


Functions.o: $(FUNCTION) $(FUNCTION_HEADER)
	g++ -c $(FUNCTION) $(PARAMS)


main.cgi: Functions.o Photo.o Album.o MainApp.o
	g++ -o $(OUTPUT) main.cpp Functions.o MainApp.o Album.o Photo.o $(PARAMS)

clean:
	rm $(OUTPUT) && rm *.o
