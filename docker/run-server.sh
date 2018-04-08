#!/bin/bash

: "${MYSQL_USER:?MYSQL_USER environment variable must be set!}"
: "${MYSQL_PASSWORD:?MYSQL_PASSWORD environment variable must be set!}"

sudo mkdir -p datadir
sudo chown -R $USER datadir

# Cleanup old containers.
docker rm -f myadmin sqlserver

# Launch services.
docker run --name sqlserver -d -p 3306:3306 -e MYSQL_ROOT_PASSWORD=root -e MYSQL_DATABASE=magic_cards -e MYSQL_USER=${MYSQL_USER} -e MYSQL_PASSWORD=${MYSQL_PASSWORD} -v $(pwd)/sql:/docker-entrypoint-initdb.d -v $(pwd)/datadir:/var/lib/mysql mysql/mysql-server:5.7
docker run --name myadmin -d -p 8081:80 -e MYSQL_ROOT_PASSWORD=root --link sqlserver:db phpmyadmin/phpmyadmin:4.7
