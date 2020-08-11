---
layout: post
permalink: /posts/thm/you-cant-solve-this
title: "THM write-up: You Can't Solve This"
date: 2020-08-11 9:53
tags: tryhackme CTF recon linux troll
description: "Another tryhackme CTF write-up. Today we are going for a CBBC themed challenge which is specially created for children ages 9 -12 years old."
---

![titlecard](/assets/images/THM/2020-08-11-you-cant-solve-this/1.png)

[Link: https://tryhackme.com/room/youcantsolvethis](https://tryhackme.com/room/youcantsolvethis)

Another day, another tryhackme CTF write-up. Today we are going for a CBBC themed challenge which is specially created for children ages 9 -12 years old. If you can't solve it, you are worst than 9 years old kids. I'm Just kidding. The challenge is really easy providing you knowing how a Linux system work. Also, this room is designed to infuriate the challenger. Contrary, I found this room quite funny and interesting instead of getting humiliated. Without further ado, let's begin the walkthrough.

## Task 1: Capture the flags

There are a total of 8 flags hidden inside the machine given that the flags are not in proper orders. For the sake of simplicity, we are going to find the flag according to the task order.

### Task 1-1: The first flag

Launch your Nmap scanner with the following command.

```
nmap -Pn -p- -A -v <Machine IP>
```

![nmap](/assets/images/THM/2020-08-11-you-cant-solve-this/2.png)

There are two open ports available in the machine which is Port 22 (SSH) and Port 64695 (Python simpleHTTP). Let's make a visit to the HTTP port.

![seizer](/assets/images/THM/2020-08-11-you-cant-solve-this/3.gif)

What the freak is this, I nearly got a seizure for this. Also, we can't inspect the element of the page as it keeps reload and redirect. Alright, I going to use the curl command to see what is inside the page.

```
curl http://<Machine IP>:64695
```

![curl](/assets/images/THM/2020-08-11-you-cant-solve-this/4.png)

Look like they removed the robots.txt to avoid the flag getting expose. Also, there is a list of files: wannacry.html, ssh.html, flag.html, answer.html. Let's check the file one by one, including the robots.txt

#### 1) robots.txt

![robots](/assets/images/THM/2020-08-11-you-cant-solve-this/5.png)

The robots.txt contains hex number. Maybe an ASCII?

![base16](/assets/images/THM/2020-08-11-you-cant-solve-this/6.png)

Nope, they are too clever for that.

#### 2) wannacry.html

![click](/assets/images/THM/2020-08-11-you-cant-solve-this/7.png)

Oh no, this is the infamous wannacry ransomware. Before you click it, check the page source.

![no click](/assets/images/THM/2020-08-11-you-cant-solve-this/8.png)

The link redirects to a local IP address. Better don't click it, we are not sure about the hidden PHP code inside the script even though it looks safe.

#### 3) answer.html

![answer](/assets/images/THM/2020-08-11-you-cant-solve-this/9.png)

Nothing interesting, let's move on.

#### 4) flag.html

![bitly](/assets/images/THM/2020-08-11-you-cant-solve-this/10.png)

Neh, nothing interesting either.

#### 5) ssh.html

![SSH](/assets/images/THM/2020-08-11-you-cant-solve-this/11.png)

That's it. The SSH login credential (user: iamstupid, pass: password). After that, log in to the user ssh shell using the following command.

```
ssh iamstupid@<Machine IP>
```

![flag 1](/assets/images/THM/2020-08-11-you-cant-solve-this/12.png)

After logging in, check for the flag file. This is the easiest flag in the entire challenge.

Note: Always read the python script before running it, this is all I can say. (Luckily I read the script before running it.)

### Task 1-2: The second flag

This task is a little bit tricky where the flag is 'hidden' inside a text file. A big thanks to the creator of this room, user Brandon who provide the hint. Before we moving on, I need you to take a look at [this article](https://medium.com/@stdout_/accessing-ntfs-extended-attributes-from-linux-f79552947981) and [this](https://www.tutorialspoint.com/unix_commands/getfattr.htm). It is about extended attributes of the filesystem. [Extended file attributes](https://en.wikipedia.org/wiki/Extended_file_attributes) are somehow similar to the metadata of an image file. If you fully understand what is going on, let's capture the second flag.

For your information, the flag is 'hidden' inside the cool_story_bro.txt (within the coolFolder). The problem is, you can't read the text file. This is because the permission level is 000. No one includes the root user will get permission denied while accessing the file.

![cool story](/assets/images/THM/2020-08-11-you-cant-solve-this/13.png)

If you are an expert on the Linux file system, you should know what to do. If you are not, take a look at [this tutorial](https://www.linux.com/tutorials/understanding-linux-file-permissions/). Basically, this file is own by user 'iamstupid' or us. We can simply change the full permission with the following command.

```
chmod 777 cool_story_bro.txt
```

![not flag 2](/assets/images/THM/2020-08-11-you-cant-solve-this/14.png)

However, this is not the flag we want. It is 'hidden' inside the text file. We are going to use getfattr command to read the hidden flag.

```
getfattr -d cool_story_bro.txt
```

![flag 2](/assets/images/THM/2020-08-11-you-cant-solve-this/15.png)

You just got your second flag. (Note: Actually you don't need the chmod to solve this task, a straight getfattr command should be okay)

### Task 1-3: The third flag

The third file is hidden inside the .git folder. If you are a lazy person, just use the grep command to pull all the file contains 'flag'. However, It is better to search every file manually.

```
grep -rnw '/home/iamstupid' -e 'flag'
```

![flag 3](/assets/images/THM/2020-08-11-you-cant-solve-this/16.png)

### Task 1-4: The fourth flag

NEVER EVER MISS ANY INFORMATION YOU GOT ESPECIALLY ON THE CTF CHALLENGE. This is the only thing I can say if you struggling with finding the fourth flag. Still, remember the curl command? The flag is inside the HTML.

![flag 4](/assets/images/THM/2020-08-11-you-cant-solve-this/17.png)

### Task 1-5: The fifth flag

If you know the Linux file system pretty well, this should a piece of cake for you. The hint is "your phone number", I guess is about your ID. Where you can find your user ID? id command is one of the way but not the correct path. How about a full detail of your user ID? /etc/passwd is the location to reveal your full ID.

![flag 5](/assets/images/THM/2020-08-11-you-cant-solve-this/18.png)

That is the flag you looking for. Why flag6 instead of flag5? Well, things are not always as they seem.

Fun fact: The flag is an MD5 hash. Try to decode it.

### Task 1-6: The sixth flag

Ah, this is my favorite flag thoughtout the entire challenge. Easy but tricky. Do you read the hints? Or you just follow this write-up without trying it. Remember the task 1-4? Here the answer.

![flag6](/assets/images/THM/2020-08-11-you-cant-solve-this/19.png)

Got it?

### Task 1-7: The seventh flag

You need to look at the given hints. 6 out of 9 given letters and all in alphabetic. Somemore this is the password for the admin. Which admin? root? Neither one. It is the cbbcadmin.

![home](/assets/images/THM/2020-08-11-you-cant-solve-this/20.png)

Your task is to brute-force cbbcadmin's ssh shell using hydra. How about the wordlist? You need to create one using crunch.

```
crunch 9 9 ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz -t nY4s33@@@ -o password.lst
```

After that, brute-force cbbcadmin using the wordlist you just created.

```
hydra -t 64 -l cbbcadmin -P password.lst ssh://<Machine IP>
```

It going to take approximately 30 to 1 hour and it depends on your processor and internet connection. For THM kali machine, it takes 37 mins. (Why not give it a try)

![cbbc log](/assets/images/THM/2020-08-11-you-cant-solve-this/21.png)

We have the cbbcadmin ssh login credential. Let's capture the seventh flag.

![flag 7](/assets/images/THM/2020-08-11-you-cant-solve-this/22.png)

Flag 7 is hidden inside the python server file. Also, we can make ourself as a superuser even though root user has nothing to do with this challenge. Just for extra information.

![sudo](/assets/images/THM/2020-08-11-you-cant-solve-this/23.png)

### Task 1-8: The eight flag

This task requires the challenge to know about the Unix Philosophy where [Everything is a file](https://en.wikipedia.org/wiki/Everything_is_a_file). The everything mentioned includes directory, modem, keyboard, printer, and even processor. We have a dozen of directory inside the Machine and how are we going to get the flag? Read the hints.txt, it mentioned about bob. It either inside the user cbbcadmin or iamstupid. So, don't be lazy, you have to check every directory using getfattr. After the search, the flag is inside the anotherFolder directory from user iamstupid.

![flag 8](/assets/images/THM/2020-08-11-you-cant-solve-this/24.png)

That's it, the final flag of the challenge or perhaps.

## Conclusion

That's it, a challenge that can be both easy or hard. Hope this challenge brushes up your Linux skill. Until next time ;)
