/**
 *       \file      Functions.cc
 *
 *       \brief      Definations of all the global functions
 *
 *       \version   0.1
 *       \date      Friday 29 March 2013 01:46:36  IST
 *       Compiler   gcc
 *
 *       \author    Piyush Parkash, achyutapiyush@gmail.com
 *        License   GNU General Public License
 *      \copyright  Copyright (c) 2013, GreatDevelopers
 *                  https://github.com/GreatDevelopers
 */


#include"Functions.h"


string makeFilename(int index, string& fileName)
{
    ostringstream result;
    result << PHOTO_DIR  << index+1 << "_" << fileName;
    return result.str();
}


void displayFile(string fileName)
{
    //Open the file
    fstream f;

    //string to hold a line from the file;
    string line;

    fileName=HTML_DIR+fileName;
    f.open(fileName.c_str(),fstream::in);

    if (f.is_open())
    {
        //Get the size of the file
        while (f.good())
        {
            getline(f,line);
            cout<<line;
        }
    }
    else
    {
        cout<<"Cannot open file" << fileName;
    }
    
    f.close();
}


void deletePhoto(CGI cgi, sqlite3* db, const char* id)
{
    //Close the bt group div
    cout<<"</div>";
    char sql[512];
    sprintf(sql,"Select * from photo where id=%s",id);
    
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(db, sql, -1, &statement, NULL)==SQLITE_OK)
    {
        if (sqlite3_step(statement)==SQLITE_ROW)
        {
            //Using ostringstream to construct the filename
            ostringstream temp;
            temp<< PHOTO_DIR;
            temp<<sqlite3_column_int(statement,0) << "_" 
                <<sqlite3_column_text(statement,1);
            string filename=temp.str();

            int res=remove(filename.c_str());
            //Filename constructed now Delete them one by one
            
            if (res==0)
            {
                //if deletion was successfull
                //Now we can delete the entry from the database

                //Prepare the sql to delete the photo entry
                sprintf(sql,"delete from photo where id=%s",id);

                if (sqlite3_exec(db,sql,NULL,NULL,NULL)!=SQLITE_OK)
                {
                    cout<<"<div class='alert alert-error'>"
                        <<"Cannot delete the entry from database"
                        <<"</div>";
                }
                else
                {
                    //If both the operations was successfull
                    //Redirect user the album page

                    cout<<"<script type='text/javascript'>"
                        <<"window.location='main.cgi?action=viewalbum"
                        <<"&id="<<cgi.value("albumid")
                        <<"';</script>";
                }
            }
            else
            {
                //If file removal was not successfull
                cout<<"<div class='alert alert-error'>Cannot Remove"
                    <<" file. Error Occured</div>";
                exit(1);
            }
        }
        else
        {
            cout<<"Didn't get any record from database";
        }
    }
}


void displayAlbumLinks(sqlite3 *db)
{
    //Closing the button group div
    cout<<"</div>";
    
    //Prepare the sql
    char sql[512];
    sprintf(sql,"select * from album");
    
    
    //Start Evaluating the sql
    sqlite3_stmt *statement;
    
    if (sqlite3_prepare_v2(db,sql,-1, &statement,NULL)==SQLITE_OK)
    {
        //Display the album
        cout<<"<div class='row row-fluid'>";
        int i=0;
        while (sqlite3_step(statement)==SQLITE_ROW)
        {
            //TODO: Output the first image of the album
            cout<<"<div class='span4' id='" 
                <<sqlite3_column_int(statement,0) <<"'>";
            cout<<"<a href='main.cgi?action=viewalbum&id="
                <<sqlite3_column_int(statement,0)<<"'>"
                << "<h3>"<<sqlite3_column_text(statement, 1)
                << "</h3></a> "
                <<"</div>";
                i++;
        }
        //IF no albums is found then...
        if (i==0)
        {
            cout<<"<h2>No Albums</h2>";
        }
        cout<<"</div>";
    }
    else
    {
        cout<<"<div class='alert alert-info'>"
            <<"Cannot Prepare the statement</div>";
    }
}


void deleteAlbum(sqlite3 *db, const char* id)
{
    //Close the btn group division
    cout<<"</div>";

    //Prepare the sql get information about the photos in the album
    char sql[512];
    sprintf(sql,"select * from photo where albumid=%s",id);
    sqlite3_stmt *statement;
    
    if (sqlite3_prepare_v2(db,sql,-1, &statement, NULL)==SQLITE_OK)
    {
        ostringstream temp;
        while (sqlite3_step(statement)==SQLITE_ROW)
        {
            //First make the filename
            temp<< PHOTO_DIR
                <<sqlite3_column_int(statement,0)
                <<"_"<<sqlite3_column_text(statement,1);
            const char* fileName=temp.str().c_str();

            //Firstly delete the file
            if (remove(temp.str().c_str())==0)
            {
                //File has been deleted
                //Now delete the entry in the database
                
                sprintf(sql,"delete from photo where id=%d",
                              sqlite3_column_int(statement,0));
                if (sqlite3_exec(db,sql,NULL,NULL,NULL)!=SQLITE_OK)
                {
                    cout<<"<div class='alert alert-error'>"
                        <<"Cannot Execute delete query</div>";
                    break;
                }
                
                //Clear the buffer
                temp.str("");
                temp.clear();
            }
            else
            {
                cout<<"<div class='alert alert-error'>"
                    <<"Cannot delete photo from album";
                exit(1);
            }
        }
    }
    //There is a error in the sql
    else
    {
        cout<<"<div class='alert alert-error'>"
            <<"Error in the sql</div>";
            exit(1);
    }
    
    //Tough guy huh? Reached here... Album is empty now
    //Now we can delete the album
    
    sprintf(sql,"delete from album where id=%s",id);
    if (sqlite3_exec(db,sql,NULL,NULL,NULL)!=SQLITE_OK)
    {
        cout<<"<div class='alert alert-info'>"
            <<"Cannot delete album. Error Occured</div>";
        return;
    }

    //Redirect user to the default page
    cout<<"<div class='alert alert-success'>"
        <<"Album Deleted</div>"
        <<"<script type='text/javascript'>"
        <<"window.location='main.cgi';</script>";
}


void displayAlbum(MainApp app,sqlite3 *db, CGI cgi, const char* id)
{
    
    cout<<"<a class='btn' href='javascript:void(0);' id='addphoto'>"
        <<"Add Photos</a>"
        <<"<a class='btn' href='main.cgi?action=editalbum&id="
        <<cgi.value("id")
        <<"'>Edit Album</a>"
        <<"<a class='btn btn-danger' href='main.cgi"
        <<"?action=deletealbum&id="
        <<id<<"'>Delete Album</a>"
        <<"</div>";
    displayFile("uploadphoto.html");

    //Check if a photo was uploaded
    if (strcmp(cgi.value("displayalbum-upload"),"1")==0)
    {
        //Checking if a file was submited
        if (cgi.isFile("file") && cgi.exists("file"))
        {
            //Check if uploaded file is an image
            ostringstream temp;
            temp<<cgi.contenttype("file");
            string contentType=temp.str();
            if (contentType.find("image",0)!=1)
            {
                //Very first thing add an entry in the database
                const char *fileName=cgi.filename("file");
                const char *albumID=cgi.value("id");

                //Prepare the sql
                char sql[512];
                
                //Get the id of the executed sql and use it in
                //the filename to prevent same filename clashes

                sprintf(sql, "select * from photo"
                " order by id DESC");
                sqlite3_stmt *statement;
                
                //Took zero as the makeFileName will increment by 1
                int latestID=0;

                int res1,res2;
                res1=sqlite3_prepare_v2(db,sql,-1,&statement,NULL);
                if (res1==SQLITE_OK)
                {
                    res2=sqlite3_step(statement);
                    if (res2==SQLITE_OK)
                    {
                        //Get the latest ID
                        latestID=sqlite3_column_int(statement,0);
                    }
                }

                string filenameString(fileName);

                ostringstream temp;
                //Prepare the filename

                ofstream dataFile;
                dataFile.open(makeFilename(latestID,
                                     filenameString).c_str(),
                                             fstream::binary);
                if (dataFile.is_open())
                {
                    //Prepare the data to be written
                    long int fileLength= cgi.length("file");
    
                    //Write data to the file
                    dataFile.write(cgi.value("file"),fileLength);

                    //Check if the file was written properly
                    //Then only we can add Entry in the database
                    if (dataFile.good())
                    {
                       sprintf(sql, "insert into photo"                      
                       "(photofilename,albumid) values('%s','%s')",
                       fileName, albumID);                                   
                       if (sqlite3_exec(db,sql,NULL,NULL,NULL)
                             !=SQLITE_OK)
                       {
                          cout<<"<div class='alert alert-error'"
                              <<">Error Occured!</div>";
                       }
                       //Close the file
                       dataFile.close();
                    }
                }
                 else
                 {
                     cout<<"<div class='alert alert-error'>"
                         <<"Cannot Open the new file to write";
                     exit(1);
                 }
                
            }
            else
            {
                cout<<"<div class='alert alert-error'>"
                    <<"Invalid Image Uploaded"
                    <<"</div>";
                
            }
        }
        else
        {
            cout<<"<div class='alert alert-error'>"
                <<"No File received. Please try again."
                <<"</div>";
        }

    }
    
    //Start dislaying the images
    cout<<"<div style='text-align:center'><ul class='thumbnails'>";
    char sql[512];

    sprintf(sql,"select * from photo where albumid=%s",
                 cgi.value("id"));
    sqlite3_stmt *statement;
    int i=0;
    if (sqlite3_prepare_v2(db,sql,-1,&statement,NULL)==SQLITE_OK)
    {
        while (sqlite3_step(statement)==SQLITE_ROW)
        {
            cout<<"<li class='span6' style='list-style-type:none'>"
                <<"<a href='main.cgi?action=viewphoto&id="
                <<sqlite3_column_int(statement,0)
                <<"' class='thumbnail'>"
                <<"<img src='" << PHOTO_DIR
                <<sqlite3_column_int(statement,0)
                <<"_"<<sqlite3_column_text(statement,1)
                <<"' alt=''>"
                <<"</a><a class='btn btn-danger' style='margin:2%'"
                <<" href='main.cgi?action=deletephoto&id="
                <<sqlite3_column_int(statement,0)
                <<"&albumid="
                <<cgi.value("id")<<"'>Delete</a>"
                <<"</li>";
                i++;
        }
    }
    cout<<"</ul></div>";
    
    //If no photos found in the album then..

    if (i==0)
    {
        cout<<"<h2>No photos in the album</h2>";
    }
}


void editAlbum(CGI cgi, sqlite3* db)
{
    //Close the button group div
    cout<<"</div>";

    char sql[512];
    sprintf(sql,"select * from album where id=%s",cgi.value("id"));
    sqlite3_stmt *statement;
    
    if (sqlite3_prepare_v2(db,sql,-1,&statement,NULL)==SQLITE_OK)
    {
        if (sqlite3_step(statement)==SQLITE_ROW)
        {
            cout<<"<form method='post' class='well' "
                <<"style='text-align:left'>"
                <<"<fieldset>"
                <<"<legend>Edit Album</legend>"
                <<"<label>Album name</label>"
                <<"<input type='text' placeholder='Album Name' "
                <<"name='albumname' id='albumname' value='"
                <<sqlite3_column_text(statement,1)<<"' >"
                <<"<span class='help-block'>"
                <<"Enter the new name of the album</span>"
                <<"<input type='hidden' name='editalbum-action'"
                <<"value='1' />"
                <<"<button type='submit' class='btn'>"
                <<"Submit</button>"
                <<"</fieldset>"
                <<"</form>";
        }
    }
}




void header()
{
    cout<<"Content-type:text/html\r\n\r\n";
}



void displayPhoto(sqlite3* db, const char* id,CGI cgi)
{
    stringstream sql;
    sql<<"select * from photo where id="<<id;
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(db,sql.str().c_str(),-1,&statement,NULL)
                                                ==SQLITE_OK)
    {
        if (sqlite3_step(statement)==SQLITE_ROW)
        {
            cout<<"a class='btn btn-danger' href='main.cgi?action="
                <<"deletephoto&id="<<sqlite3_column_int(statement,0)
                <<"&albumid="<<cgi.value("id")<<"'>Delete</a>"
                <<"<a class='btn' href='main.cgi?action=viewalbum&id="
                <<sqlite3_column_int(statement,2)<<"' >Back</a>"
                <<"</div><div style='text-align:center'><ul style='"
                <<"list-style-type:none' class='thumbnail'>"
                <<"<li style='text-align:center'>"
                <<"<img src='"<< PHOTO_DIR 
                <<sqlite3_column_int(statement,0)
                <<"_"<<sqlite3_column_text(statement,1)<<"' />"
                <<"</li>"
                <<"<ul></div>";
        }
    }
}


void createAlbum()
{
   //Close the button div group
    cout<<"</div>";
    displayFile("createalbum.html");
}
