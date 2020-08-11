---
layout: post
permalink: /posts/thm/knockknock
title: "THM write-up: KnockKnock"
date: 2020-08-11 10:26
tags: tryhackme CTF recon privilege_escalate port_knocking wireshark
description: "Hello there, welcome to another tryhackme CTF writeup. Today, I going to show you something special which is port knocking."
---

![titlecard](/assets/images/THM/2020-08-11-knockknock/1.png)

[Link:https://tryhackme.com/room/knockknock](https://tryhackme.com/room/knockknock)

Note: The room has been discontinued

Hello there, welcome to another tryhackme CTF writeup. Today, I going to show you something special which is port knocking. Well, this is my first encounter on this privsec technique and I am amused. Basically, [port knocking](https://en.wikipedia.org/wiki/Port_knocking) is a method to access a hidden port by attempting a correct connection sequence. In short, you need to knock the correct port in order to access a hidden port. Interesting huh? I can't wait to tell you the story, let's start the walkthrough.

## Task 1: Capture the flag

Your task is to capture the flag.

### Task 1-1/1-2: The webpage and the packet file

First and foremost, fire up your Nmap scanner with the following command.

```
nmap -Pn -p- -A -v <Machine IP>
```

Oh, there are only one port open publically inside the machine which is port 80 (HTTP).

![page](/assets/images/THM/2020-08-11-knockknock/2.png)

Look like a pcap file download link. Guess I have to open the packet file using the Wireshark.

### Task 1-3: The last knocked port

We have to find the user role based on the packet file.

![wireshark](/assets/images/THM/2020-08-11-knockknock/3.png)

By referring to the ping result, one can conclude that **IP: 192.168.56.102** is the client while **IP: 192.168.56.101** is the server. So now, we are only interested in how the client knocks the server. Let filter out the result with TCP port only.

![wireshark sequence](/assets/images/THM/2020-08-11-knockknock/4.png)

Look like the client knock the port in the following sequence: 7000, 8000, 9000, 7000, 8000, 9000, 8888. Bear in mind that, the last port might be port access by the user. This made the sequence of  7000, 8000, 9000, 7000, 8000, 9000. Before you made a knock, made sure you download the [knock script](https://github.com/grongor/knock). If you are done, punch in the following command to reveal a secret message.

```
./knock <machine IP> 7000 8000 9000 7000 8000 9000 && telnet 10.10.144.55 8888
```

### Task 1-4: The first hidden directory

![knock](/assets/images/THM/2020-08-11-knockknock/5.png)

After that, the terminal reveals a secret directory.

### Task 1-5: Locate the second packet file

Visiting the secret directory reveal another message with a download link

![more page](/assets/images/THM/2020-08-11-knockknock/6.png)

Download the packet file and open up with the Wireshark

![more wireshark](/assets/images/THM/2020-08-11-knockknock/7.png)

This time, the packet look quite messy when compared to the first one. A port knocks usually one packet of request, response and then request, response until it stops. However, we have two response from the server (Port 8080) at the same time with a size of over 2000 bytes. Let's take a look.

![check pcap](/assets/images/THM/2020-08-11-knockknock/8.png)

The packet contains a readable ASCII character, Look like an ASCII image. In order to further our investigation, we can follow the TCP stream by right click the packet.

![follow stream](/assets/images/THM/2020-08-11-knockknock/9.png)

![1337](/assets/images/THM/2020-08-11-knockknock/10.png)

A hidden message? It is written in the German language which translated as one three three seven or 1337. Knocking port 1337 only? Not going to work. How about Port 1 3 3 7 and telnet port 1337.

### Task 1-6: The second directory

![1 3 3 7](/assets/images/THM/2020-08-11-knockknock/11.png)

Well, it just works and we got the second hidden directory.

### Task 1-7: Another message

![more pagesss](/assets/images/THM/2020-08-11-knockknock/12.png)

Look like a base64 encoded message. Let's decode it.

![another port knock](/assets/images/THM/2020-08-11-knockknock/13.png)

Another port knocking sequence. This time, we are going to open an SSH shell instead of telnet. Punch in the following command.

```
./knock <Machine IP> 8888 9999 7777 6666 && ssh <Machine IP>
```

### Task 1-8: Who inside the Machine

![SSH cred](/assets/images/THM/2020-08-11-knockknock/14.png)

An SSH shell with butthead's login credential. Great!.

### Task 1-9: SSH problem

Without further ado, let's login into butthead's SSH shell.

![SSH failed](/assets/images/THM/2020-08-11-knockknock/15.png)

Uh-oh, the shell instantly closed after we logged in. After a short internet searching and researching, I come across this [help forum](https://superuser.com/questions/589547/log-in-with-different-shell-when-original-shell-is-broken). We can force open a /bin/sh in SSH using the following command.

```
ssh butthead@<Machine IP> /bin/sh
```

![SSH](/assets/images/THM/2020-08-11-knockknock/16.png)

Yes, we are now able to access the shell. But before that, let's [spawn a shell](https://netsec.ws/?p=337) using the python cause we might need the TTY shell.

```
python -c 'import pty; pty.spawn("/bin/sh")'
```

### Task 1-10: Privilege escalate

I had tried the sudo -l, the GTFObin, crontabs, and none of them work. How about the infamous [overlayfs exploit](https://www.exploit-db.com/exploits/37292) ? We need to check the kernel version just to be sure.

![uname](/assets/images/THM/2020-08-11-knockknock/17.png)

Great, the machine is vulnerable to overlayfs exploitation. I'm going to cut this short and you can visit [my previous writeup on the overlayfs](/posts/thm/goldeneye) exploitation. From this point onward, I assumed you have the C script inside your tmp directory. Compile the script and launch it.

![root](/assets/images/THM/2020-08-11-knockknock/18.png)

Congratulation, you are now rooted in the machine. Let's capture the root flag.

## Conclusion

That's it, a short and simple CTF challenge. Hope you enjoy the write-up. Once again, see you another time ;).
