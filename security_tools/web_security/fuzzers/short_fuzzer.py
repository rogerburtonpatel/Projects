## short_fuzzer.py
##
## Fuzzes site at a user-inputted URL for XSS vulnerabilities using a basic 
## XSS payload. 
##
## Author: Roger A. Burtonpatel 
## Updated 7/20/2021

import requests

target = input("Submit target URL")
payload = "<script>alert(XSS);</script>"
req = requests.get(target + payload)

if payload in req.text:
   print(f'XSS Vulnerablity discovered! Payload = {payload}')
   print("Appending payload to URL may result in unexpected behavior.")
else:
   print(f'Scanner indicates site is secure from payload {payload}.')