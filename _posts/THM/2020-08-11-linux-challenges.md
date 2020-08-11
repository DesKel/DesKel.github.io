---
layout: post
permalink: /posts/thm/linux-challenges
title: "THM write-up: Linux Challenges"
date: 2020-08-11 11:40
tags: tryhackme linux
description: "Welcome to another tryhackme CTF write-up. Today, we are going through a Linux challenge. This room is created to sharpen up your Linux skill."
---

![titlecard](/assets/images/THM/2020-08-11-linux-challenges/1.png)

[Link: https://tryhackme.com/room/linuxctf](https://tryhackme.com/room/linuxctf)

Hello there, welcome to another tryhackme CTF write-up. Today, we are going through a Linux challenge. Either you are a new or old Linux system user, this challenge is just for you. This room is created to sharpen up your Linux skill.

~~Disclaim: If you are looking for flag 25 and the RDP flag, this is not the right walkthrough for you. So far, none of the challengers are able to solve the entire challenge and I have tried my best. Maybe, just maybe in the future, I will try to reattempt the task again. ~~

Update (30/10/2019): **Flag 25 and RDP flag are officially marked as unsolvable. Basically, this is a complete walkthrough. Enjoy!**

## Task 2: Introduction

### Task 2-1: Garry's home directory

First and foremost, ssh to Garry's SSH shell using the following command.

```
ssh garry@<Machine IP>
```

![ssh](/assets/images/THM/2020-08-11-linux-challenges/2.png)

Require directory list command

```
ls
```

![list file](/assets/images/THM/2020-08-11-linux-challenges/3.png)

## Task 3: The basic

### Task 3-1: Flag 1

Require Read a file command

```
cat
```

![flag 1](/assets/images/THM/2020-08-11-linux-challenges/4.png)

### Task 3-2: Flag 2

Login to bob's SSH shell for flag 2

![flag 2](/assets/images/THM/2020-08-11-linux-challenges/5.png)

### Task 3-3: Flag 3

Use ls -la to list hidden file and directory. The flag is hidden within .bash_history.

![flag 3](/assets/images/THM/2020-08-11-linux-challenges/6.png)

### Task 3-4: Flag 4

Required user defined cornjob command

```
crontab -e
```

![flag 4](/assets/images/THM/2020-08-11-linux-challenges/7.png)

### Task 3-5: Flag 5

Flag 5 is hidden within bob directory. Use recursive search with -rnw flag

```
grep -rnw /home/bob -e 'flag5'
```

![flag 5](/assets/images/THM/2020-08-11-linux-challenges/8.png)

### Task 3-6: Flag 6

Require recursive search command

```
cat /home/flag6.txt | grep c9
```

![flag 6](/assets/images/THM/2020-08-11-linux-challenges/9.webp)

### Task 3-7: Flag 7

Require system process command

```
ps -aef
```

![flag 7](/assets/images/THM/2020-08-11-linux-challenges/10.webp)

### Task 3-8: Flag 8

Require tar decompress command

```
tar -xvzf flag8.tar.gz
```

![flag 8](/assets/images/THM/2020-08-11-linux-challenges/11.png)

### Task 3-9: Flag 9

The hosts file located at /etc/hosts

```
cat /etc/hosts
```

![flag 9](/assets/images/THM/2020-08-11-linux-challenges/12.png)

### Task 3-10: Flag 10

You can find all user at /etc/passwd

```
cat /etc/passwd
```

![flag 10](/assets/images/THM/2020-08-11-linux-challenges/13.png)

## Task 4: Linux functionality

### Task 4-1: Flag 11

The alias story within .bashrc file

```
cat .bashrc
```

![flag 11](/assets/images/THM/2020-08-11-linux-challenges/14.webp)

### Task 4-2: Flag 12

The banner usually stored at /etc/update-motd.d

```
cat /etc/update-motd.d/00-header
```

![flag 12](/assets/images/THM/2020-08-11-linux-challenges/15.png)

### Task 4-3: Flag 13

Require different command

```
diff flag13/script1 flag13/script2
```

![flag 13](/assets/images/THM/2020-08-11-linux-challenges/16.webp)

### Task 4-4: Flag 14

Log files are usually store in /var/log

```
cat /var/log/flagtourteen.txt | grep 3
```

![flag 14](/assets/images/THM/2020-08-11-linux-challenges/17.png)

### Task 4-5: Flag 15

You can find the system information at /etc/*release

```
cat /etc/*release
```

![flag 15](/assets/images/THM/2020-08-11-linux-challenges/18.png)

### Task 4-6: Flag 16

This one is a little bit tricky.

```
ls /media/f/l/a/g/1/6/is
```

![flag 16](/assets/images/THM/2020-08-11-linux-challenges/19.png)

### Task 4-7: Flag 17

Login to alice account and get the flag. (alice:TryHackMe123)

![flag 17](/assets/images/THM/2020-08-11-linux-challenges/20.png)

### Task 4-8: Flag 18

It is a hidden file. List it using ls -la command.

```
$ cat .flag18
```

![flag 18](/assets/images/THM/2020-08-11-linux-challenges/21.png)

### Task 4-9: Flag 19

To read a certain line of a text file, you need sed command

```
sed -n 2345p flag19
```

![flag 19](/assets/images/THM/2020-08-11-linux-challenges/22.png)

## Task 5: Data representation, strings and permission

### Task 5-1: Flag 20

Require base64 decoder.

```
cat flag20 | base64 --decode
```

![flag 20](/assets/images/THM/2020-08-11-linux-challenges/23.png)

## Task 5-2: Flag 21

You need less instead of cat to read the php file. The flag is inside bob directory.

```
less flag21.php
```

![flag 21](/assets/images/THM/2020-08-11-linux-challenges/24.png)

### Task 5-3: Flag 22

Require hex to ASCII converter

```
cat flag22 | xxd -r -p
```

![flag 22](/assets/images/THM/2020-08-11-linux-challenges/25.png)

### Task 5-4: Flag 23

Require a text reverse command

```
cat flag23|rev
```

![flag 23](/assets/images/THM/2020-08-11-linux-challenges/26.png)

### Task 5-5: Flag 24

To reveal readable strings, you are require strings command.

```
strings /home/garry/flag24
```

![flag 24](/assets/images/THM/2020-08-11-linux-challenges/27.png)

### Task 5-6: Flag 25

(Marked as unsolvable)

### Task 5-7: Flag 26

The find flag 26, punch in the following command

```
find / -xdev -type f -print0 2>/dev/null | xargs -0 grep -E '^[a-z0-9]{32}$' 2>/dev/null
```

![flag 26](/assets/images/THM/2020-08-11-linux-challenges/28.webp)

### Task 5-8: Flag 27

Alice has sudo permission on reading the root flag.

```
sudo cat /home/flag27
```

![flag 27](/assets/images/THM/2020-08-11-linux-challenges/29.webp)

### Task 5-9: Flag 28

Require uname comamnd

```
uname -a
```

![flag 28](/assets/images/THM/2020-08-11-linux-challenges/30.webp)

### Task 5-10: Flag 29

Follow the following step to reveal the flag. (Garry)

```
cat flag29 | tr -d ' ' >flag29_noS
cat flag29_noS | tr -d '/n' >flag29_noSN
cat flag29_noSN
```

![flag 29](/assets/images/THM/2020-08-11-linux-challenges/31.webp)

## Task 6: SQL, FTP, Groups, and RDP

### Task 6-1: Flag 30

There are two ways to solve this problem. Through the browser or the curl command. Since this is the Linux challenge, I suggested curl.

```
curl localhost
```

![flag 30](/assets/images/THM/2020-08-11-linux-challenges/32.png)

### Task 6-2: Flag 31

If you are an expert on backend web production, this should be a piece a cat for you. Firstly, log in to MySQL using the following command.

```
mysql -u root -p
```

After that enter the password. The first thing you need to do is check all the available databases.

```
mysql> SHOW DATABASES;
```

![flag 31](/assets/images/THM/2020-08-11-linux-challenges/33.png)

### Task 6-3: Flag 31_A

A bonus flag. After identifying the database, you need to list all the table.

```
mysql> USE database_2fb1cab13bf5f4d61de3555430c917f4
mysql> SHOW TABLES;
```

![flag 31 a](/assets/images/THM/2020-08-11-linux-challenges/34.png)

Look like we have a flag table inside the database. To read the content inside the table, u need to select all.

```
mysql> SELECT * FROM flags;
```

![flag 31 aa](/assets/images/THM/2020-08-11-linux-challenges/35.png)

### Task 6-4: Flag 32

Download the flag from Alice directory using Filezilla and listen to it. Easy!

### Task 6-5: Flag 33

The .profile is the correct location to store your $PATH (Bob directory)

![flag 33](/assets/images/THM/2020-08-11-linux-challenges/36.png)

### Task 6-6: Flag 34

To list the enviroment variable, you need printenv command.

```
printenv
```

![flag 34](/assets/images/THM/2020-08-11-linux-challenges/37.png)

### Task 6-7: Flag 35

getent is the answer.

```
getent group
```

![flag 35](/assets/images/THM/2020-08-11-linux-challenges/38.png)

### Task 6-8: Flag 36

The flag file is located at /etc. Who has the permission to read it?

```
id
cat /etc/flag36
```

![flag 36](/assets/images/THM/2020-08-11-linux-challenges/39.png)

Look like bob is the chosen one.

### Task 6-9: Flag 37

You need remote access to the bob desktop. Punch in the following command in your own machine.

```
rdesktop -u bob -p linuxrules
```

The answer to this task is pending. But I found an interesting backup folder called deja-dup. Perhaps that is the answer?

## Conclusion

That's all for the Linux CTF challenge. Hope you learn something today. See you again ;)

## Easter egg

This easter egg is for the [Cross-site scripting in tryhackme (XSS)](https://tryhackme.com/room/xss). This is the solution to Task 8. Just for future reference, nothing personal. If you are interested in knowing how XSS works, you can try the XSS room.

```
Task 8-1: xss"><!--><svg/onload=alert("Hello")>
Task 8-2: xss"><!--><svg/onload=prompt("Hello")>
Task 8-3: xss"><!--><svg/onload=alert(Hello)>
Task 8-4: xss"><!--><svg/onclick=alert("Hello")>
```
