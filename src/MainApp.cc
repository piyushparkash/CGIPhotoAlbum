/**
 *       \file      MainApp.cc
 *
 *       \brief     The Main Application handling all the class
 *
 *       \version   0.1
 *       \date      Friday 29 March 2013 01:35:17  IST
 *       Compiler   gcc
 *
 *       \author    Piyush Parkash, achyutapiyush@gmail.com
 *        License   GNU General Public License
 *      \copyright  Copyright (c) 2013, GreatDevelopers
 *                  https://github.com/GreatDevelopers
 */

#include"MainApp.h"


/**
 *      \class  MainApp
 *      \fn     MainApp :: MainApp
 *      \brief  The Constructor of the class
 *      \param  con The connection handler of SQLite
 */
MainApp :: MainApp(sqlite3* con)
{
    db=con;
}


/**
 *      \class  MainApp
 *      \fn     MainApp :: installDatabase
 *      \brief  This function creates the Table Structure in the
 *              Database
 *      \param  db  The connection handler of SQLite
 */
int MainApp :: installDatabase(sqlite3* db)
{
    string sql="create table (id INTEGER PRIMARY KEY ASC, albumname";
    sql += " TEXT)";
    int albumTable=sqlite3_exec(db,sql.c_str(),NULL,NULL,NULL);
    sql="create table (id INTERGET PRIMARY KEY ASC,photofilename TEXT";
    sql += ", albumid NUMERIC)";
    int photoTable=sqlite3_exec(db,sql.c_str(),NULL,NULL,NULL);
    
    return (albumTable || photoTable);
}


/**
 *      \class  MainApp
 *      \fn     MainApp :: getAlbums
 *      \brief  This function return all the albums present in the
 *              database
 */
AlbumList MainApp :: getAlbums()
{
    AlbumList Albums;
    string sql="select * from album";
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(db,sql.c_str(),-1, &statement,NULL)==SQLITE_OK)
    {
        while (sqlite3_step(statement)==SQLITE_ROW)
        {
            Album temp(db,sqlite3_column_int(statement,0),
                    (char *)sqlite3_column_text(statement,1));
            Albums.push_back(temp);
        }
    }
    return Albums;
}


/**
 *      \class  MainApp
 *      \fn     MainApp :: getAlbum
 *      \brief  This returns all the information about the Album as
 *              the Album structure
 *      \param  db  The SQLite Connection handler
 *      \param  ID  The ID of the ALbum
 */
Album MainApp :: getAlbum(sqlite3* db, const char* ID)
{
    stringstream sql;
    Album a;
    sql<<"select * from photo where albumid=";
    sql<<ID;
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(db,sql.str().c_str(),
                    -1,&statement, NULL)==SQLITE_OK)
    {
        while(sqlite3_step(statement)==SQLITE_ROW)
        {
            //a.init(db,sqlite3_column_int(statement,0),
            //(char *)sqlite3_column_text(statement,1));

        }
    }
    return a;
}


/**
 *      \class  MainApp
 *      \fn     MainApp :: addAlbum
 *      \brief  This function is used to create a new Album
 *      \param  albumName   The name of the Album
 */
bool MainApp :: addAlbum(const char* albumName)
{
    stringstream sql;
    sql<<"insert into album(albumname) values('"
       <<albumName<<"')";
    int rc=sqlite3_exec(db,sql.str().c_str(),NULL,NULL,NULL);
    if (rc==SQLITE_OK)
    {
        return true;
    }
    else
    {
        return false;
    }
}


/**
 *      \class  MainApp
 *      \fn     MainApp :: deleteAlbum
 *      \brief  This function is used to delete a whole album along
 *              with its photos
 *      \param  albumID The ID of the album to be deleted
 */
bool MainApp :: deleteAlbum(int albumID)
{
    stringstream sql;
    sql<<"delete from album where id="<<albumID;
    int rc=sqlite3_exec(db,sql.str().c_str(),NULL,NULL,NULL);
    if (rc==SQLITE_OK)
    {
        return true;
    }
    else
    {
        return false;
    }
}
