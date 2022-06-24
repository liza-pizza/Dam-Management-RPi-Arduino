#  Steps to set up dev environment

1. Create venv (Optional)
```
python3 -m venv venv
source venv/bin/activate
```

2. Install requirements.txt

```
pip install -r requirements.txt
```

3. Run server

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

