---
layout: post
permalink: /posts/thm/ha-joker-ctf
title: "THM write-up: HA Joker CTF"
date: 2020-08-13 12:45
tags: tryhackme CTF recon reverse_shell privilege_escalate password_cracking
description: "Today, we are going for the dark knight theme with Joker. This room introduced another privilege escalation technique by using the LXD."
---

![titlecard](/assets/images/THM/2020-08-13-ha-joker-ctf/1.png)

[Link: https://tryhackme.com/room/jokerctf](https://tryhackme.com/room/jokerctf)

Howdy there, welcome to another tryhackme CTF write-up. Today, we are going for the dark knight theme a.k.a batman with Joker. This room introduced another privilege escalation technique by using the LXD. If you are not sure what is LXD about, kindly check [this article](https://linuxcontainers.org/lxd/introduction/). In short, LXD is like a virtual machine but uses LXC instead. Without further ado, let kick start the machine.

## Task 1: Joker CTF

For your information, this is a simple CTF training room. It involves enumeration, hash cracking, brute-forcing, exploitation, and privilege escalation, Have fun!

### Task 1-1: Nmap enumerate

To start off with the room, we need to enumerate for open ports. Simply use the following command.

```
nmap -A -v <Machine IP>
```

![nmap](/assets/images/THM/2020-08-13-ha-joker-ctf/2.png)

We have a total of 3 ports open on the machine specifically, Port 22 (SSH), Port 80 (HTTP) and Port 8080 (HTTP). We have zero clues on the SSH port, we have to skip it.

### Task 1-2: Apache version

Refer to the Nmap result, you will notice the apache 2.4.29 is used on the machine. Nothing much we can do here. Let's move on.

### Task 1-3: Port 80

![http](/assets/images/THM/2020-08-13-ha-joker-ctf/3.png)

Nice Joker's face! Port 80 doesn't need any username and password in order to access it.

### Task 1-4: The hidden file

Alright, we have the site online, time to enumerate for the hidden files with gobuster.

```
gobuster dir -u <Machine IP> -w /usr/share/dirb/wordlists/common.txt -x txt,php,htm
```

![gobuster](/assets/images/THM/2020-08-13-ha-joker-ctf/4.png)

Look like we get a hidden file called secret.txt. Let's take a look.

![secret](/assets/images/THM/2020-08-13-ha-joker-ctf/5.png)

This is a dialog between Batman and Joker. But I have no idea what is this all about.

### Task 1-5: Hidden directory

By referring to the previous gobuster result, you will notice several hidden directories on the site.

![phpinfo](/assets/images/THM/2020-08-13-ha-joker-ctf/6.png)

Visiting the site, give us the following result.

![phpinfo page](/assets/images/THM/2020-08-13-ha-joker-ctf/7.png)

Nothing we can do here because the PHP version is quite new.

### Task 1-6 and 1-7: The user and the port

Do not forget the port 8080! There might be something interesting inside it.

![port](/assets/images/THM/2020-08-13-ha-joker-ctf/8.png)

Shoot!, the site ask for login credential. My primary guess is Joker as the username (according to the theme). We have our guessed username, time to brute-force the password.

### Task 1-8: Brute-force the HTTP basic

This time, I'm going to use xhydra instead of the hydra. Actually both are the same, xhydra is the GUI version of the hydra. Setup the configuration according to the figure below and start the attack.

![xhydra 1](/assets/images/THM/2020-08-13-ha-joker-ctf/9.png)

![xhydra 2](/assets/images/THM/2020-08-13-ha-joker-ctf/10.png)

![xhydra 3](/assets/images/THM/2020-08-13-ha-joker-ctf/11.png)

Take note that, xhydra is not always the best brute-forcing tool to use with. For example,  the HTTP-POST form might contain certain parameter instead of a username and password, you need to use hydra in CLI.

### Task 1-9: Another hidden directory

Alright, we are inside the webpage now. The favicon tells me that this is a Joomla CMS. Time for Nikto web enumeration.

```
nikto -h http://10.10.202.227:8080/ -id joker:hannah
```

![nikto](/assets/images/THM/2020-08-13-ha-joker-ctf/12.png)

The website contains robots.txt file and the /administrator/  redirect us to the admin login site.

![joomla cms](/assets/images/THM/2020-08-13-ha-joker-ctf/13.png)

Another password cracking?

### Task 1-10: The backup file

While waiting for the Nikto getting the job done, I stumbled across a zip file.

![backup](/assets/images/THM/2020-08-13-ha-joker-ctf/14.png)

Download the zip file and check it out.

![zip](/assets/images/THM/2020-08-13-ha-joker-ctf/15.png)

No good, the zip file is password protected. Ring, ring, is this Mr.John?

### Task 1-11: Crack the zip

Launch you zip2john to convert the zip file into a hash, after that call john to crack the hash.

```
zip2john backup.zip > joker.hash
```

```
john joker.hash
```

![john](/assets/images/THM/2020-08-13-ha-joker-ctf/16.png)

The password is the same as the one we get from the hydra.

### Task 1-12: Joomla super duper user

We got two folders after the extraction. The db folder caught my eye. After a quick search, the Joomla super-duper username and hashed password are inside the SQL file.

![database](/assets/images/THM/2020-08-13-ha-joker-ctf/17.png)

### Task 1-13: Joomla password

Similar to task 1-11, copy the hash into a text editor and summon Mr.john again

![joomla password](/assets/images/THM/2020-08-13-ha-joker-ctf/18.png)

### Task 1-14 to 1-16: Spawn a shell

Use the login credential we just found on the previous tasks. you will be then redirected to the Joomla admin dashboard.

![dashboard](/assets/images/THM/2020-08-13-ha-joker-ctf/19.png)

Spawning a shell is easy. Firstly, download the PHP [reverse shell](https://github.com/pentestmonkey/php-reverse-shell/blob/master/php-reverse-shell.php) script. After that locate the template.

![template](/assets/images/THM/2020-08-13-ha-joker-ctf/20.png)

Choose beez3

![beez](/assets/images/THM/2020-08-13-ha-joker-ctf/21.png)

Then, click the index.php on the left sidebar and replace it with the reverse shell

![index](/assets/images/THM/2020-08-13-ha-joker-ctf/22.png)

After that, change the IP according to your [tunnel IP](https://tryhackme.com/access) and the port. Save it.

![reverse php](/assets/images/THM/2020-08-13-ha-joker-ctf/23.png)

I'm going to use Port 4445 to listen to the incoming shell. Launch your netcat on the local terminal.

```
nc -lvnp 4445
```

Click on 'template preview'  and capture the reverse shell.

![preview](/assets/images/THM/2020-08-13-ha-joker-ctf/24.png)

![netcat reverse](/assets/images/THM/2020-08-13-ha-joker-ctf/25.png)

Simple like counting from 1 to 10. We are now a www-data with lxd GID.

### Task 1-16 to 1-17: Enumerate LXD

Make sure you read the LXD [article](https://linuxcontainers.org/lxd/introduction/) before proceeding to the escalation. If you are done, check the image ALIAS with the following command

```
lxc image list
```

![image](/assets/images/THM/2020-08-13-ha-joker-ctf/26.png)

### Task1-18 to 1-19: Capture the flag

By knowing the Alias name, it should be enough to mount the /root folder into the container and make ourself as the root user. Checking the following [article](https://www.hackingarticles.in/lxd-privilege-escalation/) gives us an idea of how to mount the /root file on /mnt.

```
lxc init myalpine joker -c security.privileged=true
lxc config device add joker mydevice disk source=/ path=/mnt/root recursive=true
lxc start joker
lxc exec ignite /bin/sh
```

![root](/assets/images/THM/2020-08-13-ha-joker-ctf/27.png)

Congratulations, you are now rooted in the machine. The root folder is located at /mnt/root/root. Locate the directory and capture our final flag.

![flag](/assets/images/THM/2020-08-13-ha-joker-ctf/28.png)

## Conclusion

That'all for the Joker room from tryhackme. Hope you learn something today, see ya ;)
