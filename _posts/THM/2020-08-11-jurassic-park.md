---
layout: post
permalink: /posts/thm/jurassic-park
title: "THM write-up: Jurassic Park"
date: 2020-08-11 19:46
tags: tryhackme CTF privilege_escalate sqli
description: Greeting again, I got another tryhackme walkthrough just for you. Today we are going to walk through a park, Jurassic Park. Amazing huh, let's roll the theme song then."
---

![titlecard](/assets/images/THM/2020-08-11-jurassic-park/1.png)

[Link: https://tryhackme.com/room/jurassicpark](https://tryhackme.com/room/jurassicpark)

Greeting again, I got another tryhackme walkthrough just for you. Today we are going to walk through a park, Jurassic Park. Amazing huh, let's roll the theme song then.

[theme song](https://www.youtube.com/watch?v=D8zlUUrFK-M)

Alright, enough of BS. Time to get our work done. Similar to Rick and Morty room, this Jurassic room does involve with SQL injection. I got a hard time solving this room but thanks to user Darkstar, I am able to complete this room. Let's get started, shall we?

## Task 1: Capture the flags

There are a total of 5 flags inside the machine. Can you find it?

### Task 1-1: What is the database?

First and foremost, we are going to make a port scan using Nmap scanner.

```
nmap -Pn -A -v <MAchine IP>
```

![nmap](/assets/images/THM/2020-08-11-jurassic-park/2.png)

We found 2 open ports in the Nmap result which is Port 22 (SSH) and Port 80 (Http). Let's check with port 80 first.

![web](/assets/images/THM/2020-08-11-jurassic-park/3.png)

Welcome to Jara.....ssic park? That is a fraud and I demand my money back! Okay, okay, enough of drama. Let's see what exploit we can be done for the webpage.

![package](/assets/images/THM/2020-08-11-jurassic-park/4.png)

Look like we can do something on the URL field. How about the basic SQL injection?

![nah uh](/assets/images/THM/2020-08-11-jurassic-park/5.png)

Uh-oh, we can't perform the basic SQLi. After playing around with the web server, I come across an interesting page.

![waf](/assets/images/THM/2020-08-11-jurassic-park/6.png)

Look like we still have a chance on performing the SQLi but not with the filtered character and text. This time, we are going to use UNION. For your information, A UNION SQLi exploitation requires a small brute-force on the number of columns field. After a short investigation, we can perform the attack using five columns.

![union](/assets/images/THM/2020-08-11-jurassic-park/7.png)

Get that? the second column on the package, the third column on price while the fourth column is about description and finally the fifth column showing the number of package that has been purchased. We need to pull the database by using the database() function.

![park](/assets/images/THM/2020-08-11-jurassic-park/8.png)

### Task 1-2: Number of columns

Obviously, the number of columns is 5 (refer to the previous task).

### Task 1-3: The system version

Use version() to reavel the system version.

![version](/assets/images/THM/2020-08-11-jurassic-park/9.png)

### Task 1-4: Dennis's password

The password is located at table **users** and the column name is **password**.

![password](/assets/images/THM/2020-08-11-jurassic-park/10.png)

### Task 1-5: Flag 1

Done with the SQLi? Time to capture the flags. Before that, log in to Dennis SSH shell using the password from the previous task.

![flag 1](/assets/images/THM/2020-08-11-jurassic-park/11.png)

Flag1 is located at Dennis's directory. How about flag 2?

### Task 1-6: Flag 2

Checking the .viminfo reveal flag 2 and flag 4 location.

![vim](/assets/images/THM/2020-08-11-jurassic-park/12.png)

But first, let's get the flag 2.

### Task 1-3

Reading the .bash_history reveal the flag.

![flag 3](/assets/images/THM/2020-08-11-jurassic-park/13.png)

### Task 1-4

Flag 4 is a joke, It was originally from /tmp directory. (Thanks to user Darkstar who provide the flag)

f5339ad0edbd0b0fe1262d91a475c2c4

### Task 1-5

Let's check what can we do as a sudo.

![sudo](/assets/images/THM/2020-08-11-jurassic-park/14.png)

An SCP huh. Let's check the [SCP variable in GTFObin](https://gtfobins.github.io/gtfobins/scp/).

![gtfo bin](/assets/images/THM/2020-08-11-jurassic-park/15.png)

Copy the line and escalate the privilege.

![root](/assets/images/THM/2020-08-11-jurassic-park/16.png)

Congratulation, you are noe rooted in the machine. The flag is located somewhere inside the /root directory.

## Conclusion

That's all for the Jurassic park CTF challenge. hope you enjoy the write-up. Until next time :)
