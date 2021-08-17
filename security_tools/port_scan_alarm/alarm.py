#!/usr/bin/python3

"""
alarm.py 

This is a crude alarm used to detect a variety of port scans which can 
be used by attackers to sniff for activity on your device. It can analyze
a live stream of network packets coming from a given IP, and can also 
detect incidents from sets of PCAPs (Packet Captures). Detects total 
number of Alarm-worthy scan protocols and prints them incrementally as
found. NOTE: THIS ALARM IS NOT A DEFENSE MECHANISM AGAINST ANY KIND OF SCAN. 
CLOSE UNUSED PORTS OR INSTALL AN ADAPTIVE FIREWALL TO PROTECT AGAINST UNWANTED 
PORT SCANNING. 

Usage: python alarm.py -i [interface] -r [pcap] -h [help]

Author: Roger A. Burtonpatel, 6/22/2021
CHANGELOG: See README
"""


import base64
import sys
from scapy.all import *
import argparse

total_alerts = 0

def packetcallback(packet):
    global total_alerts
    try:


        ## Analyzes for FIN scan
        if packet.haslayer(TCP):
            if packet[TCP].flags == 'F':    
                total_alerts += 1
                print("\nALERT #" + str(total_alerts) + 
                ": FIN scan is detected from " + packet.src + " (TCP)!")

        ## Analyzes for XMAS Tree scan (Ming's Favorite!)
        if packet[TCP].flags == "FPU":    
            total_alerts += 1
            print("\nALERT #" + str(total_alerts) + 
            ": XMAS scan is detected from " + packet.src + " (TCP)!")
    

            ## Depreciated testing code provided by Ming Chow. 
            ## Included for documentation. 

            # if "S" in packet["TCP"].flags:
            #     print("TCP SYN FLAG detected in packet from 
            #            IP address %s" %(packet[IP].src))
        
            # if packet[TCP].dport == 80:
            #     total_alerts += 1 # Missing total_alerts++
            #     print("ALERT #" + str(total_alerts) + 
            #           ": HTTP (web) traffic detected!")


        ## Analyzes for NULL scan
        if packet[TCP].flags == "":    
            total_alerts += 1
            print("\nALERT #" + str(total_alerts) + 
            ": NULL scan is detected from " + packet.src + " (TCP)!")

        ## Analyzes for Nikto scan
        Nikto_name_list = ['Nikto', 'NIKTO', 'nikto']
        found_nikto = any(ele in str(packet) for ele in Nikto_name_list)
        if found_nikto:
            total_alerts += 1
            print("\nALERT #" + str(total_alerts) + 
            ": NIKTO scan is detected from " + packet.src + " (TCP)!")


        ## Thanks for this tip, Ming!         
        payload = packet[TCP].load.decode("ascii").strip()

        ## Steve helped me out with this code. 
        ## Scans for usernames and passwords sent encoded { not encrypted :) } 
        ## in base64 via HTTP. If found, decodes and prints them. 
        if (packet.haslayer(TCP) and packet[TCP].dport == 80 
                                    and packet.haslayer(Raw)):
            if "Authorization: Basic" in payload:
                total_alerts += 1
                base64_encoded = payload.split("Authorization: "
                                               "Basic ")[1].split()[0]
                base64_decoded = str(base64.b64decode(base64_encoded))
                base64_decoded = base64_decoded[1:]
                base64decoded = base64_decoded.strip("'").split(":")
                username = base64decoded[0]
                password = base64decoded[1]
                print("\nALERT #" + str(total_alerts) + 
                ": Username and password sent in-the-clear" 
                    "(in Base64 via HTTP) (Username: " + 
                    username + ", password: " + password + ")")
        
        ## Scans for usernames and passwords sent insecurely over IMAP. 
        ## Prints them. 
        if (packet.haslayer(TCP) and packet[TCP].dport == 143 
                                    and packet.haslayer(Raw)):
            if "LOGIN" in payload and "@" in payload:
                total_alerts += 1
                username = payload.split("LOGIN ")[1].split(" ")[0]
                password = payload.split('"')[1].split('"')[0]
                print("\nALERT #" + str(total_alerts) + 
                ": Username and password sent in-the-clear (IMAP)" 
                    "(Username: " + username + ", password: " + password + ")")

        ## Searches for usernames and passwords sent insecurely over FTP. 
        ## Prints them. 
        ## Implementation note: USER and PASS separated since they can be many 
        ## packets apart in an actual scan. 
        if (packet.haslayer(TCP) and packet.haslayer(Raw) 
                            and packet[TCP].dport == 21):
            if "USER" in payload:
                total_alerts += 1
                payload_username = payload
                username = payload_username.split("USER ")[1].split()[0]
                print("\nALERT #" + str(total_alerts) + 
                ": Username sent in-the-clear (FTP) (" + username + ")")
            
            if "PASS" in payload:
                total_alerts += 1
                payload_password = payload
                password = payload_password.split("PASS ")[1].split()[0]
                print("\nALERT #" + str(total_alerts) + 
                ": Password sent in-the-clear (FTP) (" + password + ")")

        ## Detects someone attempting an RDP  
        if packet[TCP].sport == 3389:
            total_alerts += 1
            print("\nALERT #" + str(total_alerts) 
            + ": Someone scanning for Remote Desktop Protocol (RDP)!")

    except Exception as e:
        pass

## Parses arguments. -i for network interface, 
## -r for pcap file, 
## -h for help. 
parser = argparse.ArgumentParser(description='A network sniffer that' 
                                     ' identifies basic vulnerabilities')
parser.add_argument('-i', dest='interface', help='Network interface'
                    + 'to sniff on', default='eth0')
parser.add_argument('-r', dest='pcapfile', help='A PCAP file to read')
args = parser.parse_args()
if args.pcapfile:
    try:
        print("Reading" 
             " PCAP file %(filename)s..." % {"filename" : args.pcapfile})
        sniff(offline=args.pcapfile, prn=packetcallback)        
    except:
        print("Sorry, something went wrong reading"
            " PCAP file %(filename)s!" % {"filename" : args.pcapfile})
else:
    print("Sniffing on %(interface)s... " % {"interface" : args.interface})
    try:
        sniff(iface=args.interface, prn=packetcallback)
    except:
        print("Sorry, can\'t read network traffic. Are you root?")
