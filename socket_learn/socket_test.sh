#!/bin/bash


echo "control + c to end it"

g++ server.cpp -o server
sleep 1
./server & #后台执行


g++ client.cpp -o client
sleep 1
./client 


