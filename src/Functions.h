/**
 *
 *       \file      Functions.h
 *
 *       \details    Contains declaration of all the header functions
 *
 *       \version   0.1
 *       \date      Friday 29 March 2013 01:40:11  IST
 *       Compiler:  gcc
 *
 *       \author    Piyush Parkash, achyutapiyush@gmail.com
 *        License:  GNU General Public License
 *      \copyright  Copyright (c) 2013, GreatDevelopers
 *                  https://github.com/GreatDevelopers
 */

#include<sqlite3.h>
#include<rude/cgi.h>
#include"MainApp.h"
#include<fstream>
#include<cstdlib>

//The default directory to keep all the photos
#define PHOTO_DIR "../../photos/"
#define HTML_DIR "html/"

using namespace std;
using namespace rude;

/** 
 *      \brief  This function outputs the basic header needed for CGI
 */
void header();

/** 
 *      \brief  This function reads the given file and prints its out.
 *      \param  fileName    The name of the file to be read
 */
void displayFile(string);

/** 
 *      \brief  This function is used to display all the albums
 *              present in the database on the main page
 *      \param  db  The SQLite Connection Handler
 */
void displayAlbumLinks(sqlite3*);

/** 
 *      \brief  This function is used to display the Album's
 *              Photo's.This function also uploads images photos 
 *              to the album
 *      \param  app Instance of MainApp Class
 *      \param  db  The SQLite Connection Handler
 *      \param  cgi The CGI Parser
 *      \param  id  The ID of the album to be displayed
 */
void displayAlbum(MainApp, sqlite3*, CGI,const char*);

/** 
 *      \brief  This function is used to display a photo
 *      \param  db  The SQLite Connection Handler
 *      \param  id  The ID of the photo to be displayed
 *      \param  cgi The CGI Parser
 */
void displayPhoto(sqlite3* ,const char*, CGI);

/** 
 *      \brief  This function is used to output the form needed to
 *              edit the name of the Album
 */
void createAlbum();

/** 
 *      \brief  This function is used to delete photo of the given ID
 *      \param  cgi The CGI parser
 *      \param  db  The SQLite Connection Handler
 *      \param  id  The ID of the album to be deleted
 */
void deletePhoto(CGI,sqlite3*, const char*);

/** 
 *      \brief  This function is used to delete an entire Album with
 *              all of its photos
 *      \param  db  The SQLite Connection Handler
 *      \param  id  The ID of the album to be deleted
 */
void deleteAlbum(sqlite3*, const char*);

/** 
 *      \brief  This function is used to edit the name of the Album
 *      \param  cgi The CGI Parser
 *      \param  db  The SQLite Connection Handler
 */
void editAlbum(CGI,sqlite3*);

/** 
 *      \brief  This function constructs the name of the file from the
 *              filename in the database and the ID of the photo
 *      \param  index       The ID of the Photo
 *      \param  fileName    The filename of the photo
 */
string makeFilename(int index, string& fileName);
