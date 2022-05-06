
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

```
sudo nano /home/pi/.bashrc   -> start vnc thingy 


home/pi/tcpserver  -> the actual server here


/etc/systemd/system/tcpserver.service  -> add service lol