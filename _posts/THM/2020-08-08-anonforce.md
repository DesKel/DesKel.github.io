---
layout: post
permalink: /posts/thm/anonforce
title: "THM write-up: Anonforce"
date: 2020-08-08 19:43
tags: tryhackme CTF recon crack 
description: "Another day, another CTF writeup from tryhackme. This is my second boot2root writeup series. The challenge is easy."
---

![titlecard](/assets/images/THM/2020-08-08-anonforce/1.png)

[Link: https://tryhackme.com/room/bsidesgtanonforce](https://tryhackme.com/room/bsidesgtanonforce)

Another day, another CTF writeup from tryhackme. This is my second boot2root writeup series. The challenge is rather easier compared to the [first boot2root](https://deskel.github.io/posts/thm/library) write-up. Less tricky and straight forward. Without further ado, let's get it on.

## Task 1: Capture the flag

As always, your task is to capture the user and the root flag.

### Task 1-1: Capture user's flag

First and foremost, launch your nmap scanner with the following command.

```
nmap -A -v <MACHINE IP>
```

In a jiff, you will be presented two open ports, specifically Port 21 (FTP) and Port 22 (SSH). Let's check the FTP port first.

![nmap FTP](/assets/images/THM/2020-08-08-anonforce/2.png)

![nmap ssh](/assets/images/THM/2020-08-08-anonforce/3.png)

![FTP](/assets/images/THM/2020-08-08-anonforce/4.png)

OMG., who the hell put the entire system folder inside the FTP. In addition, everyone can access the FTP server. Moral of the story, direct the Anon user to a specific FTP directory (not the whole system) or secure the FTP with a password. Enough of that, let's check the user flag inside the home directory.

![user flag](/assets/images/THM/2020-08-08-anonforce/5.png)

That's it, easy and straight forward.

### Task 1-3: Capture the root's flag

#### 1) The GPG

There are tons of directory yet to be discovered. After a quick search, I come across an unusual filename called 'notread'.

![GPG](/assets/images/THM/2020-08-08-anonforce/6.png)

![notread](/assets/images/THM/2020-08-08-anonforce/7.png)

Inside the 'notread' directory, we have a PGP file and a private key. Download both files into your machine and let's import the private key using the following command.

```
gpg --import private.asc
```

![PGP prompt](/assets/images/THM/2020-08-08-anonforce/8.png)

Uh-oh, guess we need a password to access the key. Maybe Mr.john can help us out, I mean John the Ripple (JtR). Without further ado, export the key into the hash and run JtR.

```
gpg2john private.asc > hash
john hash
```

![crack](/assets/images/THM/2020-08-08-anonforce/9.png)

The password for the private key is 'xbox360'. After that, input the password to import the private key.

![import](/assets/images/THM/2020-08-08-anonforce/10.png)

Then, decrypt the backup.pgp file using the following command.

```
gpg --decrypt backup.pgp
```

![prompt password](/assets/images/THM/2020-08-08-anonforce/11.png)

Once again, you will be prompt with another password field. Now, enter the 'xbox360' password into the field.

#### 2) Crack the hash

![decrypt](/assets/images/THM/2020-08-08-anonforce/12.png)

After decrypted the PGP file, a shadow file contains two users' hashed password shown on the terminal.

```
root:$6$07nYFaYf$F4VMaegmz7dKjsTukBLh6cP01iMmL7CiQDt1ycIm6a.bsOIBp0DwXVb9XI2EtULXJzBtaMZMNd2tV4uob5RVM0:18120:0:99999:7:::

melodias:$1$xDhc6S6G$IQHUW5ZtMkBQ5pUMjEQtL1:18120:0:99999:7:::
```

To identify the type of hashes, you can visit the hash [example list from hashcat](https://hashcat.net/wiki/doku.php?id=example_hashes). After performing a quick search, the hash-name for the root user is ' sha512crypt $6$, SHA512 (Unix) 2 ' while the hash-name for user melodias is ' md5crypt, MD5 (Unix), Cisco-IOS $1$ (MD5) 2 ' . Let's do the hashcat crack using the following command.

```
hashcat64.exe -D 2 -m 1800 --hwmon-disable hash/hash.txt Dict/rockyou.txt
```

I am going to use my host computer to crack the hash because of the hashcat inside the kali VMware does not support the GPU processor. You can refer to my [previous write-up on hash cracking](https://www.embeddedhacker.com/2019/09/hacking-walkthrough-cracking-the-hashes/) for more detail.

After a few seconds, you will be prompted with the cracked password which is hikari (mean light in Japanese).

![More password](/assets/images/THM/2020-08-08-anonforce/13.png)

#### 3) Capture the flag

Meanwhile, can we crack melodias's hash? Nay, we can't. A root password should be more than enough to solve this challenge. After that, log in to the root's ssh shell using the following command.

```
ssh root@<Machine IP>
```

![root](/assets/images/THM/2020-08-08-anonforce/14.png)

Congratulation, you are now rooted in the machine. Let's check for the flag.

![root flag](/assets/images/THM/2020-08-08-anonforce/15.png)

## Conclusion

That's it, we just finished our second boot2root challenge by stuxnet. Hope you learn something new today. See ya ;)