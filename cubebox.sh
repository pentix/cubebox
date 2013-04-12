#!/bin/sh -e

CUBEBOXDIR=INSTALL_PATH

cd $CUBEBOXDIR

case $1 in
	client)
		./cubebox
	;;
	server)
		./cubebox-server
	;;
	*)
		./cubebox
	;;
esac
