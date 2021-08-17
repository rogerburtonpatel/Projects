## seclists_fuzzer.py
##
## Uses Daniel Miessler's /SecLists/Fuzzing lists to fuzz a site at 
## user-given url. Allows for some default input and testing. 
##
## Author: Roger A. Burtonpatel 
## Updated 7/20/2021

import os
import io
import requests

target = input("Please enter a target URL\n OR press 1 for \n" +
"http://www.cs.tufts.edu/comp/120/hackme.php?token=Foodler \n : ")

if target == '1':
    target = "http://www.cs.tufts.edu/comp/120/hackme.php?token=Foodler"
    print("Using http://www.cs.tufts.edu/comp/120/hackme.php?token=Foodler " +
    "as target URL. \n")

# Uncomment line 8 if you just want to test target Tufts site. 
# target = "http://www.cs.tufts.edu/comp/120/hackme.php?token=Foodler"

fuzz_input = input("Enter the path of your fuzzfile " +
"\n ex: /home/user/SecLists/Fuzzing/XSS/fuzzfile\n" +
"OR press 2 to test for XSS vulnerabilities with " +
" <script>alarm(XSS);</script> \n : ")

vulnerability_counter = 0

def xss_test(target_url, xss_payload, vulnerability_counter):
    try: 
        req = requests.get(target_url + xss_payload)
    except: 
            print("Please try again with a valid URL.")
            exit(1)

    if payload in req.text:
        print("XSS Vulnerablity discovered!")
        print(f'{payload} appended to url is potential XSS opening.')
        vulnerability_counter += 1
    else:
        print(f'Scanner indicates site is secure from payload {payload}')
    return vulnerability_counter


## Main code 
if fuzz_input == '2':
    fuzz_input = "<script>alarm(XSS);</script>"
    payload = "<script>alarm(XSS);</script>"
    vulnerability_counter = xss_test(target, payload, vulnerability_counter)

else: 
    # Makes sure file is there 
    assert os.path.exists(fuzz_input), ("I did not find the file at, " +
                                                        str(fuzz_input))
    # Uses io to open as to unicode with uft-8
    with io.open(fuzz_input,'r+') as f:
        print("Hooray, we found your file!")
        # Adds payload to url and posts. If the payload is found in the output, 
        # ups the vulnerability counter and prints the offending payload. 
        # This indicates an XSS vulnerability. 
        for line in f:
            payload = line 
            vulnerability_counter = xss_test(target, payload,
                                             vulnerability_counter)
# Displays total number of vulnerabilities, with a pat on the back if 0. 
if vulnerability_counter == 1:

    print(f'\n{vulnerability_counter} ' +
        f'XSS vulnerability found from \n [ {target} ] ' +
        f'\n using \n [ {fuzz_input} ].')
    print("Hopefully there aren't more...")

else:
    print(f'\n{vulnerability_counter} ' +
    f'total XSS vulnerabilities found from \n [ {target} ] ' +
    f'\n using \n [ {fuzz_input} ].')

    if vulnerability_counter == 0:
        print("\nThat's great!")
    else:
        print("\nGood luck with that.")