ip命令配置路由example：
- **ip -6 rule**
查看所有的路由表
```
127|generic_x86_64:/ $ ip -6 route            
generic_x86_64:/ $ ip -6 rule
0:	from all lookup local 
10000:	from all fwmark 0xc0000/0xd0000 lookup legacy_system 
10500:	from all oif eth0 uidrange 0-0 lookup eth0 
13000:	from all fwmark 0x10063/0x1ffff lookup local_network 
13000:	from all fwmark 0x10064/0x1ffff lookup eth0 
14000:	from all oif eth0 lookup eth0 
15000:	from all fwmark 0x0/0x10000 lookup legacy_system 
16000:	from all fwmark 0x0/0x10000 lookup legacy_network 
17000:	from all fwmark 0x0/0x10000 lookup local_network 
19000:	from all fwmark 0x64/0x1ffff lookup eth0 
22000:	from all fwmark 0x0/0xffff lookup eth0 
23000:	from all fwmark 0x0/0xffff uidrange 0-0 lookup main 
32000:	from all unreachable
```

- ** ip -6 route show/list table  ... **
查看某个路由表里面的配置详情
```
ip -6 route list table local
ip -6 route show table wlan0
```
- **ip -6 route add ... **
```
ip -6 route add default dev usb0 table local
```
```
ip -6 route add default dev usb0 table wlan0
ip -6 route add default dev usb0 table main

ip -6 rule add from fe80::/64 pref 50 fwmark all table 2
ip -6 route add default dev usb0 table 2

ip -6 rule add from all fwmark usb0 table 2 prio 50
ip -6 route add default dev usb0 table 2
```
```
(1)
ip -6 route add default dev usb0 table local
(2)
ip -6 rule add from all pref 1000 table 2
ip -6 route add default dev usb0 table 2
(3)
ip -6 rule add from %s/%d table 1 pref 100
ip -6 route add default dev usb0 table 1
ip -6 route add default dev usb0 table wlan0
```
