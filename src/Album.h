/**
 *
 *       \file      Album.h
 *
 *       \details   Contains declaration of class Album
 *
 *       \version   0.1
 *       \date      Thursday 28 March 2013 10:55:05  IST
 *       Compiler:  gcc
 *
 *       \author    Piyush Parkash, achyutapiyush@gmail.com
 *        License:  GNU General Public License
 *      \copyright  Copyright (c) 2013, GreatDevelopers
 *                  https://github.com/GreatDevelopers
 */

#include<string>
#include<sqlite3.h>
#include<rude/cgi.h>
#include"Photo.h"
#include<sstream>

/**
 *        \class  Album
 *        \brief  Class that holds and manipulates albums
 */
class Album
{
    public:
    int id;
    PhotoList photos;
    char* albumName;
     
    void init(sqlite3* db, int albumID, char *aName);
    Album(sqlite3* db, int albumID, char *aName);
    std::string firstPhoto();
    Album();
};

typedef std::vector<Album> AlbumList;
