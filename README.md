# WebServer

## Description

A simple HTTP WebServer in C++ that sends the time to clients.

Note: For a more complex http web server, please request access to code due to plagiarism concerns.

Note: Docker containerization not currently supported/setup.

## Setup

Requirements:
* CMAKE version 3.23
* Docker (if trying to run in container)
* Linux/Unix System

To build locally, run:
``./bin/local-setup.sh [port-number]``

If no port-number is provided, will default to 8080.

To build in docker, run: 
``./bin/docker-setup.sh``
