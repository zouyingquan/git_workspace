import requests

ak = ''

def geocode(address):
	base = url = "http://api.map.baidu.com/geocoding/v3/?address=" + address + "&output=json&ak=" + ak
	response = requests.get(base)
	answer = response.json()
	return round(answer['result']['location']['lng'],5),round(answer['result']['location']['lat'],5)

def calcDistance(origin,destination):
	start = geocode(origin) 
	end   = geocode(destination)
	base = url = "http://api.map.baidu.com/directionlite/v1/driving?origin=" + str(start[1]) + ',' + str(start[0]) + "&destination=" + str(end[1]) + ',' + str(end[0]) + "&ak=" + ak
	response = requests.get(base)
	answer = response.json()
	ans = answer['result']['routes'][0]['distance']
	return ans

distance = calcDistance("北海","合浦")
print(str(distance / 1000) + 'Km')
