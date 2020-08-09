---
layout: post
permalink: /posts/thm/ultratech
title: "THM write-up: UltraTech"
date: 2020-08-08 14:27
tags: tryhackme CTF recon privilege_escalate docker
description: "Another day, another tryhackme CTF write-up. Today, we are going to an intermediate level CTF challenge called UltraTech."
---

![titlecard](/assets/images/THM/2020-08-09-ultratech/1.png)

[Link: https://tryhackme.com/room/ultratech1](https://tryhackme.com/room/ultratech1)

Another day, another tryhackme CTF write-up. Today, we are going to an intermediate level CTF challenge called UltraTech. This room is created by user lp1. In my opinion, this challenge is much simpler compared to the other intermediate-level challenge providing you are not overthinking. It took me less than 20 min on breaking into user shell but 4 hours on privilege escalation because of 'overthinking'. Alright, let's get it on.

## Task 1: About the machine

Based on user lp1, this machine is inspired by the real-life vulnerability. The big hint on this challenge is 'keep enumerating if you stuck'. Keep in mind that enumerating is the way to solve this challenge.

## Task 2: Enumeration phase

### Task 2-1: identify port 8081

As usual, fire up you Nmap with the following command line.

```
nmap -Pn -A -v <Machine IP>
```

![nmap](/assets/images/THM/2020-08-09-ultratech/2.png)

There are 3 open ports available on the machine, specifically Port 21 (FTP), Port 22 (SSH) and  Port 8081 (Node.js). We just get our answer for task 2-1.

### Task 2-2, 2-3, 2-4, 2-5: Enumerate non-standard port

Let make a visit on some of this port

#### 1) FTP

![FTP](/assets/images/THM/2020-08-09-ultratech/3.png)

A credential is needed for FTP. Guess we have to skip it.

#### 2) SSH

We have no clue on the login credentials. Skip it!

#### 3) Node.js

![nodeJS](/assets/images/THM/2020-08-09-ultratech/4.png)

Visiting port 8081 greet us with a message. Maybe we can perform a directory attack using gobuster.

![gobuster](/assets/images/THM/2020-08-09-ultratech/5.png)

Look like we found something on gobuster.

![auth](/assets/images/THM/2020-08-09-ultratech/6.png)

We got bad news. The /auth requires a login credential too and we are stuck now. Still, remember the 'big hint'? How about performing another scan using Nmap scanner? This time, we are going to scan the entire ports from 0 to 65535 using the following command.

```
nmap -Pn -p- -v -A <Machine IP>
```

![more nmap](/assets/images/THM/2020-08-09-ultratech/7.png)

Looks like we overlook port 31331 which is an Apache server port. The number of the route used by the web application is 2 and I will explain that in the following task.

## Task 3: Exploitation phase

### Task 3-1: Obtain the database

![page](/assets/images/THM/2020-08-09-ultratech/8.png)

Visiting port 31331 leave us a stunning web page, UltraTech. If you try to perform the directory attack, a robots.txt can be found within the sever.

![robots](/assets/images/THM/2020-08-09-ultratech/9.png)

A sitemap Inside the robots.txt file? Let's check it out.

![sitemap](/assets/images/THM/2020-08-09-ultratech/10.png)

The partners.html looks suspicious.

![login](/assets/images/THM/2020-08-09-ultratech/11.png)

We managed to find a private login page. Now what? SQL injection? Nay, that didn't work. Let's see how the login page works.

![form](/assets/images/THM/2020-08-09-ultratech/12.png)

The form didn't redirect to any page, that is weird. But the js/api.js javascript file does look suspicious to me. How about we take a look?

![js](/assets/images/THM/2020-08-09-ultratech/13.png)

This is it, the api.js somehow connected to port 8081. In short, the login form will redirect to /auth which we discovered before. In addition, we have a /ping?=ip GET request. This file answers the previous task (Task 2-5). The two routes used by the webserver are /ping and /auth. Without further ado, let's check with the ping.

![ping](/assets/images/THM/2020-08-09-ultratech/14.png)

The result looks exactly like the ping command in a Linux machine. We can exploit the URL using [command injection](https://ctf101.org/web-exploitation/command-injection/what-is-command-injection/). There are several ways to perform a command injection and it depends on the filter used on the GET value. For this challenge, the URL only accepts quote special symbol.

![list file](/assets/images/THM/2020-08-09-ultratech/15.png)

### Task 3-2: Inside the database

To read the .sqlite file, simply inject the 'cat' command.

![pass](/assets/images/THM/2020-08-09-ultratech/16.png)

We are only interested in first user password hash which is own by user r00t, f357a0c52799563c7c7b76c1e7543a32.

### Task 3-3: Crack the hash

You can either crack the hash using Hashcat or online cracking tool. I have tried both method and both works for me.

#### 1) Online cracking tool

Visit this [website](https://crackstation.net/), paste your hash, solve the captcha, submit and ta-da.

![crackstation](/assets/images/THM/2020-08-09-ultratech/17.png)

#### 2) hashcat

I would prefer this method compared to the online cracking tool. This is because complicate hashes such as brycpt or hash contain salt usually can't be cracked using the online tool. Like I said before, cracking a hash is not a 100% guarantee and it all depends on what kind of password used by the user. Alright, let's start our hashcat with the following command.

```
hashcat -D 2 -m 0 f357a0c52799563c7c7b76c1e7543a32 rockyou.txt
```

If you have a problem on cracking the hash using hashcat or wanted to know more, you are always welcome to my previous write-up on ['crack the hash'](https://deskel.github.io/posts/thm/crack-the-hash).

### Task 3-4: Getting the user shell

We now have the r00t login credential. Let's try this on the partners.html.

![message](/assets/images/THM/2020-08-09-ultratech/18.png)

Well, well, well, a message delivered by lp1. By the way, there is nothing we can do here. Let's try the credential on the FTP and SSH

#### 1) FTP

![FTP login](/assets/images/THM/2020-08-09-ultratech/19.png)

Nothing inside the FTP. Let's move on

#### 2) SSH

![SSH login](/assets/images/THM/2020-08-09-ultratech/20.png)

We are now inside the r00t's SSH shell. Time to root the machine.

## Task 4: Root of all evil

Like I said in the beginning, this task took me 4 hours because of one mistake. Still, remember checking the server's configuration file? Well, that is **NOT THE RIGHT WAY** to solve this challenge. Rooting this machine is extremely easy if you know-how but definitely not checking the entire /etc/Apache2 directory. Let me go through on how I found this vulnerability inside the machine. First off, running [LinEnum](https://github.com/rebootuser/LinEnum) on this machine is the starting point. You need to get the file, put it into your own machine server and force the r00t user to download the LinEnum.sh file. You can refer to [this example](https://www.hackingarticles.in/hack-the-raven-walkthrough-ctf-challenge/) for more detail. From this point onward, I assumed you have the LinEnum.sh file inside the victim's machine. Launch the script and wait for a few seconds.

![docker](/assets/images/THM/2020-08-09-ultratech/21.png)

After checking the result, this block caught me some attention. We are a member of the docker group? The second step is to find the docker command in [GTFObins](https://gtfobins.github.io/gtfobins/docker/).

![GTFO](/assets/images/THM/2020-08-09-ultratech/22.png)

This line holds the key to escalate the privilege. Enter the following line.

```
docker run -v /:/mnt --rm -it bash chroot /mnt sh
```

After that, wait for a while and you be prompted to enter the command. Checking with 'whoami', i got the following result.

![rooted](/assets/images/THM/2020-08-09-ultratech/23.png)

Congratulation, you are now rooted in the machine. Moral of the story, do not randomly assign a user to a docker group. This is the vulnerability of the machine. We are going to capture the flag now.

![flag](/assets/images/THM/2020-08-09-ultratech/24.png)

The first 9 characters of the ssh private key are the flag for this challenge.

## Conclusion

This concludes our Ultratech vulnerability challenge by user lp1. Sometimes, the thing is simple but we tend to complicate it. Always, be the enumeration guide your way. Until next time ;)
