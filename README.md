## Calculator CLI Project using IPC Socket and Linux Service

This project is simple calculator and provides Linux CLI functionality. CLI process communicates with Linux calculation service server via IPC UNIX Domain Socket.

*Author:Mehmet Kahraman*

*Date: 11.12.2023*

Architecture:

![](architecture.svg)

Build and installation:
```
mkdir build
cd build
cmake ..
make
sudo make install
```

Starting Service:
```
sudo systemctl daemon-reload
sudo systemctl start calculatord
sudo systemctl status calculatord
sudo journalctl --unit calculatord --follow
```

Client Execution with CLI:
```
calculator_client add 2 3
```
> Client connected to server. 
>
> Client: Sending query: 1 2 3  
> Client: Received response: 5