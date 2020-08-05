---
layout: post
permalink: /posts/thm/boiler-ctf
title: "THM: Boiler CTF"
date: 2020-08-05 20:18
tags: CTF recon privilege_escalate bases joomla_cms
description: "This time I'm going to do a write-up on Boiler CTF. This is an intermediate CTF challenge. This room is written by MrSeth6797."
---

![titlecard](/assets/images/THM/2020-08-05-boiler-ctf/1.png)

[Link: https://tryhackme.com/room/boilerctf2](https://tryhackme.com/room/boilerctf2)

Another day, another adventure on the CTF challenge. This time I'm going to do a write-up on Boiler CTF. This is an intermediate CTF challenge. This room is written by MrSeth6797 who also a creator for the simple CTF challenge. Without further ado, let's jump into the rabbit-hole. 

## Task 1: Enumerate, enumerate and enumerate.

As the title said, Enumerate is the key to this challenge. Not only that, but it also serves as an important aspect in all sort of CTF challenge and pentesting. This task requires the challenger to collect any available information on the machine.

First and foremost, fire up your nmap with the following command.

```
nmap -Pn -A -v <MACHINE IP>
```

By using nmap scanner, you will discover 3 open ports namely **FTP (Port 21)**, **HTTP (Port 80)** and **Webmin (Port 10000)**. Let's move on to task 1-1.

### Task 1-1: Ghost file

Let's investigate the FTP for any anonymous file (anon file). 

![FTP](/assets/images/THM/2020-08-05-boiler-ctf/3.png)

Look like the FTP server is empty or is it? I continue to open the FTP server using Filezilla with hidden option enable.

![filezilla](/assets/images/THM/2020-08-05-boiler-ctf/2.png)

Input the IP address and port number (Username and password are not required, it is anon after all).

![hidden file](/assets/images/THM/2020-08-05-boiler-ctf/4.png)

We get a hidden file named .info.txt. Open the file up and you will get a ciphered text.

![hidden text](/assets/images/THM/2020-08-05-boiler-ctf/5.png)

Look like a Ceaser cipher + 13 or ROT 13. Decipher the text will give you the following result

![ROT13](/assets/images/THM/2020-08-05-boiler-ctf/6.png)

This is the opening hint given by the author. "Enumeration is the key".

### Task 1-2: What is on the highest port?

Just like the same old Mrseth, like to put something in the higher port number. This time we going to make a full port scan using the following command.

```
nmap -p- <MACHINE IP>
```

![nmap](/assets/images/THM/2020-08-05-boiler-ctf/7.png)

That's it, an open port can be found on 55007. Let's continue the specific scan using the following command to make sure what is inside the port.

![nmap deep scan](/assets/images/THM/2020-08-05-boiler-ctf/8.png)

Bingo! Port 55007 is reserved for ssh. Let me repeat the moral of the story again. Assign a common service to a higher number, so that those noobs will never find it out.

### Task 1-3: What is running on port 10000?

This is a straight forward answer. 

![port 10000](/assets/images/THM/2020-08-05-boiler-ctf/9.png)

### Task 1-4: can you exploit port 10000

After searching from google, none of the exploits can be applied to the port. This is because the Webmin is in the latest version (as for 23/8/2019). Moral of the story, always keeps your application up-to-date unless there is 0-day exploitation.

![webmin](/assets/images/THM/2020-08-05-boiler-ctf/10.png)

### Task 1-5: What is the CMS on port 80

Port 80? Time to fire up the gobuster to look for a suspicious directory.

```
gobuster dir -u <MACHINE IP> -w /usr/share/dirb/wordlists/common.txt
```

![gobuster](/assets/images/THM/2020-08-05-boiler-ctf/11.png)

We get Joomla CMS.

### Task 1-6: More enumeration

From this onward, you need to enumerate the Joomla server real hard. Don't worry if you getting trolled. Learning is a path of life process.

This is the first time I trolled so hard by a CTF challenge. Thanks to Mrseth who provide me some hints. The hints are, enumerate the Joomla directory with gobuster. Use the following command and dictionary.

```
gobuster dir -u 10.10.79.97/joomla/_files -w /usr/share/dirb/wordlists/common.txt
```

After that, investigate the directory one by one and eventually, you will find something different. Which directory is different than the others? The '_test'.

![test](/assets/images/THM/2020-08-05-boiler-ctf/12.png)

sar2html? what the freak is that and how we going to exploit it. After doing some googling, I got the answer below.

![sar2html](/assets/images/THM/2020-08-05-boiler-ctf/13.png)

This few sentences are very useful. This is a URL injection (kind of). Go to the sar2html page and enter the following URL and click on select host option.

```
http://<MACHINE IP>/joomla/_test/index.php?plot=;ls
```

![vuln](/assets/images/THM/2020-08-05-boiler-ctf/14.png)

What did you see? The URL is now your shell for the server but it ain't a root. The file we interested here is log.txt. To read the log file, you need the following URL

```
http://<MACHINE IP>/joomla/_test/index.php?plot=;cat log.txt
```

![vuln 2](/assets/images/THM/2020-08-05-boiler-ctf/15.png)

You get a login credential where the username and password are 'basterd' and 'superduperp@$$'. How we apply this credential to? Still, remember the ssh port like the log said. Give it a try!

## Task 2: Exploit

After the enumeration, time to exploit the machine. From this point, I assume you have successfully logged into the basterd's ssh shell.

### Task 2-1: Where is Stoner's password?

We know that there are other users called stoner and we need the ssh password. Notice that there is only one script file inside basterd's folder. Instead of running the script, read the script file.

![shell](/assets/images/THM/2020-08-05-boiler-ctf/16.png)

![stoner](/assets/images/THM/2020-08-05-boiler-ctf/17.png)

You will notice a line of phrase. That is the password for Stoner, **superduperp@$$no1knows**. Login into stoner with the password using ssh.

### Task 2-2: Capture Stoner's flag

Capturing this flag is a bit tricky where stoner folder is totally empty. Or is it? 

![stoner text](/assets/images/THM/2020-08-05-boiler-ctf/18.png)

Well, I don't think so. This flag actually a hidden with named .secret. Always check with the hidden file.

### Task 2-3: Privilege escalate 

Time for the final boss of the challenge. How are you gonna root the machine? Sudo -l? Neh, Mrseth will never repeat the same mistake.

![sudo](/assets/images/THM/2020-08-05-boiler-ctf/19.png)

This time, I'm going to do some searching on the [GTFObins with shell attribute](https://gtfobins.github.io/#+shell), the [find command](https://gtfobins.github.io/#+shell) looks promising. create a sample file inside stoner directory and run the search with the following command.

```
find sample -exec whoami \;
```

![root](/assets/images/THM/2020-08-05-boiler-ctf/20.png)

Congratulation, the machine is now rooted !!

### Task 2-4: The final flag

Input the following command and capture the final flag

```
find sample -exec cat /root/root.txt \;
```

![root.txt](/assets/images/THM/2020-08-05-boiler-ctf/21.png)

## Conclusion

That's all for the boiler CTF write-up. Before I end this post, I would like to say thanks Mrseth who guide me on completing the room. Hope you learn something new and see you again!