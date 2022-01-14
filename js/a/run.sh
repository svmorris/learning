#!/bin/bash
while [ true ];do 
    sudo docker run -v $PWD:/usr/local/apache2/htdocs -p 8000:80 httpd
done
