---
layout: post
permalink: /posts/thm/crack-the-hash
title: "THM write-up: Crack The Hash"
date: 2020-08-08 13:39
tags: tryhackme hash crack
description: "I will guide you on the challenge named crackthehash. This challenge is extremely easy if you are an experienced hacker/code cracker."
---

![titlecard](/assets/images/THM/2020-08-08-crack-the-hash/1.png)

[Link: https://tryhackme.com/room/crackthehash](https://tryhackme.com/room/crackthehash)

Today I was stumbled across a hacking challenge website called tryhackme. Multiple challenges can be found and each of the challenges is written by the community or individual. Feel free to sign up yourself and take part the challenges. 

Long story short, I will guide you on the challenge named crackthehash. This challenge is extremely easy if you are an experienced hacker/code cracker. The challenge consists of 9 tasks and I will explain it one by one.

## Task 1-1: MD5 hash

This one is easy, there are two ways to crack this MD5 hash

### Method 1: Online hash cracker

You can visit any hash cracker site to crack the hash instantly. For example, the [crack station](https://crackstation.net/). Just paste the hash and crack it. 

### Method 2: Hashcat

This method is more flexible when compared to the online hash cracker. It provides a tons of [hash mode](https://hashcat.net/wiki/doku.php?id=example_hashes). You can download hashcat (Window/Linux/MacOS) from this [website](https://hashcat.net/hashcat/).  However, you need to know some command line for terminal/CMD as the prerequisite of using this tool. On the other hand, I highly recommend launching this tool in your host computer (not on your virtual machine). This is due to cracking the hash require a large amount of processing resource and GPU is the ideal choice when compared to CPU. Also, the virtual machine cannot access GPU resource.

For this walk-through, I'm going to use Window OS. After you have downloaded the hashcat, be sure to redirect to the path where you extract the hashcat (using  the command: cd). Also, I going to use dictionary attack for this hash crack walk-through, you can download the famous [wordlist (rockyou.txt)](https://github.com/brannondorsey/naive-hashcat/releases/download/data/rockyou.txt). After that, I store the rockyou.txt into the 'Dict' directory (the directory is inside the hashcat folder).

Please create a 'Hash' directory to store all the hashes that going to be cracked soon. For this case, i saved my hash in 'hash.txt'.

![hash folder](/assets/images/THM/2020-08-08-crack-the-hash/2.png)

After that launch the hashcat using following command

```
hashcat64.exe -D 2 -m 0 Hash/hash.txt Dict/rockyou.txt
```

- hashcat64.exe --> hashcat run in 64bit
- -D --> choosing the processor mode (1-CPU, 2-GPU 3-FPGA)
- -m --> Hash mode (0-MD5), please refer to [hashcat mode](https://hashcat.net/wiki/doku.php?id=example_hashes)

After a few second/minute, the result shows in the terminal.

![result](/assets/images/THM/2020-08-08-crack-the-hash/3.png)

## Task 1-2: SHA1 hash

Similar to Task 1-1, but the mode is (-m 100) for hashcat

## Task 1-3: SHA256 hash

Similar to Task 1-1, but the mode is (-m 1400) for hashcat 

## Task 1-4: bcrypt-blowfish hash

This one is little bit tricky which is this hash cannot be cracked using online tool. That is why hashcat came in, set the mode to -m 3200

## Task 1-5: MD4 hash

Similar to Task 1-1, but the mode is (-m 900) for hashcat

## Task 2-1: SHA256 hash

Similar to Task 1-1, but the mode is (-m 1400) for hashcat 
 
## Task 2-2: NTLM hash

Similar to Task 1-1, but the mode is (-m 1000) for hashcat 

## Task 2-3: SHA512crypt, $6$ hash

This hash cannot be cracked using online tool but can be cracked using hashcat by setting the mode -m 1800. (It take some time).

## Task 2-4: SHA1 with salt hash

This hash also cannot be cracked using online tool due to the present of salt ( tryhackme ). This only can be done by using hashcat with mode -m 110.

## Identify hash

If you were not sure what kind of hash is presented on your monitor, you can try to [detect the hash](https://md5hashing.net/hash_type_checker). It listed out all possible hashes. 

## Conclusion

Cracking hashes are fun and challenge. Be sure the share this post. and have a nice day :)