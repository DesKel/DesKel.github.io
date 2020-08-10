---
layout: post
permalink: /posts/thm/pickle-rick
title: "THM write-up: Pickle Rick"
date: 2020-08-10 21:22
tags: tryhackme CTF recon dirbuster command_injection
description: "Today, we are going through the Rick and Morty inspired CTF room. This room is called pickle rickkkkkkkkk"
---

![titlecard](/assets/images/THM/2020-08-10-pickle-rick/1.png)

[Link: https://tryhackme.com/room/picklerick](https://tryhackme.com/room/picklerick)

Greeting there, it is time for another tryhackme CTF write-up. Today, we are going through the Rick and Morty inspired CTF room. This room is called pickle rickkkkkkkkkkkkkkkk. Interesting huh. This is one of the easiest challenges on the site. Without further ado, let's get into the challenge.

## Task 1: The three-ingredient

We need to find the three secret ingredients in order to turn Rick back to his old self. Rick mentioned something on the webserver. Let's enumerate the machine by using Nmap scanner.

```
nmap -Pn -Sv -A -v <Machine IP>
```

![nmap](/assets/images/THM/2020-08-10-pickle-rick/2.png)

Well, we have 2 ports available on the machine. Specifically, Port 80 (HTTP) and Port 22 (SSH). Since we are not sure the login credential for port 22, guesses port 80 is the only way in.

![http](/assets/images/THM/2020-08-10-pickle-rick/3.png)

Look like a message from Rick. The three secret ingredients are inside Rick's computer. I have to get it. Before that, let's check with the source code for more information.

![source code](/assets/images/THM/2020-08-10-pickle-rick/4.png)

We have the username now. How about the password? Time to use the gobuster.

```
gobuster dir -u <Machine IP> -w /usr/share/dirb/wordlists/common.txt
```

![gobuster](/assets/images/THM/2020-08-10-pickle-rick/5.png)

We got robots.txt file inside the webserver. Gonna check it out.

![robots](/assets/images/THM/2020-08-10-pickle-rick/6.png)

Wubbalubbadubdub? Probably a password. Since we have the username and password, let's try to log into the SSH.

![SSH denied](/assets/images/THM/2020-08-10-pickle-rick/7.png)

WHAT! denied! Huh........ gonna find another way in. While inspecting the /assets file, I come across another three image files.

![images](/assets/images/THM/2020-08-10-pickle-rick/8.png)

We can't extract a single piece of information inside the image files. What else we can do? Where are these images file used to? Maybe we overlook something. Let's enumerate the webserver using dirbuster.

![dirbuster](/assets/images/THM/2020-08-10-pickle-rick/9.png)

Yup, we just missed the portal.php files. Time to visit the portal site.

![portal](/assets/images/THM/2020-08-10-pickle-rick/10.png)

The portal site has been resolved into a login page. How about trying the login credential we found it earlier (user: R1ckRul3s, pass: Wubbalubbadubdub)?

![panel](/assets/images/THM/2020-08-10-pickle-rick/11.png)

A command page? That is amazing! How about listing the files and directory?

![list file](/assets/images/THM/2020-08-10-pickle-rick/12.png)

We got the first secret ingredient file. Let's read it using cat command.

![no](/assets/images/THM/2020-08-10-pickle-rick/13.png)

Noooooooo! The command was disabled by Rick. How about a reverse shell using netcat?

![reverse](/assets/images/THM/2020-08-10-pickle-rick/14.png)

![terminate](/assets/images/THM/2020-08-10-pickle-rick/15.png)

We are instantly terminated! How about the alternative command to read the file, **less**.

### Task 1-1: First ingredient

![secret 1](/assets/images/THM/2020-08-10-pickle-rick/16.png)

Ah, found you.

### Task 1-2: Second ingredient

Let's find what is inside the clue.txt.

![location](/assets/images/THM/2020-08-10-pickle-rick/17.png)

There is another ingredient file hidden inside the file system. There might be another user inside the system.

![location found](/assets/images/THM/2020-08-10-pickle-rick/18.png)

The second ingredient is inside the rick's directory.

![secret 2](/assets/images/THM/2020-08-10-pickle-rick/19.png)

### Task 1-3: Third ingredient

I guess the next ingredient locate at /root directory. Before we make a visit to the directory, let see what we can do for the sudo command.

![sudo](/assets/images/THM/2020-08-10-pickle-rick/20.png)

Cool, we can do everything using the sudo command. Let see what is inside the /root directory.

![root](/assets/images/THM/2020-08-10-pickle-rick/21.png)

Yes, the third ingredient is inside the root directory.

![flag](/assets/images/THM/2020-08-10-pickle-rick/22.png)

We are now gathering all 3 ingredients. Time to make the potion.

![rick back](/assets/images/THM/2020-08-10-pickle-rick/23.gif)

Now Rick is back to himself. Yeah!

## Conclusion

That's all for the Rick and Morty CTF adventure. See you next time ;).
