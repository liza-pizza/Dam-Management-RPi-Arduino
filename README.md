
1. create venv if you want
```
python3 -m venv venv
source venv/bin/activate
```

2. install requirements.txt

```
pip install -r requirements.txt
```

3. run 

```
python3 tcpServer.py
```

4. Locations to add things 

    4a. start vnc thingy 
    
    ``` 
    home/pi/.bashrc
    ```

    
    
    4b. the actual server here
    
    ``` 
    /home/pi/tcpserver
    ```
    

    4c. add service here lol
    
    ``` 
    /etc/systemd/system/tcpserver.service 
    ```

