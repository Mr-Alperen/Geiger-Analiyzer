import requests
import time
import random

url = "http://192.168.163.19:8080/geiger"

while True:
    alpha_cps = random.randint(0, 5)
    gamma_cps = random.randint(0, 3)

    alpha_cpm = alpha_cps * 60
    gamma_cpm = gamma_cps * 60

    json_data = {
        "alpha_cps": alpha_cps,
        "alpha_cpm": alpha_cpm,
        "gamma_cps": gamma_cps,
        "gamma_cpm": gamma_cpm
    }

    requests.post(url, json=json_data)
    print("Gönderildi:", json_data)
    time.sleep(1)
