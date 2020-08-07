---
layout: post
permalink: /posts/thm/simple-ctf
title: "THM write-up: Simple CTF"
date: 2020-08-05 18:42
tags: tryhackme CTF recon privilege_escalate sqli
description: "Hello there, welcome to another short and simple CTF challenge write-up from tryhackme. This challenge involved with CVE number which is realistic."
---

![titlecard](/assets/images/THM/2020-08-05-simple-ctf/1.png)

[Link: https://tryhackme.com/room/easyctf](https://tryhackme.com/room/easyctf)

Hello there, welcome to another short and simple CTF challenge write-up from tryhackme. This challenge is a little bit different compared to my other write-up. It involved [CVE system](https://www.cvedetails.com/cve-help.php) or known as common vulnerabilities and exposures. CVE system provides a reference-method for publicly known information-security vulnerabilities and exposures. This made the challenge a little bit realistic. Without further ado, let's dig it up!

## Task 1: Capture the flag

You have only one task for this challenge, capture the flags.

### Task 1-1: How many open port?

This task required the user to find out the number of the open port under port number 1000. For this task, I am going to use nmap to find out the open ports.

```
nmap -p-1000 -A -v <Machine IP>
```

In case you need an explanation on the flag:
- -p-1000: Scan for first 1000 ports
- -A: OS detection, version detection and script scanning
- -v: Verbose mode

![nmap scan](/assets/images/THM/2020-08-05-simple-ctf/2.png)

2 open ports are scanned which are port 21 (FTP) and 80 (HTTP).

### Task 1-2: What is in the higher port?

This is not the end for the nmap! Let's scan something beyond port 1000 using the following command.

```
nmap -p- -v <MACHINE IP>
```

![nmap another scan](/assets/images/THM/2020-08-05-simple-ctf/3.png)

We have something on port 2222. After searching on the Internet, EthernetIP-1 service exploitation doesn't sound a lot to me. To double confirm it, I made another scan just for port 2222.

```
nmap -p 2222 -A -v <MACHINE IP>
```

![nmap port 2222](/assets/images/THM/2020-08-05-simple-ctf/4.png)

Bingo! port 2222 actually used for SSH service instead of port 22. Moral of the story, assign a famous port such as ssh to another port number. (Those noobs will never find it out!)

### Task 1-3: What CVE can be used to against the machine?

So far we know port 21 (FTP), port 80 (HTTP) and port 2222 (SSH) is the opened port. Let's investigate it one by one.

#### FTP (Port 21)

![FTP](/assets/images/THM/2020-08-05-simple-ctf/5.png)

Well, the FTP server looks empty. I guess we have to look on to another port.

#### HTTP (Port 80)

![HTTP](/assets/images/THM/2020-08-05-simple-ctf/6.png)

Port 80 shows the Apache default page. Nothing out of ordinary.

#### SSH (Port 22)

![ssh](/assets/images/THM/2020-08-05-simple-ctf/7.png)

What are the username and password for the SSH server? Guess we have to come back for this later on. Alright, We need more information to get down to the rabbit-hole!!!!!!

#### HTTP (Port 80) - revisit

I try to make another deep scan on port 80 using the following command.

```
nmap -p 80 -A -v <MACHINE IP>
```

![HTTP - revisit](/assets/images/THM/2020-08-05-simple-ctf/8.png)

We get robots.txt from the scan. Let's find it out.

![robots](/assets/images/THM/2020-08-05-simple-ctf/9.png)

Still, the robot.txt doesn't give any useful information. It just tells the search engine not to index the CUPS server (print server).  Since port 139 and 145 are not open, we can forget the SMB exploitation. What else we can do? Directory attack.

Next, fire up the gobuster with the following command.

```
gobuster dir -u 10.10.199.126 -w /usr/share/dirb/wordlists/common.txt
```

![gobuster](/assets/images/THM/2020-08-05-simple-ctf/10.png)

The "/simple" directory look interesting. Let's find out.

![simple](/assets/images/THM/2020-08-05-simple-ctf/11.png)

We get a webpage called "CMS made simple". After [googling](https://packetstormsecurity.com/files/152356/CMS-Made-Simple-SQL-Injection.html) it, this is what I get.

![CMS](/assets/images/THM/2020-08-05-simple-ctf/12.png)

Yes, it is one of the latest CVE numbers which is CVE-2019-9053 and there is a python script inside the page.

### Task 1-4: What kind of vulnerability?

Judging from the page, it is a kind of SQLi or SQL injection vulnerable.

### Task 1-5: The script

Since the script is the only hint to complete the challenge. Copy, save and launch the script with the following command

```
python CVE-2019-9053.py -u http://<MACHINE IP>/simple/ --crack -w /usr/share/dirb/wordlists/others/best110.txt 
```

![crack](/assets/images/THM/2020-08-05-simple-ctf/13.png)

I am able to obtain a username and password called 'mitch' and 'secret'. How am I going to use this credential?

### Task 1-6: The credential

Still, remember the SSH (Port 2222)? Let's give it a try.

```
ssh -p 2222 mitch@<MACHINE IP>
```

![ssh crack](/assets/images/THM/2020-08-05-simple-ctf/14.png)

Voila, breach in success!

### Task 1-7: Find mitch's flag

This task is easy, redirect to mitch's folder and capture the flag.

![mitch flag](/assets/images/THM/2020-08-05-simple-ctf/15.png)

### Task 1-8: Find another user

Well, the answer is on the previous task.

### Task 1-9: Mitch's privilege

It is time to escalate our privilege to root and how are we gonna do that? Let see what Mitch can do with Sudo

```
sudo -l
```

![sudo](/assets/images/THM/2020-08-05-simple-ctf/16.png)

Ah-ha! VIM is the bridge to reach the root. Time to launch the vim, with sudo. After that, type ':!bash' (without the quote) and enter!

![vim](/assets/images/THM/2020-08-05-simple-ctf/17.png)

Congratulation, you are now rooted in the machine.

### Task 1-10: Capture the flag

Like the title said, capture the flag and complete the task.

![root](/assets/images/THM/2020-08-05-simple-ctf/18.png)

## Conclusion

That's it, you just finished the CTF challenge. Hope you enjoy my write-up, have a nice day ;)