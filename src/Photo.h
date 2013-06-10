/**
 *
 *       \file      Photo.h
 *
 *       \details   Contains Declaration of Photo Class
 *
 *       \version   0.1
 *       \date      Thursday 28 March 2013 10:51:38  IST
 *       Compiler:  gcc
 *
 *       \author    Piyush Parkash, achyutapiyush@gmail.com
 *        License:  GNU General Public License
 *      \copyright  Copyright (c) 2013, GreatDevelopers
 *                  https://github.com/GreatDevelopers
 */

#include<vector>

/**
 *        \class  Photo
 *        \brief  This class holds information about a photo in the
 *                album
 */

class Photo
{
    public:
    char *fileName;
    int albumID;
    int id;
   
    Photo(int, int ,char*);
};


typedef std::vector<Photo> PhotoList;
