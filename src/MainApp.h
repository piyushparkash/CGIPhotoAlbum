/**
 *
 *       \file      MainApp.h
 *
 *       \details   This is the main class which handles all the
 *                  funtions of the PhotoAlbum
 *
 *       \version   0.1
 *       \date      Saturday 09 March 2013 05:23:02  IST
 *       Compiler:  gcc
 *
 *       \author    Piyush Parkash, achyutapiyush@gmail.com
 *        License:  GNU General Public License
 *      \copyright  Copyright (c) 2013, GreatDevelopers
 *                  https://github.com/GreatDevelopers
 */

#include<iostream>
#include<sqlite3.h>
#include<vector>
#include<cstring>
#include"Album.h"

using namespace std;


/**
 *        \class  MainApp
 *        \brief  The is the main class which handles all the
 *                functions of the PhotoAlbum
 *        \param  sqlite*
 */

class MainApp
{
    public:
    sqlite3* db; /**< This will hold the connection to the database */
    
    //The Construtor of the class which inputs the connection to the
    //database
    MainApp(sqlite3*);
    int installDatabase(sqlite3* db);
    AlbumList getAlbums();
    Album getAlbum(sqlite3*, const char* ID);
    bool addAlbum(const char*);
    bool deleteAlbum(int);
};
