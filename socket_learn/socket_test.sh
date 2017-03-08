#!/bin/bash

echo "begin"

g++ server.cpp -o server
./server & #后台执行

echo "服务端挂起"


echo "客户端请求"

g++ client.cpp -o server
./client

echo "end"
