/**
 *       \file      main.cpp
 *
 *       \brief     The Main file which will use all the executables
 *
 *       \version   0.1
 *       \date      Friday 05 April 2013 02:32:28  IST
 *       Compiler   gcc
 *
 *       \author    Piyush Parkash, achyutapiyush@gmail.com
 *        License   GNU General Public License
 *      \copyright  Copyright (c) 2013, GreatDevelopers
 *                  https://github.com/GreatDevelopers
 */

#include<iostream>
#include<rude/cgi.h>
#include<cstring>
#include<fstream>
#include<sqlite3.h>
#include<cstdlib>
#include<sstream>
#include<string>
#include"Functions.h"


//The Namespaces
using namespace std;
using namespace rude;

int main()
{
    //The very first and basic step of CGI to output Content-Type
    header();

    //The database connection holder
    sqlite3* db;

    //Open the connection to database
    int ret=sqlite3_open("photo.db",&db);
    if (ret!=SQLITE_OK)
    {
        cout<<"Database cannot be establishment";
        return 1;
    }
    
    //Library to parse GET, POST and FILE Data
    CGI cgi;

    //MainApp object  that controls the object
    MainApp app(db);

    //Display the header file
    displayFile("header.html");

    //The container to output the content
    cout<<"<div class='container-fluid' style='text-align:center;"
        <<"background-color:#dceaf4; margin-left:3%;"
        <<" margin-right:3%'>"<<endl;

    //Display appropriate Buttons
    cout<<"<div class='btn-group' style='margin:2%; text-align:center"
        <<"'>"
        <<"<a class='btn' href='main.cgi'>Home</a>"                   
        <<"<a class='btn' href='main.cgi?action=createalbum'>"
        <<"Create Album</a>";

        //Show content according to the action value
    if (strcmp(cgi.value("action"),"viewalbum")==0)
    {
        //Display the album
        displayAlbum(app,db,cgi,cgi.value("id"));
    }
    else if (strcmp(cgi.value("action"),"viewphoto")==0)
    {
        //Display the given photo
        displayPhoto(db, cgi.value("id"),cgi);
    }
    else if (strcmp(cgi.value("action"),"createalbum")==0)
    {
        //Display the form to create album
        createAlbum();
    }
    else if (strcmp(cgi.value("action"),"deletephoto")==0)
    {
        //Delete the given photo
        deletePhoto(cgi,db,cgi.value("id"));
    }
    else if (strcmp(cgi.value("editalbum-action"),"1")==0)
    {
        //This is initiated when Form to edit album is submitted
        stringstream sql;
        sql<<"update album set albumname='"<<cgi.value("albumname")
            <<"' where id="<<cgi.value("id");

        //Close the Button Group Division
        cout<<"</div>";
        
        //IF sql was successful then
        if (sqlite3_exec(db,sql.str().c_str(),NULL,NULL,NULL)
            ==SQLITE_OK)
        {
            cout<<"<script type='text/javascript'>"
                <<"window.location='main.cgi'</script>";
        }
        else //If there is an error
        {
            cout<<"<div class='alert alert-error'>"
                <<"Cannot Update name in database.";

        }
    }
    else if (strcmp(cgi.value("action"),"editalbum")==0)
    {
        //Display the form to edit album
        editAlbum(cgi,db);
    }
    else if (strcmp(cgi.value("action"),"deletealbum")==0)
    {
        //Delete the given album and all its photos
        deleteAlbum(db,cgi.value("id"));
    }
    else if (strcmp(cgi.value("createalbum-action"),"1")==0)
    {
        //This is initiated when create album form is posted
        
        //Close the btn group division
        cout<<"</div>";

        //Add the album
        if (app.addAlbum(cgi.value("albumname")))
        {
            cout<<"<div class='alert alert-success'>"
                <<"Album Successful Created</div>";
        }
        else
        {
            cout<<"<div class='alert alert-error'>"
                <<"Error Occured while creating album</div>";
        }
    }
    else
    {
        //The default section which is executed when none of
        //above option is selected
        displayAlbumLinks(db);
    }

    //Close the btn group div as all the options has been added
    cout<<"</div>";

    //Display the Footer HTML
    displayFile("footer.html");
    return 0;

}
