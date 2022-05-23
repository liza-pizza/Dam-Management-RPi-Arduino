import json
import random as rd
import requests

data = {}
data['site'] = '4'
data['sensor'] = '11'
data['water_depth'] = str(rd.randrange(900, 950))
print(data['water_depth'])
json_data = json.dumps(data)
print(json_data)
y = requests.post('http://localhost:8000/dam-information/update', json = json_data)
print(y.status_code)
print(json_data)
