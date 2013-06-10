/**
 *       \file      Photo.cc
 *
 *       \brief     This class handles a basic Photo Entity 
 *
 *       \version   0.1
 *       \date      Saturday 09 March 2013 05:37:37  IST
 *       Compiler   gcc
 *
 *       \author    Piyush Parkash, achyutapiyush@gmail.com
 *        License   GNU General Public License
 *      \copyright  Copyright (c) 2013, GreatDevelopers
 *                  https://github.com/GreatDevelopers
 */
#include"Photo.h"


/**
 *      \class  Photo
 *      \fn     Photo :: Photo
 *      \brief  The Constructor of the Class. Inputs the basic
 *              details of the Photo
 *      \param  photoID The ID of the Photo
 *      \param  aID     The ID of the Album
 *      \param  fName   The filename of the Image
 */
Photo :: Photo(int photoID,int aID,char* fName)
{
     id=photoID;
     albumID=aID;
     fileName=fName;
}

