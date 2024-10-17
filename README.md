# socket-based real-time chat room
## Description： 
Implement a real-time chat room using sockets, with two client chat rooms that can communicate in the server chat room.

## How to setup
### 1. Compiler server with winsock(ws2_32.lib)
```bash
g++ socket_server.cpp -o socket_server -lws2_32
```
### 2. Compiler client and client2 with winsock(ws2_32.lib)
```bash
g++ socket_client.cpp -o socket_client -lws2_32
```
```bash
g++ socket_client2.cpp -o socket_client2 -lws2_32
```
## Usage
### 1. First run server
```bash
./socket_server
```
### 2. Run client and client2
```bash
./socket_client
```
```bash
./socket_client2
```
### 3. You can enter text client and client2 then text will show on server
![image](https://github.com/user-attachments/assets/2f22633c-8748-4761-89ed-8594ae662965)
