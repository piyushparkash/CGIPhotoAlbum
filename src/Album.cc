/**
 *       \file      Album.cc
 *
 *       \brief     Contains declaration of class Album
 *
 *       \version   0.1
 *       \date      Thursday 28 March 2013 10:53:32  IST
 *       Compiler   gcc
 *
 *       \author    Piyush Parkash, achyutapiyush@gmail.com
 *        License   GNU General Public License
 *      \copyright  Copyright (c) 2013, GreatDevelopers
 *                  https://github.com/GreatDevelopers
 */

#include"Album.h"

using namespace std;

/**
 *      \class  Album
 *      \fn     Album :: init
 *      \brief  This functions initializes all the variable used in
 *              the class
 *      \param  db      The SQLite Connection Handler
 *      \param  albumID ID of the album to hold
 *      \param  aName   Name of the Album
 */
void Album :: init(sqlite3* db, int albumID, char* aName)
{
    id=albumID;
    albumName=aName;
    
    //Get the details of the album and save it in the class
    std::stringstream temp;
    temp<<"Select * from photo where albumid="
        <<albumID;

    sqlite3_stmt *statement;
    
    if (sqlite3_prepare_v2(db, temp.str().c_str(), -1, &statement, NULL)==SQLITE_OK)
    {
        char *fileName;
        int photoID;
        while (sqlite3_step(statement)==SQLITE_ROW)
        {
            photoID=sqlite3_column_int(statement,0);
            fileName=(char *)sqlite3_column_text(statement,1);
            albumID=sqlite3_column_int(statement,2);
            Photo temp(photoID, albumID, fileName);
            photos.push_back(temp);
        }
    }
}


/**
 *      \class  Album
 *      \fn     Album :: Album
 *      \brief  The constructor of the class
 *      \param  db      The connection handler of SQLite
 *      \param  albumID ID of the album
 *      \param  aName   Name of the album to hold
 */
Album :: Album(sqlite3* db, int albumID, char *aName)
{
    init(db, albumID, aName);
}


/**
 *      \class  Album
 *      \fn     Album :: firstPhoto
 *      \brief  This function returns the first photo of the Album
 */
string Album :: firstPhoto()
{
    ostringstream temp;
    temp<<photos[0].id<<"_"<<photos[0].fileName;
    return temp.str();
}


/**
 *      \class  Album
 *      \fn     Album :: Album
 *      \brief  The empty Constructor
 */
Album :: Album()
{
    
}
