---
layout: post
permalink: /posts/thm/cc-pen-testing
title: "THM write-up: CC Pen Testing"
date: 2020-08-15 10:48
tags: tryhackme CTF recon cracking privilege_escalate
description: "Welcome to a short THM CTF writeup. Today, we are going to go through the final task of the pentest crash course. This room created by our lovely para."
---

![titlecard](/assets/images/THM/2020-08-15-cc-pen-testing/1.png)

[Link: https://tryhackme.com/room/ccpentesting](https://tryhackme.com/room/ccpentesting)

Greeting again, welcome to another short THM CTF write-up. Today, we are going to go through the final task of the pentest crash course. This room created by our lovely para.  As for other tasks, you have to read the manual page. Without further ado, let's get started

## Part 1: Enumerate the machine

First off, start the Nmap scanner with the following command.

```
nmap -A -v <machine IP>
```

![nmap](/assets/images/THM/2020-08-15-cc-pen-testing/2.png)

We have two open ports on the target machine, specifically Port 80 (HTTP) and Port 22 (SSH)

## Part 2: Brute-forcing port 80

![web](/assets/images/THM/2020-08-15-cc-pen-testing/3.png)

We have an ordinary Apache page on the port 80. Guess we have to brute-force the webserver with gobuster.

```
gobuster dir -u <Target IP> -w /usr/share/dirb/wordlists/common.txt
```

![gobuster](/assets/images/THM/2020-08-15-cc-pen-testing/4.png)

We found a hidden directory inside the webserver. Visit the directory result on the following page.

![hidden](/assets/images/THM/2020-08-15-cc-pen-testing/5.png)

A blank page? Well, that is unusual. Actually there is a file hidden inside the /secret directory. We have to search for the file by using the gobuster with -x option.

```
gobuster dir -u http://<Target IP>/secret -w /usr/share/dirb/wordlists/common.txt -x txt
```

![secret](/assets/images/THM/2020-08-15-cc-pen-testing/6.png)

Bingo, we found a secret.txt hidden inside a secret directory. Read the file.

![nyan](/assets/images/THM/2020-08-15-cc-pen-testing/7.png)

We have a username nyan and an sha1 hashed password.

## Part 3: Crack the hash

To crack the hash, simply punch in the following command (for VM)

```
hashcat -a 0 -m 100 046385855FC9580393853D8E81F240B66FE9A7B8 /usr/share/wordlists/rockyou.txt --force
```

![hashcat](/assets/images/THM/2020-08-15-cc-pen-testing/8.png)

With both username and password, we are able to login to the SSH shell.

## Part 4: Privilege escalate

First and foremost, let's capture user flag.

![user](/assets/images/THM/2020-08-15-cc-pen-testing/9.png)

This is the famous phrase used by para. How cute~~~

As for the privsec, simply type in the following command to check our privilege as sudo.

```
sudo -l
```

![sudo](/assets/images/THM/2020-08-15-cc-pen-testing/10.png)

Cool, we can be a superuser.

```
sudo su
```

![su](/assets/images/THM/2020-08-15-cc-pen-testing/11.png)

Ta-da, easy point.

## Conclusion

That's all for the quick and simple CTF write up for the pentest crash course. Hope you like it ;)
