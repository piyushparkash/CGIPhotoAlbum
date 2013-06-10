CGIPhotoAlbum
=============


REQUIREMENTS:
-------------

    1) GNU G++ Compiler
    2) Configure public_html and cgi-bin in home
    3) RUDE CGI Library
    4) SQLITE for C++

Installation of requirements

1) GNU G++ Compiler
    
Run following command in terminal to install
    
    $ sudo apt-get install build-essential

2) Configure public_html/cgi-bin folder for executing files on browser.<br>
Assuming you already installed apache if not then run following
command in terminal

    $ sudo apt-get install apache2
    
**Steps to configure public_html**
        
    $ mkdir ~/public_html
    
    $ sudo a2enmod userdir
        
    $ sudo service apache2 restart
        
Give 755 permissions to public_html directory
        
    $ chmod -R 755 ~/public_html
        
Now open http://localhost/~username in browser.
Here username is your login name.
    
**Steps to configure cgi-bin in public_html**
    
    $ sudo a2enmod cgi
    
    $ sudo a2enmod cgid
    
    $ sudo service apache2 restart
     
    $ cd ~/public_html
    
    $ mkdir cgi-bin
    
    $ cd /etc/apache2
    
    $ sudo vim sites-available/default
    
Add following text in file:
    
    ScriptAlias /cgi-bin/ /home/*/public_html/cgi-bin/
    <Directory "/home/*/public_html/cgi-bin">
        AllowOverride None
        Options +ExecCGI -MultiViews +SymLinksIfOwnerMatch
        SetHandler cgi-script
        Order allow,deny
        Allow from all
    </Directory>
    
Save it and then restart apache

    $ sudo service apache2 restart
    
Installing RUDE CGI Library
-----------------------------
Execute the following command to install RUDE CGI Library

    $ sudo apt-get install librudecgi5 librudecgi-dev
    
Installing SQLITE For C++
-------------------------
    $ sudo apt-get install libsqlite3-dev
    
AUTHORS:
--------
<b>Mentor and Manager</b>

Dr. Hardeep Singh Rai

Website: http://gndec.ac.in/~hsrai

Piyush Parkash

Website: piyushparkash.blogspot.com

Email: achyutapiyush \[AT\] gmail.com
